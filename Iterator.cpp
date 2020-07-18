#include "Iterator.h"
#include <iostream>
//
Iterator::Iterator(Node* iter_prin, Node* iter_fin)
{
	this->iter_prin = iter_prin;
	this->iter_fin = iter_fin;
}

Iterator::~Iterator(){// EN Construcción
	//delete  iter_prin;
	//delete 	iter_fin;
}

bool Iterator::hasNext()
{
	if (iter_prin == iter_fin) return false;
	return true;
}

int Iterator::current() {
	return iter_prin->value;
}

int Iterator::next()
{
	if (hasNext()) {
		iter_prin = iter_prin->next;
		return iter_prin->value;
	}
	else return iter_prin->value;

}

void Iterator::reset(Node* curr, Node* end)
{
	iter_prin = curr;
	iter_fin = end;
}

std::pair<int, Node*> Iterator::current_Node()
{
	return std::make_pair(iter_prin->value, iter_prin);
}

std::pair<int, Node*> Iterator::next_Node()
{
	if (hasNext()) {
		iter_prin = iter_prin->next;
		return std::make_pair(iter_prin->value,iter_prin);
	}
	else return std::make_pair(iter_prin->value, iter_prin);
}
