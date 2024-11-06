
//			This file contains all the algorithms that will be used for maze generation

#ifndef MAZEALGORITHMS_H
#define MAZEALOGRITHMS_H
#include "Visual.h"

void BruteMaze(std::vector<std::vector<Node>>& grid);
void BacktrackingMaze(std::vector<std::vector<Node>>& grid,sf::RenderWindow& w);
void PrimsMaze(std::vector<std::vector<Node>>& grid);
void KruskalsMaze(std::vector<std::vector<Node>>& g,sf::RenderWindow& w);


#endif