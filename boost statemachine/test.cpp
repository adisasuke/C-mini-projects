#include <iostream>


using namespace std;


struct parent
{

public:
	parent():x(10)
	{

	}
	int& get()
	{
		return x;
	}


private :
int x;

};




struct child:parent
{

public:
	void fun()
	{
		get() = get() + 990;
		int x = get();
		cout<<x<<endl;
		std::cout<<"hello world"<<endl;
	}

};


int main()
{

	child c;
	c.fun();

	return 0;
}