#ifndef NODE_H
#define NODE_H
// Node structure which will hold every nodes parent node, explored, gcosts, hcost
struct Node
{
	// point to parent node
	Node* parent;
	
	

	bool wall;						//	is wall
	bool start;						//	is start
	bool end;						//	is end
	bool exp;						//	is explored
	bool hex;						//	has been considered for next move
	bool empty;						//	is none of the above
	bool path;


	// for Kruskals
	Node* kparent;


	// for A*
	int gcost = 0;					// movement cost
	int hcost = 0;					// heuristic
	int fcost = 0;					// g+h
};



#endif