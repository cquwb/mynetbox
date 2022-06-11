#include <iostream>

template <typename T>
class Auto_ptr1
{
	T* m_ptr;
	public:
	//Pass in a pointer to "own" via the constructor
	Auto_ptr1(T* ptr=nullptr)
		:m_ptr(ptr)
	{
	}

	//The destructor will make sure it gets deallocated
	~Auto_ptr1()
	{
		delete m_ptr;
	}

	//Overload dereference and operator-> so we can use Auto_ptr1 like m_ptr.
	T& operator*() const { return *m_ptr; }
	T* operator->() const { return m_ptr; }
};

//A sample class to prove the above works
class Resource
{
	public:
		Resource() { std::cout << "Resource acquired\n"; }
		~Resource() { std::cout << "Resource destroyed\n"; }
		void sayHi() {std::cout << "Hi!\n"; }
};

void someFunction()
{
	Auto_ptr1<Resource> ptr(new Resource());  //ptr now owns the Resource

	int x;
	std::cout << "Enter an integer: ";
	std::cin >> x;

	if (x == 0)
		return; // the function returns early

	// do stuff with ptr here
	ptr->sayHi();
}

void passByValue(Auto_ptr1<Resource> res)
{
	std::cout << "passByValue\n";
}


int main()
{
	Auto_ptr1<Resource> res1(new Resource());
	passByValue(res1);
	std::cout << "main end\n";
	return 0;
} 
//res goes out of scope here, and destroys the allocated Resource for us
