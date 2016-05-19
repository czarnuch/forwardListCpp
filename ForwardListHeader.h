#ifndef ForwardListHeader_H
#define ForwardListHeader_H
#include<iostream>
namespace uj
{
	template <typename T>
	class List{
	private:
		//VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV
		/*
		 *Struktura listy
		 */
		struct listStruct {
			T val;
			listStruct * next;
		};
		//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
		listStruct node;
		listStruct * _end;

		void findEnd(){
			listStruct* temp = &node;
			while (temp!=nullptr)
			{
				temp = temp->next;
			}
			_end = temp;
		}
	public:
		//VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV
		/*
		 *Klasa iteratora
		 */
		class iterator{
		private:
			listStruct * previousElement;

			bool hasNext(){
				if (previousElement->next != nullptr){
					return true;
				}
				return false;
			}
			T nullObject = NULL;

			T& getNullObject(){
				nullObject = NULL;
				return	nullObject;
			}

		public:
			/*
			* konstruktor domy�lny iteratora
			*/
			iterator(){
				previousElement = nullptr;
			}
			/*
			* konstruktor przyjmuj�cy wska�nik
			* @param element wska�nik na element kt�ry przypiszemy do iteratora
			*/
			iterator(listStruct * element){
				previousElement = element;
			}
			//###### Przeci��anie operator�w ######
			/*
			* pobranie warto�ci elemmentu kolejnego
			*
			* @return true or false
			*/
			T& operator*()
			{
				if (hasNext()){						// TO nale�y usun�� potem
					listStruct* ls = previousElement->next;
					return ls->val;
				}
				else
				{
					return getNullObject();			// TO nale�y usun�� potem
				}
			}
			iterator& operator++() {
				previousElement = previousElement->next;
				return *this;
			}
			iterator operator++(int trash) {
				iterator tmp = iterator(*this);
				previousElement = previousElement->next;
				return tmp;
			}
			iterator& operator=(const iterator& a)
			{
				previousElement = a.previousElement;
				return *this;
			}
			bool operator!=(const iterator& lhs) const {
				return !(lhs.previousElement == previousElement);
			}
			bool operator==(const iterator& lhs) const {
				return (lhs.previousElement == previousElement);
			}
			iterator insert(const T& value) {
				listStruct* newLS = new listStruct;
				newLS->next = previousElement->next;
				newLS->val = value;
				previousElement->next = newLS;
		
				return *this;
			}
			iterator earse(){
				if (!hasNext()){
					return NULL;
				}
				listStruct* tmp= previousElement->next->next;
				delete previousElement->next;
				previousElement->next = tmp;
				return *this;
			}
		};
		/*
		* Metoda sprawdzaj�ca czy istnieje kolejny element.
		* @param node jest to pierwszy element listy
		* @return zwraca prawd� je�eli istnieje kolejny element, w przeciwnm wypadku fa�sz.
		*/
		bool hasNext(listStruct* node){
			if (node->next != nullptr){
				return true;
			}
			return false;
		}
		/*
		* Metoda dla const, gwarantuj�ca niezmienno�� obiektu,
		* sprawdzaj�ca czy istnieje kolejny element.
		* @param node jest to pierwszy element listy
		* @return zwraca prawd� je�eli istnieje kolejny element, w przeciwnm wypadku fa�sz.
		*/
		bool hasNext(const listStruct* node) const{
			if (node->next != nullptr){
				return true;
			}
			return false;
		}
		/*
		* Metoda dodaj�ca elementy na pocz�tek listy
		* @param value warto�� �a�cucha listy
		*
		*/
		void push_front(T value){
			listStruct* newNode = new listStruct;
			if (!hasNext(&node))
				_end = newNode;
			newNode->next = node.next;
			newNode->val = value;
			node.next = newNode;
		};
		//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
		/*
		 * konstruktor domy�lny
		 */
		List(){
			node.next = nullptr;
			_end = &node;
		}
		/*
	List & operator=(const List & other){

			List newCopy;
			iterator it = newCopy.begin();
			iterator b = other.begin();
			iterator e = other.end();
			while (b!=e)
			{
				it = it.insert(*b);
				++b;
			}
			return newCopy;
		}
		*/
		/*
		* destruktor, niszczy wzystkie stworzone dynamiczne struktury
		*/
		~List(){

			listStruct* tmp = &node;
			listStruct* tmp2;
			tmp = tmp->next;
			while (hasNext(tmp))
			{
				tmp2 = tmp->next;
				delete tmp;
				tmp = tmp2;
			}
		}
		/* 
		* metoda zwracaj�ca wielko�� listy
		* @return wielko�� listy
		*/
		size_t size() const{
			const listStruct* tmp = &node;
			size_t count=0;
			while (hasNext(tmp)){
				tmp = tmp->next;
				count++;
			}
			return count;
		}
		/*
		* metoda zwracaj�ca iterator do pierwszego elementu
		* @return iterator do pierwszego elementu
		*/
		iterator begin() const {
			return iterator((listStruct*)&node);
		}
		iterator end() const{
			return iterator(_end);
		}

		/*
		* metoda czyszcz�ca list�
		*/
		void clear(){
			listStruct* tmp = &node;
			listStruct* tmp2;
			tmp = tmp->next;
			while (hasNext(tmp))
			{
				tmp2 = tmp->next;
				delete tmp;
				tmp = tmp2;
			}
			node.next = nullptr;
		}
		/*
		* metoda sprawdzaj�ca czy lista jest pusta
		* @return zwraca true je�eli lista pusta 
		*/
		bool empty() const{
			if (hasNext(&node)){
				return false;
			}
			else
				return true;
		}
		iterator insert(iterator pos, const T & value){
			iterator it;
			if (pos == end()){
				it=pos.insert(value);
				findEnd();
		}
			return it;
		}
		iterator erase(iterator pos){
			return pos.earse();			
		}
	};
}
#endif // !1/
