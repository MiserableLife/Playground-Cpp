#include <iostream>
#include <memory>


class StatusTeller
{
	private:
		int _id;
	public:
		StatusTeller(int id) : _id(id) {std::cout<<_id<<"Construct!"<<std::endl;}
		~StatusTeller(){std::cout<<_id<<"Destruct!"<<std::endl;}
		
};


int main()
{
	std::cout<<"program start!"<<std::endl;

#ifdef S1
	/* scene 1 
	 * assign compile error */
	std::unique_ptr<int> a = std::unique_ptr<int>(new int(3));
	std::unique_ptr<int> b = a; // error!!
#endif


#ifdef S2
	/* scene 2
	 * std::move can resolve */
	int* x=new int;
	std::unique_ptr<int> a(x);
	std::unique_ptr<int> b = std::move(a); // error!!
	std::cout<<x<<std::endl;
	std::cout<<b.get()<<std::endl;
	std::cout<<a.get()<<std::endl;
#endif


#ifdef S3
	/* scene 3 std::unique_str::reset method
	 * when you call reset method, the assigned ptr value is deleted(object destruct) and replaced another value */
	std::unique_ptr<StatusTeller> ptr;
	ptr.reset(new StatusTeller(1));
	ptr.reset(new StatusTeller(2));
	ptr.reset();
	ptr.reset();

#endif


#ifdef S4
	
	std::unique_ptr<StatusTeller> ptr(new StatusTeller(1));
	StatusTeller* st = ptr.release();
	std::cout<<st<<std::endl;


#endif


#ifdef S5 
	auto deleter = [](int* p)
	{
		std::cout<<"unique_ptr deleter called! \n"<<std::endl;delete p;
	};

	std::unique_ptr<int, decltype(deleter)> foo(new int, deleter);

//	std::cout<<"use_count : "<<foo.use_count<<std::endl;


#endif


	std::cout<<"program end!"<<std::endl;
	return 0;
}
