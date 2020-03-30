function string:split(sep)
        local sep, fields = sep or ":", {}
        local pattern = string.format("([^%s]+)", sep)
        self:gsub(pattern, function(c) fields[#fields+1] = c end)
        return fields
end

function string:trim()
  return (self:gsub("^%s*(.-)%s*$", "%1"))
end


function convert_vhd_hex(instring)

   local sfind_sharp  = instring:find("#", 1, true)
   if (sfind_sharp ~= nil) then
      return "0x"..string.sub(instring, sfind_sharp + 1, #instring - 1)
   end
   
   return instring
  
end

function binary_or(a,b)
   local r = 0
   local neg = 1
   if (a < 0) then
      a = a * (-1)
      neg = neg * (-1)
   end
   if (b < 0) then
      b = b * (-1)
      neg = neg * (-1)
   end
   for i = 31, 0, -1 do
      local x = 2^i
      if (a >= x or b>=x) then
         r = r + 2^i
      end
      if (a >= x) then
         a = a - x
      end
      if (b >= x) then
         b = b - x
      end
   end
   return r * neg
end


function analyze_file(filename)

   newsect = {}
   newsect.regs = {}
   newsect.name = filename:split("_")[2]:split(".")[1]

   for line in io.lines(filename) do 
      line = line:trim()
      local sfind_open  = line:find("(", 1, true)
      local sfind_close = line:find(")", 1, true)
      if (sfind_open ~= nil and sfind_close ~= nil and string.sub(line, 1, 1) ~= "-") then
         --print(line)
         
         newreg = {}
         newreg.name = line:split(" ")[2]
         
         bracketline = string.sub(line, sfind_open + 1, sfind_close - 1)
         --print(newreg.name, line)
         
         parts = bracketline:split(",")
         newreg.address    = convert_vhd_hex(parts[1]:trim())
         newreg.msb        = parts[2]:trim()
         newreg.lsb        = parts[3]:trim()
         newreg.count      = parts[4]:trim()
         newreg.default    = convert_vhd_hex(parts[5]:trim())
         newreg.accesstype = parts[6]:trim()
         
         local sfind_comment  = line:find("--", 1, true)
         if (sfind_comment ~= nil) then
            newreg.comment    = string.sub(line, sfind_comment + 3, #line)
         end
         
         newsect.regs[#newsect.regs + 1] = newreg
         max_addr = math.max(tonumber(newreg.address), max_addr) 
      end
   end
   
   sections[#sections + 1] = newsect
   
end

function output_h(filename, classname, objectname)

   local outfile = nil
   while (outfile == nil) do
      outfile=io.open(filename,"w")
   end
   io.output(outfile)
   
   io.write("#pragma once\n")
   io.write("#include <string>\n")
   io.write("using namespace std;\n")
   io.write("\n")
   io.write("#include \"types.h\"\n")
   io.write("#include \"DSReg.h\"\n")
   io.write("\n")
   
   -- write section classes
   for i = 1, #sections do
      io.write("class RegSect_"..sections[i].name.."\n")
      io.write("{\n")
      io.write("public:\n")
      for j = 1, #sections[i].regs do
         if (sections[i].regs[j].comment ~= nil) then
            io.write("    /// <summary>\n")
            io.write("    /// "..sections[i].regs[j].comment:gsub("%s+", " ").."\n")
            io.write("    /// </summary>\n")
         end
         io.write("    DSReg "..sections[i].regs[j].name..";\n")
      end
      io.write("\n")
      io.write("    RegSect_"..sections[i].name.."();\n")
      io.write("};\n")
      io.write("\n")
   end
   
   io.write("class "..classname.."\n")
   io.write("{\n")
   io.write("public:\n")
   for i = 1, #sections do
      io.write("    RegSect_"..sections[i].name.." Sect_"..sections[i].name..";\n")
   end
   io.write("\n")
   io.write("    byte data[4208];\n")
   io.write("    byte rwmask[4208];\n")
   io.write("\n")
   io.write("    void reset();\n")
   io.write("};\n")
   io.write("extern "..classname.." "..objectname..";\n")
   
   
   io.close(outfile)

end

function output_cpp(filename, filename_h, classname, objectname)

   local outfile = nil
   while (outfile == nil) do
      outfile=io.open(filename,"w")
   end
   io.output(outfile)
   
   -- includes
   io.write("#include \""..filename_h.."\";\n")
   io.write("\n")
   io.write(classname.." "..objectname..";\n")
   io.write("\n")
   io.write("\n")
   
   -- write section classes
   for i = 1, #sections do
      io.write("RegSect_"..sections[i].name.."::RegSect_"..sections[i].name.."()\n")
      io.write("{\n")
      for j = 1, #sections[i].regs do
         io.write("    "..sections[i].regs[j].name.." = DSReg(")
         io.write(sections[i].regs[j].address..", ")
         io.write(sections[i].regs[j].msb..", ")
         io.write(sections[i].regs[j].lsb ..", ")
         io.write(sections[i].regs[j].count..", ")
         io.write(sections[i].regs[j].default..", ")
         io.write("\""..sections[i].regs[j].accesstype.."\", ")
         io.write(objectname..".data")
         io.write(");\n")
      end
      io.write("}\n")
      io.write("\n")
   end
   
   -- write combined class
   io.write("void "..classname.."::reset()\n")
   io.write("{\n")
   for i = 1, #sections do
      for j = 1, #sections[i].regs do
         local value = tonumber(sections[i].regs[j].default) * math.pow(2, sections[i].regs[j].lsb)
         if (value > 0)        then 
            io.write("      // "..sections[i].regs[j].name .." at "..sections[i].regs[j].address.." = "..sections[i].regs[j].default..";\n") 
            io.write("      data["..(tonumber(sections[i].regs[j].address) + 0).."] = "..value.." & 0xFF;\n") 
            if (value > 0xFF)     then io.write("      data["..(tonumber(sections[i].regs[j].address) + 1).."] = ("..value.." >> 8) & 0xFF;\n") end
            if (value > 0xFFFF)   then io.write("      data["..(tonumber(sections[i].regs[j].address) + 2).."] = ("..value.." >> 16) & 0xFF;\n") end
            if (value > 0xFFFFFF) then io.write("      data["..(tonumber(sections[i].regs[j].address) + 3).."] = ("..value.." >> 24) & 0xFF;\n") end
         end    
      end
   end
   
   io.write("\n")

   for addr = 0, max_addr do
      local rwmask = 0
      local firstreg = nil
      for i = 1, #sections do
         for j = 1, #sections[i].regs do
            if (tonumber(sections[i].regs[j].address) == addr) then
            
               if (firstreg == nil) then
                  firstreg = sections[i].regs[j]
               end
            
               if (sections[i].regs[j].accesstype ~= "writeonly") then
                  local lsb = sections[i].regs[j].lsb
                  local msb = sections[i].regs[j].msb
                  local filter = 0
                  for i = lsb, msb do
                     filter = filter + 2^i;
                  end
                  rwmask = binary_or(rwmask, filter)
                  --print(filter, rwmask)
               end
            end
         end
      end
      
      if (firstreg ~= nil) then
         local valhex = "0x"..string.format("%X", rwmask)
         io.write("    // "..firstreg.name .." at "..firstreg.address.." = "..valhex..";\n") 
         io.write("    rwmask["..(addr + 0).."] = (byte)(" ..valhex.." & 0xFF);\n") 
         io.write("    rwmask["..(addr + 1).."] = (byte)(("..valhex.." >> 8) & 0xFF);\n")
         io.write("    rwmask["..(addr + 2).."] = (byte)(("..valhex.." >> 16) & 0xFF);\n")
         io.write("    rwmask["..(addr + 3).."] = (byte)(("..valhex.." >> 24) & 0xFF);\n")
      end
         
   end
   io.write("}\n")
   
   
   io.close(outfile)

end

sections = {}
max_addr = 0

analyze_file("regds_display9.vhd")
analyze_file("regds_dma9.vhd")
analyze_file("regds_timer9.vhd")
analyze_file("regds_keypad9.vhd")
analyze_file("regds_system9.vhd")

max_addr = max_addr + 4

output_h("regs_arm9.h", "REGS_Arm9", "Regs_Arm9")
output_cpp("regs_arm9.cpp", "regs_arm9.h", "REGS_Arm9", "Regs_Arm9")

sections = {}
max_addr = 0

analyze_file("regds_display7.vhd")
analyze_file("regds_sound7.vhd")
analyze_file("regds_dma7.vhd")
analyze_file("regds_timer7.vhd")
analyze_file("regds_keypad7.vhd")
analyze_file("regds_system7.vhd")

max_addr = max_addr + 4

output_h("regs_arm7.h", "REGS_Arm7", "Regs_Arm7")
output_cpp("regs_arm7.cpp", "regs_arm7.h", "REGS_Arm7", "Regs_Arm7")





