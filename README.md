# SFML Game of Life

C++ SFML implementation of [Conway's Game of Life](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life)

Pre-built static binaries available for windows & linux x86_64 [in releases page.](https://github.com/SuperRonJon/GameOfLife/releases/latest)

## Controls

Space to pause

## Build dependencies for static build

- SFML 3.0.0+
- libEGL_mesa
- libfreetype
- libudev
- libX11
- libXcursor
- libXrandr
- libXi

fedora install command: `sudo dnf install libXrandr-devel libXcursor-devel libXi-devel libudev-devel freetype-devel mesa-libEGL-devel`

### To Build with makefile:
- Download/build a copy of the SFML library files.
- Create include/ and lib/ directories in this project's directory.
- Place the SFML headers directory into include
- Place the compiled sfml library files (libsfml-*.a files) into the lib/ directory
- `make` or `make windows` to build