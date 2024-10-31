#include "Visual.h"




int rows = 10, columns = 10;
sf::RectangleShape rect;


void DrawGrid(sf::RenderWindow& w) {												// Draw the grid
	rect.setPosition(0, 0);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			w.draw(rect);
			rect.move(rect.getSize().x,0);
		}
		rect.setPosition(0,rect.getPosition().y + rect.getSize().y);
	}
}








void MainWindowLoop() {
	
	sf::RenderWindow window(sf::VideoMode(800, 800), "Pathfinding");				// Create the window
	sf::Event ev;																	// Create event object
	
	// Edit elements of the rectangle
	rect.setFillColor(sf::Color::White);
	rect.setSize(sf::Vector2f(800 / rows, 800 / columns));
	rect.setOutlineThickness(1);
	rect.setOutlineColor(sf::Color::Black);
	//--------------------------------


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