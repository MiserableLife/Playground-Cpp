#include <iostream>


void analyze_char_array(char* arr, int size)
{
	std::cout<<"size : "<<size<<std::endl;
	for(int i=0; i<size ; i++)
		if(arr[i])
			printf("%2c|",arr[i]);
		else
			printf("  |");
	printf("\n");
	for(int i=0; i<size ; i++)
		printf("%2d|",i);
	printf("\n");

}


int main()
{


	/* Raw String Literals*/
	std::string raw_basic_str = R"(col1	col2	col3	col4)";
	std::string raw_delimeter_str = \
	R"nc(a\
 b\nc()"
     )nc";
	/* before C++11 above string can be expressed below: */
	std::string str = "a\\\n b\\nc()\"\n " ;


	std::cout<<raw_basic_str<<std::endl;
	std::cout<<raw_delimeter_str<<std::endl;
	std::cout<<str<<std::endl;

	/* Encoded String Literals */

	/* encoding prefix specifies a string encoding defined in code */

	char basic[]="char type";
	char u8[] = u8"const char type (utf8)";
	char16_t u[] = u"char16_t type";
	char32_t U[] = U"char32_t type";
	wchar_t L[] = L"wchar_t type";

	analyze_char_array(basic,sizeof(basic));
	analyze_char_array(u8,sizeof(u8));
	analyze_char_array((char*)u,sizeof(u));
	analyze_char_array((char*)U,sizeof(U));
	analyze_char_array((char*)L,sizeof(L));



//raw string 의 R 도 이런 맥락으로 처리됨. 





	return 0;
}
