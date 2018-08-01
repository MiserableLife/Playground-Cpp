#include <iostream>
#include <ratio>


int main()
{

	typedef std::ratio<5,3> fiveThirds; // it is not a variable... it also be metaprogrammed.... 
//	std::ratio<5,3> testfiveThirds; // it is not a variable... it also be metaprogrammed.... 
	std::cout<< fiveThirds::num<<"/"<<fiveThirds::den<<std::endl;

	/* four arithmetic calculation */
	typedef std::ratio_add<std::ratio<2,7>, std::ratio<2,6>>::type add;
	std::cout<<add::num<<"/"<<add::den<<std::endl;
	typedef std::ratio_subtract<std::ratio<2,7>, std::ratio<2,6>>::type sub;
	std::cout<<sub::num<<"/"<<sub::den<<std::endl;
	typedef std::ratio_multiply<std::ratio<2,7>, std::ratio<2,6>>::type mul;
	std::cout<<mul::num<<"/"<<mul::den<<std::endl;
	typedef std::ratio_divide<std::ratio<2,7>, std::ratio<2,6>>::type div;
	std::cout<<div::num<<"/"<<div::den<<std::endl;


	std::pico;
	std::cout<<std::pico::num<<"/"<<std::pico::den<<std::endl;
	std::nano;
	std::cout<<std::nano::num<<"/"<<std::nano::den<<std::endl;
	std::micro;
	std::cout<<std::micro::num<<"/"<<std::micro::den<<std::endl;
	std::milli;
	std::cout<<std::milli::num<<"/"<<std::milli::den<<std::endl;
	std::centi;
	std::cout<<std::centi::num<<"/"<<std::centi::den<<std::endl;
	std::deci;
	std::cout<<std::deci::num<<"/"<<std::deci::den<<std::endl;
	std::deca;
	std::cout<<std::deca::num<<"/"<<std::deca::den<<std::endl;
	std::hecto;
	std::cout<<std::hecto::num<<"/"<<std::hecto::den<<std::endl;
	std::kilo;
	std::cout<<std::kilo::num<<"/"<<std::kilo::den<<std::endl;

	return 0;
}
