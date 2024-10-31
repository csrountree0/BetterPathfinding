#include "MazeAlgorithms.h"
#include "Visual.h"
#include <cstdlib>
#include <ctime>


// Randomly place walls around every other node
void bruteMaze(std::vector<std::vector<Node>>& grid) {
	srand(time(0));


	// outline the grid with walls
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			if (i == 0 || i == rows - 1 || j == 0 || j == columns - 1) {
				grid[i][j].wall = 1;
			}
			
		}
	}



	for (int i = 2; i < rows - 2; i++) {
		for (int j = 2; j < columns - 2; j++) {
			if (!(j % 2) && !(i % 2)) {
				grid[i][j].wall = 1;
				if (rand() % 4 == 0) {
					grid[i][j - 1].wall = 1;
				}
				else if (rand() % 4 == 1) {
					grid[i+1][j].wall = 1;
				}
				else if (rand() % 4 == 2) {
					grid[i][j+1].wall = 1;
				}
				else {
					grid[i-1][j].wall = 1;
				}
			}
		}
	}
}

void KruskalMaze(std::vector<std::vector<Node>>& grid) {

}