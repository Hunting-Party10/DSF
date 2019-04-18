#ifndef UF_H_
#define UF_H_
class UF
{
private:
	int *a;
	int *size;
	int root(int);
public:
	UF(int);
	~UF();
	void Union(int,int);
};
#include"UF.cpp"
#endif
