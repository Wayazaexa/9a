#include <iostream>

#ifndef EXAMPLE_CLASS
#define EXAMPLE_CLASS

class ExampleClass {
	int x;
	char y;
	double z;
public:
	ExampleClass();
	ExampleClass(int x,char y,double z);
	void doit();
	void doit(int what);
	friend std::ostream& operator<<(std::ostream &out, const ExampleClass &c);
};

#endif
