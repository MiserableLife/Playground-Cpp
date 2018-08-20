#include <iostream>
#include <regex>

int main()
{	
	std::string data= "<person>\n"
					  " <first>Nico</first>\n"
					  " <last>Josuttis</last>\n"
					  "</person>\n";
	std::string rdata = R"(<person>
 <first>Nico</first>
 <last>Josuttis</last>
</person> )";

	std::regex reg("<(.*)>(.*)</(\\1)>");
	std::cout<<std::regex_replace(data, 
								  reg, 
								  "<$1 value=\"$2\"/>") <<std::endl;


	//sed syntax
	std::cout<< std::regex_replace(data,
								   reg,
								   "<\\1 value=\"\\2\"/>",
								   std::regex_constants::format_sed) <<std::endl;



	return 0;
}
