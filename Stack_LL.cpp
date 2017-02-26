/**This is an implementation of stack using Linked Lists**/

#include<stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;
struct node {
    int data;
    struct node * next;
    struct node * prev;
};
class stack
{
    struct node *top;
public:
    stack()
    {
        top=NULL;
    }
    void push(){
        int value;
        struct node *ptr;
        cout<<"\nPUSH Operation";
        cout<<"\nEnter a number to insert: ";
        cin>>value;
        ptr=new node;
        ptr->data=value;
        ptr->next=NULL;
        if(top!=NULL)
            ptr->next=top;
        top=ptr;
        cout<<"\nNew item is inserted to the stack!!!";

    }
    void pop(){

        struct node *temp;
        if(top==NULL)
        {
            cout<<"nThe stack is empty!!!";
        }
        temp=top;
        top=top->next;
        cout<<"nPOP Operation........nPoped value is "<<temp->data;
        delete temp;
    }
    void show(){
        struct node *ptr1=top;
        cout<<"nThe stack is\n";
        while(ptr1!=NULL)
        {
            cout<<ptr1->data<<" ->";
            ptr1=ptr1->next;
        }
        cout<<"NULL\n";
    }
};
int main()
{
    stack s;
    int choice;
    while(1)
    {
        cout<<"\n-----------------------------------------------------------";
        cout<<"\n\t\tSTACK USING LINKED LIST\n\n";
        cout<<"1:PUSH\n2:POP\n3:DISPLAY STACK\n4:EXIT";
        cout<<"\nEnter your choice(1-4): ";
        cin>>choice;
        switch(choice)
        {
            case 1:
                s.push();
                break;
            case 2:
                s.pop();
                break;
            case 3:
                s.show();
                break;
            case 4:
                return 0;
                break;
            default:
                cout<<"Please enter correct choice(1-4)!!";
                break;
        }
    }
    return 0;
}