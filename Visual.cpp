#include "Visual.h"


void MainWindowLoop() {
	sf::RenderWindow window(sf::VideoMode(800, 800), "Sort");
	sf::Event ev;

	while (window.isOpen()) {
		while (window.pollEvent(ev)) {
			if (ev.type == sf::Event::Closed) {
				window.close();
			}

		}




		window.clear(sf::Color::Black);



		window.display();






	}
}