UF::UF(int n)
{
	a = new int(n+1);
	size = n;
	for(int i = 0;i <= n;i++)
		a[i] = i;
}
UF::~UF()
{
	a = NULL;
}

int UF::find(int x)
{
	return a[x];
}

bool UF::isConnected(int x,int y)
{
	return find(x) == find(y);
}

void UF::Union(int x,int y)
{
	int p = find(x);
	int q = find(y);
	
	for(int i = 0;i <= size; i++)
		if(a[i] == p)
			a[i] = q;
}

