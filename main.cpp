#include<iostream>

template <typename T> 
struct listStruct {
	T val;
	listStruct<T>* next;
};


template <typename T>
class ForwardList {
private:
	listStruct<T> lst;
	listStruct<T>* _end = &lst;

public:
	ForwardList() 
	{
		lst.val = NULL;
		lst.next = nullptr;
	}
	struct iterator {
		listStruct<T>* previous;
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
	};
	iterator begin() {
		iterator iter{ &lst };
		return iter;
	}

	iterator end() {
		if (_end != NULL) {
			if (_end->next == nullptr) {
				iterator iter{ _end };
				return iter;
			}
		}
		iterator iter{ &lst };
		while (iter.previous->next != nullptr)
		{
			iter.previous = iter.previous->next;
		}
		_end = iter.previous;
		return iter;
	}

	void push_back(T val)
	{
		iterator iter = end();
		iter.previous->next = new listStruct<T>{ val, nullptr };
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
		int i=0;
		iterator iter{ &lst };
		while (iter.previous->next != nullptr)
		{
			iter.previous = iter.previous->next;
			i++;
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
}