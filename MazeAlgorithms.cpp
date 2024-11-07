#include "MazeAlgorithms.h"
#include "Visual.h"

//#include <algorithm>

// Randomly place walls around every other node
void BruteMaze(std::vector<std::vector<Node>>& grid,sf::RenderWindow& w) {


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
				DrawGrid(w);
			}
		}
	}
}


void BacktrackHelper(std::vector<std::vector<Node>>& grid, std::vector<std::vector<bool>>& v, int sx, int sy, int x, int y,sf::RenderWindow& w) {
	v[x][y] = 1;
	std::vector<int> direction = { 1,2,3,4 };
	bool done = 0;
	// 1 up, 2 right, 3 down, 4 left

	while (!direction.empty()) {
		int ran = rand() % direction.size();
	if (direction[ran] == 1) {
		if (x - 2 > 0 && !v[x-2][y]) {
			v[x-1][y] = 1;
			grid[x - 1][y].wall = 0;
			grid[x - 2][y].end = 1;
			DrawGrid(w);
			grid[x - 2][y].end = 0;
			BacktrackHelper(grid, v, sx, sy, x - 2, y, w);
		//	break;
		}
	}
	else if (direction[ran] == 2) {
		if (y+2 < columns-1 && !v[x][y+2]) {
			v[x][y+1] = 1;
			grid[x][y+1].wall = 0;

			grid[x][y+2].end = 1;
			DrawGrid(w);
			grid[x][y+2].end = 0;
			BacktrackHelper(grid, v, sx, sy, x, y+2, w);
			//break;
		}
	}
	else if (direction[ran] == 3) {
		if (x + 2 < rows-1 && !v[x + 2][y]) {
			v[x + 1][y] = 1;
			grid[x + 1][y].wall = 0;

			grid[x+2][y].end = 1;
			DrawGrid(w);
			grid[x+2][y].end = 0;
			BacktrackHelper(grid, v, sx, sy, x + 2, y, w);
			//break;
		}
	
	}
	else {
		if (y - 2 >0 && !v[x][y - 2]) {
			v[x][y - 1] = 1;
			grid[x][y - 1].wall = 0;

			grid[x][y - 2].end = 1;
			DrawGrid(w);
			grid[x][y - 2].end = 0;
			BacktrackHelper(grid, v, sx, sy, x, y - 2,w);
		//	break;
		}
		
	}
			direction.erase(direction.begin() + ran);
	}
	return;

}
void BacktrackingMaze(std::vector<std::vector<Node>>& grid, sf::RenderWindow& w) {
	std::vector<std::vector<bool>> visited(rows);
	// outline the grid with walls
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			if (i == 0 || i == rows - 1 || j == 0 || j == columns - 1) {
				grid[i][j].wall = 1;
				visited[i].push_back(1);
				
			}
			else if ((!(j % 2) || !(i % 2))) {
				grid[i][j].wall = 1; 
				visited[i].push_back(0);
			}
			else {
				visited[i].push_back(0);

			}

		}
	}


	int sx = rand() % (rows - 2);
	sx = !(sx % 2) ? sx + 1 : sx;
	int sy = rand() % (columns - 2);
	sy = !(sy % 2) ? sy + 1 : sy;
	BacktrackHelper(grid, visited, sx, sy, sx, sy,w);

}



// Prims
bool comp(std::pair<int,int>&a, std::pair<int,int>&b) {
	if (a.first == b.first) {
		return a.second < b.second;
	}
	else {
		return a.first < b.first;
	}
}
void RemoveWall(int x, int y, std::vector<std::pair<int, int>>& w) {
	sort(w.begin(), w.end(), comp);
	int l = 0, m = 0, r = w.size() - 1;

	while (l <= r) {

		m = (l+r)/2;
		if (w[m].first == x && w[m].second == y) {
		//	std::cout << "wall at " << x << " " << y << " has been erased\n";
			w.erase(w.begin() + m);
			return;
		}
		else if (w[m].first == x) {
			if (w[m].second > y) {
				r = m-1;
			}
			else {
				l = m+1;
			}
		}
		else {
			if (w[m].first > x) {
				r = m-1;
			}
			else {
				l = m+1;
			}
		}
		
	}


	//std::cout << "No wall to erase\n";
}
// Kruskals
std::pair<Node*, Node*> SameParent(Node* n1, Node* n2) {
	while (n1->kparent != NULL) {
		n1 = n1->kparent;
	}
	while (n2->kparent != NULL) {
		n2 = n2->kparent;
	}
	return { n1,n2 };
}
void KruskalsMaze(std::vector<std::vector<Node>>& g, sf::RenderWindow &w) {


	std::vector<std::pair<int, int>> walls;

		// outline the grid with walls
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns; j++) {
				if (i == 0 || i == rows - 1 || j == 0 || j == columns - 1) {
					g[i][j].wall = 1;
					//walls.push_back({ i,j });
				}
				else if ((!(j % 2) || !(i % 2))) {
					g[i][j].wall = 1;
				//	walls.push_back({ i,j });

					if (!(i % 2 == 0 && j % 2 == 0)) {
						walls.push_back({ i,j });
					}


				}

			}
		}
		// pick a random wall and see if the two open nodes are of the same group if so remove wall from list other wise make it a path and do until no more walls
		while (!walls.empty()) {
			int ran = rand() % walls.size();
			int wx = walls[ran].first;
			int wy = walls[ran].second;

			if (rand() % 2) {														// up down
				if (!(wx < 2 || wx > rows - 2) && (!g[wx+1][wy].wall && !g[wx-1][wy].wall)) {
					std::pair<Node*, Node*> parents = SameParent(&g[wx + 1][wy],& g[wx - 1][wy]);
					if (parents.first == parents.second) {
						RemoveWall(wx, wy, walls);
					}
					else {
						g[wx][wy].wall = 0;
						DrawGrid(w);
						parents.first->kparent = parents.second;
						RemoveWall(wx, wy, walls);
					}
				}
		


			}
			else {																	// left right
				if (!(wy < 2 || wy > columns - 2) && (!g[wx][wy+1].wall && !g[wx][wy-1].wall)) {
					std::pair<Node*, Node*> parents = SameParent(&g[wx][wy+1], &g[wx][wy-1]);
					if (parents.first == parents.second) {
					//	std::cout << "ran\n";
						RemoveWall(wx, wy, walls);
					}
					else {
						g[wx][wy].wall = 0;
						DrawGrid(w);
						RemoveWall(wx, wy, walls);
						parents.first->kparent = parents.second;
				//		std::cout << "left wall becomes head\n\n";
					}
				}


				
			}
		//	break;

		}



		

}




