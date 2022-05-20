#include <iostream>

class Student {
	public:
	Student();
	~Student();
};


Student::Student() {
	std::cout << "constructor" << std::endl;	
}


Student::~Student() {
	std::cout << "destructor" << std::endl;	
}

int main() {
	Student *stu = new Student();
	Student *stu2 = new Student[10];

	std::cout << "begin delete" << std::endl;

	delete stu;
	delete [] stu2;
}
