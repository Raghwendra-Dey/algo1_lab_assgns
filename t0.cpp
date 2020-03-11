/*
Name: Raghwendra Dey
link: https://cse.iitkgp.ac.in/~abhij/course/lab/Algo1/Spring20/A2.pdf
i have added some more features as well ;)
*/

#include <iostream>
#include <stdlib.h>

using namespace std;

struct node
{
	int data;
	struct node* h;
	struct node* v;
};

struct node* initcal()
{
	struct node* c;
	
	struct node* curr = (struct node*)malloc(1*sizeof(struct node));
	curr->data = 0;
	curr->h = NULL;
	curr->v = NULL;
	
	c = curr;
	
	struct node* curr_h = curr;
	struct node* curr_v = curr;
	struct node* start = curr;
	
	for(int i=0;i<20;i++)
	{
		for(int j=0;j<21;j++)
		{
			if((i==0)&&(j==0))
			{
				continue;
			}
			struct node* curr = (struct node*)malloc(1*sizeof(struct node));
			curr->data = 0;
			curr->h = NULL;
			curr->v = NULL;
			if(j==0)
			{
				start = curr;
				curr_h = curr;
			}
			if(j!=0)
			{
				curr_h->h = curr;
				curr_h = curr;
			}
			if(i!=0)
			{
				curr_v->v = curr;
				curr_v = curr_v->h;
			}
		}
		curr_v = start;
	}
	return c;
}

int storemonth(struct node* c, int month, int st_day,bool is_leap)
{
	int univ_row = month/3;
	int univ_col = month%3;
	int row = univ_row*5;
	int col = univ_col*7;
	int date = 1;
	int num_days;
	
	struct node* curr = c;
	
	for(int i=0;i<row;i++)
	{
		curr = curr->v;
	}
	for(int j=0;j<col;j++)
	{
		curr = curr->h;
	}
	
	struct node* start = curr;
	
	if(month == 1)
	{
		if(is_leap)
		{
			num_days = 29;
		}
		else
		{
			num_days = 28;
		}
	}
	else if(month <= 6)
	{
		num_days = 31 - month%2;
	}
	else
	{
		num_days = 30 + month%2;
	}
	
	if((st_day == 5)&&(num_days==31))
	{
		curr->data = 31;
		curr = start;
	}
	else if(st_day == 6)
	{
		if(num_days == 31)
		{
			curr->data = 30;
			curr = curr->h;
			curr->data = 31;
			curr = curr->h;
		}
		else if(num_days == 30)
		{
			curr->data = 30;
		}
		curr = start;
	}
	
	for(int i=0;i<7;i++)
	{
		if(i<st_day)					//error
		{
			curr = curr->h;
			continue;
		}
		curr->data = date;
		curr = curr->h;
		date++;
	}
	start = start->v;
	curr = start;
	
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<7;j++)
		{
			if(date>num_days)			//error
				return num_days;
			curr->data = date;
			curr = curr->h;
			date++;
		}
		start = start->v;
		curr = start;
	}
	return num_days;
}

void raw_print_borders(struct node* c)
{
	struct node* curr = c;
	struct node* start = curr;
	
	for(int i=0;i<20;i++)
	{
		if(i%5==0)
			cout << endl << endl;

		for(int j=0;j<21;j++)
		{
			if(curr->data)
			{
				if((curr->data)/10==0)
					cout << ' ';
				cout << curr->data << ' ';
			}
			else
				cout << "   ";
			curr = curr->h;
			if((j+1)%7==0)
				cout << " | ";
		}
		cout << endl;
		start = start->v;
		curr = start;
	}
	cout << endl << endl;
}

void neatprint(struct node* c, int yr)
{
	struct node* curr = c;
	struct node* start = curr;
	cout << "                           ";
	cout << "Calender of " << yr << endl;
	
	for(int i=0;i<20;i++)
	{
		if(i%5==0)
		{
			cout << endl;
			switch(i)
			{
				case 0:
					cout << "       January       ";
					cout << "         February      ";
					cout << "          March        " << endl;
					break;
				case 5:
					cout << "        April        ";
					cout << "           May         ";
					cout << "          June         " << endl;
					break;
				case 10:
					cout << "         July        ";
					cout << "          August       ";
					cout << "        September      " << endl;
					break;
				case 15:
					cout << "       October       ";
					cout << "         November      ";
					cout << "         December      " << endl;
					break;
			}
			for(int i=0;i<3;i++)
			{
				cout << "Su Mo Tu We Th Fr Sa   ";
			}
			cout << endl;
		}

		for(int j=0;j<21;j++)
		{
			if(curr->data)
			{
				if((curr->data)/10==0)
					cout << ' ';
				cout << curr->data << ' ';
			}
			else
				cout << "   ";
			curr = curr->h;
			if((j+1)%7==0)
				cout << "  ";
		}
		cout << endl;
		start = start->v;
		curr = start;
	}
	cout << endl << endl;
}

int getyear()
{
	int yr;
	cout << "Enter the year: ";
	cin >> yr;
	return yr;
}

void fill_calendar(struct node* c, int month, int st, int yr)
{
	int num_days;
	bool is_leap = (yr%4==0);
	int st_day = st;
	for(int i=month;i<12;i++)
	{
		num_days = storemonth(c,i,st_day,is_leap);
		st_day += num_days;
		st_day %= 7;
	}
	st_day = st;
	for(int i=month;i>=0;i--)
	{
		num_days = storemonth(c,i,st_day,is_leap);
		if(i==1)
			num_days = 31;
		else if(i==2)
			num_days = 28 + is_leap;
		else if(i!=7)
		{
			num_days = (num_days==31)?(30):(31);
		}
		st_day -= num_days;
		st_day += 35;
		st_day %= 7;
	}
}

//calculated wrt 2020
int cal_st_day(int yr, bool is_leap)
{
	int st_day = 3;
	if(yr>2020)
	{
		int diff = (yr-2020);
		st_day = 3 + diff*365 + diff/4;
		st_day %= 7;
	}
	else
	{
		int diff = 2020 - yr;
		st_day = 3 + ((diff*365)/7 + 1)*7 - diff*365 - diff/4;
		st_day %= 7;
	}
	return st_day;
}

void fill_calendar1(struct node* c, int yr)
{
	int num_days;
	bool is_leap = (yr%4==0);
	int st_day = cal_st_day(yr, is_leap);
	
	for(int i=0;i<12;i++)
	{
		num_days = storemonth(c,i,st_day,is_leap);
		st_day += num_days;
		st_day %= 7;
	}
}

int main()
{
	struct node* c = initcal();
	int yr = getyear();
	// fill_calendar(c,4,5,yr);
	fill_calendar1(c,yr);
	neatprint(c, yr);
}






















