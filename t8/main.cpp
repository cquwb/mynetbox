#include <iostream>
#include <memory>
class Tmp {
	   public:
		       Tmp(int a);
			       ~Tmp();
				       void print__a() { std::cout << "value = " << __a << std::endl; }
					    
					      private:
					       int __a;
};
 
Tmp::Tmp(int a) : __a(a) {
	    std::cout << "start" << __a << std::endl;
}
 
Tmp::~Tmp() {
	    std::cout << "finish" << __a << std::endl;
}
 
int main() {
	/*
	std::shared_ptr<Tmp> sp;  // empty

	Tmp *xx = new Tmp(10);
	sp.reset(xx);  // takes ownership of pointer
	sp->print__a();

	std::cout << "============11" << std::endl;
	Tmp *tt = new Tmp(20);
	sp.reset(tt);  // takes ownership of pointer
	sp->print__a();
	std::cout << "============22" << std::endl;

	sp.reset();  // deletes managed object
				 // sp->print__a();  //crash
	if (!sp.get()) {
		printf("empty\n");
	}
	*/
	///// 下面这个写法是错误的
	//std::shared_ptr<Tmp> sp = new Tmp(10);
	std::shared_ptr<Tmp> sp( new Tmp(10));
	std::shared_ptr<Tmp> sp2 = sp;
	std::cout << "use count :" <<sp.use_count() <<std::endl;
	sp2->print__a();
	sp2.reset();
	std::cout << "use count :" <<sp.use_count() <<std::endl;
	sp->print__a();
	std::cout << "sp print__a()" << std::endl;
	sp2->print__a();
	return 0;
}
