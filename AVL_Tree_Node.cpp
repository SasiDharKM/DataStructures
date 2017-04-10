#include<iostream>
#include<cstdio>
#include<sstream>
#include<algorithm>
#define pow2(n) (1 << (n))
using namespace std;

struct avl_node
{
    int data;
    struct avl_node *left;
    struct avl_node *right;
}*root;

class avlTree
{
public:
    int height(avl_node *temp){
        int h =0;
        if (temp != NULL){
            int l_h = height(temp->left);
            int r_h = height(temp->right);
            int max_h = max(l_h,r_h);
             h =max_h +1;
        }
        return h;

    }

    int diff(avl_node * temp){
        int l_h = height(temp->left);
        int r_h = height(temp->right);
        int b_f = l_h -r_h;
        return b_f;
    }

    avl_node *rr_rotation(avl_node * parent){
        avl_node *temp;
        temp = parent->right;
        parent->right = temp->left;
        temp->left = parent;
        return temp;
    }

    avl_node *ll_rotation(avl_node *parent ){
        avl_node *temp;
        temp = parent->right;
        parent->left = temp->right;
        temp->right = parent;
        return temp;
    }

    avl_node *lr_rotation(avl_node *parent){
        avl_node *temp;
        temp =parent->left;
        parent->left = rr_rotation(temp);
        return ll_rotation(parent);
    }

    avl_node *rl_rotation(avl_node *parent ){
        avl_node *temp;
        temp = parent->right;
        parent->right = ll_rotation(temp);
        return rr_rotation(parent);

    }

    avl_node* balance(avl_node *temp){
        int bal_factor = diff(temp);
        if (bal_factor > 1){
            if (diff(temp->left) >0)
                temp = ll_rotation(temp);
            else
                temp =lr_rotation(temp);
        }
        else if (bal_factor < -1){
            if (diff(temp->right) > 0)
                temp =rl_rotation(temp);
            else
                temp = rr_rotation(temp);
        }
        return temp;
    }

    avl_node* insert(avl_node *, int ){

    }

    void display(avl_node *ptr, int level){
        int i;
        if(ptr!= NULL){
            display(ptr->right, level + 1);
            cout<<"\n";
            if(ptr == root)
                cout<<"Root-> ";
            for(i=0; i<level && ptr !=root; i++)
                cout<<"       ";
            cout<< ptr->data;
            display(ptr->left,level+1);
        }
    }

    avlTree()
    {
        root = NULL;
    }
};

int main()
{
    int choice, item;
    avlTree avl;
    while (1)
    {
        cout<<"\n---------------------"<<endl;
        cout<<"AVL Tree Implementation"<<endl;
        cout<<"\n---------------------"<<endl;
        cout<<"1.Insert Element into the tree"<<endl;
        cout<<"2.Display Balanced AVL Tree"<<endl;
        cout<<"3.Exit"<<endl;
        cout<<"Enter your Choice: ";
        cin>>choice;
        switch(choice)
        {
            case 1:
                cout<<"Enter value to be inserted: ";
                cin>>item;
                root = avl.insert(root, item);
                break;
            case 2:
                if (root == NULL)
                {
                    cout<<"Tree is Empty"<<endl;
                    continue;
                }
                cout<<"Balanced AVL Tree:"<<endl;
                avl.display(root, 1);
                break;
            case 3:
                exit(1);
                break;
            default:
                cout<<"Wrong Choice"<<endl;
        }
    }
    return 0;
