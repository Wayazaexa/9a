#include "ExampleClass.hh"

ExampleClass::ExampleClass() 
{ 
	x=3; 
	y='a'; 
	z=0.2; 
}

ExampleClass::ExampleClass(int x,char y,double z) 
{
	this->x=3;
	this->y='a';
	this->z=0.2; 
}

void ExampleClass::doit() 
{ 
	std::cout << "ExampleClass::doit()" << std::endl; 
}

void ExampleClass::doit(int what) 
{
	std::cout << "ExampleClass::doit( what=" << what << ")" << std::endl; 
}

std::ostream& operator<<(std::ostream &out, const ExampleClass &c)
{
	out << "x=" << c.x;
	return out ;
}
