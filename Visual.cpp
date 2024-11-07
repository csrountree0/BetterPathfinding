#include "Visual.h"
#include "MazeAlgorithms.h"
#include "PathAlgorithms.h"


int rows =59, columns = 59;
sf::RectangleShape rect;
std::vector<std::vector<Node>> grid(rows);
bool mazegen = 0;
bool done = 0;

void DrawGrid(sf::RenderWindow& w) {	
	// Draw the grid
	w.clear(sf::Color::Black);
	rect.setPosition(0, 0);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {

			// change rect color based on what it represents
			if (grid[i][j].wall) {
			//	rect.setFillColor(sf::Color(16, 16, 16));
				rect.setFillColor(sf::Color::Black);
			}
			else if (grid[i][j].start) {
				rect.setFillColor(sf::Color::Green);
			}
			else if (grid[i][j].end) {
				rect.setFillColor(sf::Color::Red);
			}
			else if (grid[i][j].path) {
				rect.setFillColor(sf::Color::Yellow);
			}
			else if (grid[i][j].exp) {
				rect.setFillColor(sf::Color::Magenta);
			}
			else if (grid[i][j].hex) {
				rect.setFillColor(sf::Color(sf::Color(64, 64, 64)));
			}
			else {
				rect.setFillColor(sf::Color::White);
			}

			w.draw(rect);
			rect.move(rect.getSize().x,0);
		}
		rect.setPosition(0,rect.getPosition().y + rect.getSize().y);
	}
	w.display();
}


void MainWindowLoop() {
	srand(time(0));

	// initialize the grid with nodes
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			grid[i].emplace_back();
		}
	}


	
	// Edit elements of the rectangle
	rect.setFillColor(sf::Color::White);
	rect.setSize(sf::Vector2f(800.0 / rows, 800.0 / columns));
	rect.setOutlineThickness(1);
	rect.setOutlineColor(sf::Color::Black);
	//--------------------------------

	//BruteMaze(grid);
	//BacktrackingMaze(grid);
	//KruskalMaze(grid,window);
	//PrimsMaze(grid);

	sf::RenderWindow window(sf::VideoMode(800, 800), "Pathfinding");				// Create the window
	sf::Event ev;																	// Create event object
	window.clear(sf::Color::Black);
	while (window.isOpen()) {														// Loop the window until it's closed
		while (window.pollEvent(ev)) {
			if (ev.type == sf::Event::Closed) {
				window.close();
			}
		}

			if (!mazegen) {
				//BruteMaze(grid, window);
			//	BacktrackingMaze(grid,window);
				KruskalsMaze(grid,window);
				mazegen = 1;
				grid[1][1].start = 1;
				grid[rows-2][columns-2].end = 1;
			//	BackTrackingPath(grid, window);
				AStar(grid, window, 1, 1,rows-2,columns-2);
			}

		DrawGrid(window);
	}
}