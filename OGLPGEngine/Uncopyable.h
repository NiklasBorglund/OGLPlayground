//Uncopyable.h
//Inherit from this to make your object uncopyable
#ifndef UNCOPYABLE_H_INCLUDED
#define UNCOPYABLE_H_INCLUDED
class Uncopyable
{
protected:
	Uncopyable(){}
	~Uncopyable(){}
private:
	Uncopyable(const Uncopyable&);
	Uncopyable& operator=(const Uncopyable&);
};

#endif //UNCOPYABLE_H_INCLUDED