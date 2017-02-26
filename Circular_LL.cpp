/**This is an implementation of Circularly Linked Lists**/

#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;
struct node{
    int data;
    struct node *next;
}*last;

class circular_list{
public:
    void create_node(int val){
        struct node *temp;
        temp = new(struct node);
        temp->data = val;
        if (last==NULL){
            last =temp;
            temp->next = last;
        }
        else
        {
            temp->next =last->next;
            last->next = temp;
            last = temp;
        }
    }

    void add_begin(int val){
        if (last == NULL){
            cout<<"list is empty\n";
            return;
        }
        struct node *temp;
        temp =new(struct node);
        temp->data =val;
        temp->next = last->next;
        last->next =temp;
    }
    void add_after(int val,int pos){
        if(last==NULL){
            cout<<"list is empty\n";
        }
        struct node *temp,*s;
        s= last->next;
        for(int i = 0;i< pos-1;i++){
            s=s->next;
            if(s== last->next){
                cout<<"There are less than "<<pos<<"in the list\n";
                return;
            }
        }
        temp= new(struct node);
        temp->next =s->next;
        temp->data =val;
        s->next =temp;
        if(s == last){
            last=temp;
        }
    }

    void display_list(){
        struct node *s;
        if (last == NULL)
        {
            cout<<"List is empty, nothing to display\n";
            return;
        }
        s = last->next;
        cout<<"Circular Link List: \n";
        while (s != last)
        {
            cout<<s->data<<"->";
            s = s->next;
        }
        cout<<s->data<<'\n';
    }

    void search_element(int val){
        struct node *s;
        int pos = 0;
        s = last->next;
        while (s != last)
        {
            pos++;
            if (s->data == val)
            {
                cout<<"Element "<<val<<" found at position "<<pos<<'\n';
                return;
            }
            s = s->next;
        }
        if (s->data == val)
        {
            pos++;
            cout<<"Element "<<val<<" found at position "<<pos<<'\n';
            return;
        }
        cout<<"Element "<<val<<" not found\n";
    }

    void update(){
        int value, pos, i;
        if (last == NULL)
        {
            cout<<"List is empty, nothing to update\n";
            return;
        }
        cout<<"Enter the node position to be updated: ";
        cin>>pos;
        cout<<"Enter the new value: ";
        cin>>value;
        struct node *s;
        s = last->next;
        for (i = 0;i < pos - 1;i++)
        {
            if (s == last)
            {
                cout<<"There are less than "<<pos<<" elements.\n";
                return;
            }
            s = s->next;
        }
        s->next->data = value;
        cout<<"Node Updated\n";
    }

    void delete_element(int val){
        struct node *temp,*s;
        s = last->next;

        if(last->next ==last && last->data == val){
            temp =last;
            last =NULL;
            free(temp);
            return;
        }
        if(s->data == val){
            temp =s;
            last->next = s->next;
            free(temp);
            return;
        }
        while(s->next != last){
            if(s->next->data == val){
                temp = s->next;
                s->next = temp->next;
                free(temp);
                cout<<"Element:"<<val<<" deleted\n";
                return;
            }
            s=s->next;
        }
        if(s->next->data == val){
            temp =s->next;
            s->next =last->next;
            free(temp);
            last =s;
            return;
        }
        cout<<"Element "<<val<<" found\n";
    }

};
int main() {
    int choice, element, pos;
    circular_list cl;
    while(true){
        cout<<"*_*_*_*_*_*_*_*_*_*\nCircular singly linked list\n*_*_*_*_*_*_*_*_*_*\n";
        cout<<"1. Create Node\n";
        cout<<"2. Add at beginning\n";
        cout<<"3. Add after\n";
        cout<<"4. Display List\n";
        cout<<"5. Search list\n";
        cout<<"6. Update list\n";
        cout<<"7. Delete element\n";
        cout<<"8. Quit\n";
        cout<<"Enter your choice: ";
        cin>>choice;
        switch(choice){
            case 1:
                cout<<"Enter the element: ";
                cin>>element;
                cl.create_node(element);
                cout<<'\n';
                break;
            case 2:
                cout<<"Enter the element: ";
                cin>>element;
                cl.add_begin(element);
                cout<<'\n';
                break;
            case 3:
                cout<<"Enter the element: ";
                cin>>element;
                cout<<"Insert element after position: ";
                cin>>pos;
                cl.add_after(element, pos);
                cout<<endl;
                break;
            case 4:
                cl.display_list();
                break;
            case 5:
                if (last == NULL)
                {
                    cout<<"List Empty!! Can't search"<<'\n';
                    break;
                }
                cout<<"Enter the element to be searched: ";
                cin>>element;
                cl.search_element(element);
                cout<<'\n';
                break;
            case 6:
                cl.update();
                break;
            case 7:
                if (last == NULL)
                {
                    cout<<"List is empty, nothing to delete"<<'\n';
                    break;
                }
                cout<<"Enter the element for deletion: ";
                cin>>element;
                cl.delete_element(element);
                cout<<'\n';
                break;
            case 8:
                exit(1);

                break;
            default:
                cout<<"Wrong Option\n";

        }
    }
    return 0;
}