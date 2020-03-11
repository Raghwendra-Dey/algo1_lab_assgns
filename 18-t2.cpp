#include <iostream>
#include <cstdlib>

using namespace std;

extern int registerme ( int );
extern void startsort ( );
extern int compareballs ( int, int );
extern void verifysort ( int*);
extern void startmatch ( int );
extern int fitsin ( int i, int j );
extern void verifymatch ( int*);

int * merge(int * l1, int *l2, int len1, int len2)
{
	int* s = (int*)malloc((len1+len2)*sizeof(int));
	int i=0, j=0;
	for(int k=0;k<len1+len2;k++)
	{
		if(i==len1)
		{
			while(j<len2)
			{
				s[k] = l2[j];
				k++;j++;
			}
			break;
		}
		else if(j==len2)
		{
			while(i<len1)
			{
				s[k] = l1[i];
				k++;i++;
			}
			break;
		}
		else if(compareballs(l1[i], l2[j]) == -1)
		{
			s[k] = l1[i];
			i++;k++;
		}
		else
		{
			s[k] = l2[j];
			j++;k++;
		}
	}
	return s;
}

int* mergesort(int st, int ed, int* s)
{
	int len = (ed-st);
	if(len == 1)
		return s;
	int* l1 = mergesort(st, (st + len/2), s);
	int* l2 = mergesort((st + len/2), ed, s);
	int* res = merge(l1, l2, len/2, len - len/2);
	return res;
}

int main()
{
	int n;
	cin >> n;
	registerme(n);
	cout << "+++ Sorting the balls..." << endl;
	startsort();
	int* arr = (int*)malloc(n*sizeof(int));
	for(int i=0;i<n;i++)
	{
		arr[i] = i;
	}
	int * s = mergesort(0, n, arr);
	verifysort(s);
	
	
}




















