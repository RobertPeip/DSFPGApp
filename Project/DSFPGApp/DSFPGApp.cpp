#include <iostream>
#include <algorithm>
#include "SDL.h"
using namespace std;

//#define CONSOLE

#include <windows.h>

#include "gameboy.h"
#include "GPU.h"
#include "Joypad.h"
#include "CPU.h"
#include "FileIO.h"
#include "Memory.h"
#include "OSD.h"
#include "spi_intern.h"

const int WIDTH = 256;
const int HEIGHT = 192;

uint framebuffer_raw_a[256 * 192];
uint framebuffer_raw_b[256 * 192];
int screensizemult = 3;

uint drawmode = 0;
uint touchmode = 0;
int touchposX = WIDTH / 2;
int touchposY = HEIGHT / 2;

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Texture* framebuffer1; // vertical mode
SDL_Texture* framebuffer2; // horizontal mode
SDL_Texture* framebuffer3; /// together as 200/100% mode
SDL_Texture* framebuffer4; /// together as 200/100% mode
SDL_mutex* mutex;

SDL_Thread* gbthread;

int emuframes;

bool speedunlock = false;

int emu(void* ptr)
{
	gameboy.run();
	return 0;
}

void savegame()
{
	Memory.createGameRAMSnapshot = true;
	while (Memory.createGameRAMSnapshot)
	{
		SDL_Delay(1);
	}
	Memory.save_gameram(gameboy.filename);
}

void savestate()
{
	gameboy.do_savestate = true;

	while (gameboy.do_savestate)
	{
		SDL_Delay(1);
	}
}

void loadstate()
{
	gameboy.do_loadstate = true;

	while (gameboy.do_loadstate)
	{
		SDL_Delay(1);
	}
}

void loadstate_fromdisk(string filename)
{
	FileIO.readfile(gameboy.savestate, filename, true);
	loadstate();
}

void loadstate_fromdisk_auto(string filename)
{
	string savefilename = filename.substr(filename.find_last_of("/\\") + 1);
	savefilename = savefilename.substr(0, savefilename.find_last_of(".") + 1) + "sst";
	FileIO.readfile(gameboy.savestate, savefilename, false);
	loadstate();
}

void savestate_todisk(string filename)
{
	string savefilename = filename.substr(filename.find_last_of("/\\") + 1);
	savefilename = savefilename.substr(0, savefilename.find_last_of(".") + 1) + "sst";
	FileIO.writefile(gameboy.savestate, savefilename, 131072 * 4,false);
}

void exportmem()
{
	gameboy.do_exportmem = true;
	while (gameboy.do_exportmem)
	{
		SDL_Delay(1);
	}
}

void openrom()
{
	if (gameboy.filename != "")
	{
		OSD.isOpen = false;
		if (gbthread != 0)
		{
			gameboy.on = false;
			int threadReturnValue;
			SDL_WaitThread(gbthread, &threadReturnValue);
		}
		gameboy.coldreset = true;
		emuframes = 0;
		gbthread = SDL_CreateThread(emu, "emuthread", (void*)NULL);
	}
}

void set_displaysize(int mult, bool fullscreen)
{
	if (fullscreen)
	{
		OSD.displaysize = 0;
		SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
		SDL_DisplayMode DM;
		SDL_GetCurrentDisplayMode(0, &DM);
		switch (drawmode)
		{
		case 0: screensizemult = min(DM.w / WIDTH, (DM.h / 2) / HEIGHT); break;
		case 1: screensizemult = min((DM.w / 2) / WIDTH, DM.h / HEIGHT); break;
		case 2: screensizemult = min((DM.w / 3) / WIDTH, DM.h / HEIGHT); break;
		}
	}
	else
	{
		OSD.displaysize = mult;
		SDL_SetWindowFullscreen(window, 0);
		screensizemult = mult;
		switch (drawmode)
		{
		case 0: SDL_SetWindowSize(window, WIDTH * mult, HEIGHT * mult * 2); break;
		case 1: SDL_SetWindowSize(window, WIDTH * mult * 2, HEIGHT * mult); break;
		case 2: SDL_SetWindowSize(window, WIDTH * mult * 3, HEIGHT * mult * 2); break;
		}
	}

	switch (drawmode)
	{
	case 0: SDL_RenderSetLogicalSize(renderer, WIDTH, HEIGHT * 2); break;
	case 1: SDL_RenderSetLogicalSize(renderer, WIDTH * 2, HEIGHT); break;
	case 2: SDL_RenderSetLogicalSize(renderer, WIDTH * 3, HEIGHT * 2); break;
	}

}

void drawer()
{
	window = SDL_CreateWindow ("DSFPGApp", 200, 200, WIDTH * 3, HEIGHT * 3 * 2, SDL_WINDOW_OPENGL);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
	framebuffer1 = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT * 2);
	framebuffer2 = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, WIDTH * 2, HEIGHT);
	framebuffer3 = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT);
	framebuffer4 = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT);
	SDL_RenderSetLogicalSize(renderer, WIDTH, HEIGHT * 2);
	SDL_RenderSetIntegerScale(renderer, SDL_bool::SDL_TRUE);
	mutex = SDL_CreateMutex();
	const Uint8* keystate = SDL_GetKeyboardState(NULL);

	// gamepad
	SDL_GameController* controller = NULL;
	for (int i = 0; i < SDL_NumJoysticks(); ++i) {
		if (SDL_IsGameController(i)) {
			controller = SDL_GameControllerOpen(i);
			if (controller) 
			{
				break;
			}
		}
	}


	// drawer
	Uint64 currentTime = SDL_GetPerformanceCounter();
	Uint64 lastTime_frame = SDL_GetPerformanceCounter();
	Uint64 lastTime_second = SDL_GetPerformanceCounter();
	Uint64 lastTime_idle = SDL_GetPerformanceCounter();
	double delta = 0;

	unsigned short frames = 0;

	int OSDidlecheck = 0;

#ifdef CONSOLE
	AllocConsole();
	freopen("CONOUT$", "w", stdout);
#endif

	const long frametime = (1000000 / 60);

	UInt64 oldcycles = 0;
	UInt64 oldcommands9 = 0;
	UInt64 oldcommands7 = 0;

	bool running = true;
	while (running)
	{
		currentTime = SDL_GetPerformanceCounter();

		double frametimeleft = frametime;

		delta = (double)((currentTime - lastTime_frame) * 1000000 / (double)SDL_GetPerformanceFrequency());
		if (delta >= frametimeleft)
		{
			frametimeleft = max(5000, frametimeleft + frametime - delta);
			lastTime_frame = SDL_GetPerformanceCounter();

			if (OSD.isOpen)
			{
				OSD.render(renderer);
			}
			else
			{
				GPU_A.draw_game(framebuffer_raw_a);
				GPU_B.draw_game(framebuffer_raw_b);
				uint* framebuffer_raw1 = framebuffer_raw_a;
				uint* framebuffer_raw2 = framebuffer_raw_b;
				if (GPU_A.swap)
				{
					framebuffer_raw1 = framebuffer_raw_b;
					framebuffer_raw2 = framebuffer_raw_a;
				}
				SDL_Rect copyrect;

				SDL_DisplayMode DM;
				SDL_GetCurrentDisplayMode(0, &DM);
				int offset_x = 0;
				int offset_y = 0;

				if (drawmode == 0)
				{
					copyrect.x = 0; copyrect.y = 0; copyrect.w = WIDTH; copyrect.h = HEIGHT;
					SDL_UpdateTexture(framebuffer1, &copyrect, framebuffer_raw1, WIDTH * sizeof(uint32_t));
					copyrect.x = 0; copyrect.y = HEIGHT; copyrect.w = WIDTH; copyrect.h = HEIGHT;
					SDL_UpdateTexture(framebuffer1, &copyrect, framebuffer_raw2, WIDTH * sizeof(uint32_t));
					SDL_RenderClear(renderer);
					SDL_RenderCopy(renderer, framebuffer1, NULL, NULL);
					if (touchmode > 0)
					{
						if (OSD.displaysize == 0)
						{
							int realwidth = screensizemult * WIDTH;
							int realheight = screensizemult * HEIGHT * 2;
							offset_x = (DM.w - realwidth) / 2;
							offset_y = (DM.h - realheight) / 2;
						}
						SDL_WarpMouseInWindow(window, offset_x + touchposX * screensizemult, offset_y + touchposY * screensizemult + HEIGHT * screensizemult);
					}
				}
				else if (drawmode == 1)
				{
					copyrect.x = 0; copyrect.y = 0; copyrect.w = WIDTH; copyrect.h = HEIGHT;
					SDL_UpdateTexture(framebuffer2, &copyrect, framebuffer_raw1, WIDTH * sizeof(uint32_t));
					copyrect.x = WIDTH; copyrect.y = 0; copyrect.w = WIDTH; copyrect.h = HEIGHT;
					SDL_UpdateTexture(framebuffer2, &copyrect, framebuffer_raw2, WIDTH * sizeof(uint32_t));
					SDL_RenderClear(renderer);
					SDL_RenderCopy(renderer, framebuffer2, NULL, NULL);
					if (touchmode > 0)
					{
						if (OSD.displaysize == 0)
						{
							int realwidth = screensizemult * WIDTH * 2;
							int realheight = screensizemult * HEIGHT;
							offset_x = (DM.w - realwidth) / 2;
							offset_y = (DM.h - realheight) / 2;
						}
						SDL_WarpMouseInWindow(window, offset_x + touchposX * screensizemult + WIDTH * screensizemult, offset_y + touchposY * screensizemult);
					}
				}
				else if (drawmode == 2)
				{
					copyrect.x = 0; copyrect.y = 0; copyrect.w = WIDTH; copyrect.h = HEIGHT;
					SDL_UpdateTexture(framebuffer3, &copyrect, framebuffer_raw1, WIDTH * sizeof(uint32_t));
					SDL_UpdateTexture(framebuffer4, &copyrect, framebuffer_raw2, WIDTH * sizeof(uint32_t));
					SDL_RenderClear(renderer);
					SDL_Rect framerect_src; framerect_src.x = 0; framerect_src.y = 0; framerect_src.w = WIDTH;     framerect_src.h = HEIGHT;
					SDL_Rect framerect_dst; framerect_dst.x = 0; framerect_dst.y = 0; framerect_dst.w = WIDTH * 2; framerect_dst.h = HEIGHT * 2;
					SDL_RenderCopy(renderer, framebuffer3, &framerect_src, &framerect_dst);
					framerect_src.x = 0;         framerect_src.y = 0; framerect_src.w = WIDTH; framerect_src.h = HEIGHT;
					framerect_dst.x = WIDTH * 2; framerect_dst.y = HEIGHT / 2; framerect_dst.w = WIDTH; framerect_dst.h = HEIGHT;
					SDL_RenderCopy(renderer, framebuffer4, &framerect_src, &framerect_dst);
					if (touchmode > 0)
					{
						if (OSD.displaysize == 0)
						{
							int realwidth = screensizemult * WIDTH * 3;
							int realheight = screensizemult * HEIGHT * 2;
							offset_x = (DM.w - realwidth) / 2;
							offset_y = (DM.h - realheight) / 2;
						}
						SDL_WarpMouseInWindow(window, offset_x + touchposX * screensizemult + WIDTH * screensizemult * 2, offset_y + touchposY * screensizemult + HEIGHT * screensizemult / 2);
					}
				}
			}

			SDL_RenderPresent(renderer);
			SDL_PumpEvents();

			frames++;

			if (OSD.isOpen)
			{
				gameboy.pause = true;
				if (keystate[SDL_SCANCODE_ESCAPE] | SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_BACK))
				{
					if (OSD.idle)
					{
						OSD.isOpen = false;
						OSD.idle = false;
					}
				}
				else if (keystate[SDL_SCANCODE_UP] | SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_UP))
				{
					OSD.selectPrev();
				}
				else if (keystate[SDL_SCANCODE_DOWN] | SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_DOWN))
				{
					OSD.selectNext();
				}
				else if (keystate[SDL_SCANCODE_LEFT] | SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_LEFT))
				{
					OSD.largePrev();
				}
				else if (keystate[SDL_SCANCODE_RIGHT] | SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_RIGHT))
				{
					OSD.largeNext();
				}
				else if (keystate[SDL_SCANCODE_A] | SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_A))
				{
					if (OSD.idle)
					{
						OSD.idle = false;
						if (OSD.OsdType == OSDTYPE::MAIN)
						{
							switch ((OSDMAINMENU)OSD.selected)
							{
							case OSDMAINMENU::LOADGAME: OSD.gotoLoadGame(); break;
							case OSDMAINMENU::SAVESTATE: savestate(); OSD.isOpen = false; break;
							case OSDMAINMENU::SAVEMEMDISK: savegame(); OSD.isOpen = false; break;
							case OSDMAINMENU::SAVESTATEDISK: savestate_todisk(gameboy.filename); OSD.isOpen = false; break;
							case OSDMAINMENU::LOADSTATE: loadstate(); OSD.isOpen = false; break;
							case OSDMAINMENU::LOADSTATEDISK: loadstate_fromdisk_auto(gameboy.filename); OSD.isOpen = false; break;
							case OSDMAINMENU::DISPLAYSIZE:
								OSD.displaysize += 1;
								if (OSD.displaysize > 6)
									OSD.displaysize = 0;
								if (OSD.displaysize == 0)
								{
									set_displaysize(0, true);
									OSD.exchangeText((int)OSDMAINMENU::DISPLAYSIZE, "Displaysize: Fullscreen");
								}
								else
								{
									set_displaysize(OSD.displaysize, false);
									OSD.exchangeText((int)OSDMAINMENU::DISPLAYSIZE, "Displaysize: " + std::to_string(OSD.displaysize));
								}
								break;
							case OSDMAINMENU::FLICKERBLEND:
								GPU_A.interlace_blending = !GPU_A.interlace_blending;
								GPU_B.interlace_blending = GPU_A.interlace_blending;
								if (GPU_A.interlace_blending)
								{
									OSD.exchangeText((int)OSDMAINMENU::FLICKERBLEND, "Flickerblend: on");
								}
								else
								{
									OSD.exchangeText((int)OSDMAINMENU::FLICKERBLEND, "Flickerblend: off");
								}
								break;
							case OSDMAINMENU::CPUSTEPS:
								CPU9.additional_steps += 1;
								if (CPU9.additional_steps > 10)
									CPU9.additional_steps = -10;
								CPU7.additional_steps = CPU9.additional_steps;
								OSD.exchangeText((int)OSDMAINMENU::CPUSTEPS, "CPU Steps: " + std::to_string(CPU9.additional_steps));
								break;
							case OSDMAINMENU::EXIT: running = false; break;
							}
						}
						else if (OSD.OsdType == OSDTYPE::LOAD)
						{
							if (OSD.selectFile())
							{
								openrom();
								OSD.isOpen = false;
							}
						}
					}
				}
				else if (keystate[SDL_SCANCODE_S] | SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_X))
				{
					if (OSD.idle)
					{
						OSD.idle = false;
						if (OSD.OsdType == OSDTYPE::MAIN)
						{
							OSD.isOpen = false;
						}
						else if (OSD.OsdType == OSDTYPE::LOAD)
						{
							OSD.gotoMain();
						}
					}
				}
				else
				{
					OSD.idle = true;
				}
			}
			else
			{
				gameboy.pause = false;

				switch (touchmode)
				{
				case 0:
					int mouse_x;
					int mouse_y;
					bool pressed;
					Int32 xval;
					Int32 yval;
					if (SDL_GetMouseState(&mouse_x, &mouse_y) & SDL_BUTTON(SDL_BUTTON_LEFT))
					{
						if (OSD.displaysize == 0)
						{
							int realwidth;
							int realheight;
							switch (drawmode)
							{
							case 0:
								realwidth = screensizemult * WIDTH;
								realheight = screensizemult * HEIGHT * 2;
								break;
							case 1:
								realwidth = screensizemult * WIDTH * 2;
								realheight = screensizemult * HEIGHT;
								break;
							case 2:
								realwidth = screensizemult * WIDTH * 3;
								realheight = screensizemult * HEIGHT * 2;
								break;
							}

							SDL_DisplayMode DM;
							SDL_GetCurrentDisplayMode(0, &DM);
							mouse_x -= (DM.w - realwidth) / 2;
							mouse_y -= (DM.h - realheight) / 2;
						}

						int realx = -1;
						int realy = -1;
						switch (drawmode)
						{
						case 0:
							realx = (mouse_x / screensizemult) - 1;
							realy = (mouse_y / screensizemult) - 193;
							break;
						case 1:
							realx = (mouse_x / screensizemult) - 257;
							realy = (mouse_y / screensizemult) - 1;
							break;
						case 2:
							realx = (mouse_x / screensizemult) - (WIDTH * 2) - 1;
							realy = (mouse_y / screensizemult) - (HEIGHT / 2) - 1;
							break;
						}

						if (realx >= 0 && realx < 256 && realy >= 0 && realy <= 192)
						{
							SPI_Intern.updateADCTouchPos(true, realx, realy);
						}
					}
					else
					{
						SPI_Intern.updateADCTouchPos(false, 0, 0);
					}
					break;

				case 1:
				case 2:
					xval = (Int32)SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTX);
					yval = (Int32)SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTY);
					if (xval > -500 && xval < 500) xval = 0;
					if (yval > -500 && yval < 500) yval = 0;
					xval = WIDTH / 2 + (xval * (WIDTH / 2) / 0x8000);
					yval = HEIGHT / 2 + (yval * (WIDTH / 2) / 0x8000);
					if (xval < 0) xval = 0;
					if (yval < 0) yval = 0;
					if (xval > WIDTH) xval = WIDTH;
					if (yval > HEIGHT) yval = HEIGHT;
					pressed = true;
					if (touchmode == 1) pressed = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_TRIGGERRIGHT) > 0;
					SPI_Intern.updateADCTouchPos(pressed, xval, yval);
					touchposX = xval;
					touchposY = yval;
					break;

				case 3:
				case 4:
					xval = (Int32)SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTX);
					yval = (Int32)SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTY);
					if (xval > -500 && xval < 500) xval = 0;
					if (yval > -500 && yval < 500) yval = 0;
					touchposX += xval / 4000;
					touchposY += yval / 4000;
					if (touchposX < 0) touchposX = 0;
					if (touchposY < 0) touchposY = 0;
					if (touchposX > WIDTH) touchposX = WIDTH;
					if (touchposY > HEIGHT) touchposY = HEIGHT;
					pressed = true;
					if (touchmode == 3) pressed = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_TRIGGERRIGHT) > 0;
					SPI_Intern.updateADCTouchPos(pressed, touchposX, touchposY);
					break;

				}
				//SPI_Intern.updateADCTouchPos(true, 50, 50);

				Joypad.KeyA = keystate[SDL_SCANCODE_A] | SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_A);
				Joypad.KeyB = keystate[SDL_SCANCODE_S] | SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_X);
				Joypad.KeyAToggle = keystate[SDL_SCANCODE_F];
				Joypad.KeyBToggle = keystate[SDL_SCANCODE_G];
				Joypad.KeyL = keystate[SDL_SCANCODE_Q] | SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_LEFTSHOULDER);
				Joypad.KeyR = keystate[SDL_SCANCODE_W] | SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_RIGHTSHOULDER);
				Joypad.KeyStart = keystate[SDL_SCANCODE_D] | SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_START);
				Joypad.KeySelect = keystate[SDL_SCANCODE_C] | SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_BACK);
				Joypad.KeyX = keystate[SDL_SCANCODE_X] | SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_Y);
				Joypad.KeyY = keystate[SDL_SCANCODE_Y] | keystate[SDL_SCANCODE_Z] | SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_B);
				Joypad.KeyLeft = keystate[SDL_SCANCODE_LEFT] | SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_LEFT);
				Joypad.KeyRight = keystate[SDL_SCANCODE_RIGHT] | SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_RIGHT);
				Joypad.KeyUp = keystate[SDL_SCANCODE_UP] | SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_UP);
				Joypad.KeyDown = keystate[SDL_SCANCODE_DOWN] | SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_DOWN);

				if (keystate[SDL_SCANCODE_ESCAPE] | SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_RIGHTSTICK))
				{
					if (OSD.idle)
					{
						OSD.gotoMain();
						OSD.isOpen = true;
						OSD.idle = false;
					}
				}
				else
				{
					OSD.idle = true;
				}

				if (keystate[SDL_SCANCODE_F5])
				{
					savestate();
				}
				if (keystate[SDL_SCANCODE_F6])
				{
					savegame();
				}
				if (keystate[SDL_SCANCODE_F7])
				{
					savestate_todisk(gameboy.filename);
				}
				if (keystate[SDL_SCANCODE_F9])
				{
					loadstate();
				}
				if (keystate[SDL_SCANCODE_F10])
				{
					loadstate_fromdisk_auto(gameboy.filename);
				}
				if (keystate[SDL_SCANCODE_F3])
				{
					exportmem();
				}

				if (keystate[SDL_SCANCODE_F1])
				{
					if (GPU_A.layerenable == 0x1F) GPU_A.layerenable = 0;
					else if (GPU_A.layerenable == 0) GPU_A.layerenable = 1;
					else if (GPU_A.layerenable == 0x10) GPU_A.layerenable = 0x1F;
					else GPU_A.layerenable <<= 1;
					while (keystate[SDL_SCANCODE_F1]) SDL_PumpEvents();
				}
				if (keystate[SDL_SCANCODE_F2])
				{
					if (GPU_B.layerenable == 0x1F) GPU_B.layerenable = 0;
					else if (GPU_B.layerenable == 0) GPU_B.layerenable = 1;
					else if (GPU_B.layerenable == 0x10) GPU_B.layerenable = 0x1F;
					else GPU_B.layerenable <<= 1;
					while (keystate[SDL_SCANCODE_F2]) SDL_PumpEvents();
				}				
				
				if (keystate[SDL_SCANCODE_M])
				{
					drawmode = (drawmode + 1) % 3;
					while (keystate[SDL_SCANCODE_M]) SDL_PumpEvents();
					set_displaysize(OSD.displaysize, OSD.displaysize == 0);
				}
				if (keystate[SDL_SCANCODE_T])
				{
					touchmode = (touchmode + 1) % 5;
					while (keystate[SDL_SCANCODE_T]) SDL_PumpEvents();
				}

				if (keystate[SDL_SCANCODE_SPACE] || keystate[SDL_SCANCODE_0] || (SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_TRIGGERLEFT) > 0))
				{
					GPU_A.lockSpeed = false;
					GPU_A.frameskip = 10;
					GPU_B.lockSpeed = false;
					GPU_B.frameskip = 10;
					speedunlock = keystate[SDL_SCANCODE_0];
				}
				else if (!speedunlock && !keystate[SDL_SCANCODE_SPACE])
				{
					GPU_A.lockSpeed = true;
					GPU_A.frameskip = 0;
					GPU_B.lockSpeed = true;
					GPU_B.frameskip = 0;
				}
				else if (speedunlock && keystate[SDL_SCANCODE_SPACE])
				{
					speedunlock = false;
				}
			}

			if (keystate[SDL_SCANCODE_1]) { set_displaysize(1, false); }
			if (keystate[SDL_SCANCODE_2]) { set_displaysize(2, false); }
			if (keystate[SDL_SCANCODE_3]) { set_displaysize(3, false); }
			if (keystate[SDL_SCANCODE_4]) { set_displaysize(4, false); }
			if (keystate[SDL_SCANCODE_5]) { set_displaysize(5, false); }
			if (keystate[SDL_SCANCODE_6]) { set_displaysize(6, false); }
			if (keystate[SDL_SCANCODE_RETURN] && keystate[SDL_SCANCODE_LALT]) { set_displaysize(0, true); }
		}

		delta = (double)((currentTime - lastTime_idle) * 1000000 / (double)SDL_GetPerformanceFrequency());
		if (delta >= 10000)
		{
			if (!OSD.idle)
			{
				OSDidlecheck--;
				if (OSDidlecheck <= 0)
				{
					OSD.idle = true;
					OSDidlecheck = 20;
				}
			}
			else
			{
				OSDidlecheck = 50;
			}
			lastTime_idle = SDL_GetPerformanceCounter();
		}

		delta = (double)((currentTime - lastTime_second) * 1000000 / (double)SDL_GetPerformanceFrequency());
		if (delta >= 1000000)
		{
			UInt64 cpucycles = (UInt64)gameboy.totalticks;
			double newcycles = (double)(cpucycles - oldcycles);
#ifdef CONSOLE
			std::cout << "CPU%: " << (int)(100 * newcycles / 67027964);
			std::cout << " | FPS: " << frames;
			std::cout << " | Intern FPS: " << GPU.intern_frames;
			std::cout << "(" << GPU.videomode_frames << ")";
			std::cout << " | AVG Cycles: " << (newcycles / (CPU9.commands - oldcommands)) << "\n";
#endif
			string title = std::to_string(100 * newcycles / 67027964);
			title += " | Touchmode " + to_string(touchmode);
			if (GPU_A.swap) title += " | ScreenSwapped ";
			if (GPU_A.layerenable != 0x1F) title += " | LayerA " + to_string(GPU_A.layerenable);
			if (GPU_B.layerenable != 0x1F) title += " | LayerB " + to_string(GPU_B.layerenable);
			title += " | AVG Cycles(9/7): ";
			title += to_string((newcycles / (CPU9.commands - oldcommands9)));
			title += " | ";
			title += to_string((newcycles / (CPU7.commands - oldcommands7)));
			
			SDL_SetWindowTitle(window, title.c_str());

			lastTime_second = SDL_GetPerformanceCounter();
			frames = 0;
			if (SDL_LockMutex(mutex) == 0)
			{
				emuframes = 0;
				SDL_UnlockMutex(mutex);
			}
			if (SDL_LockMutex(GPU_A.drawlock) == 0)
			{
				GPU_A.intern_frames = 0;
				GPU_A.videomode_frames = 0;
				oldcycles = cpucycles;
				oldcommands9 = CPU9.commands;
				oldcommands7 = CPU7.commands;
				SDL_UnlockMutex(GPU_A.drawlock);
			}
		}
	}

	gameboy.on = false;
	int threadReturnValue;
	SDL_WaitThread(gbthread, &threadReturnValue);

	SDL_DestroyWindow(window);
	SDL_Quit();
}

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_GAMECONTROLLER); // SDL_INIT_EVERYTHING
	TTF_Init();
	set_displaysize(3, false);
	OSD.init();

	//GPU_A.disabled = true;
	//GPU_B.disabled = true;

	GPU_A.drawlock = SDL_CreateMutex();

	// debug

	openrom();

	//loadstate_fromdisk("savestate.sst");

	drawer();

	return 0;
}