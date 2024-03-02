cmake_minimum_required(VERSION 3.27)
project(nuff-mdverter)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(nuff-mdverter
        main.cpp
        CommandsParser.cpp
        OutputInterface.h
        FileOutput.h
        FileOutput.cpp
        InputInterface.h
        StandardTerminalOutput.h
        StandardTerminalOutput.cpp)
