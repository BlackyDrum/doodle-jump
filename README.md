# Flappy Bird Clone in SFML + ImGui!
This is a C++ project that implements a clone of the popular game Flappy Bird using SFML.<br>
You have the option to modify some of the game options/assets such as flying speed, gravity, skins, etc. with ImGui.

![ezgif com-video-to-gif (2)](https://github.com/BlackyDrum/flappy-bird/assets/111639941/413f82f2-5fe0-4683-ab20-4525980da979)


## Controls
- ``Space`` - Add force to the bird
- ``Enter`` - Open settings
- ``Escape`` - Pause

## Prerequisites
Before running the Flappy Bird clone, make sure you have the following installed on your system:
-   SFML library: You can download SFML from the official website ([https://www.sfml-dev.org/](https://www.sfml-dev.org/)) and follow the installation instructions for your operating system, for example on Debian-based systems:
```
$ sudo apt-get install libsfml-dev
```
- OpenGL library: You can install the library with the following command:
```
$ sudo apt-get install libglu1-mesa-dev mesa-common-dev
```
- A C++ compiler, e.g. ``GCC``
```
$ sudo apt-get install build-essential
```
- On Windows, make sure to set the ``SFML_PATH`` variable to the root path of the SFML library:
```
set SFML_PATH=C:\path\to\sfml
```
 
## Build using Makefile
If you have ``GNU Make`` installed on your system, you can use the included ``Makefile`` to build the project.

1. Clone the repository to your local machine:
```
$ git clone https://github.com/BlackyDrum/flappy-bird.git
```
2. Change to the cloned directory:
```
$ cd flappy-bird
```
3. Use make to build the project. The executable ``flappy-bird`` will be generated in the root directory.
```
$ make
```
4. Run the binary file (or double click the .exe on Windows):
```
$ ./flappy-bird
```
Note: <em>If you encounter any problems on Windows trying to run ``flappy-bird.exe``, make sure to put the .dll in the same directory as the .exe.
You can find the .dll in the SFML ``bin`` folder.</em>

## Acknowledgements

-   SFML: Simple and Fast Multimedia Library ([https://www.sfml-dev.org/](https://www.sfml-dev.org/))
-   Flappy Bird: Original game developed by Dong Nguyen ([https://en.wikipedia.org/wiki/Flappy_Bird](https://en.wikipedia.org/wiki/Flappy_Bird))
-   Assets: Sounds and textures ([https://github.com/samuelcust/flappy-bird-assets](https://github.com/samuelcust/flappy-bird-assets))
