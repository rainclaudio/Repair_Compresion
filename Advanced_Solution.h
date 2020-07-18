#pragma once
#include <vector>
#include <map>
#include "DoublyLinkedLists.h"
#include "Max_heap.h"

typedef std::pair<int, std::pair<Node*, Node*>> MyPair;

typedef std::pair<int,int> IntPair;

typedef std::pair<IntPair, Node*> PairWithDir;

typedef std::map<IntPair, MyPair> MyMap;

class Advanced_Solution
{
private:
	int o;
	Max_heap* heap;
	DoublyLinkedLists* doubly_list;
	void frequencyAndNode(MyMap& map_frequency);
	//void fill_pointers(std::map<std::pair<int, int>, MyPair>& map_frequency);
	void change_List(IntPair, MyMap&, Max_heap*);
	bool wasInMap(PairWithDir*,MyMap&);
	void mod_First_oc_map(PairWithDir*,MyMap&);
public:
	Advanced_Solution(int o);
	~Advanced_Solution();
	void add_Sequence(std::vector<int> values);
	void re_Pair_Advanced();
};
