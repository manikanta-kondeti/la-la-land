# la-la-land
This repository has source code written in C++. It contains a game developed using glut, openGL. 
![alt tag](https://s28.postimg.org/gis792eh9/imageedit_3_5679531462.png)

## About Game :
- The character in the game is named as Mike. 
- Objective for Mike is, he has to collect coins within less time.
- The Game has three levels.
- Level 2 & 3: has blocks on tiles 


## How to run?

###Requirements :

Linux: 
Make sure glut libraries are installed or 
* sudo apt-get install freeglut3 freeglut3-dev

###Commands :
+ make 
+ ./output 

Mac(change the versions in the g++ command accordingly): 
brew install freeglut
brew install --cask xquartz
open -a XQuartz
 export DISPLAY=:0.0
g++ -Wall -o output Main.cpp imageloader.cpp -I/opt/homebrew/Cellar/freeglut/3.4.0/include -L/opt/homebrew/Cellar/freeglut/3.4.0/lib/ -lglut -framework OpenGL 
./output


## Instructions:


* j - jump 
* h - Camera wrt Mike
* x - Camera wrt 1st tile
* Press 4 & d - Move camera  
* Press 4 & w - Move camera 
* Press 4 & a - Move camera 
* press 4 & s - Move camera
* n - Camera from Mikes behind
* Esc - Kill the game 
