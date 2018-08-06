#include <regex>
#include <iostream>
#include <exception>

void print(int n , bool b)
{
	std::cout<<"#"<<n ; 
	if(b)
	 	std::cout<<"  success!";
	else
		std::cout<< "  fail!";
	std::cout<< std::endl;
}


int main()
{

	/*Match
	 * Search
	 * Tokenize
	 * Replace
	 * */

	int i=1;
	std::regex reg1("<.*>.*</.*>");
	bool found = std::regex_match("<tag>value</tag>", //data
																						reg1); //regular expression

	print(i++, found);
	std::regex reg2("<(.*)>.*</\\1>");  //    () means caputre group. we can refer to it in regular expression 
	found = std::regex_match("<tag>value</tag>", 
														reg2);

	print(i++, found);

	found = std::regex_match("XML tag : <tag>value</tag>",
			std::regex("<(.*)>.*</\\1>")); //fail to match.  
	print(i++, found);



									


	return 0;
}
