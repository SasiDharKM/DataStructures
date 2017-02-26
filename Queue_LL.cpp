/**This is an implementation of queue using Linked Lists**/

#include<stdio.h>
#include <stdlib.h>
#include<iostream>
using namespace std;
struct node {
    int data;
    struct node * next;
    struct node * prev;
}*front = NULL,*rear = NULL,*p = NULL,*np = NULL;
void enqueue(int a)
{
    np = new node;
    np->data = a;
    np->next = NULL;
    if(front == NULL)
    {
        front = rear = np;
        rear->next = NULL;
    }
    else
    {
        rear->next = np;
        rear = np;
        rear->next = NULL;
    }
}int dequeue()
{
    int x;
    if(front == NULL)
    {
        cout<<"empty queue\n";
    }
    else
    {
        p = front;
        x = p->data;
        front = front->next;
        delete(p);
        return(x);
    }
}

int main() {
    int n, c = 0, x;
    cout << "Enter the number of values to be enqueued into queue\n";
    cin >> n;
    while (c < n) {
        cout << "Enter the value to be entered into queue\n";
        cin >> x;
        enqueue(x);
        c++;
    }
    cout << "\n\nRemoved Values\n\n";
    while (true) {
        if (front != NULL)
            cout << dequeue() << endl;
        else
            break;
    }
    return 0;
    }
