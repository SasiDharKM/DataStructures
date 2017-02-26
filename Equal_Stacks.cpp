/** This is a program to check if two stacks are equal**/


#include <iostream>
using namespace std;
typedef struct equ
{
    int stack[100];
    int top;
};
int main()
{
	equ s1,s2;
    int m,n;
	int i;
    bool check =true;
	cout<<"Enter the size of first stack";
	cin>>m;
	cout<<"Enter size of the second stack";
	cin>>n;
	if(m==n)
	{
		s1.top=-1;
		s2.top=-1;
		int a=0;
		cout<<"Enter the elements of first stack:";
		for(s1.top=0;s1.top<m;s1.top++)
		{
			cin>>a;
			s1.stack[s1.top]=a;
		}
		cout<<"Enter the elements of second stack:";
		for(s2.top=0;s2.top<n;s2.top++)
		{
			cin>>a;
			s2.stack[s2.top]=a;
		}
		for(i=0;i<m;i++)
		{
			if(s1.stack[i]!=s2.stack[i])
			check = false;
		}
		if(check)
		cout<<"Two stacks are equal";
		else
		cout<<"Two stacks are not equal";
}
else
cout<<"Two stacks are not equal";
return 0;
}

