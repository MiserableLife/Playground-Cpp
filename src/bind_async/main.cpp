#include <iostream>
#include <functional>


/* Callable Objects */
void func(int x, int y)
{
	std::cout<<"func called with x : "<<x<<" y : "<<y<<std::endl;
}
auto l = [](int x, int y){std::cout<<"lambda called with x : "<<x<<" y : "<<y<<std::endl; };
class FunctionObject
{
	public:
		void operator() (int x, int y) const
		{
			std::cout<<"FunctionObject called with x : "<<x << " y : "<<y<<std::endl;
		}
		void memfunc(int x, int y) const
		{
			std::cout<<"member function memfunc called with x : "<< x<< " y : "<<y<<std::endl;
		}
};


int main()
{
	FunctionObject fo;
	int i=0,j=1;
//	std::cout<<"start"<<std::endl;
	auto a= std::bind(func,i++,j++);
	auto b= std::bind(l, i++,j++);
	auto c=	std::bind(FunctionObject(), i++,j++);
	auto d=	std::bind(&FunctionObject::memfunc, fo, i++, j++);
	auto e=	std::bind(&FunctionObject::memfunc, &fo, i++, j++);
	a();b();c();d();e();


	/*you can make a another callable object with parameter... */
	auto aa= std::bind(func,std::placeholders::_1,std::placeholders::_2);
	aa(999,999);

	return 0;


}
