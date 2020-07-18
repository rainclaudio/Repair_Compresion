#pragma once
#include "DoublyLinkedLists.h"
#include <utility>
//delete
struct Node;

class Iterator
{
private:
	Node* iter_prin;
	Node* iter_fin;
public:
	Iterator(Node* iter_prin, Node* inter_fin);
	~Iterator();
	bool hasNext();
	int current();
	int next();
	void reset(Node* curr, Node* end);
	std::pair<int,Node*> current_Node();
	std::pair<int,Node*> next_Node();
};
