#include <memory>
#include <vector>
#include <string>
#include <iostream>

int usage()
{
	std::shared_ptr<std::string> pNico(new std::string("nico"));
	std::shared_ptr<std::string> pJutta(new std::string("juta"));

	(*pNico)[0] = 'N'; //capitalize 
	pJutta->replace(0,1,"J"); 

	std::vector<std::shared_ptr<std::string>> whoMadeCoffee;

	whoMadeCoffee.push_back(pJutta);
	whoMadeCoffee.push_back(pJutta);
	whoMadeCoffee.push_back(pNico);
	whoMadeCoffee.push_back(pJutta);
	whoMadeCoffee.push_back(pNico);

	//print all elements
	for(auto& ptr : whoMadeCoffee)
		std::cout<< *ptr<<" " ;

	std::cout<<std::endl;

	*pNico = "Nicolai";

	for(auto& ptr : whoMadeCoffee)
		std::cout<<*ptr<<" ";
	
	std::cout<<std::endl;

	//print first entries reference
	std::cout<<"use_count : "<<whoMadeCoffee[0].use_count() << std::endl;

	return 0;
}

int construct()
{
	
	//std::shared_ptr<std::string> pNico = new std::string("nico");
	//Error. because it does not allow implicit conversion 
	std::shared_ptr<std::string> pNico{ new std::string("nico")};//use two allocation
	std::shared_ptr<std::string> pJutta = std::make_shared<std::string>("jutta");
	//this way of creation is faster/safer. use one allocation 
	

	//assignment
	std::shared_ptr<std::string> pNicoteen;
	//pNicoteen = new std::string("nicoteen");//Error. no assignment for ordinary pointers
	pNicoteen.reset(new std::string("nicoteen")); 


	//access 
	(*pNicoteen)[0]= 'N' ;//access to address 
	pNicoteen->replace(0,1,"P");//access to method or member variable


	return 0;
}

int destruct()
{
	std::shared_ptr<std::string> pNico(new std::string("nico"), [](std::string* p){ std::cout<<"delete "<<*p<<std::endl; delete p; });
	std::shared_ptr<int> pArr(new int[10], [](int* pInt){ std::cout<<"delete Integer "<<pInt<<std::endl; delete[] pInt; });
	std::shared_ptr<int> pArr2(new int[10], std::default_delete<int[]>() );//it is for unique_ptr because it has to provide a deleter on creation 





	pNico = nullptr;

	return 0;


}

class Person
{
	public:
		std::string name;
		std::shared_ptr<Person> mother;
		std::shared_ptr<Person> father;
#ifndef WEAK
		std::vector<std::shared_ptr<Person>> kids;
#else
		std::vector<std::weak_ptr<Person>> kids;
#endif

		Person(const std::string& n, std::shared_ptr<Person> m = nullptr, std::shared_ptr<Person> f = nullptr) : name(n), mother(m), father(f) {}
		~Person(){std::cout<<"delete "<<name<<std::endl; }

};

std::shared_ptr<Person> initFamily(const std::string& name)
{
	std::shared_ptr<Person> mom(new Person(name+"'s mom"));
	std::shared_ptr<Person> dad(new Person(name+"'s dad"));
	std::shared_ptr<Person> kid(new Person(name, mom, dad));
	mom->kids.push_back(kid);
	dad->kids.push_back(kid);
	return kid;
}





int weakptr()
{
		/* initialization */
	std::shared_ptr<Person> pNico = initFamily("nico");

	std::cout<<"nico's family exists!"<<std::endl;

	std::cout<<"- nico is shared "<<pNico.use_count()<< " times"<<std::endl;
#ifndef WEAK
	std::cout<<"- name of 1st kid of nico's mom : "<<pNico->mother->kids[0]<<std::endl;
#else
	std::cout<<"- name of 1st kid of nico's mom : "<<pNico->mother->kids[0].lock()->name<<std::endl;
	

#endif

	/*initialization*/
	std::shared_ptr<Person> pJim = initFamily("jim");
	std::cout<<"jim's family exists!"<<std::endl;

}


int check_expired()
{
	std::shared_ptr<int> pInt( new int);
	std::weak_ptr<int> weak_pInt(pInt);

	pInt.reset();

	try{
		std::cout<<"is expired? : "<<
		weak_pInt.expired()//might be faster than use_count==0. 
		<<std::endl;
		std::cout<<"use_count : "<<weak_pInt.use_count()<<std::endl;
		std::shared_ptr<int> error(weak_pInt);
	}
	catch (const std::exception& e)
	{
		std::cout<<"exception : "<<e.what()<<std::endl;
	}
}


int main()
{

//	usage();
//	weakptr();
	check_expired();
	return 0;
}
