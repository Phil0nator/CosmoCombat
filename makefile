#Copyright Notice:
#The files within this zip file are copyrighted by Lazy Foo' Productions (2004-2014)
#and may not be redistributed without written permission.

#OBJS specifies which files to compile as part of the project
OBJS = CosmoCombat.cpp

#CC specifies which compiler we're using
CC = g++

#INCLUDE_PATHS specifies the additional include paths we'll need
INCLUDE_PATHS = -IC:/SDL/SDL2-devel-2.0.10-mingw/SDL2-2.0.10/i686-w64-mingw32/include/SDL2 -I C:/SDL/SDL2_ttf-2.0.15/i686-w64-mingw32/include/SDL2 -I C:/SDL/SDL2_image-devel-2.0.5-mingw/SDL2_image-2.0.5/i686-w64-mingw32/include/SDL2

#LIBRARY_PATHS specifies the additional library paths we'll need
LIBRARY_PATHS =-L C:/mingw_dev_lib/lib -LC:/SDL/SDL2-devel-2.0.10-mingw/SDL2-2.0.10/i686-w64-mingw32/lib -L C:/SDL/SDL2_image-devel-2.0.5-mingw/SDL2_image-2.0.5/i686-w64-mingw32/lib -L C:/SDL/SDL2_ttf-2.0.15/i686-w64-mingw32/lib

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
# -Wl,-subsystem,windows gets rid of the console window
COMPILER_FLAGS = -Wreturn-type

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -l mingw32 -l SDL2main -l SDL2 -l SDL2_image -l SDL2_ttf

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = CosmoCombat

#This is the target that compiles our executable
all : $(OBJS)
	$(CC) -g $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME) -fpermissive
