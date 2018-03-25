/*
 *	Before C++11, there are various initialization method. 
 *	e.g.) int x[]={1,2,3}; //array initialization
 *		  std::string x="myname"; // assign operator initialization
 *		  std::ifstream in("file"); //class initialization( constructor)
 *
 * 	Since C++!1, only syntax covers them. Moreover, it is more powerful. 
 *
 *
 */


#include <iostream>
#include <vector>
#include <string>
#include <complex>


int main()
{

	int values[] { 1, 2, 3 }; //array initialization
	std::vector<int> v{ 2, 3, 5, 7, 11, 13, 17 }; //collection initialization
	std::vector<std::string> cities { "Berlin", "New York", "London", "Braunschweig", "Cairo", "Cologne" }; 
	std::complex<double> c{4.0,3.0}; // equivalent to c(4.0,3.0) class initialization

	std::cout<<"int values[]{1,2,3}; is initialized as :"<<std::endl;
	for(int i=0; i< sizeof(values)/sizeof(int); i++)
		std::cout<<values[i]<<" ";
	std::cout<<std::endl;

	std::cout<<"std::vector<int> v{2,3,5,7,11,13,17}; is initialized as :"<<std::endl;
	for(int i=0; i< v.size(); i++)
		std::cout<<v[i]<<" ";
	std::cout<<std::endl;

	std::cout<<"std::vector<std::string> cities{\"Berlin\", \"New York\", \"London\", \"Braunschweig\", \"Cairo\", \"Cologne\" }; is initialized as :"<<std::endl;
	for(int i=0; i< cities.size(); i++)
		std::cout<<cities[i]<<" ";
	std::cout<<std::endl;





	/* it can be used to initialize base type to 0. if it is pointer, to nullptr */


	int i; // i has undeﬁned value 
	int j{}; // j is initialized by 0 
	int* p; // p has undeﬁned value 
	int* q{}; // q is initialized by nullptr 
	std::cout<<"i : "<<i<<" j : "<<j<< " p : "<<p<<" q : "<<q<<std::endl;


	/* narrowing initialization ( the type casting where precision loss occuring as type coverage shrinks ... e.g. int x= 4.2) 
	 * cannot be initialized by uniform initialization {} 
	 * */


	int x1(5.3); // OK, but OUCH: x1 becomes 5 => narrowing initialization
	int x2 = 5.3; // OK, but OUCH: x2 becomes 5 
//	int x3{5.0}; // ERROR: narrowing 
//	int x4 = {5.3}; // ERROR: narrowing 
	char c1{7}; // OK: even though 7 is an int, this is not narrowing char c2{99999}; // ERROR: narrowing (if 99999 doesn’t ﬁt into a char) std::vector v1 { 1, 2, 4, 5 }; // OK 
//	std::vector<int> v2 { 1, 2.3, 4, 5.6 }; // ERROR: narrowing doubles to ints 
 



	/* how to initialize class or struct type which defined by user ? 
	 * answer : std::initializer_list
	 * */

	class P
	{
	public:
		P(int x, int y)
		{
			std::cout<<"constructor P(int x, int y) is called!"<<std::endl;
		}
		P(std::initializer_list<int> il)
		{
			std::cout<<"constructor P(std::initializer_list il) is called!"<<std::endl;
		}
	};

	P pp(77,5); // calls P::P(int,int)
	P pq{77,5}; // calls P::P(initializer_list)
	P pr{77,5,42}; // calls P::P(initializer_list)



	return 0;
}
