#ifndef PLAYER_CLASS_H
#define PLAYER_CLASS_H
#include "Grid2D.h"
#include <fmx.h>
#include <string>
#include <vector>
class Player
{
// for convenience i put these 2 as Public so i can access without getters
public:
	TImage* playerImage{ nullptr };
	Grid2D myPosition{};

private:
	int playerID{};

	std::string m_name{};

public:
	Player(const std::string& name = "");
	~Player(){
		if (playerImage){
			delete playerImage;
			playerImage = nullptr;
		}
	}

	static inline int playerCount{ 0 };

	void move(int steps);

    const int getID() const { return playerID; }
	const std::string& getName() const { return m_name; }
	const std::array<double, 2> getPos() const { return myPosition.getPosition(); }
	const int getGrid() const { return myPosition.getGrid(); }

    void resetPos(double x, double y, int grid = 0);

	bool hasWon{};


};
#endif // !PLAYER_CLASS_H
