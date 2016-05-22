#ifndef ForwardlistHeader_H
#define ForwardlistHeader_H
#include<iostream>
namespace uj
{
	template <typename T>
	class list{
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
			listStruct* previousElement;

			bool hasNext(){
				if (previousElement->next != nullptr){
					return true;
				}
				return false;
			}
//			T nullObject = NULL;
//			T& getNullObject(){
//				nullObject = NULL;
//				return	nullObject;
//			}

		public:
			/*
			* konstruktor domyœlny iteratora
			*/
			iterator(){
				previousElement = nullptr;
			}
			/*
			* konstruktor przyjmuj¹cy wskaŸnik
			* @param element wskaŸnik na element który przypiszemy do iteratora
			*/
			iterator(listStruct * element){
				previousElement = element;
			}
			//###### Przeci¹¿anie operatorów ######
			/*
			* pobranie wartoœci elemmentu kolejnego
			*
			* @return true or false
			*/
			T& operator*()
			{
	//			if (hasNext()){						// TO nale¿y usun¹æ potem
					listStruct* ls = previousElement->next;
					return ls->val;
//				else
//				{
//					return getNullObject();			// TO nale¿y usun¹æ potem
//				}
				
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
		* Metoda sprawdzaj¹ca czy istnieje kolejny element.
		* @param node jest to pierwszy element listy
		* @return zwraca prawdê je¿eli istnieje kolejny element, w przeciwnm wypadku fa³sz.
		*/
		bool hasNext(listStruct* node){
			if ( node->next != nullptr){
				return true;
			}
			return false;
		}
		/*
		* Metoda dla const, gwarantuj¹ca niezmiennoœæ obiektu,
		* sprawdzaj¹ca czy istnieje kolejny element.
		* @param node jest to pierwszy element listy
		* @return zwraca prawdê je¿eli istnieje kolejny element, w przeciwnm wypadku fa³sz.
		*/
		bool hasNext(const listStruct* node) const{
			if (node->next != nullptr){
				return true;
			}
			return false;
		}
		/*
		* Metoda dodaj¹ca elementy na pocz¹tek listy
		* @param value wartoœæ ³añcucha listy
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
		void reverse(list & toReverse){
			iterator b = toReverse.begin();
			iterator e = toReverse.end();
			T temp;
			while(b!=e){
				toReverse.push_front(*b);
				b.earse();
				++b;
			}
			
		}
		//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
		/*
		 * konstruktor domyœlny
		 */
		list(){
			node.next = nullptr;
			_end = &node;
		}

		list(const list & other){
			node.next = nullptr;
			iterator it = &node;
			iterator b = other.begin();
			iterator e = other.end();
			while (b!=e)
			{
				it = it.insert(*b);
				++it;
				++b;
			}
			
		}

		list & operator=(const list & other){
			if(this == &other){
				return *this;
			}
			
			if(begin() != end()){
				clear();// musz¿ usun¿¿ dane				
			}
			
			iterator it = &node;
			iterator b = other.begin();
			iterator e = other.end();
			while (b!=e)
			{
				it = it.insert(*b);
				++it;
				++b;
			}
			return *this;
		}
		/*
		* destruktor, niszczy wzystkie stworzone dynamiczne struktury
		*/
		~list(){

			listStruct* tmp = &node;
			listStruct* tmp2;
			tmp = tmp->next;
			if(tmp != nullptr){
				while (hasNext(tmp))
				{
					tmp2 = tmp->next;
					delete tmp;
					tmp = tmp2;
				}
			}
		}
		/* 
		* metoda zwracaj¹ca wielkoœæ listy
		* @return wielkoœæ listy
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
		* metoda zwracaj¹ca iterator do pierwszego elementu
		* @return iterator do pierwszego elementu
		*/
		iterator begin() const {
			return iterator((listStruct*)&node);
		}
		iterator end() const{
			return iterator(_end);
		}

		/*
		* metoda czyszcz¹ca listê
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
		* metoda sprawdzaj¹ca czy lista jest pusta
		* @return zwraca true je¿eli lista pusta 
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
			return it = pos.insert(value);
		}
		iterator erase(iterator pos){
			return pos.earse();			
		}
	};
}
#endif // !1/
