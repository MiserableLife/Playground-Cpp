#include <iostream>
#include <locale>

int main()
{

	std::locale loc;
	const std::collate<char>& col = std::use_facet<std::collate<char>>(loc);
	std::string s1="do my best";
	std::cout<<s1<<std::endl;
	std::cout<< col.hash(s1.data(), s1.data() + s1.length())<<std::endl;


	return 0;
}
