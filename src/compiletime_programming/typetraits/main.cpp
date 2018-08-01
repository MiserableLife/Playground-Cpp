#include<iostream>
#include <type_traits>

template <typename T>
void foo(const T& val)
{
	if(std::is_pointer<T>::value)//is_pointer yields std::true_type or std::false_type . ::value yields true or false value. in compile time, if(true) generated. if(false) generated 
		std::cout<< "foo() called for a pointer ";//<< *val << std::endl;//but *val generate compile error ... in case that T is value, function foo for typename T generate code for *val although it will not execute
	else
		std::cout<<"foo() called for a value "<< val <<std::endl;
}


/* solution 
 * overloading implementation */

template <typename T>
void foo_impl(const T& val, std::true_type)
{
	std::cout<<"foo() called for a pointer"<<*val << std::endl;
}
template <typename T>
void foo_impl(const T& val, std::false_type)
{
	std::cout<<"foo() called for a value"<< val << std::endl;
}



template <typename T>
void foo_overload(const T& val)
{
	foo_impl(val, std::is_pointer<T>()); //at compile time, foo_impl(val, std::true_type) or foo_impl(val,std::false_type) is determined 
//	foo_impl(val, std::is_integral<T>());//integral : int/short/ etc... floating-pointer : float, double, long double

}



/* finding common type */

template <typename T1, typename T2>
struct my_common_type{
	typedef decltype( std::declval<T1>() < std::declval<T2>() ? std::declval<T1>() : std::declval<T2>() ) type;
};
template <typename T1, typename T2>
typename my_common_type<T1, T2>::type common_min(const T1& x, const T2& y)
{
	return x<y ? x:y;
}




int main()
{
	int x=0;
	long y=-1;
	foo_overload(&x);
	foo_overload(x);
	common_min<int,long>(x,y);
	return 0;
}
