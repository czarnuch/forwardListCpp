#include<iostream>
#include<vector>

#include"uj_list.hpp"

using std::cout;
using std::cin;
using std::endl;
using std::vector;

int main() {

	uj::list<int> listaPierwsza;
	uj::list<int>::iterator it;
	//listaPierwsza.push_front(1);
	//listaPierwsza.push_front(3);
	it = listaPierwsza.begin();
	listaPierwsza.insert(it, 7);
	listaPierwsza.insert(it, 8);
	listaPierwsza.insert(it, 9);
	cout << "Po dodaniu\n";

	while(it!= listaPierwsza.end()){
		cout << *it<<endl;
		++it;
	}

	uj::list<int> listaDruga = listaPierwsza;
	uj::list<int>::iterator it2 = listaDruga.begin();
	cout << "\nRozmiar listy:   " << listaDruga.size() << "\n";
	cout <<"\n############ Teraz kopia z konstruktora ##############\n" << endl;
	
	while(it2!= listaDruga.end()){
		cout << *it2<<endl;
		++it2;
	}
	cout <<"\n#### Teraz czyścimy za pomoca clear i to samo co po tescie kopii ####\n" << endl;
	listaDruga.clear();
	it2 = listaDruga.begin();
	cout << "\nRozmiar listy:   " << listaDruga.size() << "\n";

	while(it2!= listaDruga.end()){
		cout << *it2<<endl;
		++it2;
	}
	cout <<"\n#### Teraz dodaje 2 elementy i jeden kasuje ####\n" << endl;
	
	it2 = listaDruga.begin();
	listaDruga.insert(it2,77);
	listaDruga.push_front(22);
	listaDruga.erase(it2);
	it2 = listaDruga.begin();
while(it2!= listaDruga.end()){
		cout << *it2<<endl;
		++it2;
	}

	cin.get();
	cin.get();
	return(0);
}
