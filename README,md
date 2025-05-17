# Building Instructions (from raylib-quickstart)

## VSCode Users (all platforms)

_Note_ You must have a compiler toolchain installed in addition to vscode.

- Download the quickstart
- Rename the folder to your game name
- Open the folder in VSCode
- Run the build task ( CTRL+SHIFT+B or F5 )
- You are good to go

## Windows Users

There are two compiler toolchains available for windows, MinGW-W64 (a free compiler using GCC), and Microsoft Visual Studio

### Using MinGW-W64

- Double click the `build-MinGW-W64.bat` file
- CD into the folder in your terminal
- run `make`
- You are good to go

#### Note on MinGW-64 versions

Make sure you have a modern version of MinGW-W64 (not mingw).
The best place to get it is from the W64devkit from
https://github.com/skeeto/w64devkit/releases
or the version installed with the raylib installer

#### If you have installed raylib from the installer

Make sure you have added the path

`C:\raylib\w64devkit\bin`

To your path environment variable so that the compiler that came with raylib can be found.

DO NOT INSTALL ANOTHER MinGW-W64 from another source such as msys2, you don't need it.

### Microsoft Visual Studio

- Run `build-VisualStudio2022.bat`
- double click the `.sln` file that is generated
- develop your game
- you are good to go

## Linux Users

- CD into the build folder
- run `./premake5 gmake2`
- CD back to the root
- run `make`
- you are good to go

## MacOS Users

- CD into the build folder
- run `./premake5.osx gmake2`
- CD back to the root
- run `make`
- you are good to go
