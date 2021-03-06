#ifndef BOARD_H
#define BOARD_H
#include <map>
#include <vector>
#include <array>
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

	static inline std::map<int, int> KeyToIndexSnakes{
	{21, 0},
	{23, 1},
	{29, 2},
	{35, 3},
	{47, 4},
	{52, 5},
	{71, 6},
	{82, 7},
	{95, 8},
	{99, 9},
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
	// std::vector of std::vector of array of 2 doubles representing coordinates
	// of Snakes for animation waypoints.
	static inline std::vector<std::vector<std::array<double, 2>>> SnakesCoords {
		{ {3, 381.3}, {3, 478}, {91, 462}, {139, 510}, {195, 470}, {171, 414}, {211, 374}, {271.5, 435} },
		{ {110.4, 381.3}, {155, 374}, {195, 406}, {235, 406}, {235, 446}, {203, 486}, {235, 502}, {271.5, 488.7} },
		{ {432.6, 381.3}, {395, 350}, {371, 382}, {323, 382}, {315, 430}, {347, 462}, {315, 478}, {271.5, 435} },
		{ {271.5, 327.6}, {243, 278}, {211, 294}, {155, 278}, {155, 334}, {99, 326}, {83, 374}, {64, 408}, {110.4, 435} },
		{ {325.2, 273.9}, {379, 222}, {419, 270}, {467, 270}, {499, 310}, {467, 334}, {432.6, 327.6} },
		{ {432.6, 220.2}, {411, 158}, {347, 158}, {299, 118}, {259, 206}, {179, 166}, {139, 230}, {91, 286}, {110.4, 327.6} },
		{ {486.3, 112.8}, {427, 78}, {395, 150}, {331, 166}, {315, 238}, {379, 262}, {387, 326}, {325.2, 327.6} },
		{ {56.7, 59.1}, {91, 86}, {83, 126}, {115, 158}, {83, 182}, {35, 182}, {27, 222}, {56.7, 220.2} },
		{ {271.5, 5.4}, {299, 38}, {283, 70}, {275, 110}, {219, 102}, {219, 158}, {171, 150}, {131, 158}, {110.4, 112.8} },
		{ {56.7, 5.4}, {11, 22}, {19, 62}, {0, 102}, {24, 126}, {56.7, 112.8} },
	};

	static inline std::map<int, int> occupiedPositions {
		// key is PlayerID, value is m_gridPosition
		{0, 0},
		{1, 0},
		{2, 0},
		{3, 0},
	};
	// A way for the board to convey the index of the Snake/Ladder to Unit1.cpp
	struct JustSteppedOn{
		bool snake{};
		int index{};
	};
	static inline JustSteppedOn steppedOnInfo{false, 0};
};
#endif // !BOARD_H

