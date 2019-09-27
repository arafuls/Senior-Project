# Senior-Project
The code portion of my submission for CMPS 450 Senior Project at Ramapo College.

## Installation Guide
Installing this program is fairly simple but will require you to download some dynamic-link library files from the SFML website which can be found at https://www.sfml-dev.org/download.php.

The files you will need are listed below and should be kept with the program’s executable file.
* sfml-audio-2.dll
* sfml-audio-d-2.dll
* sfml-graphics-2.dll
* sfml-graphics-d-2.dll
* sfml-network-2.dll
* sfml-network-d-2.dll
* sfml-system-2.dll
* sfml-system-d-2.dll
* sfml-window-2.dll
* sfml-window-d-2.dll

You will now need to download the Config, Fonts, and Resources folder from my GitHub <https://github.com/arafuls>. Once you have done that, place them in the same folder with the game executable.

Once you have completed that, we are almost done! You will now need to create a world file called “Test-Save.slmp” that contains the following text. Feel free to rename the texture file if you are using your own.

10 10
100
1
Resources/Images/World/textures1.png

These values and their meaning will be better explained in greater detail later on in this document.

## Outline
The primary feature of concern for this program was the graphical user interface. Thankfully, instead of writing the graphics equivalent of assembly which is writing OpenGL code from scratch, SFML managed to pull through. A great API for creating games and other multimedia applications. It is also cross-platform and works great for desktop applications, which it will be used for in this project. It provides very complex features such as sprites and window rendering, which would take forever to write in OpenGL, and makes it a couple of trivial statements instead.

A game engine is typically very complex tools but nothing ever starts out complex. Being that this is just a senior project and a one-man job done in a relatively short amount of time, it is easy to describe this game engine in only a few words. 

The SFML Game/Engine is a Windows-oriented 2D game engine and game aimed at being user friendly. It provides a rudimentary set of simple tools that allow users to create simple maps for the game while also provided the client to play them. It is created using C++ and the assistance of the SFML library, which you can read more about at https://www.sfml-dev.org/index.php.

For a more in-depth view of the SFML Game Engine, you are encouraged to read this documentation further.

## The End-User
When within the main menu and settings state, all you can do is click on buttons. No other inputs are to be recognized by the program.

When within the game state, you can use the following keybindings accordingly by default unless a configuration file has been changed:
•	W: Moves the player sprite up.
•	A: Moves the player sprite left.
•	S: Moves the player sprite down.
•	D: Moves the player sprite right.
•	Escape: Toggles the pause menu.

When within the editor state, you can use the following keybindings accordingly by default unless a configuration file has been changed:
•	Left Mouse Button: Selects a texture from the texture menu or paints the selected tile with the most recently selected texture if the tile is not already painted.
•	Right Mouse Button: Removes a texture from an already painted tile if selected.
•	Escape: Toggles the pause menu.
