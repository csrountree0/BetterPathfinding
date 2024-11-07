/*
			This file contains all the algorithms that will be used for pathfinding
*/


#ifndef ALGORITHMS_H
#define ALOGRITHMS_H
#include "Visual.h"
#include <queue>
void BackTrackingPath(std::vector<std::vector<Node>>& g, sf::RenderWindow& w);
void AStar(std::vector<std::vector<Node>>& g, sf::RenderWindow& w, int spx, int spy, int epx, int epy);






#endif