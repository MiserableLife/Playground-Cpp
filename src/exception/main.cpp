#include <iostream>
#include <string>
#include <stdlib.h>
#include <exception>


static std::exception_ptr eptr=nullptr;
int exception_with_enum(int argc, char* argv[])
{
	/* exception generating with enum value */	
	enum xxx
	{
		ERROR1,
		ERROR2,
		ERROR3
	};
	try
	{
		if(argc ==2 && std::string(argv[1]) == "err1")
			throw ERROR1;
		std::cout<<"well? nothing happend! "<<std::endl;
		return 0;
	}
	catch( int& err)
	{
		switch(err)
		{	
			std::cout<<"err";
			case ERROR1:
				std::cout<<"1";
				break;
			case ERROR2:
				std::cout<<"2";
				break;
			case ERROR3:
				std::cout<<"3";
				break;

		}
	}
	catch (enum xxx kk)
	{
		std::cout<<"kk : "<<kk;
	}
	std::cout<<"happens!"<<std::endl;
	return 0;
}


int exception_with_class(int code)
{
	// logic_error / system_error/ runtime_error / out_of_range
	try
	{
		switch(code)
		{
			case 1:
				throw std::logic_error("code1 you generated....");
				break;
			case 2:
				throw std::logic_error("you generated code2....");
				break;
			default:
				break;

		}
	}
	catch(const std::exception& e)
	{
		std::cout<< e.what()<<std::endl;
		eptr = std::current_exception();//store current exception 
	}
	
	return 0;	
}
//		make_error_code()
int rehandling_e_with_exceptionptr()
{
	if(eptr)
	{
		try{
			std::rethrow_exception(eptr);
		}
		catch(const std::logic_error& le)
		{
			std::cout<<"logic error... "<< le.what()<<std::endl;

		}
		catch(const std::exception& e)
		{
			std::cout<<"i dont know what exception...."<<std::endl;
		}

	}

	return 0;
}



int main(int argc, char* argv[])
{

	exception_with_class(atoi(argv[1]));
	rehandling_e_with_exceptionptr();

	return 0;
}
