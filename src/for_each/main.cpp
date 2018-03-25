/*
 *	latest programming languages like matlab or python have different syntax from the one C++ has
 *	it is also called for-each syntax 
 *	for( decl : coll) 
 *	{ statement } 
 *
 *
 * */


#include <iostream>
#include <vector>

//Thus, a generic function to print all elements of a collection should be implemented as follows: type auto make it possible! 
template<typename T>  
void printElements (const T& coll) 
{ 
	for (const auto& elem : coll) 
	{ std::cout << elem << std::endl; } 
}


int main()
{

	for ( int i : { 2, 3, 5, 7, 9, 13, 17, 19 } ) 
	{ std::cout << i << std::endl; }
 
	std::vector<int> vec{1,2,3,4}; 
	for ( auto& elem : vec ) 
		{ elem *= 3; } // each element of vector is multiplied by 3. and it is applied because it is refenreced 





	return 0;
}
