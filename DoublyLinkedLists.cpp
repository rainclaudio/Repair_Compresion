#include "DoublyLinkedLists.h"
#include <iostream>
#include <utility>

//cout
DoublyLinkedLists::DoublyLinkedLists()
{
	tam = 0;
	head = nullptr;
	tail = nullptr;
}

DoublyLinkedLists::~DoublyLinkedLists(){
	if(this->head != NULL){
 if(tam != 1){
	 Node *deletethis;
		while(this->head->next !=NULL){
				deletethis = this->head;
				this->head = this->head->next;
				deletethis ->next = NULL;
				delete deletethis;
				tam--;
			}
			deletethis = this->head;
			this->head = NULL;
			delete deletethis;
			tam--;
 } else {
	 Node *deletethis = this->head;
	 this->head = NULL;
	 delete deletethis;
	 tam--;
 }
} else {
 std::cout << "Empty" << std::endl;
}
}

void DoublyLinkedLists::insert(const int value){
	Node* new_nodo = new Node();
	new_nodo->value = value;

	if (head == nullptr) {
		head = new_nodo;
		tail = head;
	}
	else {
		new_nodo->prev = tail;
		tail->next = new_nodo;
		tail = new_nodo;
	}

	tam++;
}


PairWithDir* DoublyLinkedLists::change_And_Get_Info(Node** curr, int o){
	/*change_And_Get_Info = nos recolecta toda la información relevante al realizar una modificación
		es decir, los nodos Right-left afectados y los nodos right-left nuevos(SI ES QUE EXISTEN).
		EX: 2 3 4 2 1 2 3 4 -> 4 2 por 28 -> 2 3 28 1 2
				affected = 3 4 y 2 1 /direcciones alpha1 y alpha2 (dir de sus sig ocurrencias)
				nuevos =  3 28 y 28 1 / direcciones delta 1 y delta 2( 1ras ocurrencias pq son nuevos)
	*/

	/*colector es quien nos recolecta toda la información. Para affected, elegimos
		la direcciones de sus siguientes ocurrencias porque MAP necesita una actualización
		de la "nueva primera ocurrencia del par afectado". Si no, éste otorgará
		una direccion eliminada.
	*/
	PairWithDir *collector = initCollector();

		Node* extra1 = new Node();
		Node* delete_curr = new Node();
		Node* delete_next = new Node();
		Node* next = new Node();

		delete_curr = *curr;
		delete_next = (*curr)->next;

		next = (*curr)->next;
		extra1->value = o;
		o++;
		/* Todos los casos tienen de BASE el siguiente proceso:
			(1)  hacemos que nuestro reemplazo apunte al anterior y al siguiente de
			     current y next respectivamente.

			(2)	 luego redireccionamos el siguiente y anterior de los punteros prev y next
					 para que apunten a nuestro reemplazo.

			(3)	collector guardará toda la información relevante especificada anteriormente.

			(4)	curr deberá apuntar a la nueva ocurrencia del par para luego eliminar
					el par actual

			(5)  destruimos los nodos que ya no nos sirven, no sin antes hacer que
					 sus punteros apunten a null.

		  (6)  disminuimos su tamaño.
*/

			if (*curr != head) {
				if(next != tail){
					//(1)

					extra1->prev = (*curr)->prev;
					extra1->next = next->next;
					//(2)
					(*curr)->prev->next = extra1;
					next->next->prev = extra1;
					//(3)
					//(3-L)
					collector[0].first.first = delete_curr->prev->value;//valor1
					collector[0].first.second = delete_curr->value;//valor2
					collector[0].second = delete_curr->prev->next_oc;//dir next ocurrence
					//(3-R)
					collector[1].first.first = delete_next->value;//valor1
					collector[1].first.second = delete_next->next->value;//valor2
					collector[1].second = delete_next->next_oc; //dir next ocurrence
					//Nuevos
					//(3-L)
					collector[2].first.first = extra1->prev->value;
					collector[2].first.second = extra1->value;
					collector[2].second = extra1->prev; // dir new ocurrence
					//(3-R)
					collector[3].first.first = extra1->value;
					collector[3].first.second = extra1->next->value;
					collector[3].second = extra1;//dir new ocurrence
			  	//*next = tail;
					//*curr = extra1;

					//(4)
					(*curr) = delete_curr->next_oc;

					//(5)
					delete_next->next = delete_next->prev = nullptr;
					delete_curr->next = delete_curr->prev = nullptr;

					delete delete_curr;
					delete delete_next;
					this->tam--;//(6)
				}
				else {
					//(1)
					extra1->prev = (*curr)->prev;
					extra1->next = nullptr;

					//(2)
					(*curr)->prev->next = extra1;


					//(3)
					//Afectados
					//(3-L)
					collector[0].first.first = delete_curr->prev->value;
					collector[0].first.second = delete_curr->value;
					collector[0].second = nullptr;
					//Nuevos
					//(3-L)
					collector[2].first.first = extra1->prev->value;
					collector[2].first.second = extra1->value;
					collector[2].second = extra1->prev;
					//(4)
					(*curr) = nullptr;

					tail = extra1;
					next = tail;

					//(5)
					delete_next->next = delete_next->prev = nullptr;
					delete_curr->next = delete_curr->prev = nullptr;
					delete delete_curr;
					delete delete_next;

					this->tam--;//(6)
				}
			}	else {
				//(1)
				extra1->prev = nullptr;
				extra1->next = next->next;
				//(2)
				next->next->prev = extra1;
				//(3)
				//Afectados
				//(3-L)
				collector[1].first.first = delete_next->value;
				collector[1].first.second = delete_next->next->value;
				collector[1].second = delete_next->next_oc;

				//Nuevos
				//(3-R)
				collector[3].first.first = extra1->value;
				collector[3].first.second = extra1->next->value;
				collector[3].second = extra1;

				//(4)
				(*curr) = delete_curr->next_oc;
				head = extra1;

				//(5)
				delete_next->next = delete_next->prev = nullptr;
				delete_curr->next = delete_curr->prev = nullptr;
				delete delete_curr;
				delete delete_next;
				//(6)
				this->tam--;
			}


			Node* extra2 = new Node();
			extra2 = head;
			std::cout << "-----------------------------------------------------" << std::endl;
			std::cout << "DOUBLY_LIST: ";
			while (extra2 != nullptr) {
				std::cout << extra2->value <<" ";
				extra2 = extra2->next;
			}
			std::cout<<'\n'<< "-----------------------------------------------------" << std::endl;

	return collector;
}

PairWithDir* DoublyLinkedLists::initCollector(){
	PairWithDir* collector = new PairWithDir[4];
	for(int i = 0; i < 4; ++i){
		collector[i].first.first = -1;
		collector[i].first.second = -1;
		collector[i].second = nullptr;
	}
	return collector;
}



void DoublyLinkedLists::remove()
{
	if (head == nullptr) return;
	else {
		Node* extra = new Node();
		extra = tail;
		tail = tail->prev;
		delete extra;
	}
}

int DoublyLinkedLists::at(int pos)
{
	int it = 0;
	Node* extra = new Node();
	extra = head;

	if (extra == nullptr) return -1;

	while (extra != nullptr) {
		if (it == pos) return extra->value;
		else {
			extra = extra->next;
		}
		it++;
	}

	return -1;
}

int DoublyLinkedLists::size()
{
	return tam;
}

bool DoublyLinkedLists::isEmpty()
{
	return false;
}
void DoublyLinkedLists::printList(){
    Node *print = this->head;
    int counter = 0;
    while(counter < tam){
			if(print->next_oc){
				std::cout << " "<< print->value <<" ";
				std::cout<<"\nn: " << print->next_oc->value << '\n';

			} else std::cout << " "<< print->value <<" ";

    	print = print -> next;
      counter++;
    }
    std::cout  << '\n';
    delete print;
}
Iterator DoublyLinkedLists::begin(){
	Iterator iter(head,tail);
	return iter;
}
