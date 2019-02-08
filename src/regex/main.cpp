#include <regex>
#include <iostream>
#include <exception>
#include <string>
#include <iomanip>

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

	found = std::regex_match("XML tag : <tag>value</tag>",
			std::regex(".*<(.*)>.*</\\1>.*")); //success match.  

	print(i++, found);

	found = std::regex_search("XML tag : <tag>value</tag>",
			std::regex("<(.*)>.*</\\1>")); //success search  


	print(i++, found);
	found = std::regex_search("XML tag : <tag>value</tag>",
			std::regex(".*<(.*)>.*</\\1>.*")); //success search.  

	print(i++, found);


	std::string data = "XML tag : <tag>value</tag>";
	std::string data2 = "\"InstallDir\"=\"C:\\\\Users\\\\Dongwan\\\\AppData\\\\Local\\\\Amazon\\\\Kindle\\\\application\"\r";
	std::smatch m;

	//char* data = ""
	//std::cmatch m
	found = std::regex_search(data,
			m,
			std::regex("<(.*)>.*</\\1>")); //success search  
	found = std::regex_search(data2,
			m,
			std::regex("(.*)=(.*)")); //success search  


	std::cout<<"m.emtpy() : "<<m.empty()<<std::endl;
	std::cout<<"m.size() : "<<m.size()<<std::endl;
	if(found)
	{
		std::cout<<"m.str() : "<<m.str()<<std::endl;
		std::cout<<"m.str() : "<<m[0].str()<<std::endl;
		std::cout<<"m.str() : "<<m[1].str()<<std::endl;
		std::cout<<" : "<<(data2[0]=='\"')<<std::endl;

	}


	return 0;
}
