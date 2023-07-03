# Doodle Jump Clone in SFML + ImGui!
This is a C++ project that implements a clone of the popular game Doodle Jump using SFML.<br>
You have the option to modify some of the game options/assets such as jump force, gravity, etc. with ImGui.

![ezgif com-optimize](https://github.com/BlackyDrum/doodle-jump/assets/111639941/3390d4ba-623d-471e-98ac-b1b492c71d42)


## Controls
<table>
  <tr>
  <td><strong>Key</strong></td>
  <td><strong>Action</strong></td>
 </tr>
 <tr>
  <td>A</td>
  <td>Left</td>
 </tr>
  <tr>
  <td>D</td>
  <td>Right</td>
 </tr>
  <tr>
  <td>Space</td>
  <td>Shoot</td>
 </tr>
  <tr>
  <td>Enter</td>
  <td>Settings</td>
 </tr>
  <tr>
  <td>Escape</td>
  <td>Pause</td>
 </tr>
</table>


## Prerequisites
Before running the Doodle Jump clone, make sure you have the following installed on your system:
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
$ git clone https://github.com/BlackyDrum/doodle-jump.git
```
2. Change to the cloned directory:
```
$ cd doodle-jump
```
3. Use make to build the project. The executable ``doodle-jump`` will be generated in the root directory.
```
$ make
```
4. Run the binary file (or double click the .exe on Windows):
```
$ ./doodle-jump
```
<strong>Note: If you encounter any problems on Windows trying to run ``doodle-jump.exe``, make sure to put the .dll in the same directory as the ``doodle-jump.exe``.
You can find the .dll files in the official SFML ``bin`` folder.</strong>

## Acknowledgements

-   <strong>SFML</strong>: Simple and Fast Multimedia Library ([https://www.sfml-dev.org/](https://www.sfml-dev.org/))
-   <strong>Doodle Jump</strong>: Original game developed by Lima Sky ([http://www.limasky.com/](http://www.limasky.com/))
