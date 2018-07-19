/*
 *
 * there are overloaded functions , handling integer and pointer parameter respectively
 * when I use f(NULL) to call the function handling pointer with null pointer,  ambiguous error happen!
 * It's because NULL is defined as 0 
 * If we use nullptr instead, the problem solved.  
 * It is one of the C++11 features
 *
 *
 */




#include <iostream>


void f(int x)
{
	std::cout<<"function f(int x) for integer parameter is called!"<<std::endl;
}	
void f(void*)
{
	std::cout<<"function f(void* x) for pointer is called!"<<std::endl;
}

int main()
{
	f(0); // calls f(int) 
	f(NULL); // calls f(int) if NULL is 0, ambiguous otherwise 
	f(nullptr); // calls f(void*) 

	return 0;
}
