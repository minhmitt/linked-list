#include <iostream>
#include <cmath>
#include <iomanip>
#include <cstdlib>

using namespace std;

struct node{
    double data;
    node *next;
};

node *makeNode(double data){
    node *newnode = new node;
    newnode->data = data;
    newnode->next = nullptr;
    return newnode;
}


void push(node **stack, double data){
    node *newnode = makeNode(data);
    if(*stack == nullptr){
        *stack = newnode;
        return;
    }
    else{
        newnode->next = *stack;
        *stack = newnode;
    }
}

double peek(node *stack){
    if(stack != nullptr){
        return stack->data;
    }
    else{
        cout << "Stack is empty!\n";
        return 0;
    }
}

void pop(node **stack){
    if(*stack != nullptr){
        node *tmp = *stack;
        *stack = tmp->next;
        delete tmp;
    }
    else{
        cout << "Stack is empty!\n";
        return;
    }
}

double calculateResult(double a, double b, char c){
    double result = 0;
	if (c == '+') {
		result = a + b;
	}
	else if (c == '-') {
		result = a - b;
	}
	else if (c == '*') {
		result = a * b;
	}
	else if (c == '/') {
		result = a / b;
	}
	else if (c == '^') {
		result = pow(a, b);
	}
	return result;
}

double executePostfix(string s){
    double res = 0;
    int n = s.length();
    node *stack = nullptr;
    for (int i = 0; i < n; i++)
    {
        if(s[i] == ' '){
            continue;
        }
        else if(s[i] > '9' || s[i] < '0'){// nếu kí tự tại vị trí i là toán tử
            double b = peek(stack);
            pop(&stack);
            double a = peek(stack);
            pop(&stack);
            res = calculateResult(a, b, s[i]);
            push(&stack, res);
        }
        else{// trường hợp còn lại, kí tự vị trí i là toán hạng
            double number = 0;
            double c = (double)(s[i] - '0');
            while(c >= 0 && c <= 9){
                number = number * 10 + c;
                ++i;
                c = (double)(s[i] - '0');
            }
            --i;
            push(&stack, number);
        }
    }
    return peek(stack);
}

int main(){
    int t;
	cin >> t;
	cin.ignore();
	while (t--) {
		string str;
		getline(cin, str);
		cout << executePostfix(str) << endl;
	}
    
    return 0;
}