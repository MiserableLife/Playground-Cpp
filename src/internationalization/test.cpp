#include <iostream>
#include <locale>
#include <exception>
#include <fstream>

int main()
{

	std::locale loc;
	const std::collate<char>& col = std::use_facet<std::collate<char>>(loc);
	std::string s1="do my best";
	std::cout<<s1<<std::endl;
	std::cout<< col.hash(s1.data(), s1.data() + s1.length())<<std::endl;

	try
	{
		std::cout<<std::locale("").name()<<std::endl;;
	}
	catch(std::runtime_error& e)
	{
		std::cout<<e.what()<<std::endl;
	}

	char* lpcstr = "typelibraryname";
	unsigned int lcid = 0x4913;
	char syskind=3;
	std::string concatenation = lpcstr;
	std::cout<<concatenation<<std::endl;
	for(int i=0; i< concatenation.length(); i++)
		printf("%02x ",    concatenation.data()[ i] );
	printf("\n");
	concatenation += (char*)&lcid;
	concatenation.insert(concatenation.end(), (char*)&lcid, (char*)&lcid + 4);
	for(int i=0; i<4; i++)
		printf("%02x ", *((char*)&lcid+i)  );
	printf("\n");
	concatenation += syskind;
	for(int i=0; i< concatenation.size(); i++)
		printf("%02x ",    concatenation.data()[ i] );
	printf("\n");
	for(int i=0; i< concatenation.size(); i++)
		printf("%2c ",    concatenation.data()[ i] );
	printf("\n");
	std::cout<< (unsigned long)col.hash(concatenation.data(), concatenation.data() + concatenation.size())<<std::endl;
	std::cout<< (unsigned long)col.hash(concatenation.data(), concatenation.data() + concatenation.length())<<std::endl;


	std::ifstream in;
	std::cout<<"###start###"<<std::endl;
	in.open("data");
	char buffer[255];
	while(in && !in.eof())
	{
		in.getline(buffer,255);

		unsigned int l = 0x4913;
		char syskind=1;
		std::string c = buffer;
		c.insert(c.end(), (char*)&l, (char*)&l + 4);
		c += syskind;
		std::cout<< (unsigned long)col.hash(c.data(), c.data() + c.size())<<std::endl;

	}
	std::cout<<"###end###"<<std::endl;
	in.close();



	return 0;
}
