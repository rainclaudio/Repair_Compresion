#pragma once
#include <utility>
#include "Iterator.h"

//delete
class Iterator;

struct Node {
	int value;
	Node* prev;
	Node* next;
	Node* previous_oc;
	Node* next_oc;
};
typedef std::pair<int, int> IntPair;

typedef std::pair<IntPair, Node*> PairWithDir;

class DoublyLinkedLists
{
private:
	Node* head;
	Node* tail;
	int tam;
public:
	DoublyLinkedLists();
	~DoublyLinkedLists();
	void insert(int value);
	PairWithDir* change_And_Get_Info(Node** curr, int o);
	PairWithDir* initCollector();
	void remove();
	int at(int pos);
	int size();
	void printList();
	bool isEmpty();
	Iterator begin();
};
