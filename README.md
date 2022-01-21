# SnakeAndLadderGame
Snake and ladder built with c++ builder
There are 3 main classes that I used to create this game: Board, Grid2D and Player
The aim was to practice certain concepts of OOP.

The board class is a completely static class as such no Board object has to be instantiated to use its members.
The board portrays the snakes and ladders with std::maps as well as the coordinates of each square with 
two static array[10] of doubles. It also keeps track of the occupiedPositions that will be used to implement
the pushback mechanic when a player lands on another player.

The Grid2D class handles the conversion of the integer grid position to the coordinates given by the Board.
Honestly could have been part of the Player class itself.

The Player class is transparent to the coordinates and just deals with integer grid positions. EXCEPT for the playerImage.
This is not good.

main.cpp and main.h are legacy files from before when I wrote the code in VS, and I just decided to keep it as separate files
for practice of linking files.

Unit1.cpp is the file with the running code.
