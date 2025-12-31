# SFML Game of Life

C++ SFML implementation of [Conway's Game of Life](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life)

Pre-built static binaries available for windows & linux x86_64 [in releases page.](https://github.com/SuperRonJon/GameOfLife/releases/latest)

## Controls

Space to pause

While paused:
- Right arrow: Advance one step
- Left Arrow: Revert to starting position
- Enter: Randomize all cells
- Backspace: Set all cells to dead
- Right mouse click: Click and drag to paint live cells
- Left mouse click: Click and drag to paint dead cells

# Building
## CMake (Preferred)
Build using cmake with the following commands for Windows & Linux. Linux requires the SFML dependencies (listed below) to be installed to build it from source.

Windows only requires git and cmake to be installed prior to building.

From the top level directory:

```sh
   cmake -B build -DCMAKE_BUILD_TYPE=Release
   cmake --build build
```
This will create a statically linked binary `life.exe` in `build/bin/`

## Linux dependencies for static build
These libraries are required for building SFML from source through cmake, and statically linking the libraries if building manually.

- SFML 3.0.0+
- libEGL_mesa
- libfreetype
- libudev
- libX11
- libXcursor
- libXrandr
- libXi

fedora install command: `sudo dnf install libXrandr-devel libXcursor-devel libXi-devel libudev-devel freetype-devel mesa-libEGL-devel libvorbis-devel flac-devel`
