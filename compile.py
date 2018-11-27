#!/usr/bin/python3.6

import sys, os

#Define the binary name
ExeName = "pbrain-BORDEAUX-Cotoni.Martin.exe"
#!Define the binary name

#Define all '.hpp' files path
IncludeUtils = " ./Src/Utils"
IncludeCore = " ./Src/Core"
IncludeErrors = " ./Src/Errors"
IncludeBrain = " ./Src/Brain"
IncludeReader = " ./Src/Reader"
IncludePattern = " ./Src/Pattern"
IncludeThreat = " ./Src/Threat"
#!Define all '.hpp' files path

#Define all '.cpp' files path
CPPMain = " ./Src/Main.cpp"
CPPUtils = IncludeUtils + "/Utils.cpp"
CPPCore = IncludeCore + "/Core.cpp"
CPPErrors = IncludeErrors + "/Errors.cpp"
CPPBrain = IncludeBrain + "/Brain.cpp"
CPPReader = IncludeReader + "/Reader.cpp"
CPPPattern = IncludePattern + "/Pattern.cpp"
#!Define all '.cpp' files path

#Add all 'Includes" & 'CPP' in 2 variables
Include = "-I" + IncludeUtils + " -I" + IncludeCore + " -I" + IncludeErrors + " -I" + IncludeBrain + " -I" + IncludeReader + " -I" + IncludePattern + " -I" + IncludeThreat
Files = CPPMain + CPPUtils + CPPCore + CPPErrors + CPPBrain + CPPReader + CPPPattern
#!Add all 'Includes" & 'CPP' in 2 variables

def compile(): {
    os.system("g++" + Files + " -W -Wall -Wextra " + Include + " -o " + ExeName)
}

compile()