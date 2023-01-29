# Raylib arkanoid test project
*Classic Arkanoid game replica written in modern C++/Raylib*


### How to build:
I used `Ninja`/`Mingw`/`Cmake` environment (default to CLion) in order to build this project. 

However, it's possible to build it inside Visual Studio with installed `CMake` support and `/std:c++17` compiler flag

You need to have `glm` installed. I used `vckpg` for that (add `-DCMAKE_TOOLCHAIN_FILE=D:/apps/vcpkg/scripts/buildsystems/vcpkg.cmake` flag for CMAKE)

You don't have to install `raylib`, it's fetched automatically from git
### How to run:
I included `raylib_vs.exe` and `raylib_mingw.exe` (which is, for whatever reason, should be run from terminal only) to the repo for Windows users.

### Guidelines and requirements:
1. You will have 48h to complete the test
2. You can choose to use C++ (and any graphic API like SDL2 or Raylib for example) /
   Unreal 4.27.2 (C++).
3. If a plain C++ project is delivered, its solution must be provided using Visual Studio.
   Am Unreal project must be delivered otherwise
4. The game should include(at least) the following workflow: Splash -> Main Menu ->
   Game -> Game Results
5. The game should be your own implementation of a classic game (please choose
   your favorite from the list below):
   a. Tetris
   b. Pacman
   c. Arkanoid (breakout)
   d. Propose us your favorite classic :)
6. Using coding assets from the Marketplace is completely forbidden (if using Unreal).
   Only support plugins like reading CSV or json file (basically tasks that are not core to
   programming your videogame / test).
7. If using Unreal, blueprints are allowed to control UI components but not the main
   game’s logic
8. The game should include at least the following components:
   a. Input detection
   b. Sprite / 3D animation (if in a Game Engine, use its system)
   c. Background music + sound effects
   d. Particle system
   e. Use Raycast for collision detection at least once (or if using C++ a physics
   engine integration is allowed)
9. The game should contain a win / lose condition
10. Using code from other developers / internet is allowed. Copy without understanding
    the code is not
11. If you have questions during the creation of your game feel free to ask. Questions are
    more than welcome
12. Anything else you consider is needed to get a good game feeling, better user
    experience
### What we will evaluate (among other things):
    ● The general game feeling. It must be fun to play
    ● No major bugs. The project must have no major (or breaking) bugs
    ● Project organization:
    ○ If using Unreal we will check the usage of maps, animations, particle effects,
    etc
    ○ If using a custom c++ engine, we will evaluate the folder structure, how you
    load resources, etc
    ● Coding style. Following coding conventions and best practices.
    ● Usage of programming patterns when needed.
    ● Overall performance. Not wasted performance!.