#ifndef BOARD_H
#define BOARD_H
#include <map>
class Board
{
	static inline std::map<int, int> Snakes{
	{ 21, 15 },
	{ 23, 6 },
	{ 29, 15 },
	{ 35, 18 },
	{ 47, 32 },
	{ 52, 38 },
	{ 71, 34 },
	{ 82, 59 },
	{ 95, 78 },
	{ 99, 79 },
	};

	static inline std::map<int, int> Ladders{
	{ 2, 18 },
	{ 11, 31 },
	{ 12, 28 },
	{ 22, 40 },
	{ 36, 62 },
	{ 41, 59 },
	{ 46, 55 },
	{ 70, 94 },
	{ 77, 84 },
	{ 85, 97 },
	};
public:

	static const int returnGrid(int currentGrid);
	static const int searchDictionaries(int numToFind);

	static inline double horizontalCoords[10]
	{
		3, 56.7, 110.4, 164.1, 217.8, 271.5, 325.2, 378.9, 432.6, 486.3
	};
	static inline double verticalCoords[10]
	{
		488.7, 435, 381.3, 327.6, 273.9, 220.2, 166.5, 112.8, 59.1, 5.4
	};
	static inline std::map<int, int> occupiedPositions {
		// key is PlayerID, value is m_gridPosition
		{0, 0},
		{1, 0},
		{2, 0},
		{3, 0},
	};
};
#endif // !BOARD_H

