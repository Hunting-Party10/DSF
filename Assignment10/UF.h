#ifndef UF_H_
#define UF_H_
class UF
{
private:
	int *a;
	int size;
public:
	UF(int);
	~UF();
	void Union(int,int);
	int find(int);
	bool isConnected(int,int);
};
#include"UF.cpp"
#endif
