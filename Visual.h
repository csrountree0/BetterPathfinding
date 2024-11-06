#ifndef VISUAL_H
#define VISUAL_H
#include <sfml/Graphics.hpp>
#include <sfml/Audio.hpp>
#include <iostream>
#include "Node.h"

extern int rows, columns;
extern sf::RectangleShape rect;
extern std::vector<std::vector<Node>> grid;
extern bool mazegen;

void MainWindowLoop();			// runs the main window that everything will be displayed on
void DrawGrid(sf::RenderWindow& w);				// Draws the grid




#endif // !VISUAL_H
