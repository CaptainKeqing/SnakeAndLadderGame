#include "Board.h"
#include "Grid2D.h"

// experimenting with Out parameters
void Grid2D::convertGridToRowColumnOut(int grid, int& rowOut, int& columnOut){
	if (grid % 10 == 0) {
		rowOut = grid / 10 - 1;
		columnOut = (rowOut % 2 == 0 ? 9 : 0);
	}
	else {
		rowOut = grid / 10;
		// check even or odd row
		if (rowOut % 2 == 0) {
			columnOut = grid % 10 - 1;
		}
		else {
			columnOut = 10 - grid % 10;
			}
	}
}
void Grid2D::advance(int stepsToTake) {
	if (m_gridPosition + stepsToTake > 100)
	{
		int exceededBy{ m_gridPosition + stepsToTake - 100 };
//		std::cout << "Exceed end by " << exceededBy << '\n';
		m_gridPosition = 100 - exceededBy - stepsToTake;		// -stepsToTake cause im adding stepsToTake after this block
	}
	m_gridPosition += stepsToTake;	// guaranteed not to exceed 100

	int newGrid{ Board::returnGrid(m_gridPosition) };
	if (newGrid != m_gridPosition) {
//		std::cout << "Walking to position " << m_gridPosition << "... ";
//		std::cout << (newGrid < m_gridPosition ? "You stepped on a snake!" : "You reached a ladder :)") << '\n';
		m_gridPosition = newGrid;
	}

	int rowIndex{};
	int columnIndex{};
	convertGridToRowColumnOut(m_gridPosition, rowIndex, columnIndex);
	m_coords[0] = Board::horizontalCoords[columnIndex];
	m_coords[1] = Board::verticalCoords[rowIndex];
}

void Grid2D::resetPosition(double x, double y, int grid){
    m_gridPosition = grid;
	m_coords[0] = x;
	m_coords[1] = y;
}
