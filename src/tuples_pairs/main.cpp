#include <iostream>
#include <utility>
#include <tuple>


void f(std::pair<int,const char*>)
{}
void g(std::pair<const int, std::string>)
{}

class Foo
{

	public:
		Foo(std::tuple<int, float>){std::cout<<"Foo::Foo(tuple)"<<std::endl;}
		template<typename ...Args>
		Foo(Args... args){std::cout<<"Foo::Foo(args...)"<<std::endl;}
};

int main()
{

	std::pair<int, const char*> p(42,"hello");
	f(p);// OK; copy constructor called
	g(p);// OK; template constructor 


	f(std::make_pair(42, "empty"));
	f({42, "empty"});//initializer lists can replace make_pair 
	g(std::make_pair(42, "chiar")); 
	g({42, "chiar"});  

	std::string s="s!", t="t!";
	int i=0;
	auto p = std::make_pair(std::move(s),std::move(t) );
	auto pp = std::make_pair(std::ref(i), std::ref(i) );
	++pp.first;
	++pp.second;
	std::cout<<"i : "<< i <<std::endl;



	std::tuple<int, float> t(1,2.22);

	std::pair<int, Foo> p1(42,t);
	// 
	std::pair<int, Foo> p2(std::piecewise_construct, std::make_tuple(42), t);
	// 튜플로 인자를 받아서 그거를 다 해체한 다음 생겨난 element 들을 argument로 보내서 필요한 구조체 생성 
	// The construct of this form breaks up two tuples into elements. Then, it creates argument of std::pair. in this case, int and Foo 
	// when making Foo, the constructor Foo(1, 2.22) is called not Foo(std::tuple<int, float> ) because the copy of tuple t was broken up. 




	auto tiepair = std::make_pair('a','b');
	char c;
	std::tie(std::ignore, c) = tiepair; // extract second value into c ignoring first one. 



}
