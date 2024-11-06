#include "PathAlgorithms.h"




void BacktrackPathHelper(std::vector<std::vector<Node>>& g, int sx, int sy, int x, int y, sf::RenderWindow& w, bool& done, std::vector<std::vector <bool>>v) {
	if (g[x][y].end == 1) {
		done = 1;
		return;
	}

	v[x][y] = 1;


	std::vector<int> direction = { 1,2,3,4 };
	// 1 up, 2 right, 3 down, 4 left


	g[x][y].exp = 1;
	DrawGrid(w);
	while (!direction.empty() && !done) {
		int ran = rand() % direction.size();
		if (direction[ran] == 1) {
			if (x - 1 > 0 && !grid[x - 1][y].wall && !v[x-1][y]) {
				BacktrackPathHelper(g, 1, 1, x - 1, y, w, done,v);
			}
			direction.erase(direction.begin() + ran);
			if (!done) {
				continue;
			}
			else {
				g[x][y].path = 1;

			}

		}
		else if (direction[ran] == 2) {
			if (y + 1 < columns - 1 && !grid[x][y + 1].wall && !v[x][y+1]) {
				BacktrackPathHelper(g, 1, 1, x, y + 1, w, done,v);

			}
			direction.erase(direction.begin() + ran);
			if (!done) {
				continue;
			}
			else {
				g[x][y].path = 1;

			}

		}
		else if (direction[ran] == 3) {
			if (x + 1 < rows - 1 && !grid[x + 1][y].wall && !v[x+1][y]) {
				BacktrackPathHelper(g, 1, 1, x + 1, y, w, done,v);

			}
			direction.erase(direction.begin() + ran);
			if (!done) {
				continue;
			}
			else {
				g[x][y].path = 1;

			}

		}
		else {
			if (y - 1 > 0 && !grid[x][y - 1].wall && !v[x][y-1]) {
				BacktrackPathHelper(g, 1, 1, x, y - 1, w, done,v);

			}
			direction.erase(direction.begin() + ran);
			if (!done) {
				continue;
			}
			else {
				g[x][y].path = 1;

			}

		}

	}

}






void BackTrackingPath(std::vector<std::vector<Node>>& g, sf::RenderWindow& w) {
	std::vector<std::vector<bool>> v(rows);
	bool d=0;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			if (i == 0 || i == rows - 1 || j == 0 || j == columns - 1) {
				v[i].push_back(1);

			}
			else {
				v[i].push_back(0);

			}

		}
	}
	BacktrackPathHelper(g, 1, 1, 1, 1, w, d, v);




}