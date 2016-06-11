#include<iostream>
#include <typeinfo>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TestFixture.h>
#include <cppunit/TestAssert.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestCaller.h>

#include"uj_list.hpp"

/*! 
 *  \brief     Unit test for forward list
 *  \details   Aplikacja testujaca liste jednokierunkowa
 *  \author    Adam Zajac
 *  \version   1.0
 *  \date      2016
 *  \warning   Uzywasz aplikacji na wlasne ryzyko
 */

using std::cout;
using std::cin;
using std::endl;

//! Definicja klasy testow
class List_test : public CppUnit::TestCase {
public:
		
			//! Testy wstawiania
			/*! Testowana jest metoda insert
			*/
	void insertingMethodsTest1(){
		int a=111;
		int b=222;
		int c=333;
		uj::list<int> listaPierwsza;
		uj::list<int>::iterator it;
		it = listaPierwsza.begin();
		listaPierwsza.insert(it, a);
		listaPierwsza.insert(it, b);
		listaPierwsza.insert(it, c);
		it = listaPierwsza.begin();
			CPPUNIT_ASSERT_EQUAL(c ,*it);
			++it;
			CPPUNIT_ASSERT_EQUAL(b ,*it);
			++it;
			CPPUNIT_ASSERT_EQUAL(a ,*it);
			listaPierwsza.insert(it, c);
			++it;
			CPPUNIT_ASSERT_EQUAL(a ,*it);
			
	}	
	
			//! Testy wstawiania
			/*! Testowana jest metoda push_front
			*/
	void insertingMethodsTest2(){
		int a=111;
		int b=222;
		int c=333;
		uj::list<int> listaPierwsza;
		uj::list<int>::iterator it;
		listaPierwsza.push_front(a);
		listaPierwsza.push_front(b);
		listaPierwsza.push_front(c);
		it = listaPierwsza.begin();
			CPPUNIT_ASSERT_EQUAL(c ,*it);
			++it;
			CPPUNIT_ASSERT_EQUAL(b ,*it);
			++it;
			CPPUNIT_ASSERT_EQUAL(a ,*it);
	}
	
			//! Testy konstruktora
			/*! Testowana jest poprawnosc dzialania konstruktara 
			* list(size_t n ,const T& value)
			*/
	void constructorsTest1(){
		const double x = 1.0;
		size_t sz= 1000;
		double suma=0;
		uj::list<double> lista(sz, x);
		uj::list<double>::iterator it3 = lista.begin();
		
		for(size_t i=1; i<sz ; i++){	//i=1 by nie wyjechac po za zakres przy odczycie
			it3++;
		}
		CPPUNIT_ASSERT_EQUAL(x ,*it3);

		it3 = lista.begin();
		while(it3!=lista.end()){
				suma += *it3;
				it3++;
			}
		CPPUNIT_ASSERT_EQUAL(double(sz)*x, suma );	
	}
		
			//! Testy konstruktora
			/*! Testowana jest poprawnosc dzialania konstruktara 
			* list(const list & other)
			*/
	void constructorsTest2(){
			uj::list<int> listaPierwsza;
			int silnia=0;
			for(int i=0; i<=10 ; i++){
				listaPierwsza.push_front(i);
				silnia*=i;
			}
			uj::list<int> listaDruga(listaPierwsza);
			uj::list<int>::iterator it2 = listaDruga.begin();
			
			for(int i=0; i<=10 ; i++){
				CPPUNIT_ASSERT_EQUAL(*it2 , 10-i);	
				it2++;
			}	
		}
				
			//! Testy przypisania
			/*! Testowana jest poprawnosc dzialania przeciazonego operatora przypisania 
			* list & operator=(const list & other)  
			*/
		void assignmentListOperatorTest(){
			uj::list<int> listaPierwsza;
			int silnia=0;
			for(int i=0; i<=10 ; i++){
				listaPierwsza.push_front(i);
				silnia*=i;
			}
			uj::list<int> listaTrzecia = listaPierwsza;
			uj::list<int>::iterator it3 = listaTrzecia.begin();
			
			for(int i=0; i<=10 ; i++){
				CPPUNIT_ASSERT_EQUAL(*it3 , 10-i);	
				it3++;
			}
			it3 = listaTrzecia.begin();
			int temp=0;
			while(it3!=listaTrzecia.end()){
				temp *= *it3;
				it3++;
			}
				CPPUNIT_ASSERT_EQUAL(temp , silnia);			
		}
			//! Testy funkcji odwracajacej
			/*! Testowana jest poprawnosc dzialania metody odwracajacej szyk listy 
			*/
		void reverseTest(){
			uj::list<int> lista;
			for(int i=0; i<=10 ; i++){
				lista.push_front(i);
			}
			lista.reverse();
			uj::list<int>::iterator it;
			it= lista.begin();
			for(int i=0; i<=10 ; i++){
				CPPUNIT_ASSERT_EQUAL(i ,*it );
				++it;
			}
		}
			//! Testy usuwania elementow
			/*! Testowana jest poprawnosc wykonywania usuwania elementow listy
			*/
		void earseTest(){
			int a=111;
			int b=222;
			int c=333;
			uj::list<int> lista;
			uj::list<int>::iterator it;
			lista.push_front(a);
			lista.push_front(b);
			lista.push_front(c);
			it = lista.begin();
			it++;
			lista.erase(it);
			CPPUNIT_ASSERT_EQUAL(*it, 111);
			it = lista.begin();
			CPPUNIT_ASSERT_EQUAL(*it,333);
		}
			//! Testy funkcji czyszczacej liste oraz test metody empty
			/*! Testowana jest poprawnosc czyszczenia elementow listy oraz metoda empty
			*/
			
		void clearAndEmptyTest(){
			std::string x = "Ala ma koteł";
			size_t sz= 1000;
			uj::list<std::string> lista(sz, x);
			lista.clear();
			CPPUNIT_ASSERT_EQUAL(true, lista.empty());
		}
		//! Testy pobrania rozmiaru
			/*! Testowana jest poprawnosc danych podawanych przez metode size
			*/
		void sizeTest(){
			double x = 7.0;
			size_t sz= 1000;
			uj::list<double> lista(sz, x);
			CPPUNIT_ASSERT_EQUAL(sz , lista.size());
			lista.clear();
			sz=0;
			CPPUNIT_ASSERT_EQUAL(sz , size_t(lista.size()));
			lista.push_front(222.222);
			sz=1;
			CPPUNIT_ASSERT_EQUAL(sz , size_t(lista.size()));
			
		}

};


int main() {

CppUnit::TextUi::TestRunner runner;

runner.addTest( new CppUnit::TestCaller<List_test>(
                       "insertingMethodsTest1", 
                       &List_test::insertingMethodsTest1 ) );
					   
runner.addTest( new CppUnit::TestCaller<List_test>(
                       "insertingMethodsTest2", 
                       &List_test::insertingMethodsTest2 ) );
					   

runner.addTest( new CppUnit::TestCaller<List_test>(		//wylaczyc test jezeli nie ma konstruktora list(size_type n, const value_type& val,)
						"constructorsTest1", 
						&List_test::constructorsTest1) );
						
runner.addTest( new CppUnit::TestCaller<List_test>(	
						"constructorsTest2", 
						&List_test::constructorsTest2) );	
						
runner.addTest( new CppUnit::TestCaller<List_test>(	
						"assignmentListOperatorTest", 
						&List_test::assignmentListOperatorTest) );
						
runner.addTest( new CppUnit::TestCaller<List_test>(	
						"sizeTest", 
						&List_test::sizeTest) );	
						
runner.addTest( new CppUnit::TestCaller<List_test>(	
						"clearAndEmptyTest", 
						&List_test::clearAndEmptyTest) );

runner.addTest( new CppUnit::TestCaller<List_test>(	
						"earseTest", 
						&List_test::earseTest) );

 
runner.addTest( new CppUnit::TestCaller<List_test>(	
						"reverseTest", 
						&List_test::reverseTest) );

 
runner.run();

}
 