#OBJS specifies which files to compile as part of the project
OBJS = CosmoCombat.cpp

#CC specifies which compiler we're using
CC = g++

#INCLUDE_PATHS specifies the additional include paths we'll need
INCLUDE_PATHS = -IC:\SDL\SDL2-devel-2.0.10-mingw\SDL2-2.0.10\x86_64-w64-mingw32\include\SDL2 -IC:\SDL\SDL2_ttf-2.0.15\x86_64-w64-mingw32\include\SDL2 -IC:\SDL\SDL2_image-devel-2.0.5-mingw\SDL2_image-2.0.5\x86_64-w64-mingw32\include\SDL2

#LIBRARY_PATHS specifies the additional library paths we'll need (-LC)
LIBRARY_PATHS =-LC:\mingw_dev_lib\lib -LC:\SDL\SDL2-devel-2.0.10-mingw\SDL2-2.0.10\x86_64-w64-mingw32\lib -LC:\SDL\SDL2_image-devel-2.0.5-mingw\SDL2_image-2.0.5\x86_64-w64-mingw32\lib -LC:\SDL\SDL2_ttf-2.0.15\x86_64-w64-mingw32\lib

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
# -Wl,-subsystem,windows gets rid of the console window
COMPILER_FLAGS = -w

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2.dll -lSDL2_image.dll -lSDL2_ttf.dll

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = CosmoCombat

#This is the target that compiles our executable
#$(LIBRARY_PATHS)
all : $(OBJS)
	$(CC) $(OBJS) $(INCLUDE_PATHS)   $(LIBRARY_PATHS)     $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME) -fpermissive
