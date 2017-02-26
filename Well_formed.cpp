/**This is a program to check if an  expression is well formed**/
#include <iostream>

using namespace std;

int top =-1;
char stack[50];

void push(char s){
    top++;
    stack[top]=s;
}
char pop(){
    char temp='\0';
    if(top ==-1){
        cout<<"not well formed";
        exit(0);
    }
    else {
        temp = stack[top];
        top--;
    }
    return temp;
}
void output(){
    if (top ==-1){
        cout<<"well formed";
    }
    else
        cout<<"not well formed";
}
int  main(){
    int i;
    char a[70];
    cout<<"enter the expression";
    gets(a);
    for (i=0;a[i]!='\0';i++){
        if(a[i]=='('){
            push(a[i]);
        }
        else if(a[i]==')'){
            if (pop()!='('){
                cout<<"not well formed";
                exit(0);
            }

        }
        if(a[i]=='['){
            push(a[i]);
        }
        else if(a[i]==']'){
            if (pop()!='['){
                cout<<"not well formed";
                exit(0);
            }
        }
        if(a[i]=='{'){
            push(a[i]);
        }
        else if(a[i]=='}'){
            if (pop()!='{'){
                cout<<"not well formed";
                exit(0);
            }
        }
        if(a[i] == '+' ||a[i] == '-'||a[i] == '*'||a[i] == '/'||a[i] == '^'){
            if(a[i+1] == '+' ||a[i+1] == '-'||a[i+1] == '*'||a[i+1] == '/'||a[i+1] == '^'||a[i+1]=='\0'){
                cout<<"not well formed";
                exit(0);
            }
        }
    }
    output();
    return 0;

}