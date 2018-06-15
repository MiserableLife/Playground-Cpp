#include <iostream>
#include <vector>



int main()
{
	std::vector<int> x;
	for(int i=0; i< 10; i++)
		x.push_back(i);

	for(auto it = x.begin();it!= x.end(); it++)
	{
		*it = 4;
	}

	
	for(auto it = x.begin();it!= x.end(); it++)
		std::cout<<*it<<std::endl;



	return 0;
}


