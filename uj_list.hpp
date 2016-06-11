#ifndef UJ_LIST_HPP
#define UJ_LIST_HPP
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
			//! Przeciążenie *
			/*! Pobranie wartosci elemmentu kolejnego
			* @return true or false
			*/
			T& operator*()
			{
				listStruct* ls = previousElement->next;
				return ls->val;
				
			}
			//! Przeciążenie ++ (pre inkrementacji)
			/*!
			przesowa iterator do przodu o jedno miejesce.
			*/
			iterator& operator++() {
				previousElement = previousElement->next;
				return *this;
			}
			//! Przeciążenie ++ (post inkrementacji)
			/*! Przesowa iterator do przodu o jedno miejesce.
			*@param trash parametr podawany w celu odroznienia post inkrementacji
		
			*/
			iterator operator++(int trash) {
				iterator tmp = iterator(*this);
				previousElement = previousElement->next;
				return tmp;
			}
			//! Przeciążenie =
			/*! Pozwala na przypisywanie iteratorow do siebie
			*@param a itererator ktory zostanie skopiowany
			*/
			iterator& operator=(const iterator& iter)
			{
				previousElement = iter.previousElement;
				return *this;
			}
			//! Przeciążenie !=
			/*! Pozwala sprawdzic czy iteratory są rozne
			*@param lhs porownywany iterator
			*@return zwraca true lub false
			*/
			bool operator!=(const iterator& lhs) const {
				return !(lhs.previousElement == previousElement);
			}
			//! Przeciążenie ==
			/*! Pozwala sprawdzic czy iteratory są rowne
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
		//! Sprawdzenie czy lista pusta
		/*! Metoda sprawdzajaca czy lista jest pusta
		* @return zwraca true jezeli lista pusta 
		*/
		bool empty() const{
			if (node.next == nullptr){
				return true;
			}
			else
				return false;
		}
		//! Dodawanie na początek
		/*! Metoda dodajaca elementy na poczatek listy
		* @param value wartosc lancucha listy
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
		//! Odwrócenenie szyku
		/*!	Metoda pozwalająca odwrócić szyk listy
		*@param toReverse lista do obrocenia
		*/
		void reverse(){
			iterator b = begin();
			iterator e = end();
			iterator tmp = b;
			if(b!=e)
				b++;
			while(tmp!=e){
				tmp = b;
				tmp++;
				push_front(*b);
				erase(b);				
			}			
		}
		//! Konstruktor domyslny listy
		list(){
			node.next = nullptr;
			_end = &node;
		}
		//! Konstruktor kopiujacy
		/*!
		Konstruktor tworzacy obiekt na podstawie innej listy
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
		}
		//!Konstruktor wypelniajacy zadana wartoscia
		/*!
		Kostruktor tworzy liste o zadanej wielkosci z podana wartoscia
		*@param n wielkosc listy
		*@param value wartosc wstawiana
		*/
		list(size_t n ,const T& value){
			_end = &node;
			_end->next = nullptr;
			for(size_t i = 0; i<n; i++){
				push_front(value);
			}
		}
		//! Przeciążenie =
		/*! Pozwala na przepisanie listy między zmiennymi
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
			return *this;
		}
		
		//! destruktor, niszczy wzystkie stworzone dynamiczne struktury
		~list(){

			listStruct* tmp = node.next;
			listStruct* tmp2;
			if(tmp != nullptr){
				while (tmp->next!=nullptr)
				{
					tmp2 = tmp->next;
					delete tmp;
					tmp = tmp2;
				}
			}
		}
		//! Rozmiar listy
		/*! Metoda zwracajaca wielkosc listy
		* @return wielkosc listy
		*/
		size_type size() const{
			const listStruct* tmp = &node;
			size_t count=0;
			while (tmp->next!=nullptr){
				tmp = tmp->next;
				count++;
			}
			return count;
		}
		//! Iterator poczatku
		/*! Metoda zwracajaca iterator do pierwszego elementu
		* @return iterator do pierwszego elementu
		*/
		iterator begin() const {
			return iterator((listStruct*)&node);
		}
		//! Iterator konca
		/*!
		*Metoda zwracajaca iterator na ostatni element
		*@return zwraca iterator
		*/
		iterator end() const{
			return iterator(_end);
		}

		//! Czyszczenie listy
		/*! Metoda czyszczaca liste
		*/
		void clear(){
			listStruct* tmp = &node;
			listStruct* tmp2;
			tmp = tmp->next;
			while (tmp->next!=nullptr)
			{
				tmp2 = tmp->next;
				delete tmp;
				tmp = tmp2;
			}
			node.next = nullptr;
			_end= &node;
		}
		//! Wstawianie elementow
		/*!
		Metoda sluzy do wstawiania wartosci za iteratorem
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
		//! Usuwanie elementu
		/*! Metoda usuwajaca wskazany przez iterator element listy
		*@param pos przyjmuje miejsce po ktorym zostanie usuniety element
		*@return zwraca itrerator przed usunietym elementem
		*/
		iterator erase(iterator pos){
			listStruct* posStruct = pos.previousElement;
			if(posStruct->next==nullptr){
				return pos;
			}
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
