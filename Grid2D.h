#ifndef GRID_2D_H
#define GRID_2D_H
#include <array>
#include <fmx.h>
class Grid2D
{
private:
	int m_gridPosition{ 0 };		// start at 0, signifying out of board. ranges from 1-100.
	std::array<double, 2> m_coords{};
public:
	Grid2D() = default;

	void convertGridToRowColumnOut(int grid, int& rowOut, int& columnOut);
	void advance(int stepsToTake);

	const std::array<double, 2> getPosition() const { return m_coords; }

    void resetPosition(double x, double y, int grid);
	const int getGrid() const{ return m_gridPosition; }
};
#endif // !GRID_2D_H

