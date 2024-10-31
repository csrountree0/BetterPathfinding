#include "Visual.h"
#include "MazeAlgorithms.h"



int rows = 19, columns = 19;
sf::RectangleShape rect;
std::vector<std::vector<Node>> grid(rows);

void DrawGrid(sf::RenderWindow& w) {												// Draw the grid
	rect.setPosition(0, 0);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {

			// change rect color based on what it represents
			if (grid[i][j].wall) {
				rect.setFillColor(sf::Color::Black);
			}
			else if (grid[i][j].start) {
				rect.setFillColor(sf::Color::Red);
			}
			else if (grid[i][j].end) {
				rect.setFillColor(sf::Color::Green);
			}
			else {
				rect.setFillColor(sf::Color::White);
			}

			w.draw(rect);
			rect.move(rect.getSize().x,0);
		}
		rect.setPosition(0,rect.getPosition().y + rect.getSize().y);
	}
}


void MainWindowLoop() {
	// initialize the grid with nodes
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			grid[i].emplace_back();
		}
	}


	sf::RenderWindow window(sf::VideoMode(800, 800), "Pathfinding");				// Create the window
	sf::Event ev;																	// Create event object
	
	// Edit elements of the rectangle
	rect.setFillColor(sf::Color::White);
	rect.setSize(sf::Vector2f(800 / rows, 800 / columns));
	rect.setOutlineThickness(1);
	rect.setOutlineColor(sf::Color::Black);
	//--------------------------------

	bruteMaze(grid);
	
	while (window.isOpen()) {														// Loop the window until it's closed
		while (window.pollEvent(ev)) {
			if (ev.type == sf::Event::Closed) {
				window.close();
			}

		}

		window.clear(sf::Color::Black);

		DrawGrid(window);





		window.display();
	}
}