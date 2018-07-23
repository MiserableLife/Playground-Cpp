#include <iostream>
#include <limits>


class Done
{

};

int main()
{


	std::cout<<  "min(int) : " << std::numeric_limits<int>::min() <<std::endl;
	std::cout<<  "max(int) : " << std::numeric_limits<int>::max() <<std::endl;
	std::cout<<  "lowest(int) : " << std::numeric_limits<int>::lowest() <<std::endl;
	std::cout<<  "digits(int) : " << std::numeric_limits<int>::digits <<std::endl;
	std::cout<<  "digits10(int) : " << std::numeric_limits<int>::digits10 <<std::endl;
	std::cout<<  "max_digits10(int) : " << std::numeric_limits<int>::max_digits10 <<std::endl;
	std::cout<<  "radix(int) : " << std::numeric_limits<int>::radix <<std::endl;
	std::cout<<  "min_exponent(int) : " << std::numeric_limits<int>::min_exponent <<std::endl;
	std::cout<<  "max_exponent(int) : " << std::numeric_limits<int>::max_exponent <<std::endl;
	std::cout<<  "epsilon(int) : " << std::numeric_limits<int>::epsilon() <<std::endl;
	std::cout<<  "is_specialized(int) : " << std::numeric_limits<int>::is_specialized <<std::endl;
	std::cout<<  "is_specialized(Done) : " << std::numeric_limits<Done>::is_specialized <<std::endl;//type Done is specialized? (defined?)

	return 0;
}
