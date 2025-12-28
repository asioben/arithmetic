@echo off

set SDL2_include=C:\msys64\mingw64\include\SDL2
set SDL2_lib=C:\msys64\mingw64\lib\SDL2
set ttf_include=C:\msys64\mingw64\include\SDL2_ttf
set ttf_lib=C:\msys64\mingw64\lib\SDL2_ttf
set image_include=C:\msys64\mingw64\include\SDL2_image
set image_lib=C:\msys64\mingw64\lib\SDL2_image

gcc ./src/main.c ./src/update.c ./src/button.c ./src/input.c ./src/game.c ./sdl2_utility/window.c ./sdl2_utility/utility.c ./sdl2_utility/texture.c ./sdl2_utility/time.c -I%SDL2_include% -L%SDL2_lib% -I%ttf_include% -L%ttf_lib% -I%image_include% -L%image_lib% -w -Wl,-subsystem,windows -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_image -o main 