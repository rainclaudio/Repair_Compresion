#include "Advanced_Solution.h"
#include <iostream>
#include <vector>
#include <map>
#include <utility>


Advanced_Solution::Advanced_Solution(int o)
{
	this->o = o;
	doubly_list = new DoublyLinkedLists();
}

Advanced_Solution::~Advanced_Solution()
{
}

void Advanced_Solution::frequencyAndNode(MyMap& map_frequency){
	MyPair aux;
	std::pair<int, Node*> next_value, curr_value;
	IntPair pair_values;
	Iterator iter = doubly_list->begin();

	while (iter.hasNext()) {
		curr_value = iter.current_Node();
		next_value = iter.next_Node();
		pair_values = std::make_pair(curr_value.first, next_value.first);
		if (map_frequency.find(pair_values) != map_frequency.end()) {
			aux = map_frequency[pair_values];
			map_frequency[pair_values].first++;
			map_frequency[pair_values].second.second = curr_value.second;
			map_frequency[pair_values].second.second->previous_oc = aux.second.second;
			aux.second.second->next_oc = map_frequency[pair_values].second.second;
		}
		else map_frequency[{curr_value.first, next_value.first}] = MyPair(1, std::make_pair(curr_value.second, curr_value.second));
	}
}


void Advanced_Solution::add_Sequence(std::vector<int> values)
{
	if (values.empty()) return;
	for (size_t i = 0; i < values.size(); i++) doubly_list->insert(values.at(i));
}

void Advanced_Solution::change_List(IntPair value_pair,MyMap& map_frequency,Max_heap* myheap){
	std::pair<int, Node*> curr_value;
	std::pair<int, Node*> next_value;

	PairWithDir* collector;
	Node** iterator = &map_frequency[value_pair].second.first;
	//cambiamos todas las ocurrencias del par por un parámetro sigma
	while(*iterator){
		//Paso1: recolectamos toda la información al realizar el cambio
		collector = doubly_list->change_And_Get_Info(iterator, o+1);//explicada en DoublyLinkedLists.cpp
		PairWithDir *affL = &collector[0];
		PairWithDir *affR = &collector[1];

		PairWithDir *nuevoL = &collector[2];
		PairWithDir *nuevoR = &collector[3];
		std::cout << "iterator: "<<(*iterator) << '\n';
		std::cout << '\n';
		std::cout << "------Pares afectados-----" << '\n';
		std::cout << "aff1: "<<affL->first.first<<' '<<affL->first.second<<" dir: "<<affL->second << '\n';
		std::cout << "aff2: "<<affR->first.first<<' '<<affR->first.second<<" dir: "<<affR->second << '\n';

		std::cout << "nuevo1: "<<nuevoL->first.first<<' '<<nuevoL->first.second<<" dir: "<<nuevoL->second << '\n';
		std::cout << "nuevo2: "<<nuevoR->first.first<<' '<<nuevoR->first.second<<" dir: "<<nuevoR->second << '\n';

  	// hemos conseguido la información de manera exitosa

		//Paso2: atualizaremos la información en mapa y en Max_heap

		//2.1: disminuimos las frecuencias de los pares afectados
		if(affL->first.first!=-1){
		/*modificamos la dirección de la primera ocurrencia de
			ese par llamando a mapa, sólo si es que hemos conseguido una*/
				mod_First_oc_map(affL,map_frequency);
		 //	else debemos eliminarlo del mapa pq notiene ocurrencia

			//también disminuimos la frecuencia en una unidad
				myheap->mod_key(-1,affL->first);
		}
		  // lo mismo para el par de la derecha
		if(affR->first.first!=-1){
			/*modificamos la dirección de la primera ocurrencia de
				ese par llamando a mapa, sólo si es que hemos conseguido una*/
				mod_First_oc_map(affR,map_frequency);
			//else se elmina pq no tiene siguiente ocurrencia

			//también disminuimos la frecuencia en una unidad
			myheap->mod_key(-1,affR->first);
		}
		//2.2: evaluamos los nuevos pares creados
		if(nuevoL->first.first!=-1){
		/*vemos si lo que hemos conseguido se encuentra en el mapa, diferenciando entre
			aumentar la frecuencia o insertarlo dentro de Max_heap*/
	  if(wasInMap(nuevoL,map_frequency))myheap->mod_key(1,nuevoL->first);
		else{
				MyPair_heap mp = std::make_pair(1,std::make_pair(nuevoL->first.first,nuevoL->first.second));
				myheap->insert(mp);
			}
		}
		std::cout << "todo bien" << '\n';
		if(nuevoR->first.first!=-1){
			std::cout << "aahhh" << '\n';
		/*vemos si lo que hemos conseguido se encuentra en el mapa, diferenciando entre
			aumentar la frecuencia o insertarlo dentro de Max_heap
		*/
		if(wasInMap(nuevoR,map_frequency)){
			std::cout << ":ssssss" << '\n';
			myheap->mod_key(1,nuevoR->first);
		}
			else{
				std::cout << "aaaaaaaaaaaaa" << '\n';
				MyPair_heap mp = std::make_pair(1,std::make_pair(nuevoR->first.first,nuevoR->first.second));
				myheap->insert(mp);
			}
		}
		std::cout << "puchis" << '\n';
		std::cout << "new iterator:  "<<*iterator << '\n';
		//o++;
	}

	myheap->printHeap();
	std::cout<<'\n'<< "-----------M A P-----------------" << '\n';
	std::cout << "pair\tfrec\tdir" << '\n';
	for (std::map<std::pair<int, int>, MyPair>::iterator iterator_map = map_frequency.begin(); iterator_map != map_frequency.end(); iterator_map++){
		std::cout << iterator_map->first.first<<' '<<iterator_map->first.second<<'\t'<<iterator_map->second.first<< '\t';
		std::cout << iterator_map->second.second.first << '\n';
	}

	o++;
}

void Advanced_Solution::mod_First_oc_map(PairWithDir *pairWithDir,MyMap& map_frequency){
	MyPair aux;
	/*mod_First_oc_map(): similar a wasInMap(), sólo que en este caso debemos establecer
											una nueva dirección a la primera ocurrencia, puesto que la anterior
											la hemos eliminado.
	*/
	aux = map_frequency[pairWithDir->first];
	map_frequency[pairWithDir->first].first--;
	map_frequency[pairWithDir->first].second.first = pairWithDir->second;
	if(!pairWithDir->second || !pairWithDir->second->next_oc)map_frequency[pairWithDir->first].second.second = nullptr;
}

bool Advanced_Solution::wasInMap(PairWithDir* pairWithDir,MyMap& map_frequency){
	/*wasInMap(): funcion encargarda de insertar un par con su respectiva dirección.
								Esto lo hacemos de una manera muy cuidadosa, puesto que debemos
								conectar todas las ocurrencias meidante las direcciones: next_oc y previous_oc,
								además de establecer el nuevo par como última ocurrencia.
	*/
	bool wasInMap = false;
	MyPair aux;
	std::cout << "pair  "<<pairWithDir->first.first<<' '<<pairWithDir->first.second << '\n';
	// si ya se encuentra, conectamos. Si no, lo creamos.
	if (map_frequency.find(pairWithDir->first) != map_frequency.end()) {
		aux = map_frequency[pairWithDir->first];
		if(aux.second.first){
			map_frequency[pairWithDir->first].first++;
			map_frequency[pairWithDir->first].second.second = pairWithDir->second;
			map_frequency[pairWithDir->first].second.second->previous_oc = aux.second.second;
			std::cout << "im in was in map" << '\n';
			aux.second.second->next_oc = map_frequency[pairWithDir->first].second.second;
			wasInMap = true;
		} else {
			aux.second.first = pairWithDir->second;
			map_frequency[pairWithDir->first].first++;
			wasInMap = true;
		}
	}
	else map_frequency[{pairWithDir->first.first,pairWithDir->first.second}] = MyPair(1, std::make_pair(pairWithDir->second, pairWithDir->second));
	return wasInMap;
}

void Advanced_Solution::re_Pair_Advanced(){

	std::map<IntPair, MyPair> map_frequency;
	// setear todas los pares con sus respectivas ocurrencias
	frequencyAndNode(map_frequency); //nlog(n)

	//guardar esos pares con su clave dentro de Max_heap
	heap = new Max_heap(map_frequency,doubly_list->size());

	heap->printHeap();

	std::cout << "clave\tPar\t" << '\n';
	std::cout << heap->top().first<<'\t'<<heap->top().second.first<<' '<<heap->top().second.second << '\n';

	MyPair_heap var1 = heap->top(); // par FRECUENCIA - par
	heap->removeMax();

	//iteramos hasta que la clave de la raiz de max heap sea 1
	while(var1.first>=2){
		change_List(var1.second,map_frequency,heap);//log(n)
		var1 = heap->top();
		heap->removeMax();
	}

	heap->printHeap();
	doubly_list->printList();
	std::cout << "end Advanced_Solution" << '\n';
	//heap->removeMax(); // par FRECUENCIA - par // log(n)
	//}
}
