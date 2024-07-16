<p align="center">
 <img  src="https://i.ibb.co/jG0PmCK/head3.png" width=250 height=250>
</p>

<h1 align="center">🧈 Bon Beurre Man 🧈</h1>
<h3 align="center"> Engine/Game Prototype </h3>
<p align="center">
   <a href="https://fr.wikipedia.org/wiki/C%2B%2B"> 
        <img src="https://img.shields.io/badge/C++17-%204--2--1?style=for-the-badge&label=language&color=blue">
    </a>
    <a href="https://www.sfml-dev.org/download/sfml/2.6.1/"> 
        <img src="https://img.shields.io/badge/2--6--1-Godot%204--2--1?style=for-the-badge&logo=sfml&logoColor=white&label=SFML%20version&color=GREEn">
    </a>
  
</p>

<p align="center">
        <img src="https://i.ibb.co/dQgwmYD/bonber-ezgif-com-resize-2.gif">
</p>


## Overview
This project is an Engine/Network Game prototype made in C++ and [SFML](https://www.sfml-dev.org/index.php)

Its based on the famous Bomberman game except here you play farmer that fight into barns and make butter explode on the face of each other ! You can play on local/remote multiplayer

all maps of the game was made using my [TileMapperLite](https://github.com/Amealky/TileMapperLite) software

## Run it
The github file already provide the ``.exe`` and a ``binary linux file`` just double click on the file regarding your OS

You can also open a terminal and run ``make run`` at the root of the project


## How to play
Z/Q/S/D or Arrow -> Move

B -> Put Butter Bomb where you stand

Enter/Escape/Arrows -> Navigate into menu

The rule are simple, since its based on [Bomberman](https://fr.wikipedia.org/wiki/Bomberman). You have to use butter bomb to make your path into the map and kill all the opponents. Sometime ``milk`` appear on the map you can drink it by walking on it to enhance you explosion size.


## Build the project
If you want to build the project you can follow the steps below :

- Ensure you have ``GCC`` installed
- ( For ``Windows`` users install ``MinGw`` )
- Download [SFML-2.6.1](https://www.sfml-dev.org/download/sfml/2.6.1/)
- Open the Makefile and set the var ``SFML_FOLDER`` at the path where your SFML folder is
- And then just run ``make compile`` (`` MinGw32-make compile``  for windows users ) command this will replace the binary in the output folder that match your OS
- Then you can launch the app or run ``make run``  


Note : Build with G++11.4.0 using SFML-2.6.1

