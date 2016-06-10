#ifndef ForwardlistHeader_H
#define ForwardlistHeader_H
#include<iostream>
namespace uj
{
	template <typename T>
	//! Definicja klasy listy
	class list{
	private:
		
		//! Struktura listy
		struct listStruct {
			T val;
			listStruct * next;
		};
		listStruct node;
		listStruct * _end;

	public:
		 //! Klasa iteratora
		class iterator{
		private:
			listStruct* previousElement;

			bool hasNext(){
				if (previousElement->next != nullptr){
					return true;
				}
				return false;
			}
			friend class list;
			/*!
			* konstruktor przyjmujacy wskaznik
			* @param element wskaznik na element ktory przypiszemy do iteratora
			*/
			iterator(listStruct * element){
				previousElement = element;
			}
		public:
			typedef std::forward_iterator_tag iterator_category;
        		typedef T value_type;
        		typedef std::ptrdiff_t difference_type;
       			typedef T * pointer;
        		typedef T & reference;
			typedef const T & const_reference;
			
			//! konstruktor domyslny iteratora
			iterator(){
				previousElement = nullptr;

			}
			/*!
			* pobranie wartosci elemmentu kolejnego
			* @return true or false
			*/
			T& operator*()
			{
				listStruct* ls = previousElement->next;
				return ls->val;
				
			}
			/*!
			przesowa iterator do przodu o jedno miejesce przeciazenie pre inkrementacji
			*/
			iterator& operator++() {
				previousElement = previousElement->next;
				return *this;
			}
			/*!
			*@param trash parametr podawany w celu odroznienia post inkrementacji
			*przesowa iterator do przodu o jedno miejesce, przeciazenie post inkrementacji
			*/
			iterator operator++(int trash) {
				iterator tmp = iterator(*this);
				previousElement = previousElement->next;
				return tmp;
			}
			/*! Przeciazenie operatora przypisania
			*@param a itererator ktory zostanie skopiowany
			*/
			iterator& operator=(const iterator& iter)
			{
				previousElement = iter.previousElement;
				return *this;
			}
			/*!
			*Przeciazony operator testu roznosci
			*@param lhs porownywany iterator
			*@return zwraca true lub false
			*/
			bool operator!=(const iterator& lhs) const {
				return !(lhs.previousElement == previousElement);
			}
			/*!
			*Przeciazony operator testu rownosci
			*@param lhs porownywany iterator
			*@return zwraca true lub false
			*/
			bool operator==(const iterator& lhs) const {
				return (lhs.previousElement == previousElement);
			}

		};

		typedef std::forward_iterator_tag iterator_category;
	        typedef T value_type;
	        typedef std::ptrdiff_t difference_type;
        	typedef T * pointer;
	        typedef T & reference;
		typedef const T & const_reference;
		typedef size_t size_type;
		/*!
		* Metoda sprawdzajaca czy istnieje kolejny element.
		* @param node jest to pierwszy element listy
		* @return zwraca prawde jezeli istnieje kolejny element, w przeciwnm wypadku falsz.
		*/
		
		bool hasNext(listStruct* node){
			if ( node->next != nullptr){
				return true;
			}
			return false;
		}
		/*!
		* metoda sprawdzajaca czy lista jest pusta
		* @return zwraca true jezeli lista pusta 
		*/
		bool empty() const{
			if (node.next == nullptr){
				return true;
			}
			else
				return false;
		}
		/*!
		* Metoda dla const, gwarantujaca niezmiennosc obiektu,
		* sprawdzajaca czy istnieje kolejny element.
		* @param node jest to pierwszy element listy
		* @return zwraca prawde jezeli istnieje kolejny element, w przeciwnm wypadku falsz.
		*/
		bool hasNext(const listStruct* node) const{
			if (node->next != nullptr){
				return true;
			}
			return false;
		}
		/*!
		* Metoda dodajaca elementy na poczatek listy
		* @param value wartosc lancucha listy
		*
		*/
		void push_front(T value){
			listStruct* newNode = new listStruct;
			newNode->val=value;
			if(empty()){
				newNode->next=nullptr;
				node.next = newNode;
				_end = newNode;
			}else{
				newNode->next = node.next;
				node.next = newNode;
			}
		}
		/*!
		*Metoda odwracajaca szyk listy
		*@param toReverse lista do obrocenia
		*/
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
		//! konstruktor domyslny
		list(){
			node.next = nullptr;
			_end = &node;
		}
		/*!
		*Konstruktor tworzacy obiekt na podstawie innej listy
		*@param other lista
		*/
		list(const list & other){
			node.next = nullptr;
			iterator it = begin();
			iterator b = other.begin();
			iterator e = other.end();
			while (b!=e)
			{
				it = insert(it, *b);
				++it;
				++b;
				if(_end->next!=nullptr)
					_end=_end->next;
			}
			//findEnd();	
		}
		/*!
		Przeciazony operator przypisania, kopiujacy liste
		*@param other lista
		*/
		list & operator=(const list & other){
			if(this == &other){
				return *this;
			}
			
			if(begin() != end()){
				clear();// musze usunac dane				
			}
			
			iterator it = &node;
			iterator b = other.begin();
			iterator e = other.end();
			while (b!=e)
			{
				it = insert(it, *b);
				++it;
				++b;
				if(_end->next!=nullptr)
					_end=_end->next;
			}
			//findEnd();
			return *this;
		}
		
		//! destruktor, niszczy wzystkie stworzone dynamiczne struktury
		~list(){

			listStruct* tmp = node.next;
			listStruct* tmp2;
			if(tmp != nullptr){
				while (hasNext(tmp))
				{
					tmp2 = tmp->next;
					delete tmp;
					tmp = tmp2;
				}
			}
		}
		/*! 
		 metoda zwracajaca wielkosc listy
		* @return wielkosc listy
		*/
		size_type size() const{
			const listStruct* tmp = &node;
			size_t count=0;
			while (hasNext(tmp)){
				tmp = tmp->next;
				count++;
			}
			return count;
		}
		/*!
		* metoda zwracajaca iterator do pierwszego elementu
		* @return iterator do pierwszego elementu
		*/
		iterator begin() const {
			return iterator((listStruct*)&node);
		}
		/*!
		*Metoda zwracajaca iterator na ostatni element
		*@return zwraca iterator
		*/
		iterator end() const{
			return iterator(_end);
		}

		//!
		/*!
		* metoda czyszczaca liste
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

		/*!
		sluzy do wstawiania wartosci
		*@param pos pozycja iteratora po ktorym zostanie dodane nowe ogniwo
		*@param value wartosc wstawiana
		*@return
		*/
		iterator insert(iterator pos, const T & value){
			listStruct* posStruct = pos.previousElement;
			bool moveEnd=false;
			if(posStruct->next==nullptr)
				moveEnd=true;	
			listStruct* newLS = new listStruct;
			newLS->next = posStruct->next;
			newLS->val = value;
			posStruct->next = newLS;
	
			if (moveEnd){
				_end=newLS;
			}
			return pos;
		}
		/*!
		*Metoda usuwajaca wskazany element listy
		*@param pos przyjmuje miejsce po ktorym zostanie usuniety element
		*@return zwraca itrerator przed usunietym elementem
		*/
		iterator erase(iterator pos){
			listStruct* posStruct = pos.previosElement;
			if(posStruct->next==nullptr)
				return NULL;
			if(posStruct->next->next==nullptr)
				_end=posStruct;
			listStruct* tmp= posStruct->next->next;
			delete posStruct->next;
			posStruct->next = tmp;		
			return pos;			
		}
	};
}
#endif // !1/
