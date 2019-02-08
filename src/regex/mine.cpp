#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include <unordered_map>

int main(int argc, char* argv[])
{
	if(argc != 3) 
	{
		std::cout<<"Usage : "<<argv[0]<< " dllfile mapfile"<<std::endl;
		return 1;
	}


	std::ifstream in;
	bool found = false;
	std::regex pattern("<symbol.* ordinal=\"([^\"]*)\" .*>(.*)</symbol>");
	char buffer[0x10000];
	std::smatch m;
	std::unordered_map<std::string, int> cache;
	in.open(argv[2]);

	while(in && !in.eof())
	{
		in.getline(buffer,255);
		std::string line = buffer;
		found = std::regex_search(line,m, pattern);
		if(!found)
			continue;

//  func_name               ordinal
		cache[m[2]] =  std::stoi(m[1]);

	}
	in.close();



	in.open(argv[1]);
	std::string funcfile;
	while(in && !in.eof())
	{

		in.read(buffer,0x10000);
		funcfile += buffer;
	}
	in.close();

	//std::cout<<funcfile<<std::endl;

//([a-zA-Z0-9_]*)[\\s\\t\\n]+
//	std::cout<<"##############"<<std::endl;
//	std::regex func_pattern("\\n([a-zA-Z0-9_]*)[\\s\\t\\n]+([a-zA-Z0-9_]*)[\\s\\t\\n]*\\(([^\\(]*)\\)[\\s\\t\\n]*\\{[^\\{]*\\}");
	std::regex func_pattern("\\n([a-zA-Z0-9_]*)[\\s\\t\\n]+(WINAPI)?[\\s\\t\\n]?([a-zA-Z0-9_]*)[\\s\\t\\n]*\\(([^\\(]*)\\)[\\s\\t\\n]*\\{[^\\{]*\\}");


	while(1)
	{
		found = std::regex_search(funcfile,m, func_pattern);
		if(!found)
			break;

		std::cout<<m[1].str()<<" TOC_ORDINAL(oleaut32,\n"<<m[3].str()<<",\n"<<cache[m[3].str()]<<",\n"<< m[4].str()<<");"<<std::endl;
		funcfile = m.suffix().str();
//		std::cout<<"funcfile : "<<funcfile<<std::endl;

	}

}
