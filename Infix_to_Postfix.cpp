/**This is a program to convert an infix expression to a postfix expression**/
#include <iostream>
#include <array>
#include <stack>

using namespace std;

int priority(char x)
{
    if(x == '^')
        return 1;
    if(x == '+' || x == '-')
        return 3;
    if(x == '*' || x == '/')
        return 2;
}

int  main()
{
   string infix;
    cout<<"Enter a expression:\n";
    getline(cin,infix);
    stack<char> stack1;

    string output;

    for( int i =0;i<infix.length();i++){
        if(infix[i] == '+' ||infix[i] == '-'||infix[i] == '*'||infix[i] == '/'||infix[i] == '^'){
            while(!stack1.empty() && priority(stack1.top())<=priority(infix[i])){
                output.push_back(stack1.top());
                stack1.pop();
            }
            stack1.push(infix[i]);
        }
        else if(infix[i] == '('){
            stack1.push(infix[i]);
        }
        else if(infix[i]==')'){
            while(stack1.top() != '('){
                output.push_back(stack1.top());
                stack1.pop();
            }
            stack1.pop();
        }
        else{
            output.push_back(infix[i]);
        }
    }
    while(!stack1.empty()){
        output.push_back(stack1.top());
        stack1.pop();
    }

    cout<< output.c_str()<<'\n';

    return 0;
}

