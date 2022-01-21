#include "PlayerClass.h"
#include <string>
#include <iostream>
#include "Board.h"

Player::Player(const std::string& name) : m_name{ name }, hasWon{ false }
{
	playerID = playerCount++;
}

void Player::move(int steps) {

	myPosition.advance(steps);

	// moving the image
	playerImage->Position->X = getPos()[0];
	playerImage->Position->Y = getPos()[1];

	std::cout << m_name << " is now at " << myPosition.getGrid() << '\n' <<'\n';

	if (myPosition.getGrid() == 100)
	{
		hasWon = true;
	}
}


void Player::resetPos(double x, double y, int grid){
	myPosition.resetPosition(x, y, grid);
	playerImage->Position->X = x;
	playerImage->Position->Y = y;
}
