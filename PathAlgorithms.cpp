#include "PathAlgorithms.h"



// Brute force
void BacktrackPathHelper(std::vector<std::vector<Node>>& g, int sx, int sy, int x, int y, sf::RenderWindow& w, bool& done, std::vector<std::vector <bool>>v) {
	if (g[x][y].end == 1) {
		done = 1;
		return;
	}

	v[x][y] = 1;


	std::vector<int> direction = { 1,2,3,4 };								// 1 up, 2 right, 3 down, 4 left


	g[x][y].exp = 1;
	DrawGrid(w);
	while (!direction.empty() && !done) {
		int ran = rand() % direction.size();

		if (direction[ran] == 1) {
			if (x - 1 > 0 && !grid[x - 1][y].wall && !v[x-1][y]) {
				BacktrackPathHelper(g, 1, 1, x - 1, y, w, done,v);
			}
		}
		else if (direction[ran] == 2) {
			if (y + 1 < columns - 1 && !grid[x][y + 1].wall && !v[x][y+1]) {
				BacktrackPathHelper(g, 1, 1, x, y + 1, w, done,v);
			}
		}
		else if (direction[ran] == 3) {
			if (x + 1 < rows - 1 && !grid[x + 1][y].wall && !v[x+1][y]) {
				BacktrackPathHelper(g, 1, 1, x + 1, y, w, done,v);
			}
		}
		else {
			if (y - 1 > 0 && !grid[x][y - 1].wall && !v[x][y-1]) {
				BacktrackPathHelper(g, 1, 1, x, y - 1, w, done,v);
			}
		}
			if (done) {
				g[x][y].path = 1;
			}
			direction.erase(direction.begin() + ran);

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



// A*
// custom comparator for priority queue
class Compare {
public:
	// Comparison operator for sorting in ascending order by fcost
	bool operator()(const std::pair<int, int>& p1, const std::pair<int, int>& p2) const {
		return grid[p1.first][p1.second].fcost > grid[p2.first][p2.second].fcost;
	}
};

void AStarHelp(std::vector<std::vector<Node>>& g,std::priority_queue< std::pair<int, int>, std::vector<std::pair<int, int>>, Compare> &pq, int x, int y, int cx, int cy) {
	if (!(x > 0 && y < columns - 1 && x < rows - 1 && y > 0) || g[x][y].wall || g[x][y].exp ) {
		return;
	}

	g[x][y].hex = 1;
	if (g[x][y].gcost == 0) {
		g[x][y].gcost = g[cx][cy].gcost + 10;
	g[x][y].fcost = g[x][y].hcost + g[x][y].gcost;
			pq.push({ x,y });
	}
	else {
		if (g[cx][cy].gcost + 10 < g[x][y].gcost) {
			g[x][y].gcost = g[cx][cy].gcost + 10;
			g[x][y].fcost = g[x][y].hcost + g[x][y].gcost;
		}
	}
	g[x][y].parent = &g[cx][cy];
}

void printpq(std::priority_queue< std::pair<int, int>, std::vector<std::pair<int, int>>, Compare> pq) {
	std::cout << "pq: ";
	while (!pq.empty()) {
		std::cout << grid[pq.top().first][pq.top().second].fcost << ' ';
		pq.pop();
	}
	std::cout << "\n";
}

void AStar(std::vector<std::vector<Node>>& g, sf::RenderWindow& w, int spx, int spy,int epx,int epy) {
	//priority queue for smallest fcost
	std::priority_queue< std::pair<int, int>, std::vector<std::pair<int,int>> , Compare> pq;
	bool done = 0;


	// calculate hcost for each non wall node
	for (int i = 1; i < rows-1; i++) {
		for (int j = 1; j < columns - 1; j++) {
			if (!g[i][j].wall) {
			g[i][j].hcost = std::min(abs(epx - i), abs(epy - j)) * 14 + (std::max(abs(epx - i), abs(epy - j)) - std::min(abs(epx - i), abs(epy - j))) * 10;
		
			//	g[i][j].hcost = std::sqrt((epx - i) * (epx - i) + (epy - j) * (epy - j));
			}
		}
	}





	int cx = spx;
	int cy = spy;
	while (!done) {
		if (g[cx][cy].end) {
			done = 1;
			break;
		}

		// push adjacent cells into pq
		// up right down left
		
		AStarHelp(g, pq, cx-1, cy, cx , cy);
		AStarHelp(g, pq, cx, cy+1, cx, cy);
		AStarHelp(g, pq, cx+1, cy, cx, cy);
		AStarHelp(g, pq, cx, cy-1, cx, cy);
		


	//	printpq(pq);
		DrawGrid(w);
		cx = pq.top().first;
		cy = pq.top().second;
		pq.pop();
		g[cx][cy].exp = 1;
		
	}

	Node* temp = &g[cx][cy];
	while (temp->start == 0) {
		temp->path = 1;
		temp = temp->parent;
	}





}