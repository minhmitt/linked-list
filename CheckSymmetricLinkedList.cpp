#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>

using namespace std;

struct node{
    int data;
    node *next;
};

node *makeNode(int data){
    node *newnode = new node;
    if(newnode == nullptr){
        return nullptr;
    }
    else{
        newnode->next = nullptr;
        newnode->data = data;
        return newnode;
    }
}

void push(node **head, int data){
    node *newnode = makeNode(data);
    if(newnode != nullptr){
        if(*head == nullptr){
            *head = newnode;
            return;
        }
        else{
            newnode->next = *head;
            *head = newnode;
        }
    }
    else{
        cout << "Cannot create new node.\n";
    }
}

int peek(node *head){
    if(head == nullptr){
        cout << "Stack is empty.\n";
        return -1;
    }
    else{
        return head->data;
    }
}

void pop(node **head){
    if(*head != nullptr){
        node *tmp = *head;
        *head = tmp->next;
        delete tmp;
    }
    else{
        cout << "Stack is empty.\n";
    }
}

bool symmetry(int *arr, int n){
    int midIndex = (n % 2 == 0 ? n / 2 - 1 : n / 2);
    node *stack = nullptr;
    for (int i = 0; i <= midIndex; i++)
    {
        push(&stack, arr[i]);
    }
    for (int i = n / 2; i < n; i++)
    {
        if(peek(stack) != arr[i]){
            return false;
        }
        pop(&stack);
    }
    return true;
}

int main(){
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        int *arr = new int[n];
        for (int i = 0; i < n; i++)
        {
            cin >> arr[i];
        }
        if(symmetry(arr, n)){
            cout << "YES\n";
        }
        else{
            cout << "NO\n";
        }
    }

    return 0;
}