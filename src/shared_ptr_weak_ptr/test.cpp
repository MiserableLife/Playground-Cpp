#include <memory>

class P
{
	public:
		int test()
		{
			std::shared_ptr<P> pp(this);
		}
};

int main()
{

	P; 

	return 0;
}
