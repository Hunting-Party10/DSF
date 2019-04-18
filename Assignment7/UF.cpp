UF::UF(int n)
{
	a = new int[n+1];
	size = new int[n+1];
	for(int i = 0 ;i<n+1;i++)
	{
		a[i] = i;
		size[i] = 1;
	}
}
UF::~UF()
{
	delete[] a;
	delete[] size;
}

bool UF::isConnected(int x,int y)
{
	return root(x) == root(y);
}

void UF::Union(int x,int y)
{
	int p = root(x);
	int q = root(y);
	if(size[p] > size[q])
	{
		a[q] = p;
		size[p] +=size[q];
	}
	else
	{
		a[p] = q;
		size[q] +=size[p];
	}
}

int UF::root(int i)
{
	while(a[i] != i)
	{
		a[i] = a[a[i]];
		i = a[i];
	}
	return i;
}
