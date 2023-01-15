#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>

using namespace std;

struct node{
    string data;
    node *next;
};

bool isEmpty(node *head){
    return head == nullptr;
}

node *makeNode(string data){
    node *newnode = new node;
    newnode->data = data;
    newnode->next = nullptr;
    return newnode;
}

void push(node **head, string data){
    node *newnode = makeNode(data);
    if(isEmpty(*head)){
        *head = newnode;
        return;
    }
    else{
        newnode->next = (*head);
        *head = newnode; 
    }
}

void pop(node **head){
    if(!isEmpty(*head)){
        node *tmp = *head;
        (*head) = tmp->next;
        delete tmp;
    }
}

string peek(node *stack){
    if(!isEmpty(stack)){
        return stack->data;
    }
    else{
        cout << "Stack is empty.\n";
        return "";
    }
}

void splitWord(node **stack, string str){
    const string delim = " ";
    auto pos = 0;
    while((pos = str.find(delim)) != string::npos){
        push(stack, str.substr(0, pos));
        str = str.substr(pos + 1);
    }
    push(stack, str);
}

void printResult(node *stack){
    while(!isEmpty(stack)){
        cout << peek(stack) << " ";
        pop(&stack);
    }
}

int main(){
    string s;
    cout << "Enter string: ";
    getline(cin, s);
    node* stack = nullptr;
    splitWord(&stack, s);
    printResult(stack);

    return 0;
}