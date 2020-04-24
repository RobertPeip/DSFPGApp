#pragma once
#include <string>
using namespace std;

#include "types.h"
#include "DSReg.h"

class RegSect_display7
{
public:
    /// <summary>
    /// General LCD Status (STAT,LYC) 2 R/W
    /// </summary>
    DSReg DISPSTAT;
    /// <summary>
    /// V-Blank flag (Read only) (1=VBlank) (set in line 160..226; not 227)
    /// </summary>
    DSReg DISPSTAT_V_Blank_flag;
    /// <summary>
    /// H-Blank flag (Read only) (1=HBlank) (toggled in all lines, 0..227)
    /// </summary>
    DSReg DISPSTAT_H_Blank_flag;
    /// <summary>
    /// V-Counter flag (Read only) (1=Match) (set in selected line) (R)
    /// </summary>
    DSReg DISPSTAT_V_Counter_flag;
    /// <summary>
    /// V-Blank IRQ Enable (1=Enable) (R/W)
    /// </summary>
    DSReg DISPSTAT_V_Blank_IRQ_Enable;
    /// <summary>
    /// H-Blank IRQ Enable (1=Enable) (R/W)
    /// </summary>
    DSReg DISPSTAT_H_Blank_IRQ_Enable;
    /// <summary>
    /// V-Counter IRQ Enable (1=Enable) (R/W)
    /// </summary>
    DSReg DISPSTAT_V_Counter_IRQ_Enable;
    /// <summary>
    /// NDS: MSB of V-Vcount Setting (LYC.Bit8) (0..262)(R/W)
    /// </summary>
    DSReg DISPSTAT_V_Count_Setting8;
    /// <summary>
    /// V-Count Setting (LYC) (0..227) (R/W)
    /// </summary>
    DSReg DISPSTAT_V_Count_Setting;
    /// <summary>
    /// Vertical Counter (LY) 2 R
    /// </summary>
    DSReg VCOUNT;

    RegSect_display7();
};

class RegSect_sound7
{
public:
    /// <summary>
    /// SOUNDxCNT - Sound Channel X Control Register (R/W)
    /// </summary>
    DSReg SOUND0CNT;
    /// <summary>
    /// 0-6 Volume Mul (0..127=silent..loud)
    /// </summary>
    DSReg SOUND0CNT_Volume_Mul;
    /// <summary>
    /// 8-9 Volume Div (0=Normal, 1=Div2, 2=Div4, 3=Div16)
    /// </summary>
    DSReg SOUND0CNT_Volume_Div;
    /// <summary>
    /// 15 Hold (0=Normal, 1=Hold last sample after one-shot sound)
    /// </summary>
    DSReg SOUND0CNT_Hold;
    /// <summary>
    /// 16-22 Panning (0..127=left..right) (64=half volume on both speakers)
    /// </summary>
    DSReg SOUND0CNT_Panning;
    /// <summary>
    /// 24-26 Wave Duty (0..7) ;HIGH=(N+1)*12.5%, LOW=(7-N)*12.5% (PSG only)
    /// </summary>
    DSReg SOUND0CNT_Wave_Duty;
    /// <summary>
    /// 27-28 Repeat Mode (0=Manual, 1=Loop Infinite, 2=One-Shot, 3=Prohibited)
    /// </summary>
    DSReg SOUND0CNT_Repeat_Mode;
    /// <summary>
    /// 29-30 Format (0=PCM8, 1=PCM16, 2=IMA-ADPCM, 3=PSG/Noise)
    /// </summary>
    DSReg SOUND0CNT_Format;
    /// <summary>
    /// 31 Start/Status (0=Stop, 1=Start/Busy)
    /// </summary>
    DSReg SOUND0CNT_Start_Status;
    /// <summary>
    /// SOUNDxSAD - Sound Channel X Data Source Register (W)
    /// </summary>
    DSReg SOUND0SAD;
    /// <summary>
    /// SOUNDxTMR - Sound Channel X Timer Register (W)
    /// </summary>
    DSReg SOUND0TMR;
    /// <summary>
    /// SOUNDxPNT - Sound Channel X Loopstart Register (W)
    /// </summary>
    DSReg SOUND0PNT;
    /// <summary>
    /// SOUNDxLEN - Sound Channel X Length Register (W)
    /// </summary>
    DSReg SOUND0LEN;
    /// <summary>
    /// SOUNDxCNT - Sound Channel X Control Register (R/W)
    /// </summary>
    DSReg SOUND1CNT;
    /// <summary>
    /// 0-6 Volume Mul (0..127=silent..loud)
    /// </summary>
    DSReg SOUND1CNT_Volume_Mul;
    /// <summary>
    /// 8-9 Volume Div (0=Normal, 1=Div2, 2=Div4, 3=Div16)
    /// </summary>
    DSReg SOUND1CNT_Volume_Div;
    /// <summary>
    /// 15 Hold (0=Normal, 1=Hold last sample after one-shot sound)
    /// </summary>
    DSReg SOUND1CNT_Hold;
    /// <summary>
    /// 16-22 Panning (0..127=left..right) (64=half volume on both speakers)
    /// </summary>
    DSReg SOUND1CNT_Panning;
    /// <summary>
    /// 24-26 Wave Duty (0..7) ;HIGH=(N+1)*12.5%, LOW=(7-N)*12.5% (PSG only)
    /// </summary>
    DSReg SOUND1CNT_Wave_Duty;
    /// <summary>
    /// 27-28 Repeat Mode (0=Manual, 1=Loop Infinite, 2=One-Shot, 3=Prohibited)
    /// </summary>
    DSReg SOUND1CNT_Repeat_Mode;
    /// <summary>
    /// 29-30 Format (0=PCM8, 1=PCM16, 2=IMA-ADPCM, 3=PSG/Noise)
    /// </summary>
    DSReg SOUND1CNT_Format;
    /// <summary>
    /// 31 Start/Status (0=Stop, 1=Start/Busy)
    /// </summary>
    DSReg SOUND1CNT_Start_Status;
    /// <summary>
    /// SOUNDxSAD - Sound Channel X Data Source Register (W)
    /// </summary>
    DSReg SOUND1SAD;
    /// <summary>
    /// SOUNDxTMR - Sound Channel X Timer Register (W)
    /// </summary>
    DSReg SOUND1TMR;
    /// <summary>
    /// SOUNDxPNT - Sound Channel X Loopstart Register (W)
    /// </summary>
    DSReg SOUND1PNT;
    /// <summary>
    /// SOUNDxLEN - Sound Channel X Length Register (W)
    /// </summary>
    DSReg SOUND1LEN;
    /// <summary>
    /// SOUNDxCNT - Sound Channel X Control Register (R/W)
    /// </summary>
    DSReg SOUND2CNT;
    /// <summary>
    /// 0-6 Volume Mul (0..127=silent..loud)
    /// </summary>
    DSReg SOUND2CNT_Volume_Mul;
    /// <summary>
    /// 8-9 Volume Div (0=Normal, 1=Div2, 2=Div4, 3=Div16)
    /// </summary>
    DSReg SOUND2CNT_Volume_Div;
    /// <summary>
    /// 15 Hold (0=Normal, 1=Hold last sample after one-shot sound)
    /// </summary>
    DSReg SOUND2CNT_Hold;
    /// <summary>
    /// 16-22 Panning (0..127=left..right) (64=half volume on both speakers)
    /// </summary>
    DSReg SOUND2CNT_Panning;
    /// <summary>
    /// 24-26 Wave Duty (0..7) ;HIGH=(N+1)*12.5%, LOW=(7-N)*12.5% (PSG only)
    /// </summary>
    DSReg SOUND2CNT_Wave_Duty;
    /// <summary>
    /// 27-28 Repeat Mode (0=Manual, 1=Loop Infinite, 2=One-Shot, 3=Prohibited)
    /// </summary>
    DSReg SOUND2CNT_Repeat_Mode;
    /// <summary>
    /// 29-30 Format (0=PCM8, 1=PCM16, 2=IMA-ADPCM, 3=PSG/Noise)
    /// </summary>
    DSReg SOUND2CNT_Format;
    /// <summary>
    /// 31 Start/Status (0=Stop, 1=Start/Busy)
    /// </summary>
    DSReg SOUND2CNT_Start_Status;
    /// <summary>
    /// SOUNDxSAD - Sound Channel X Data Source Register (W)
    /// </summary>
    DSReg SOUND2SAD;
    /// <summary>
    /// SOUNDxTMR - Sound Channel X Timer Register (W)
    /// </summary>
    DSReg SOUND2TMR;
    /// <summary>
    /// SOUNDxPNT - Sound Channel X Loopstart Register (W)
    /// </summary>
    DSReg SOUND2PNT;
    /// <summary>
    /// SOUNDxLEN - Sound Channel X Length Register (W)
    /// </summary>
    DSReg SOUND2LEN;
    /// <summary>
    /// SOUNDxCNT - Sound Channel X Control Register (R/W)
    /// </summary>
    DSReg SOUND3CNT;
    /// <summary>
    /// 0-6 Volume Mul (0..127=silent..loud)
    /// </summary>
    DSReg SOUND3CNT_Volume_Mul;
    /// <summary>
    /// 8-9 Volume Div (0=Normal, 1=Div2, 2=Div4, 3=Div16)
    /// </summary>
    DSReg SOUND3CNT_Volume_Div;
    /// <summary>
    /// 15 Hold (0=Normal, 1=Hold last sample after one-shot sound)
    /// </summary>
    DSReg SOUND3CNT_Hold;
    /// <summary>
    /// 16-22 Panning (0..127=left..right) (64=half volume on both speakers)
    /// </summary>
    DSReg SOUND3CNT_Panning;
    /// <summary>
    /// 24-26 Wave Duty (0..7) ;HIGH=(N+1)*12.5%, LOW=(7-N)*12.5% (PSG only)
    /// </summary>
    DSReg SOUND3CNT_Wave_Duty;
    /// <summary>
    /// 27-28 Repeat Mode (0=Manual, 1=Loop Infinite, 2=One-Shot, 3=Prohibited)
    /// </summary>
    DSReg SOUND3CNT_Repeat_Mode;
    /// <summary>
    /// 29-30 Format (0=PCM8, 1=PCM16, 2=IMA-ADPCM, 3=PSG/Noise)
    /// </summary>
    DSReg SOUND3CNT_Format;
    /// <summary>
    /// 31 Start/Status (0=Stop, 1=Start/Busy)
    /// </summary>
    DSReg SOUND3CNT_Start_Status;
    /// <summary>
    /// SOUNDxSAD - Sound Channel X Data Source Register (W)
    /// </summary>
    DSReg SOUND3SAD;
    /// <summary>
    /// SOUNDxTMR - Sound Channel X Timer Register (W)
    /// </summary>
    DSReg SOUND3TMR;
    /// <summary>
    /// SOUNDxPNT - Sound Channel X Loopstart Register (W)
    /// </summary>
    DSReg SOUND3PNT;
    /// <summary>
    /// SOUNDxLEN - Sound Channel X Length Register (W)
    /// </summary>
    DSReg SOUND3LEN;
    /// <summary>
    /// SOUNDxCNT - Sound Channel X Control Register (R/W)
    /// </summary>
    DSReg SOUND4CNT;
    /// <summary>
    /// 0-6 Volume Mul (0..127=silent..loud)
    /// </summary>
    DSReg SOUND4CNT_Volume_Mul;
    /// <summary>
    /// 8-9 Volume Div (0=Normal, 1=Div2, 2=Div4, 3=Div16)
    /// </summary>
    DSReg SOUND4CNT_Volume_Div;
    /// <summary>
    /// 15 Hold (0=Normal, 1=Hold last sample after one-shot sound)
    /// </summary>
    DSReg SOUND4CNT_Hold;
    /// <summary>
    /// 16-22 Panning (0..127=left..right) (64=half volume on both speakers)
    /// </summary>
    DSReg SOUND4CNT_Panning;
    /// <summary>
    /// 24-26 Wave Duty (0..7) ;HIGH=(N+1)*12.5%, LOW=(7-N)*12.5% (PSG only)
    /// </summary>
    DSReg SOUND4CNT_Wave_Duty;
    /// <summary>
    /// 27-28 Repeat Mode (0=Manual, 1=Loop Infinite, 2=One-Shot, 3=Prohibited)
    /// </summary>
    DSReg SOUND4CNT_Repeat_Mode;
    /// <summary>
    /// 29-30 Format (0=PCM8, 1=PCM16, 2=IMA-ADPCM, 3=PSG/Noise)
    /// </summary>
    DSReg SOUND4CNT_Format;
    /// <summary>
    /// 31 Start/Status (0=Stop, 1=Start/Busy)
    /// </summary>
    DSReg SOUND4CNT_Start_Status;
    /// <summary>
    /// SOUNDxSAD - Sound Channel X Data Source Register (W)
    /// </summary>
    DSReg SOUND4SAD;
    /// <summary>
    /// SOUNDxTMR - Sound Channel X Timer Register (W)
    /// </summary>
    DSReg SOUND4TMR;
    /// <summary>
    /// SOUNDxPNT - Sound Channel X Loopstart Register (W)
    /// </summary>
    DSReg SOUND4PNT;
    /// <summary>
    /// SOUNDxLEN - Sound Channel X Length Register (W)
    /// </summary>
    DSReg SOUND4LEN;
    /// <summary>
    /// SOUNDxCNT - Sound Channel X Control Register (R/W)
    /// </summary>
    DSReg SOUND5CNT;
    /// <summary>
    /// 0-6 Volume Mul (0..127=silent..loud)
    /// </summary>
    DSReg SOUND5CNT_Volume_Mul;
    /// <summary>
    /// 8-9 Volume Div (0=Normal, 1=Div2, 2=Div4, 3=Div16)
    /// </summary>
    DSReg SOUND5CNT_Volume_Div;
    /// <summary>
    /// 15 Hold (0=Normal, 1=Hold last sample after one-shot sound)
    /// </summary>
    DSReg SOUND5CNT_Hold;
    /// <summary>
    /// 16-22 Panning (0..127=left..right) (64=half volume on both speakers)
    /// </summary>
    DSReg SOUND5CNT_Panning;
    /// <summary>
    /// 24-26 Wave Duty (0..7) ;HIGH=(N+1)*12.5%, LOW=(7-N)*12.5% (PSG only)
    /// </summary>
    DSReg SOUND5CNT_Wave_Duty;
    /// <summary>
    /// 27-28 Repeat Mode (0=Manual, 1=Loop Infinite, 2=One-Shot, 3=Prohibited)
    /// </summary>
    DSReg SOUND5CNT_Repeat_Mode;
    /// <summary>
    /// 29-30 Format (0=PCM8, 1=PCM16, 2=IMA-ADPCM, 3=PSG/Noise)
    /// </summary>
    DSReg SOUND5CNT_Format;
    /// <summary>
    /// 31 Start/Status (0=Stop, 1=Start/Busy)
    /// </summary>
    DSReg SOUND5CNT_Start_Status;
    /// <summary>
    /// SOUNDxSAD - Sound Channel X Data Source Register (W)
    /// </summary>
    DSReg SOUND5SAD;
    /// <summary>
    /// SOUNDxTMR - Sound Channel X Timer Register (W)
    /// </summary>
    DSReg SOUND5TMR;
    /// <summary>
    /// SOUNDxPNT - Sound Channel X Loopstart Register (W)
    /// </summary>
    DSReg SOUND5PNT;
    /// <summary>
    /// SOUNDxLEN - Sound Channel X Length Register (W)
    /// </summary>
    DSReg SOUND5LEN;
    /// <summary>
    /// SOUNDxCNT - Sound Channel X Control Register (R/W)
    /// </summary>
    DSReg SOUND6CNT;
    /// <summary>
    /// 0-6 Volume Mul (0..127=silent..loud)
    /// </summary>
    DSReg SOUND6CNT_Volume_Mul;
    /// <summary>
    /// 8-9 Volume Div (0=Normal, 1=Div2, 2=Div4, 3=Div16)
    /// </summary>
    DSReg SOUND6CNT_Volume_Div;
    /// <summary>
    /// 15 Hold (0=Normal, 1=Hold last sample after one-shot sound)
    /// </summary>
    DSReg SOUND6CNT_Hold;
    /// <summary>
    /// 16-22 Panning (0..127=left..right) (64=half volume on both speakers)
    /// </summary>
    DSReg SOUND6CNT_Panning;
    /// <summary>
    /// 24-26 Wave Duty (0..7) ;HIGH=(N+1)*12.5%, LOW=(7-N)*12.5% (PSG only)
    /// </summary>
    DSReg SOUND6CNT_Wave_Duty;
    /// <summary>
    /// 27-28 Repeat Mode (0=Manual, 1=Loop Infinite, 2=One-Shot, 3=Prohibited)
    /// </summary>
    DSReg SOUND6CNT_Repeat_Mode;
    /// <summary>
    /// 29-30 Format (0=PCM8, 1=PCM16, 2=IMA-ADPCM, 3=PSG/Noise)
    /// </summary>
    DSReg SOUND6CNT_Format;
    /// <summary>
    /// 31 Start/Status (0=Stop, 1=Start/Busy)
    /// </summary>
    DSReg SOUND6CNT_Start_Status;
    /// <summary>
    /// SOUNDxSAD - Sound Channel X Data Source Register (W)
    /// </summary>
    DSReg SOUND6SAD;
    /// <summary>
    /// SOUNDxTMR - Sound Channel X Timer Register (W)
    /// </summary>
    DSReg SOUND6TMR;
    /// <summary>
    /// SOUNDxPNT - Sound Channel X Loopstart Register (W)
    /// </summary>
    DSReg SOUND6PNT;
    /// <summary>
    /// SOUNDxLEN - Sound Channel X Length Register (W)
    /// </summary>
    DSReg SOUND6LEN;
    /// <summary>
    /// SOUNDxCNT - Sound Channel X Control Register (R/W)
    /// </summary>
    DSReg SOUND7CNT;
    /// <summary>
    /// 0-6 Volume Mul (0..127=silent..loud)
    /// </summary>
    DSReg SOUND7CNT_Volume_Mul;
    /// <summary>
    /// 8-9 Volume Div (0=Normal, 1=Div2, 2=Div4, 3=Div16)
    /// </summary>
    DSReg SOUND7CNT_Volume_Div;
    /// <summary>
    /// 15 Hold (0=Normal, 1=Hold last sample after one-shot sound)
    /// </summary>
    DSReg SOUND7CNT_Hold;
    /// <summary>
    /// 16-22 Panning (0..127=left..right) (64=half volume on both speakers)
    /// </summary>
    DSReg SOUND7CNT_Panning;
    /// <summary>
    /// 24-26 Wave Duty (0..7) ;HIGH=(N+1)*12.5%, LOW=(7-N)*12.5% (PSG only)
    /// </summary>
    DSReg SOUND7CNT_Wave_Duty;
    /// <summary>
    /// 27-28 Repeat Mode (0=Manual, 1=Loop Infinite, 2=One-Shot, 3=Prohibited)
    /// </summary>
    DSReg SOUND7CNT_Repeat_Mode;
    /// <summary>
    /// 29-30 Format (0=PCM8, 1=PCM16, 2=IMA-ADPCM, 3=PSG/Noise)
    /// </summary>
    DSReg SOUND7CNT_Format;
    /// <summary>
    /// 31 Start/Status (0=Stop, 1=Start/Busy)
    /// </summary>
    DSReg SOUND7CNT_Start_Status;
    /// <summary>
    /// SOUNDxSAD - Sound Channel X Data Source Register (W)
    /// </summary>
    DSReg SOUND7SAD;
    /// <summary>
    /// SOUNDxTMR - Sound Channel X Timer Register (W)
    /// </summary>
    DSReg SOUND7TMR;
    /// <summary>
    /// SOUNDxPNT - Sound Channel X Loopstart Register (W)
    /// </summary>
    DSReg SOUND7PNT;
    /// <summary>
    /// SOUNDxLEN - Sound Channel X Length Register (W)
    /// </summary>
    DSReg SOUND7LEN;
    /// <summary>
    /// SOUNDxCNT - Sound Channel X Control Register (R/W)
    /// </summary>
    DSReg SOUND8CNT;
    /// <summary>
    /// 0-6 Volume Mul (0..127=silent..loud)
    /// </summary>
    DSReg SOUND8CNT_Volume_Mul;
    /// <summary>
    /// 8-9 Volume Div (0=Normal, 1=Div2, 2=Div4, 3=Div16)
    /// </summary>
    DSReg SOUND8CNT_Volume_Div;
    /// <summary>
    /// 15 Hold (0=Normal, 1=Hold last sample after one-shot sound)
    /// </summary>
    DSReg SOUND8CNT_Hold;
    /// <summary>
    /// 16-22 Panning (0..127=left..right) (64=half volume on both speakers)
    /// </summary>
    DSReg SOUND8CNT_Panning;
    /// <summary>
    /// 24-26 Wave Duty (0..7) ;HIGH=(N+1)*12.5%, LOW=(7-N)*12.5% (PSG only)
    /// </summary>
    DSReg SOUND8CNT_Wave_Duty;
    /// <summary>
    /// 27-28 Repeat Mode (0=Manual, 1=Loop Infinite, 2=One-Shot, 3=Prohibited)
    /// </summary>
    DSReg SOUND8CNT_Repeat_Mode;
    /// <summary>
    /// 29-30 Format (0=PCM8, 1=PCM16, 2=IMA-ADPCM, 3=PSG/Noise)
    /// </summary>
    DSReg SOUND8CNT_Format;
    /// <summary>
    /// 31 Start/Status (0=Stop, 1=Start/Busy)
    /// </summary>
    DSReg SOUND8CNT_Start_Status;
    /// <summary>
    /// SOUNDxSAD - Sound Channel X Data Source Register (W)
    /// </summary>
    DSReg SOUND8SAD;
    /// <summary>
    /// SOUNDxTMR - Sound Channel X Timer Register (W)
    /// </summary>
    DSReg SOUND8TMR;
    /// <summary>
    /// SOUNDxPNT - Sound Channel X Loopstart Register (W)
    /// </summary>
    DSReg SOUND8PNT;
    /// <summary>
    /// SOUNDxLEN - Sound Channel X Length Register (W)
    /// </summary>
    DSReg SOUND8LEN;
    /// <summary>
    /// SOUNDxCNT - Sound Channel X Control Register (R/W)
    /// </summary>
    DSReg SOUND9CNT;
    /// <summary>
    /// 0-6 Volume Mul (0..127=silent..loud)
    /// </summary>
    DSReg SOUND9CNT_Volume_Mul;
    /// <summary>
    /// 8-9 Volume Div (0=Normal, 1=Div2, 2=Div4, 3=Div16)
    /// </summary>
    DSReg SOUND9CNT_Volume_Div;
    /// <summary>
    /// 15 Hold (0=Normal, 1=Hold last sample after one-shot sound)
    /// </summary>
    DSReg SOUND9CNT_Hold;
    /// <summary>
    /// 16-22 Panning (0..127=left..right) (64=half volume on both speakers)
    /// </summary>
    DSReg SOUND9CNT_Panning;
    /// <summary>
    /// 24-26 Wave Duty (0..7) ;HIGH=(N+1)*12.5%, LOW=(7-N)*12.5% (PSG only)
    /// </summary>
    DSReg SOUND9CNT_Wave_Duty;
    /// <summary>
    /// 27-28 Repeat Mode (0=Manual, 1=Loop Infinite, 2=One-Shot, 3=Prohibited)
    /// </summary>
    DSReg SOUND9CNT_Repeat_Mode;
    /// <summary>
    /// 29-30 Format (0=PCM8, 1=PCM16, 2=IMA-ADPCM, 3=PSG/Noise)
    /// </summary>
    DSReg SOUND9CNT_Format;
    /// <summary>
    /// 31 Start/Status (0=Stop, 1=Start/Busy)
    /// </summary>
    DSReg SOUND9CNT_Start_Status;
    /// <summary>
    /// SOUNDxSAD - Sound Channel X Data Source Register (W)
    /// </summary>
    DSReg SOUND9SAD;
    /// <summary>
    /// SOUNDxTMR - Sound Channel X Timer Register (W)
    /// </summary>
    DSReg SOUND9TMR;
    /// <summary>
    /// SOUNDxPNT - Sound Channel X Loopstart Register (W)
    /// </summary>
    DSReg SOUND9PNT;
    /// <summary>
    /// SOUNDxLEN - Sound Channel X Length Register (W)
    /// </summary>
    DSReg SOUND9LEN;
    /// <summary>
    /// SOUNDxCNT - Sound Channel X Control Register (R/W)
    /// </summary>
    DSReg SOUND10CNT;
    /// <summary>
    /// 0-6 Volume Mul (0..127=silent..loud)
    /// </summary>
    DSReg SOUND10CNT_Volume_Mul;
    /// <summary>
    /// 8-9 Volume Div (0=Normal, 1=Div2, 2=Div4, 3=Div16)
    /// </summary>
    DSReg SOUND10CNT_Volume_Div;
    /// <summary>
    /// 15 Hold (0=Normal, 1=Hold last sample after one-shot sound)
    /// </summary>
    DSReg SOUND10CNT_Hold;
    /// <summary>
    /// 16-22 Panning (0..127=left..right) (64=half volume on both speakers)
    /// </summary>
    DSReg SOUND10CNT_Panning;
    /// <summary>
    /// 24-26 Wave Duty (0..7) ;HIGH=(N+1)*12.5%, LOW=(7-N)*12.5% (PSG only)
    /// </summary>
    DSReg SOUND10CNT_Wave_Duty;
    /// <summary>
    /// 27-28 Repeat Mode (0=Manual, 1=Loop Infinite, 2=One-Shot, 3=Prohibited)
    /// </summary>
    DSReg SOUND10CNT_Repeat_Mode;
    /// <summary>
    /// 29-30 Format (0=PCM8, 1=PCM16, 2=IMA-ADPCM, 3=PSG/Noise)
    /// </summary>
    DSReg SOUND10CNT_Format;
    /// <summary>
    /// 31 Start/Status (0=Stop, 1=Start/Busy)
    /// </summary>
    DSReg SOUND10CNT_Start_Status;
    /// <summary>
    /// SOUNDxSAD - Sound Channel X Data Source Register (W)
    /// </summary>
    DSReg SOUND10SAD;
    /// <summary>
    /// SOUNDxTMR - Sound Channel X Timer Register (W)
    /// </summary>
    DSReg SOUND10TMR;
    /// <summary>
    /// SOUNDxPNT - Sound Channel X Loopstart Register (W)
    /// </summary>
    DSReg SOUND10PNT;
    /// <summary>
    /// SOUNDxLEN - Sound Channel X Length Register (W)
    /// </summary>
    DSReg SOUND10LEN;
    /// <summary>
    /// SOUNDxCNT - Sound Channel X Control Register (R/W)
    /// </summary>
    DSReg SOUND11CNT;
    /// <summary>
    /// 0-6 Volume Mul (0..127=silent..loud)
    /// </summary>
    DSReg SOUND11CNT_Volume_Mul;
    /// <summary>
    /// 8-9 Volume Div (0=Normal, 1=Div2, 2=Div4, 3=Div16)
    /// </summary>
    DSReg SOUND11CNT_Volume_Div;
    /// <summary>
    /// 15 Hold (0=Normal, 1=Hold last sample after one-shot sound)
    /// </summary>
    DSReg SOUND11CNT_Hold;
    /// <summary>
    /// 16-22 Panning (0..127=left..right) (64=half volume on both speakers)
    /// </summary>
    DSReg SOUND11CNT_Panning;
    /// <summary>
    /// 24-26 Wave Duty (0..7) ;HIGH=(N+1)*12.5%, LOW=(7-N)*12.5% (PSG only)
    /// </summary>
    DSReg SOUND11CNT_Wave_Duty;
    /// <summary>
    /// 27-28 Repeat Mode (0=Manual, 1=Loop Infinite, 2=One-Shot, 3=Prohibited)
    /// </summary>
    DSReg SOUND11CNT_Repeat_Mode;
    /// <summary>
    /// 29-30 Format (0=PCM8, 1=PCM16, 2=IMA-ADPCM, 3=PSG/Noise)
    /// </summary>
    DSReg SOUND11CNT_Format;
    /// <summary>
    /// 31 Start/Status (0=Stop, 1=Start/Busy)
    /// </summary>
    DSReg SOUND11CNT_Start_Status;
    /// <summary>
    /// SOUNDxSAD - Sound Channel X Data Source Register (W)
    /// </summary>
    DSReg SOUND11SAD;
    /// <summary>
    /// SOUNDxTMR - Sound Channel X Timer Register (W)
    /// </summary>
    DSReg SOUND11TMR;
    /// <summary>
    /// SOUNDxPNT - Sound Channel X Loopstart Register (W)
    /// </summary>
    DSReg SOUND11PNT;
    /// <summary>
    /// SOUNDxLEN - Sound Channel X Length Register (W)
    /// </summary>
    DSReg SOUND11LEN;
    /// <summary>
    /// SOUNDxCNT - Sound Channel X Control Register (R/W)
    /// </summary>
    DSReg SOUND12CNT;
    /// <summary>
    /// 0-6 Volume Mul (0..127=silent..loud)
    /// </summary>
    DSReg SOUND12CNT_Volume_Mul;
    /// <summary>
    /// 8-9 Volume Div (0=Normal, 1=Div2, 2=Div4, 3=Div16)
    /// </summary>
    DSReg SOUND12CNT_Volume_Div;
    /// <summary>
    /// 15 Hold (0=Normal, 1=Hold last sample after one-shot sound)
    /// </summary>
    DSReg SOUND12CNT_Hold;
    /// <summary>
    /// 16-22 Panning (0..127=left..right) (64=half volume on both speakers)
    /// </summary>
    DSReg SOUND12CNT_Panning;
    /// <summary>
    /// 24-26 Wave Duty (0..7) ;HIGH=(N+1)*12.5%, LOW=(7-N)*12.5% (PSG only)
    /// </summary>
    DSReg SOUND12CNT_Wave_Duty;
    /// <summary>
    /// 27-28 Repeat Mode (0=Manual, 1=Loop Infinite, 2=One-Shot, 3=Prohibited)
    /// </summary>
    DSReg SOUND12CNT_Repeat_Mode;
    /// <summary>
    /// 29-30 Format (0=PCM8, 1=PCM16, 2=IMA-ADPCM, 3=PSG/Noise)
    /// </summary>
    DSReg SOUND12CNT_Format;
    /// <summary>
    /// 31 Start/Status (0=Stop, 1=Start/Busy)
    /// </summary>
    DSReg SOUND12CNT_Start_Status;
    /// <summary>
    /// SOUNDxSAD - Sound Channel X Data Source Register (W)
    /// </summary>
    DSReg SOUND12SAD;
    /// <summary>
    /// SOUNDxTMR - Sound Channel X Timer Register (W)
    /// </summary>
    DSReg SOUND12TMR;
    /// <summary>
    /// SOUNDxPNT - Sound Channel X Loopstart Register (W)
    /// </summary>
    DSReg SOUND12PNT;
    /// <summary>
    /// SOUNDxLEN - Sound Channel X Length Register (W)
    /// </summary>
    DSReg SOUND12LEN;
    /// <summary>
    /// SOUNDxCNT - Sound Channel X Control Register (R/W)
    /// </summary>
    DSReg SOUND13CNT;
    /// <summary>
    /// 0-6 Volume Mul (0..127=silent..loud)
    /// </summary>
    DSReg SOUND13CNT_Volume_Mul;
    /// <summary>
    /// 8-9 Volume Div (0=Normal, 1=Div2, 2=Div4, 3=Div16)
    /// </summary>
    DSReg SOUND13CNT_Volume_Div;
    /// <summary>
    /// 15 Hold (0=Normal, 1=Hold last sample after one-shot sound)
    /// </summary>
    DSReg SOUND13CNT_Hold;
    /// <summary>
    /// 16-22 Panning (0..127=left..right) (64=half volume on both speakers)
    /// </summary>
    DSReg SOUND13CNT_Panning;
    /// <summary>
    /// 24-26 Wave Duty (0..7) ;HIGH=(N+1)*12.5%, LOW=(7-N)*12.5% (PSG only)
    /// </summary>
    DSReg SOUND13CNT_Wave_Duty;
    /// <summary>
    /// 27-28 Repeat Mode (0=Manual, 1=Loop Infinite, 2=One-Shot, 3=Prohibited)
    /// </summary>
    DSReg SOUND13CNT_Repeat_Mode;
    /// <summary>
    /// 29-30 Format (0=PCM8, 1=PCM16, 2=IMA-ADPCM, 3=PSG/Noise)
    /// </summary>
    DSReg SOUND13CNT_Format;
    /// <summary>
    /// 31 Start/Status (0=Stop, 1=Start/Busy)
    /// </summary>
    DSReg SOUND13CNT_Start_Status;
    /// <summary>
    /// SOUNDxSAD - Sound Channel X Data Source Register (W)
    /// </summary>
    DSReg SOUND13SAD;
    /// <summary>
    /// SOUNDxTMR - Sound Channel X Timer Register (W)
    /// </summary>
    DSReg SOUND13TMR;
    /// <summary>
    /// SOUNDxPNT - Sound Channel X Loopstart Register (W)
    /// </summary>
    DSReg SOUND13PNT;
    /// <summary>
    /// SOUNDxLEN - Sound Channel X Length Register (W)
    /// </summary>
    DSReg SOUND13LEN;
    /// <summary>
    /// SOUNDxCNT - Sound Channel X Control Register (R/W)
    /// </summary>
    DSReg SOUND14CNT;
    /// <summary>
    /// 0-6 Volume Mul (0..127=silent..loud)
    /// </summary>
    DSReg SOUND14CNT_Volume_Mul;
    /// <summary>
    /// 8-9 Volume Div (0=Normal, 1=Div2, 2=Div4, 3=Div16)
    /// </summary>
    DSReg SOUND14CNT_Volume_Div;
    /// <summary>
    /// 15 Hold (0=Normal, 1=Hold last sample after one-shot sound)
    /// </summary>
    DSReg SOUND14CNT_Hold;
    /// <summary>
    /// 16-22 Panning (0..127=left..right) (64=half volume on both speakers)
    /// </summary>
    DSReg SOUND14CNT_Panning;
    /// <summary>
    /// 24-26 Wave Duty (0..7) ;HIGH=(N+1)*12.5%, LOW=(7-N)*12.5% (PSG only)
    /// </summary>
    DSReg SOUND14CNT_Wave_Duty;
    /// <summary>
    /// 27-28 Repeat Mode (0=Manual, 1=Loop Infinite, 2=One-Shot, 3=Prohibited)
    /// </summary>
    DSReg SOUND14CNT_Repeat_Mode;
    /// <summary>
    /// 29-30 Format (0=PCM8, 1=PCM16, 2=IMA-ADPCM, 3=PSG/Noise)
    /// </summary>
    DSReg SOUND14CNT_Format;
    /// <summary>
    /// 31 Start/Status (0=Stop, 1=Start/Busy)
    /// </summary>
    DSReg SOUND14CNT_Start_Status;
    /// <summary>
    /// SOUNDxSAD - Sound Channel X Data Source Register (W)
    /// </summary>
    DSReg SOUND14SAD;
    /// <summary>
    /// SOUNDxTMR - Sound Channel X Timer Register (W)
    /// </summary>
    DSReg SOUND14TMR;
    /// <summary>
    /// SOUNDxPNT - Sound Channel X Loopstart Register (W)
    /// </summary>
    DSReg SOUND14PNT;
    /// <summary>
    /// SOUNDxLEN - Sound Channel X Length Register (W)
    /// </summary>
    DSReg SOUND14LEN;
    /// <summary>
    /// SOUNDxCNT - Sound Channel X Control Register (R/W)
    /// </summary>
    DSReg SOUND15CNT;
    /// <summary>
    /// 0-6 Volume Mul (0..127=silent..loud)
    /// </summary>
    DSReg SOUND15CNT_Volume_Mul;
    /// <summary>
    /// 8-9 Volume Div (0=Normal, 1=Div2, 2=Div4, 3=Div16)
    /// </summary>
    DSReg SOUND15CNT_Volume_Div;
    /// <summary>
    /// 15 Hold (0=Normal, 1=Hold last sample after one-shot sound)
    /// </summary>
    DSReg SOUND15CNT_Hold;
    /// <summary>
    /// 16-22 Panning (0..127=left..right) (64=half volume on both speakers)
    /// </summary>
    DSReg SOUND15CNT_Panning;
    /// <summary>
    /// 24-26 Wave Duty (0..7) ;HIGH=(N+1)*12.5%, LOW=(7-N)*12.5% (PSG only)
    /// </summary>
    DSReg SOUND15CNT_Wave_Duty;
    /// <summary>
    /// 27-28 Repeat Mode (0=Manual, 1=Loop Infinite, 2=One-Shot, 3=Prohibited)
    /// </summary>
    DSReg SOUND15CNT_Repeat_Mode;
    /// <summary>
    /// 29-30 Format (0=PCM8, 1=PCM16, 2=IMA-ADPCM, 3=PSG/Noise)
    /// </summary>
    DSReg SOUND15CNT_Format;
    /// <summary>
    /// 31 Start/Status (0=Stop, 1=Start/Busy)
    /// </summary>
    DSReg SOUND15CNT_Start_Status;
    /// <summary>
    /// SOUNDxSAD - Sound Channel X Data Source Register (W)
    /// </summary>
    DSReg SOUND15SAD;
    /// <summary>
    /// SOUNDxTMR - Sound Channel X Timer Register (W)
    /// </summary>
    DSReg SOUND15TMR;
    /// <summary>
    /// SOUNDxPNT - Sound Channel X Loopstart Register (W)
    /// </summary>
    DSReg SOUND15PNT;
    /// <summary>
    /// SOUNDxLEN - Sound Channel X Length Register (W)
    /// </summary>
    DSReg SOUND15LEN;
    /// <summary>
    /// 
    /// </summary>
    DSReg SOUNDCNT;
    /// <summary>
    /// Bit0-6 Master Volume (0..127=silent..loud)
    /// </summary>
    DSReg SOUNDCNT_Master_Volume;
    /// <summary>
    /// Bit8-9 Left Output from (0=Left Mixer, 1=Ch1, 2=Ch3, 3=Ch1+Ch3)
    /// </summary>
    DSReg SOUNDCNT_Left_Output_from;
    /// <summary>
    /// Bit10-11 Right Output from (0=Right Mixer, 1=Ch1, 2=Ch3, 3=Ch1+Ch3)
    /// </summary>
    DSReg SOUNDCNT_Right_Output_from;
    /// <summary>
    /// Bit12 Output Ch1 to Mixer (0=Yes, 1=No) (both Left/Right)
    /// </summary>
    DSReg SOUNDCNT_Output_Ch1_to_Mixer;
    /// <summary>
    /// Bit13 Output Ch3 to Mixer (0=Yes, 1=No) (both Left/Right)
    /// </summary>
    DSReg SOUNDCNT_Output_Ch3_to_Mixer;
    /// <summary>
    /// Bit15 Master Enable (0=Disable, 1=Enable)
    /// </summary>
    DSReg SOUNDCNT_Master_Enable;
    /// <summary>
    /// (0..3FFh, usually 200h)
    /// </summary>
    DSReg SOUNDBIAS;
    DSReg SOUNDCAP;
    /// <summary>
    /// Bit0 Control of Associated Sound Channels (ANDed with Bit7) SNDCAP0CNT: Output Sound Channel 1 (0=As such, 1=Add to Channel 0) Caution: Addition mode works only if BOTH Bit0 and Bit7 are set.
    /// </summary>
    DSReg SOUNDCAP0_Control;
    /// <summary>
    /// Bit1 Capture Source Selection SNDCAP0CNT: Capture 0 Source (0=Left Mixer, 1=Channel 0/Bugged)
    /// </summary>
    DSReg SOUNDCAP0_Capture_Source;
    /// <summary>
    /// Bit2 Capture Repeat (0=Loop, 1=One-shot)
    /// </summary>
    DSReg SOUNDCAP0_Capture_Repeat;
    /// <summary>
    /// Bit3 Capture Format (0=PCM16, 1=PCM8)
    /// </summary>
    DSReg SOUNDCAP0_Capture_Format;
    /// <summary>
    /// Bit7 Capture Start/Status (0=Stop, 1=Start/Busy)
    /// </summary>
    DSReg SOUNDCAP0_Capture_Start_Status;
    /// <summary>
    /// Bit8 Control of Associated Sound Channels (ANDed with Bit7) SNDCAP1CNT: Output Sound Channel 3 (0=As such, 1=Add to Channel 2) Caution: Addition mode works only if BOTH Bit0 and Bit7 are set.
    /// </summary>
    DSReg SOUNDCAP1_Control;
    /// <summary>
    /// Bit9 Capture Source Selection SNDCAP1CNT: Capture 1 Source (0=Right Mixer, 1=Channel 2/Bugged)
    /// </summary>
    DSReg SOUNDCAP1_Capture_Source;
    /// <summary>
    /// Bit10 Capture Repeat (0=Loop, 1=One-shot)
    /// </summary>
    DSReg SOUNDCAP1_Capture_Repeat;
    /// <summary>
    /// Bit11 Capture Format (0=PCM16, 1=PCM8)
    /// </summary>
    DSReg SOUNDCAP1_Capture_Format;
    /// <summary>
    /// Bit15 Capture Start/Status (0=Stop, 1=Start/Busy)
    /// </summary>
    DSReg SOUNDCAP1_Capture_Start_Status;
    /// <summary>
    /// Destination address (word aligned, bit0-1 are always zero)
    /// </summary>
    DSReg SNDCAP0DAD;
    /// <summary>
    /// Buffer length (1..FFFFh words) (ie. N*4 bytes)
    /// </summary>
    DSReg SNDCAP0LEN;
    /// <summary>
    /// Destination address (word aligned, bit0-1 are always zero)
    /// </summary>
    DSReg SNDCAP1DAD;
    /// <summary>
    /// Buffer length (1..FFFFh words) (ie. N*4 bytes)
    /// </summary>
    DSReg SNDCAP1LEN;

    RegSect_sound7();
};

class RegSect_dma7
{
public:
    /// <summary>
    /// Source Address 4 W
    /// </summary>
    DSReg DMA0SAD;
    /// <summary>
    /// Destination Address 4 W
    /// </summary>
    DSReg DMA0DAD;
    /// <summary>
    /// Word Count 2 W
    /// </summary>
    DSReg DMA0CNT_L;
    /// <summary>
    /// Control 2 R/W
    /// </summary>
    DSReg DMA0CNT_H;
    /// <summary>
    /// 5-6 Dest Addr Control (0=Increment,1=Decrement,2=Fixed,3=Increment/Reload)
    /// </summary>
    DSReg DMA0CNT_H_Dest_Addr_Control;
    /// <summary>
    /// 7-8 Source Adr Control (0=Increment,1=Decrement,2=Fixed,3=Prohibited)
    /// </summary>
    DSReg DMA0CNT_H_Source_Adr_Control;
    /// <summary>
    /// 9 DMA Repeat (0=Off, 1=On) (Must be zero if Bit 11 set)
    /// </summary>
    DSReg DMA0CNT_H_DMA_Repeat;
    /// <summary>
    /// 10 DMA Transfer Type (0=16bit, 1=32bit)
    /// </summary>
    DSReg DMA0CNT_H_DMA_Transfer_Type;
    /// <summary>
    /// 12-13 DMA Start Timing ( 0 Start Immediately 1 Start at V-Blank 2 DS Cartridge Slot 3 DMA0/DMA2: Wireless interrupt, DMA1/DMA3: GBA Cartridge Slot
    /// </summary>
    DSReg DMA0CNT_H_DMA_Start_Timing;
    /// <summary>
    /// 14 IRQ upon end of Word Count (0=Disable, 1=Enable)
    /// </summary>
    DSReg DMA0CNT_H_IRQ_on;
    /// <summary>
    /// 15 DMA Enable (0=Off, 1=On)
    /// </summary>
    DSReg DMA0CNT_H_DMA_Enable;
    /// <summary>
    /// Source Address 4 W
    /// </summary>
    DSReg DMA1SAD;
    /// <summary>
    /// Destination Address 4 W
    /// </summary>
    DSReg DMA1DAD;
    /// <summary>
    /// Word Count 2 W
    /// </summary>
    DSReg DMA1CNT_L;
    /// <summary>
    /// Control 2 R/W
    /// </summary>
    DSReg DMA1CNT_H;
    /// <summary>
    /// 5-6 Dest Addr Control (0=Increment,1=Decrement,2=Fixed,3=Increment/Reload)
    /// </summary>
    DSReg DMA1CNT_H_Dest_Addr_Control;
    /// <summary>
    /// 7-8 Source Adr Control (0=Increment,1=Decrement,2=Fixed,3=Prohibited)
    /// </summary>
    DSReg DMA1CNT_H_Source_Adr_Control;
    /// <summary>
    /// 9 DMA Repeat (0=Off, 1=On) (Must be zero if Bit 11 set)
    /// </summary>
    DSReg DMA1CNT_H_DMA_Repeat;
    /// <summary>
    /// 10 DMA Transfer Type (0=16bit, 1=32bit)
    /// </summary>
    DSReg DMA1CNT_H_DMA_Transfer_Type;
    /// <summary>
    /// 12-13 DMA Start Timing ( 0 Start Immediately 1 Start at V-Blank 2 DS Cartridge Slot 3 DMA0/DMA2: Wireless interrupt, DMA1/DMA3: GBA Cartridge Slot
    /// </summary>
    DSReg DMA1CNT_H_DMA_Start_Timing;
    /// <summary>
    /// 14 IRQ upon end of Word Count (0=Disable, 1=Enable)
    /// </summary>
    DSReg DMA1CNT_H_IRQ_on;
    /// <summary>
    /// 15 DMA Enable (0=Off, 1=On)
    /// </summary>
    DSReg DMA1CNT_H_DMA_Enable;
    /// <summary>
    /// Source Address 4 W
    /// </summary>
    DSReg DMA2SAD;
    /// <summary>
    /// Destination Address 4 W
    /// </summary>
    DSReg DMA2DAD;
    /// <summary>
    /// Word Count 2 W
    /// </summary>
    DSReg DMA2CNT_L;
    /// <summary>
    /// Control 2 R/W
    /// </summary>
    DSReg DMA2CNT_H;
    /// <summary>
    /// 5-6 Dest Addr Control (0=Increment,1=Decrement,2=Fixed,3=Increment/Reload)
    /// </summary>
    DSReg DMA2CNT_H_Dest_Addr_Control;
    /// <summary>
    /// 7-8 Source Adr Control (0=Increment,1=Decrement,2=Fixed,3=Prohibited)
    /// </summary>
    DSReg DMA2CNT_H_Source_Adr_Control;
    /// <summary>
    /// 9 DMA Repeat (0=Off, 1=On) (Must be zero if Bit 11 set)
    /// </summary>
    DSReg DMA2CNT_H_DMA_Repeat;
    /// <summary>
    /// 10 DMA Transfer Type (0=16bit, 1=32bit)
    /// </summary>
    DSReg DMA2CNT_H_DMA_Transfer_Type;
    /// <summary>
    /// 12-13 DMA Start Timing ( 0 Start Immediately 1 Start at V-Blank 2 DS Cartridge Slot 3 DMA0/DMA2: Wireless interrupt, DMA1/DMA3: GBA Cartridge Slot
    /// </summary>
    DSReg DMA2CNT_H_DMA_Start_Timing;
    /// <summary>
    /// 14 IRQ upon end of Word Count (0=Disable, 1=Enable)
    /// </summary>
    DSReg DMA2CNT_H_IRQ_on;
    /// <summary>
    /// 15 DMA Enable (0=Off, 1=On)
    /// </summary>
    DSReg DMA2CNT_H_DMA_Enable;
    /// <summary>
    /// Source Address 4 W
    /// </summary>
    DSReg DMA3SAD;
    /// <summary>
    /// Destination Address 4 W
    /// </summary>
    DSReg DMA3DAD;
    /// <summary>
    /// Word Count 2 W
    /// </summary>
    DSReg DMA3CNT_L;
    /// <summary>
    /// Control 2 R/W
    /// </summary>
    DSReg DMA3CNT_H;
    /// <summary>
    /// 5-6 Dest Addr Control (0=Increment,1=Decrement,2=Fixed,3=Increment/Reload)
    /// </summary>
    DSReg DMA3CNT_H_Dest_Addr_Control;
    /// <summary>
    /// 7-8 Source Adr Control (0=Increment,1=Decrement,2=Fixed,3=Prohibited)
    /// </summary>
    DSReg DMA3CNT_H_Source_Adr_Control;
    /// <summary>
    /// 9 DMA Repeat (0=Off, 1=On) (Must be zero if Bit 11 set)
    /// </summary>
    DSReg DMA3CNT_H_DMA_Repeat;
    /// <summary>
    /// 10 DMA Transfer Type (0=16bit, 1=32bit)
    /// </summary>
    DSReg DMA3CNT_H_DMA_Transfer_Type;
    /// <summary>
    /// 11 Game Pak DRQ - DMA3 only - (0=Normal, 1=DRQ <from> Game Pak, DMA3)
    /// </summary>
    DSReg DMA3CNT_H_Game_Pak_DRQ;
    /// <summary>
    /// 12-13 DMA Start Timing ( 0 Start Immediately 1 Start at V-Blank 2 DS Cartridge Slot 3 DMA0/DMA2: Wireless interrupt, DMA1/DMA3: GBA Cartridge Slot
    /// </summary>
    DSReg DMA3CNT_H_DMA_Start_Timing;
    /// <summary>
    /// 14 IRQ upon end of Word Count (0=Disable, 1=Enable)
    /// </summary>
    DSReg DMA3CNT_H_IRQ_on;
    /// <summary>
    /// 15 DMA Enable (0=Off, 1=On)
    /// </summary>
    DSReg DMA3CNT_H_DMA_Enable;

    RegSect_dma7();
};

class RegSect_timer7
{
public:
    /// <summary>
    /// Timer 0 Counter/Reload 2 R/W
    /// </summary>
    DSReg TM0CNT_L;
    /// <summary>
    /// Timer 0 Control 2 R/W
    /// </summary>
    DSReg TM0CNT_H;
    /// <summary>
    /// Prescaler Selection (0=F/1, 1=F/64, 2=F/256, 3=F/1024)
    /// </summary>
    DSReg TM0CNT_H_Prescaler;
    /// <summary>
    /// Count-up Timing (0=Normal, 1=See below)
    /// </summary>
    DSReg TM0CNT_H_Count_up;
    /// <summary>
    /// Timer IRQ Enable (0=Disable, 1=IRQ on Timer overflow)
    /// </summary>
    DSReg TM0CNT_H_Timer_IRQ_Enable;
    /// <summary>
    /// Timer Start/Stop (0=Stop, 1=Operate)
    /// </summary>
    DSReg TM0CNT_H_Timer_Start_Stop;
    /// <summary>
    /// Timer 1 Counter/Reload 2 R/W
    /// </summary>
    DSReg TM1CNT_L;
    /// <summary>
    /// Timer 1 Control 2 R/W
    /// </summary>
    DSReg TM1CNT_H;
    /// <summary>
    /// Prescaler Selection (0=F/1, 1=F/64, 2=F/256, 3=F/1024)
    /// </summary>
    DSReg TM1CNT_H_Prescaler;
    /// <summary>
    /// Count-up Timing (0=Normal, 1=See below)
    /// </summary>
    DSReg TM1CNT_H_Count_up;
    /// <summary>
    /// Timer IRQ Enable (0=Disable, 1=IRQ on Timer overflow)
    /// </summary>
    DSReg TM1CNT_H_Timer_IRQ_Enable;
    /// <summary>
    /// Timer Start/Stop (0=Stop, 1=Operate)
    /// </summary>
    DSReg TM1CNT_H_Timer_Start_Stop;
    /// <summary>
    /// Timer 2 Counter/Reload 2 R/W
    /// </summary>
    DSReg TM2CNT_L;
    /// <summary>
    /// Timer 2 Control 2 R/W
    /// </summary>
    DSReg TM2CNT_H;
    /// <summary>
    /// Prescaler Selection (0=F/1, 1=F/64, 2=F/256, 3=F/1024)
    /// </summary>
    DSReg TM2CNT_H_Prescaler;
    /// <summary>
    /// Count-up Timing (0=Normal, 1=See below)
    /// </summary>
    DSReg TM2CNT_H_Count_up;
    /// <summary>
    /// Timer IRQ Enable (0=Disable, 1=IRQ on Timer overflow)
    /// </summary>
    DSReg TM2CNT_H_Timer_IRQ_Enable;
    /// <summary>
    /// Timer Start/Stop (0=Stop, 1=Operate)
    /// </summary>
    DSReg TM2CNT_H_Timer_Start_Stop;
    /// <summary>
    /// Timer 3 Counter/Reload 2 R/W
    /// </summary>
    DSReg TM3CNT_L;
    /// <summary>
    /// Timer 3 Control 2 R/W
    /// </summary>
    DSReg TM3CNT_H;
    /// <summary>
    /// Prescaler Selection (0=F/1, 1=F/64, 2=F/256, 3=F/1024)
    /// </summary>
    DSReg TM3CNT_H_Prescaler;
    /// <summary>
    /// Count-up Timing (0=Normal, 1=See below)
    /// </summary>
    DSReg TM3CNT_H_Count_up;
    /// <summary>
    /// Timer IRQ Enable (0=Disable, 1=IRQ on Timer overflow)
    /// </summary>
    DSReg TM3CNT_H_Timer_IRQ_Enable;
    /// <summary>
    /// Timer Start/Stop (0=Stop, 1=Operate)
    /// </summary>
    DSReg TM3CNT_H_Timer_Start_Stop;

    RegSect_timer7();
};

class RegSect_keypad7
{
public:
    /// <summary>
    /// Key Status 2 R
    /// </summary>
    DSReg KEYINPUT;
    /// <summary>
    /// Key Interrupt Control 2 R/W
    /// </summary>
    DSReg KEYCNT;
    /// <summary>
    /// SIO Mode Select/General Purpose Data 2 R/W
    /// </summary>
    DSReg RCNT;
    /// <summary>
    /// Key X/Y Input (R)
    /// </summary>
    DSReg EXTKEYIN;

    RegSect_keypad7();
};

class RegSect_serial7
{
public:
    /// <summary>
    /// SIO Data (Normal-32bit Mode; shared with below) 4 R/W
    /// </summary>
    DSReg SIODATA32;
    /// <summary>
    /// SIO Data 0 (Parent) (Multi-Player Mode) 2 R/W
    /// </summary>
    DSReg SIOMULTI0;
    /// <summary>
    /// SIO Data 1 (1st Child) (Multi-Player Mode) 2 R/W
    /// </summary>
    DSReg SIOMULTI1;
    /// <summary>
    /// SIO Data 2 (2nd Child) (Multi-Player Mode) 2 R/W
    /// </summary>
    DSReg SIOMULTI2;
    /// <summary>
    /// SIO Data 3 (3rd Child) (Multi-Player Mode) 2 R/W
    /// </summary>
    DSReg SIOMULTI3;
    /// <summary>
    /// SIO Control Register 2 R/W
    /// </summary>
    DSReg SIOCNT;
    /// <summary>
    /// SIO Data (Local of MultiPlayer; shared below) 2 R/W
    /// </summary>
    DSReg SIOMLT_SEND;
    /// <summary>
    /// SIO Data (Normal-8bit and UART Mode) 2 R/W
    /// </summary>
    DSReg SIODATA8;
    /// <summary>
    /// SIO JOY Bus Control 2 R/W
    /// </summary>
    DSReg JOYCNT;
    /// <summary>
    /// SIO JOY Bus Receive Data 4 R/W
    /// </summary>
    DSReg JOY_RECV;
    /// <summary>
    /// SIO JOY Bus Transmit Data 4 R/W
    /// </summary>
    DSReg JOY_TRANS;
    /// <summary>
    /// SIO JOY Bus Receive Status 2 R/?
    /// </summary>
    DSReg JOYSTAT;

    RegSect_serial7();
};

class RegSect_system7
{
public:
    /// <summary>
    /// Real Time Clock Register
    /// </summary>
    DSReg RTC_reg;
    /// <summary>
    /// 0 Data I/O (0=Low, 1=High)
    /// </summary>
    DSReg RTC_reg_Data_IO;
    /// <summary>
    /// 1 Clock Out (0=Low, 1=High)
    /// </summary>
    DSReg RTC_reg_Clock;
    /// <summary>
    /// 2 Select Out (0=Low, 1=High/Select)
    /// </summary>
    DSReg RTC_reg_Select;
    /// <summary>
    /// 3 Unused I/O Lines
    /// </summary>
    DSReg RTC_reg_Unused_IO_Line3;
    /// <summary>
    /// 4 Data Direction (0=Read, 1=Write)
    /// </summary>
    DSReg RTC_reg_Data_Direction;
    /// <summary>
    /// 5 Clock Direction (should be 1=Write)
    /// </summary>
    DSReg RTC_reg_Clock_Direction;
    /// <summary>
    /// 6 Select Direction (should be 1=Write)
    /// </summary>
    DSReg RTC_reg_Select_Direction;
    /// <summary>
    /// 7 Direction for Bit3 (usually 0)
    /// </summary>
    DSReg RTC_reg_Direction_unused3;
    /// <summary>
    /// 8-11 Unused I/O Lines
    /// </summary>
    DSReg RTC_reg_Unused_IO_Lines811;
    /// <summary>
    /// 12-15 Direction for Bit8-11 (usually 0)
    /// </summary>
    DSReg RTC_reg_Direction_unused811;
    /// <summary>
    /// IPC Synchronize Register (R/W)
    /// </summary>
    DSReg IPCSYNC;
    /// <summary>
    /// 0-3 R Data input from IPCSYNC Bit8-11 of remote CPU (00h..0Fh)
    /// </summary>
    DSReg IPCSYNC_Data_from_IPCSYNC;
    /// <summary>
    /// 8-11 R/W Data output to IPCSYNC Bit0-3 of remote CPU (00h..0Fh)
    /// </summary>
    DSReg IPCSYNC_Data_to_IPCSYNC;
    /// <summary>
    /// 13 W Send IRQ to remote CPU (0=None, 1=Send IRQ)
    /// </summary>
    DSReg IPCSYNC_IRQ_to_remote_CPU;
    /// <summary>
    /// 14 R/W Enable IRQ from remote CPU (0=Disable, 1=Enable)
    /// </summary>
    DSReg IPCSYNC_Ena_IRQ_from_remote_CPU;
    /// <summary>
    /// IPC Fifo Control Register (R/W)
    /// </summary>
    DSReg IPCFIFOCNT;
    /// <summary>
    /// 0 R Send Fifo Empty Status (0=Not Empty, 1=Empty)
    /// </summary>
    DSReg IPCFIFOCNT_Send_Fifo_Empty_Status;
    /// <summary>
    /// 1 R Send Fifo Full Status (0=Not Full, 1=Full)
    /// </summary>
    DSReg IPCFIFOCNT_Send_Fifo_Full_Status;
    /// <summary>
    /// 2 R/W Send Fifo Empty IRQ (0=Disable, 1=Enable)
    /// </summary>
    DSReg IPCFIFOCNT_Send_Fifo_Empty_IRQ;
    /// <summary>
    /// 3 W Send Fifo Clear (0=Nothing, 1=Flush Send Fifo)
    /// </summary>
    DSReg IPCFIFOCNT_Send_Fifo_Clear;
    /// <summary>
    /// 8 R Receive Fifo Empty (0=Not Empty, 1=Empty)
    /// </summary>
    DSReg IPCFIFOCNT_Receive_Fifo_Empty;
    /// <summary>
    /// 9 R Receive Fifo Full (0=Not Full, 1=Full)
    /// </summary>
    DSReg IPCFIFOCNT_Receive_Fifo_Full;
    /// <summary>
    /// 10 R/W Receive Fifo Not Empty IRQ (0=Disable, 1=Enable)
    /// </summary>
    DSReg IPCFIFOCNT_Receive_Fifo_Not_Empty_IRQ;
    /// <summary>
    /// 14 R/W Error, Read Empty/Send Full (0=No Error, 1=Error/Acknowledge)
    /// </summary>
    DSReg IPCFIFOCNT_Error_Read_Empty_Send_Full;
    /// <summary>
    /// 15 R/W Enable Send/Receive Fifo (0=Disable, 1=Enable)
    /// </summary>
    DSReg IPCFIFOCNT_Enable_Send_Receive_Fifo;
    /// <summary>
    /// IPC Send Fifo (W)
    /// </summary>
    DSReg IPCFIFOSEND;
    /// <summary>
    /// IPC Receive Fifo (R)
    /// </summary>
    DSReg IPCFIFORECV;
    /// <summary>
    /// Gamecard ROM and SPI Control
    /// </summary>
    DSReg AUXSPICNT;
    /// <summary>
    /// 0-1 SPI Baudrate (0=4MHz/Default, 1=2MHz, 2=1MHz, 3=512KHz)
    /// </summary>
    DSReg AUXSPICNT_SPI_Baudrate;
    /// <summary>
    /// 6 SPI Hold Chipselect (0=Deselect after transfer, 1=Keep selected)
    /// </summary>
    DSReg AUXSPICNT_SPI_Hold_Chipselect;
    /// <summary>
    /// 7 SPI Busy (0=Ready, 1=Busy) (presumably Read-only)
    /// </summary>
    DSReg AUXSPICNT_SPI_Busy;
    /// <summary>
    /// 13 NDS Slot Mode (0=Parallel/ROM, 1=Serial/SPI-Backup)
    /// </summary>
    DSReg AUXSPICNT_NDS_Slot_Mode;
    /// <summary>
    /// 14 Transfer Ready IRQ (0=Disable, 1=Enable) (for ROM, not for AUXSPI)
    /// </summary>
    DSReg AUXSPICNT_Transfer_Ready_IRQ;
    /// <summary>
    /// 15 NDS Slot Enable (0=Disable, 1=Enable) (for both ROM and AUXSPI)
    /// </summary>
    DSReg AUXSPICNT_NDS_Slot_Enable;
    /// <summary>
    /// Gamecard SPI Bus Data/Strobe (R/W)
    /// </summary>
    DSReg AUXSPIDATA;
    /// <summary>
    /// Gamecard Bus ROMCTRL (R/W)
    /// </summary>
    DSReg ROMCTRL;
    /// <summary>
    ///  0-12 KEY1 gap1 length (0-1FFFh) (forced min 08F8h by BIOS) (leading gap)
    /// </summary>
    DSReg ROMCTRL_KEY1_gap1_length;
    /// <summary>
    ///  13 KEY2 encrypt data (0=Disable, 1=Enable KEY2 Encryption for Data)
    /// </summary>
    DSReg ROMCTRL_KEY2_encrypt_data;
    /// <summary>
    ///  14 SE Unknown? (usually same as Bit13) (does NOT affect timing?)
    /// </summary>
    DSReg ROMCTRL_SE;
    /// <summary>
    ///  15 KEY2 Apply Seed (0=No change, 1=Apply Encryption Seed) (Write only)
    /// </summary>
    DSReg ROMCTRL_KEY2_Apply_Seed;
    /// <summary>
    ///  16-21 KEY1 gap2 length (0-3Fh) (forced min 18h by BIOS) (200h-byte gap)
    /// </summary>
    DSReg ROMCTRL_KEY1_gap2_length;
    /// <summary>
    ///  22 KEY2 encrypt cmd (0=Disable, 1=Enable KEY2 Encryption for Commands)
    /// </summary>
    DSReg ROMCTRL_KEY2_encrypt_cmd;
    /// <summary>
    ///  23 Data-Word Status (0=Busy, 1=Ready/DRQ) (Read-only)
    /// </summary>
    DSReg ROMCTRL_Data_Word_Status;
    /// <summary>
    ///  24-26 Data Block size (0=None, 1..6=100h SHL (1..6) bytes, 7=4 bytes)
    /// </summary>
    DSReg ROMCTRL_Data_Block_size;
    /// <summary>
    ///  27 Transfer CLK rate (0=6.7MHz=33.51MHz/5, 1=4.2MHz=33.51MHz/8)
    /// </summary>
    DSReg ROMCTRL_Transfer_CLK_rate;
    /// <summary>
    ///  28 KEY1 Gap CLKs (0=Hold CLK High during gaps, 1=Output Dummy CLK Pulses)
    /// </summary>
    DSReg ROMCTRL_KEY1_Gap_CLKs;
    /// <summary>
    ///  29 RESB Release Reset (0=Reset, 1=Release) (cannot be cleared once set)
    /// </summary>
    DSReg ROMCTRL_RESB_Release_Reset;
    /// <summary>
    ///  30 WR Unknown, maybe data-write? (usually 0) (read/write-able)
    /// </summary>
    DSReg ROMCTRL_WR;
    /// <summary>
    ///  31 Block Start/Status (0=Ready, 1=Start/Busy) (IRQ See 40001A0h/Bit14)
    /// </summary>
    DSReg ROMCTRL_Block_Start_Status;
    /// <summary>
    /// Gamecard bus 8-byte Command Out
    /// </summary>
    DSReg Gamecard_bus_Command_1;
    /// <summary>
    /// Gamecard bus 8-byte Command Out
    /// </summary>
    DSReg Gamecard_bus_Command_2;
    /// <summary>
    /// Gamecard bus 4-byte Data In (R)
    /// </summary>
    DSReg Gamecard_bus_DataIn;
    /// <summary>
    /// Encryption Seed 0 Lower 32bit (W)
    /// </summary>
    DSReg Encryption_Seed_0_Lower;
    /// <summary>
    /// Encryption Seed 1 Lower 32bit (W)
    /// </summary>
    DSReg Encryption_Seed_1_Lower;
    /// <summary>
    /// Encryption Seed 0 Upper 7bit (bit7-15 unused)
    /// </summary>
    DSReg Encryption_Seed_0_Upper;
    /// <summary>
    /// Encryption Seed 1 Upper 7bit (bit7-15 unused)
    /// </summary>
    DSReg Encryption_Seed_1_Upper;
    /// <summary>
    ///  SPI Bus Control/Status Register
    /// </summary>
    DSReg SPICNT;
    /// <summary>
    /// 0-1 Baudrate (0=4MHz/Firmware, 1=2MHz/Touchscr, 2=1MHz/Powerman., 3=512KHz)
    /// </summary>
    DSReg SPICNT_Baudrate;
    /// <summary>
    /// 7 Busy Flag (0=Ready, 1=Busy) (presumably Read-only)
    /// </summary>
    DSReg SPICNT_Busy_Flag;
    /// <summary>
    /// 8-9 Device Select (0=Powerman., 1=Firmware, 2=Touchscr, 3=Reserved)
    /// </summary>
    DSReg SPICNT_Device_Select;
    /// <summary>
    /// 10 Transfer Size (0=8bit/Normal, 1=16bit/Bugged)
    /// </summary>
    DSReg SPICNT_Transfer_Size;
    /// <summary>
    /// 11 Chipselect Hold (0=Deselect after transfer, 1=Keep selected)
    /// </summary>
    DSReg SPICNT_Chipselect_Hold;
    /// <summary>
    /// 14 Interrupt Request (0=Disable, 1=Enable)
    /// </summary>
    DSReg SPICNT_Interrupt_Request;
    /// <summary>
    /// 15 SPI Bus Enable (0=Disable, 1=Enable)
    /// </summary>
    DSReg SPICNT_SPI_Bus_Enable;
    /// <summary>
    /// SPI Bus Data/Strobe Register (R/W)
    /// </summary>
    DSReg SPIDATA;
    /// <summary>
    /// 0-1 Power Down Mode Select
    /// </summary>
    DSReg SPIDATA_Power_Down_Mode;
    /// <summary>
    /// 2 Reference Select (0=Differential, 1=Single-Ended)
    /// </summary>
    DSReg SPIDATA_Reference_Select;
    /// <summary>
    /// 3 Conversion Mode (0=12bit, max CLK=2MHz, 1=8bit, max CLK=3MHz)
    /// </summary>
    DSReg SPIDATA_Conversion_Mode;
    /// <summary>
    /// 4-6 Channel Select (0-7, see below)
    /// </summary>
    DSReg SPIDATA_Channel_Select;
    /// <summary>
    /// 7 Start Bit (Must be set to access Control Byte)
    /// </summary>
    DSReg SPIDATA_Start_Bit;
    /// <summary>
    /// External Memory Status (R/W..R)
    /// </summary>
    DSReg EXMEMSTAT;
    /// <summary>
    /// 0-1 32-pin GBA Slot SRAM Access Time (0-3 = 10, 8, 6, 18 cycles)
    /// </summary>
    DSReg EXMEMSTAT_GBASlot_SRAM_Access_Time;
    /// <summary>
    /// 2-3 32-pin GBA Slot ROM 1st Access Time (0-3 = 10, 8, 6, 18 cycles)
    /// </summary>
    DSReg EXMEMSTAT_GBASlot_ROM_1st_Access_Time;
    /// <summary>
    /// 4 32-pin GBA Slot ROM 2nd Access Time (0-1 = 6, 4 cycles)
    /// </summary>
    DSReg EXMEMSTAT_GBASlot_ROM_2nd_Access_Time;
    /// <summary>
    /// 5-6 32-pin GBA Slot PHI-pin out (0-3 = Low, 4.19MHz, 8.38MHz, 16.76MHz)
    /// </summary>
    DSReg EXMEMSTAT_GBASlot_PHI_pin_out;
    /// <summary>
    /// 7 32-pin GBA Slot Access Rights (0=ARM9, 1=ARM7)
    /// </summary>
    DSReg EXMEMSTAT_GBASlot_Access_Rights;
    /// <summary>
    /// 11 17-pin NDS Slot Access Rights (0=ARM9, 1=ARM7)
    /// </summary>
    DSReg EXMEMSTAT_NDSSlot_Access_Rights;
    /// <summary>
    /// 13 NDS:Always set? ;set/tested by DSi bootcode: Main RAM enable, CE2 pin?
    /// </summary>
    DSReg EXMEMSTAT_SET;
    /// <summary>
    /// 14 Main Memory Interface Mode Switch (0=Async/GBA/Reserved, 1=Synchronous)
    /// </summary>
    DSReg EXMEMSTAT_MainMem_Interface_Mode;
    /// <summary>
    /// 15 Main Memory Access Priority (0=ARM9 Priority, 1=ARM7 Priority)
    /// </summary>
    DSReg EXMEMSTAT_MainMem_Access_Priority;
    /// <summary>
    /// Wifi Waitstate Control
    /// </summary>
    DSReg WIFIWAITCNT;
    /// <summary>
    /// Wifi WS0 Control (0-7) (Ports 4800000h-4807FFFh)
    /// </summary>
    DSReg WIFIWAITCNT_WS0;
    /// <summary>
    /// Wifi WS1 Control (0-7) (Ports 4808000h-480FFFFh)
    /// </summary>
    DSReg WIFIWAITCNT_WS1;
    /// <summary>
    /// Interrupt Master Enable Register
    /// </summary>
    DSReg IME;
    /// <summary>
    /// Interrupt Enable
    /// </summary>
    DSReg IE;
    /// <summary>
    /// 0 LCD V-Blank
    /// </summary>
    DSReg IE_LCD_V_Blank;
    /// <summary>
    /// 1 LCD H-Blank
    /// </summary>
    DSReg IE_LCD_H_Blank;
    /// <summary>
    /// 2 LCD V-Counter Match
    /// </summary>
    DSReg IE_LCD_V_Counter_Match;
    /// <summary>
    /// 3 Timer 0 Overflow
    /// </summary>
    DSReg IE_Timer_0;
    /// <summary>
    /// 4 Timer 1 Overflow
    /// </summary>
    DSReg IE_Timer_1;
    /// <summary>
    /// 5 Timer 2 Overflow
    /// </summary>
    DSReg IE_Timer_2;
    /// <summary>
    /// 6 Timer 3 Overflow
    /// </summary>
    DSReg IE_Timer_3;
    /// <summary>
    /// 7 NDS7 only: SIO/RCNT/RTC (Real Time Clock)
    /// </summary>
    DSReg IE_SIO_RCNT_RTC;
    /// <summary>
    /// 8 DMA 0
    /// </summary>
    DSReg IE_DMA_0;
    /// <summary>
    /// 9 DMA 1
    /// </summary>
    DSReg IE_DMA_1;
    /// <summary>
    /// 10 DMA 2
    /// </summary>
    DSReg IE_DMA_2;
    /// <summary>
    /// 11 DMA 3
    /// </summary>
    DSReg IE_DMA_3;
    /// <summary>
    /// 12 Keypad
    /// </summary>
    DSReg IE_Keypad;
    /// <summary>
    /// 13 GBA-Slot (external IRQ source)
    /// </summary>
    DSReg IE_GBA_Slot_external_IRQ;
    /// <summary>
    /// 16 IPC Sync
    /// </summary>
    DSReg IE_IPC_Sync;
    /// <summary>
    /// 17 IPC Send FIFO Empty
    /// </summary>
    DSReg IE_IPC_Send_FIFO_Empty;
    /// <summary>
    /// 18 IPC Recv FIFO Not Empty
    /// </summary>
    DSReg IE_IPC_Recv_FIFO_Not_Empty;
    /// <summary>
    /// 19 NDS-Slot Game Card Data Transfer Completion
    /// </summary>
    DSReg IE_NDS_Slot_Transfer_Complete;
    /// <summary>
    /// 20 NDS-Slot Game Card IREQ_MC
    /// </summary>
    DSReg IE_NDS_Slot_IREQ_MC;
    /// <summary>
    /// 22 NDS7 only: Screens unfolding
    /// </summary>
    DSReg IE_Screens_unfolding;
    /// <summary>
    /// 23 NDS7 only: SPI bus
    /// </summary>
    DSReg IE_SPI_bus;
    /// <summary>
    /// 24 NDS7 only: Wifi / DSi9: XpertTeak DSP
    /// </summary>
    DSReg IE_Wifi;
    /// <summary>
    /// 25-31 unused
    /// </summary>
    DSReg IE_unused;
    /// <summary>
    /// Interrupt Request Flags / IRQ Acknowledge
    /// </summary>
    DSReg IF;
    /// <summary>
    /// 0 LCD V-Blank
    /// </summary>
    DSReg IF_LCD_V_Blank;
    /// <summary>
    /// 1 LCD H-Blank
    /// </summary>
    DSReg IF_LCD_H_Blank;
    /// <summary>
    /// 2 LCD V-Counter Match
    /// </summary>
    DSReg IF_LCD_V_Counter_Match;
    /// <summary>
    /// 3 Timer 0 Overflow
    /// </summary>
    DSReg IF_Timer_0;
    /// <summary>
    /// 4 Timer 1 Overflow
    /// </summary>
    DSReg IF_Timer_1;
    /// <summary>
    /// 5 Timer 2 Overflow
    /// </summary>
    DSReg IF_Timer_2;
    /// <summary>
    /// 6 Timer 3 Overflow
    /// </summary>
    DSReg IF_Timer_3;
    /// <summary>
    /// 7 NDS7 only: SIO/RCNT/RTC (Real Time Clock)
    /// </summary>
    DSReg IF_SIO_RCNT_RTC;
    /// <summary>
    /// 8 DMA 0
    /// </summary>
    DSReg IF_DMA_0;
    /// <summary>
    /// 9 DMA 1
    /// </summary>
    DSReg IF_DMA_1;
    /// <summary>
    /// 10 DMA 2
    /// </summary>
    DSReg IF_DMA_2;
    /// <summary>
    /// 11 DMA 3
    /// </summary>
    DSReg IF_DMA_3;
    /// <summary>
    /// 12 Keypad
    /// </summary>
    DSReg IF_Keypad;
    /// <summary>
    /// 13 GBA-Slot (external IRQ source)
    /// </summary>
    DSReg IF_GBA_Slot_external_IRQ;
    /// <summary>
    /// 16 IPC Sync
    /// </summary>
    DSReg IF_IPC_Sync;
    /// <summary>
    /// 17 IPC Send FIFO Empty
    /// </summary>
    DSReg IF_IPC_Send_FIFO_Empty;
    /// <summary>
    /// 18 IPC Recv FIFO Not Empty
    /// </summary>
    DSReg IF_IPC_Recv_FIFO_Not_Empty;
    /// <summary>
    /// 19 NDS-Slot Game Card Data Transfer Completion
    /// </summary>
    DSReg IF_NDS_Slot_Transfer_Complete;
    /// <summary>
    /// 20 NDS-Slot Game Card IREQ_MC
    /// </summary>
    DSReg IF_NDS_Slot_IREQ_MC;
    /// <summary>
    /// 22 NDS7 only: Screens unfolding
    /// </summary>
    DSReg IF_Screens_unfolding;
    /// <summary>
    /// 23 NDS7 only: SPI bus
    /// </summary>
    DSReg IF_SPI_bus;
    /// <summary>
    /// 24 NDS7 only: Wifi / DSi9: XpertTeak DSP
    /// </summary>
    DSReg IF_Wifi;
    /// <summary>
    /// VRAM Bank Status (R) + WRAM Bank Status (R)
    /// </summary>
    DSReg RAMSTAT;
    /// <summary>
    /// VRAM C enabled and allocated to NDS7 (0=No, 1=Yes)
    /// </summary>
    DSReg RAMSTAT_VRAMSTAT_C;
    /// <summary>
    /// VRAM D enabled and allocated to NDS7 (0=No, 1=Yes)
    /// </summary>
    DSReg RAMSTAT_VRAMSTAT_D;
    /// <summary>
    /// (0-3 = 32K/0K, 2nd 16K/1st 16K, 1st 16K/2nd 16K, 0K/32K)
    /// </summary>
    DSReg MemControl2_WRAM;
    /// <summary>
    /// Post Boot Flag (R/W)
    /// </summary>
    DSReg POSTFLG;
    /// <summary>
    /// Post Boot Flag (0=Boot in progress, 1=Boot completed)
    /// </summary>
    DSReg POSTFLG_Flag;
    /// <summary>
    /// Power Down Mode (0=No function, 1=Enter GBA Mode, 2=Halt, 3=Sleep)
    /// </summary>
    DSReg POSTFLG_Power_Down_Mode;
    /// <summary>
    /// Sound/Wifi Power Control Register (R/W)
    /// </summary>
    DSReg POWCNT2;
    /// <summary>
    /// Sound Speakers (0=Disable, 1=Enable) (Initial setting = 1)
    /// </summary>
    DSReg POWCNT2_Sound;
    /// <summary>
    /// Wifi (0=Disable, 1=Enable) (Initial setting = 0)
    /// </summary>
    DSReg POWCNT2_Wifi;
    /// <summary>
    /// Bios-data-read-protection address
    /// </summary>
    DSReg BIOSPROT;

    RegSect_system7();
};

class REGS_Arm7
{
public:
    RegSect_display7 Sect_display7;
    RegSect_sound7 Sect_sound7;
    RegSect_dma7 Sect_dma7;
    RegSect_timer7 Sect_timer7;
    RegSect_keypad7 Sect_keypad7;
    RegSect_serial7 Sect_serial7;
    RegSect_system7 Sect_system7;

    byte data[4208];
    byte rwmask[4208];
    const int allregcount = 469;
    DSReg allregs[469];

    void reset();
};
extern REGS_Arm7 Regs_Arm7;
