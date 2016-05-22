/*
#include<iostream>

template <typename T>
class ForwardList {
private:
	template <typename T>
	struct listStruct {
		T val;
		listStruct<T>* next;
	};

	listStruct<T> lst;
	listStruct<T>* _end = &lst;

public:
	ForwardList() 
	{
		lst.val = NULL;
		lst.next = nullptr;
	}

	class iterator {
	private:
		listStruct<T>* previous;
	public:
		iterator(){
			previous = nullptr;
		}
		iterator(listStruct<T>* lst){
			previous = lst;
		}
		T& operator*()
		{
			listStruct<T>* ls = previous->next;
			return ls->val;
		}
		void operator++() {
			previous = previous->next;
		}
		iterator& operator=(const iterator& a)
		{
			previous = a.previous;
			return *this;
		}
		bool operator!=(const iterator& lhs) const {
			return !(lhs.previous == previous);
		}
		void end(){
			while (previous->next != nullptr)
			{
				previous = previous->next;
			}
			_end = previous;
		}

		void iteratorPushBack(T val){
			end();
			previous->next = new listStruct<T>{ val, nullptr };
	}
	};


	iterator begin() {
		iterator iter( &lst );
		return iter;
	}

	iterator end() {
		if (_end != NULL) {
			if (_end->next == nullptr) {
				iterator iter{ _end };
				return iter;
			}
		}
		iterator iter( &lst );
		iter.end();
		return iter;
		
	}

	void push_back(T val)
	{
		iterator iter = begin();
		iter.iteratorPushBack(val);
	}

	T get(int index) {
		int i = -1;
		iterator iter{ &lst };
		while (index!=i)
		{
			++iter;
			i++;
		}
		return iter.previous->val;
	}
	size_t size() {
		int i = 0;
		iterator b = begin();
		iterator e = end();
		while (b!=e)
		{
			i++;
			b++;
		}
		return i;
	};


};


int main() {
	std::cout << " *******************   Testowanie listy jednokierunkowej   ******************* " << std::endl;
	ForwardList<int> f;
	f.push_back(4);
	f.push_back(9);
	f.push_back(5);
	f.push_back(1);
	std::cout << "Koniec dodwanaia\n";

	auto b = f.begin();
	auto e = f.end();
	while (b != e) {

		std::cout << *b << "\n";
		++b;
	}
	std::cout << "Koniec wypisywania z iteratorów\n";
	std::cout << "wielkoœc listy to " << f.size() << "\n";

	std::cin.get();
	std::cin.get();
	return(0);
}*/
#include<iostream>
#include<vector>

#include"ForwardListHeader.h"

using std::cout;
using std::cin;
using std::endl;
using std::vector;

int main() {

	uj::list<int> neww;
//	uj::list<int> neww2;
	uj::list<int>::iterator it;
	neww.push_front(1);
	neww.push_front(3);
	it = neww.begin();
	cout << *it;
	it++;
	cout << *it;
	neww.insert(it, 5);
	neww.insert(it, 7);
	neww.insert(it, 9);
	cout << "Po dodaniu\n";
	it= neww.begin();
	cout << *it<<endl;
	it++;
	cout << *it<<endl;
	it++;
	cout << *it<<endl;
	//neww2 = neww;
	uj::list<int> new3(neww);
	uj::list<int>::iterator it2 = new3.begin();
	cout <<"\n############ Teraz kopia z konstruktora ##############\n" <<  *it2 << endl;
	++it2;
	cout << *it2 << endl;

	cin.get();
	cin.get();
	return(0);
}
