#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>

using namespace std;

struct node{
    char data;
    node *next;
};

node *makeNode(char data){
    node *newnode = new node;
    newnode->data = data;
    newnode->next = nullptr;
    return newnode;
}

void push(node **stack, char data){
    node *newnode = makeNode(data);
    if(*stack == nullptr){
        (*stack) = newnode;
        return;
    }
    else{
        newnode->next = *stack;
        *stack = newnode;
    }
}

void pop(node **stack){
    if(*stack != nullptr){
        node *tmp = *stack;
        *stack = tmp->next;
        delete tmp;
    }
}

char peek(node *stack){
    if(stack != nullptr){
        return stack->data;
    }
    else{
        cout << "Stack is empty.\n";
        return ' ';
    }
}

int priorityLevel(char c) {
	if (c == '+' || c == '-') {
		return 1;
	}
	else if (c == '/' || c == '*') {
		return 2;
	}
	else if (c == '^') {
		return 3;
	}
	else {
		return 0;
	}
}

void infixToPostfix(string input){
    node *stack = nullptr;
    int n = input.length();
    for (int i = 0; i < n; i++)
    {
        if(input[i] == ' '){
            continue;
        }
        else{
            if (input[i] == '+' || input[i] == '-' ||
				input[i] == '*' || input[i] == '/' || input[i] == '^'){
                while((stack != nullptr) && priorityLevel(input[i]) <= priorityLevel(peek(stack))){
                    cout << peek(stack) << " ";
                    pop(&stack);
                }
                push(&stack, input[i]);
            }
            else if(input[i] == ')'){
                char op = peek(stack);
                pop(&stack);
                while(op != '('){
                    cout << op << " ";
                    op = peek(stack);
                    pop(&stack);
                }
            }
            else if(input[i] == '('){
                push(&stack, input[i]);
            }
            else{
                int number = 0;
				int c = input[i] - 48;
				while (c >= 0 && c <= 9) {
					i++;
					number = number * 10 + c;
					c = input[i] - 48;
				}
				i--;
				cout << number << " ";
            }
        }
    }
    //pop cac phan tu con lai cua stack
    while(stack != nullptr){
        char op = peek(stack);
        pop(&stack);
        if(op != '('){
            cout << op << " ";
        }
    }
}
    

int main(){
    int t;
	cin >> t;
	cin.ignore();
	while (t--) {
		string str;
		getline(cin, str);
		infixToPostfix(str);
		cout << endl;
	}

    return 0;
}