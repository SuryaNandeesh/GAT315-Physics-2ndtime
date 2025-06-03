🧪 Physics Simulator

A visual, interactive 2D physics simulation tool built with GUI support. Users can create, manipulate, and simulate static, kinematic, and dynamic bodies—complete with real-time physics, spring constraints, and full simulation control.
✨ Features
🧍 Core Simulation Support

    Static Bodies: Immovable; not affected by forces or collisions.

    Kinematic Bodies: Move with defined velocity; unaffected by physics forces.

    Dynamic Bodies: Fully simulated using gravity, collisions, and springs.

⚙️ Per-Object Configuration

Each object can be independently customized with:

    Mass

    Size

    Damping

    Gravity Scale

    Restitution (bounciness)

    Spring system (optional connection)

🔗 Spring Constraints

Connect any two bodies with realistic spring behavior:

    Stiffness (spring constant)

    Damping (resistance over time)

🛠️ Object Management

    Add static, kinematic, or dynamic bodies.

    Customize physics properties for each via the UI panel.

🌐 Global Simulation Controls

    Adjust global simulation parameters:

        Gravity

        Gravitational force

        Spring stiffness multiplier

▶️ Simulation Flow

    Start or Pause the simulation.

    Reset the scene to clear all objects and connections.

🧠 Realistic Physics Behavior

    Dynamic bodies react naturally to:

        Forces

        Collisions

        Gravity

    Spring behavior follows Hooke’s Law with damping.

    Pause freezes the simulation while preserving state.

    Reset returns to a clean slate.

📸 Screenshots

Trigonometry:
![githubimgtrig](https://github.com/user-attachments/assets/a88f5d1b-cc12-40b5-8a1d-2964ac0ebb1c)

Polar:
![githubimgpolar](https://github.com/user-attachments/assets/b756a175-def3-4c21-89e3-0a642133670e)

Fireworks:
![snandeesh_raylib_fireworks2](https://github.com/user-attachments/assets/b424e861-dddf-4576-8b66-757f0b238642)

Vector:
![githubimgvector](https://github.com/user-attachments/assets/7b6e4dd2-54de-495a-be3b-ed51523f67a7)

Spring:
![githubimgspring](https://github.com/user-attachments/assets/1ad2c1be-1219-41d1-a572-4804598ca2fd)

🧰 Built With

    C++

    raylib – for rendering and input

    Custom physics engine and integrator


# Raylib-Quickstart
A simple cross platform template for setting up a project with the bleeding edge raylib code.
Works with C or C++.

## Supported Platforms
Quickstart supports the main 3 desktop platforms:
* Windows
* Linux
* MacOS

# Naming projects
Do not name your game project 'raylib', it will conflict with the raylib library.

# VSCode Users (all platforms)
*Note* You must have a compiler toolchain installed in addition to vscode.

* Download the quickstart
* Rename the folder to your game name
* Open the folder in VSCode
* Run the build task ( CTRL+SHIFT+B or F5 )
* You are good to go

# Windows Users
There are two compiler toolchains available for windows, MinGW-W64 (a free compiler using GCC), and Microsoft Visual Studio
## Using MinGW-W64
* Double click the `build-MinGW-W64.bat` file
* CD into the folder in your terminal
* run `make`
* You are good to go

### Note on MinGW-64 versions
Make sure you have a modern version of MinGW-W64 (not mingw).
The best place to get it is from the W64devkit from
https://github.com/skeeto/w64devkit/releases
or the version installed with the raylib installer
#### If you have installed raylib from the installer
Make sure you have added the path

`C:\raylib\w64devkit\bin`

To your path environment variable so that the compiler that came with raylib can be found.

DO NOT INSTALL ANOTHER MinGW-W64 from another source such as msys2, you don't need it.

## Microsoft Visual Studio
* Run `build-VisualStudio2022.bat`
* double click the `.sln` file that is generated
* develop your game
* you are good to go

# Linux Users
* CD into the build folder
* run `./premake5 gmake2`
* CD back to the root
* run `make`
* you are good to go

# MacOS Users
* CD into the build folder
* run `./premake5.osx gmake2`
* CD back to the root
* run `make`
* you are good to go

# Output files
The built code will be in the bin dir

# Working directories and the resources folder
The example uses a utility function from `path_utils.h` that will find the resources dir and set it as the current working directory. This is very useful when starting out. If you wish to manage your own working directory you can simply remove the call to the function and the header.

# Changing to C++
Simply rename `src/main.c` to `src/main.cpp` and re-run the steps above and do a clean build.

# Using your own code
Simply remove `src/main.c` and replace it with your code, and re-run the steps above and do a clean build.

# Building for other OpenGL targets
If you need to build for a different OpenGL version than the default (OpenGL 3.3) you can specify an OpenGL version in your premake command line. Just modify the bat file or add the following to your command line

## For OpenGL 1.1
`--graphics=opengl11`

## For OpenGL 2.1
`--graphics=opengl21`

## For OpenGL 4.3
`--graphics=opengl43`

## For OpenGLES 2.0
`--graphics=opengles2`

## For OpenGLES 3.0
`--graphics=opengles3`

# License
Copyright (c) 2020-2025 Jeffery Myers

This software is provided "as-is", without any express or implied warranty. In no event 
will the authors be held liable for any damages arising from the use of this software.

Permission is granted to anyone to use this software for any purpose, including commercial 
applications, and to alter it and redistribute it freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not claim that you 
  wrote the original software. If you use this software in a product, an acknowledgment 
  in the product documentation would be appreciated but is not required.

  2. Altered source versions must be plainly marked as such, and must not be misrepresented
  as being the original software.

  3. This notice may not be removed or altered from any source distribution.
