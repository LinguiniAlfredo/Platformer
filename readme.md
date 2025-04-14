# Platformer

This is an unfinished platformer game with a concept of a level editor and a few rudimentary entities (blocks, switches, coins, etc.)
Perhaps I will return to this at some point...

## Installation (Windows)
> SDL2, SDL2-image, & SDL2-ttf must be installed.

This batch file uses the cl compiler included with Visual Studio, and expects it to be running in the terminal prior to building the game.

```cmd
"C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat" x64
```
> The path to vcvarsall.bat may be different depending on your version of Visual Studio...thanks Bill Gates.

Then run build.bat in the root directory to build the project.
```cmd
build.bat
```
This will create a main.exe inside of the Platformer folder. Run that guy to play.
