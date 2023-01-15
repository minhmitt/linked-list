#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

struct node{
    string data;
    int ts;
    node *next;
};

node *makeNode(string data){
    node *newnode = new node;
    newnode->data = data;
    newnode->ts = 1;
    newnode->next = nullptr;
    return newnode;
}

void insert(node **head, string data){
    node *newnode = makeNode(data);
    if(*head == nullptr){
        *head = newnode;
        return;
    }
    else{
        node *tmp = *head;
        node *prev = tmp;
        while(tmp != nullptr){
            if(tmp->data.compare(data) == 0){
                tmp->ts++;
                break;
            }
            prev = tmp;
            tmp = tmp->next;
        }
        prev->next = newnode;
    }
}

void displayNode(node *head){
    if(head == nullptr){
        cout << "Danh sach rong\n";
    }
    else{
        node *tmp = head;
        while(tmp != nullptr){
            cout << tmp->data << " " << tmp->ts << endl;
            tmp = tmp->next;
        }
    }
}

int findX(node *head, string key){
    for(node *i = head; i != nullptr; i = i->next){
        if(i->data.compare(key) == 0){
            return i->ts;
        }
    }
    return -1;
}

void splitAndInsert(node **head, string str){
    const string delim = " ";
    int pos = 0;
    while((pos = str.find(delim)) != string::npos){
        string word = str.substr(0, pos);
        insert(head, word);
        str = str.substr(pos + 1);
    }
    insert(head, str);
}

int main(){
    string input;
    node *head = nullptr;
    cout << "Nhap vao chuoi ki tu: ";
    getline(cin, input);
    splitAndInsert(&head, input);
    cout << "Cac tu co torng danh sach: ";
    displayNode(head);
    cout << "Nhap tu can tim: ";
    string key;
    getline(cin, key);
    cout << "So lan xuat hien cua " << key << " trong danh sach: " << findX(head, key) << endl;
    
    return 0;
}