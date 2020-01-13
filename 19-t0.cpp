#include <bits/stdc++.h>

using namespace std;

struct node
{
	int data;
	struct node * next1 = NULL;
	struct node * next2 = NULL;
};

struct node* createlist1(int a, int n)
{
	struct node* head;
	head->data = a;
	struct node* curr = head;
	for(int i=2*a;i<n/a;i+=a)
	{
		struct node* n;
		n->data = i;
		curr->next1 = n;
		curr = n;
	}
	return head;
}

struct node* createlist2(int b, int n, struct node* head_a)
{
	struct node* head;
	head->data = b;
	struct node* curr = head;
	struct node* curr_a = head_a;
	for(int i=2*b;i<n/b;i+=b)
	{
		if(curr_a->data=i)
		{
			curr->next2 = curr_a;
			continue;
		}
		else if(curr_a->data<i)
		{
			while((curr_a->data<i)&&(curr_a->next1 != NULL))
			{
				curr_a = curr_a->next1;
			}
		}
		struct node* n;
		n->data = i;
		curr->next2 = n;
		curr = n;
	}
	return head;
}

//pass 1 for the first list and 2 for the second list
void prnlist(struct node* head, int flag)
{
	struct node* curr = head;
	if(flag==1)
	{
		while(curr->next1 != NULL)
		{
			cout << curr->data << ' ';
			curr = curr->next1;
		}
	}
	else if(flag==2)
	{
		while(curr->next2 != NULL)
		{
			cout << curr->data << ' ';
			curr = curr->next2;
		}
	}
}

void prnboth(struct node* a, struct node* b)
{
	struct node* curr_a = a;
	struct node* curr_b = b;
	while((curr_a->next1!=NULL)||(curr_b->next2!=NULL))
	{
		if(curr_a->data==curr_b->data)
		{
			cout << curr_a->data << ' ';
			curr_a = curr_a->next1;
			curr_b = curr_b->next2;
		}
		else if(curr_a->data<curr_b->data)
		{
			cout << curr_a->data << ' ';
			curr_a = curr_a->next1;
		}
		else
		{
			cout << curr_b->data << ' ';
			curr_b = curr_b->next2;
		}
	}
	if(curr_a->next1==NULL)
	{
		while(curr_b->next2==NULL)
		{
			cout << curr_b->data << ' ';
			curr_b = curr_b->next2;
		}
	}
	else
	{
		while(curr_a->next1==NULL)
		{
			cout << curr_a->data << ' ';
			curr_a = curr_a->next1;
		}
	}
}

int main()
{
	int a,b,n;
	cin >> a >> b >> n;
	struct node* head_a = createlist1(a,n);
	struct node* head_b = createlist2(b,n,head_a);
	prnlist(head_a,1);
	prnlist(head_b,2);
	prnboth(head_a,head_b);
}