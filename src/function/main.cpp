#include <iostream>
#include <functional>
#include <vector>

void func(int x, int y)
{
	std::cout<<x+y<<std::endl;
}

class C
{
	public:
		void memfunc(int x, int y) const
		{
			std::cout<<"memfunc! : "<<x+y<<std::endl;
		}

};

int main()
{
	std::vector<std::function<void(int,int)>> tasks;
	tasks.push_back(func);
	tasks.push_back([](int x, int y){ std::cout<<x-y<<std::endl;});

	for(std::function<void(int,int)> f : tasks)
		f(33,22);

	std::function<void(const C&, int, int)>mf;
	mf = &C::memfunc;
	C c;
	mf(c,42,77);
	mf(C(),42,77);

	std::function<void(int,int)> fff;
	try
	{
	fff(42,99);
	}
	catch(std::bad_function_call& err)
	{
		std::cout<< err.what()<<std::endl;
	}


	return 0;
}
