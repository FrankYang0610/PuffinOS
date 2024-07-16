cmake_minimum_required(VERSION 3.28)
project(PuffinOS)

set(CMAKE_CXX_STANDARD 17)

add_executable(PuffinOS main.cpp
        PuffinOS_Class/PuffinOS.h
        PuffinOS_Class/PuffinOS.cpp

        Process_Class/Process.h
        Process_Class/Process.cpp

        File_Class/File.h
        File_Class/File.cpp

        Terminal/Terminal.cpp

        Command_Separator/Command_Separator.h
        Command_Separator/Command_Separator.cpp

        Time_Stamp/Time_Stamp.cpp
        Time_Stamp/Time_Stamp.h

        Terminal/Error_Stream/Error_Stream.h
        Terminal/Error_Stream/Error_Stream.cpp
        
        Folder_Class/Folder.h
        Folder_Class/Folder.cpp
        
        Network/Network.h
        Network/Network.cpp
)
