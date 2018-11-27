cmake_minimum_required(VERSION 3.12)
project(pbrain-BORDEAUX-Cotoni.Martin)

set(CMAKE_CXX_STANDARD 14)

include_directories(Src)
include_directories(Src/Brain)
include_directories(Src/Core)
include_directories(Src/Errors)
include_directories(Src/Pattern)
include_directories(Src/Reader)
include_directories(Src/Threat)
include_directories(Src/Utils)

add_executable(pbrain-BORDEAUX-Cotoni.Martin
        Src/Brain/Brain.cpp
        Src/Brain/Brain.hpp
        Src/Core/Core.cpp
        Src/Core/Core.hpp
        Src/Errors/Errors.cpp
        Src/Errors/Errors.hpp
        Src/Pattern/Pattern.cpp
        Src/Pattern/Pattern.hpp
        Src/Reader/Reader.cpp
        Src/Reader/Reader.hpp
        Src/Threat/Threat.hpp
        Src/Utils/Utils.cpp
        Src/Utils/Utils.hpp
        Src/Main.cpp)
