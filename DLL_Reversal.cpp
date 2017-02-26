/**This is an program for reversing a Doubly Linked List**/

#include<stdio.h>
#include <stdlib.h>
struct node {
    int data;
    struct node * prev;
    struct node * next;
}*head, *last;
int main()
{
    int i, data,n;
    struct node *newNode,*temp,*current;
    printf("Enter the no of nodes:");
    scanf("%d",&n);
    if(n >= 1)
    {
        head = (struct node *)malloc(sizeof(struct node));
        printf("Enter data of 1 node: ");
        scanf("%d", &data);
        head->data = data;
        head->prev = NULL;
        head->next = NULL;
        last = head;
        for(i=2; i<=n; i++)
        {
            newNode = (struct node *)malloc(sizeof(struct node));
            printf("Enter data of %d node: ", i);
            scanf("%d", &data);
            newNode->data = data;
            newNode->prev = last;
            newNode->next = NULL;
            last->next = newNode;
            last = newNode;
        }
    }
    printf("Before Reversal\n");
    if(head == NULL)
    {
        printf("List is empty.\n");
    }
    else
    {
        temp = head;
        printf("DATA IN THE LIST:\n");
        i=1;
        while(temp != NULL)
        {
            printf("DATA of %d node = %d\n", i, temp->data);
            i++;
            temp = temp->next;
        }
    }
    current = head;
    while(current != NULL)
    {
        temp = current->next;
        current->next = current->prev;
        current->prev = temp;
        current = temp;
    }
    temp = head;
    head = last;
    last = temp;

    printf("After Reversal\n");
    if(head == NULL)
    {
        printf("List is empty.\n");
    }
    else
    {
        temp = head;
        printf("DATA IN THE LIST:\n");
        i=1;
        while(temp != NULL)
        {
            printf("DATA of %d node = %d\n", i, temp->data);
            i++;
            temp = temp->next;
        }
    }
}