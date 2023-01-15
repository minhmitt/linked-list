#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>

using namespace std;

struct student{
    string id;
    string firstName;
    string midName;
    string lastName;
    string address;
    int age;
    double gpa;
};

student createFakeStudent(string id, string first, string mid, 
        string last, string address, int age, double gpa){
    student s;
    s.id = id;
    s.firstName = first;
    s.midName = mid;
    s.lastName = last;
    s.address = address;
    s.age = age;
    s.gpa = gpa;
    return s;
}

struct node{
    student data;
    node *next;
};

node *makeNode(student data){
    node *newnode = new node;
    newnode->data = data;
    newnode->next = nullptr;
    return newnode;
}

void insertFirst(node **head, student data){
    node *newnode = makeNode(data);
    if(*head == nullptr){
        *head = newnode;
        return;
    }
    newnode->next = *head;
    *head = newnode;
}

void insertLast(node **head, student data){
    node *newnode = makeNode(data);
    if(*head == nullptr){
        *head = newnode;
        return;
    }
    node *tmp = *head;
    while(tmp->next != nullptr){
        tmp = tmp->next;
    }
    tmp->next = newnode;
}

// chèn vào sau sinh viên có mã ID 
void insertAfterX(node **head, student data, string id){
    node *newnode = makeNode(data);
    node *tmp = *head;
    while(tmp != nullptr){
        if(tmp->data.id.compare(id) == 0){
            newnode->next = tmp->next;
            tmp->next = newnode;
            return;
        }
        tmp = tmp->next;
    }
}

void header(){
    cout << left << setw(10) << "ID" << setw(15) << "Last name"
         << setw(15) << "Mid name" << setw(15) << "First name"
         << setw(15) << "Address" << setw(8) << "Age" 
         << setw(10) << "GPA" << endl;
}

void displayInfo(student s){
    cout << left << setw(10) << s.id << setw(15) << s.lastName 
         << setw(15) << s.midName << setw(15) << s.firstName 
         << setw(15) << s.address << setw(8) << s.age 
         << setw(10) << fixed << setprecision(2) << s.gpa << endl;
}

void createFakeNode(node **head){
    insertLast(head, createFakeStudent("1001", "Nam", "Van", "Nguyen", "Co Nhue", 16, 8.0));
    insertLast(head, createFakeStudent("1002", "Khai", "Van", "Le", "Minh Khai", 17, 8.0));
    insertLast(head, createFakeStudent("1003", "Nhat", "Minh", "Dinh", "Dong Anh", 18, 9.6));
    insertLast(head, createFakeStudent("1004", "Khang", "Viet", "Nguyen", "Minh Khai", 17, 9.2));
}

void displayNode(node *head){
    if(head == nullptr){
        cout << "Danh sach rong\n";
    }
    else{
        node *tmp = head;
        while(tmp != nullptr){
            displayInfo(tmp->data);
            tmp = tmp->next;
        }
    }
}

void displayByAddress(node *head, string address){
    if(head == nullptr){
        cout << "Danh sach rong\n";
    }
    else{
        cout << "Danh sach cac sinh vien cung dia chi:\n";
        node *tmp = head;
        while(tmp != nullptr){
            if(tmp->data.address.compare(address) == 0){
                displayInfo(tmp->data);
            }
            tmp = tmp->next;
        }
    }
}

//liệt kê các sinh viên có điểm trung bình >= x
void displayByGpa(node *head, double gpa){
    if(head == nullptr){
        cout << "Danh sach rong\n";
    }
    else{
        cout << "Danh sach cac sinh vien co diem TB >= " << gpa << ":\n";
        node *tmp = head;
        while(tmp != nullptr){
            if(tmp->data.gpa >= gpa){
                displayInfo(tmp->data);
            }
            tmp = tmp->next;
        }
    }
}

bool removeFirst(node **head){
    if(*head != nullptr){
        node *tmp = *head;
        *head = tmp->next;
        delete tmp;
        return true;
    }
    return false;
}

bool removeLast(node **head){
    if(*head != nullptr){
        node *tmp = *head;
        node *prev = tmp;
        while(tmp->next != nullptr){
            prev = tmp;
            tmp = tmp->next;
        }
        if(tmp == *head){
            return removeFirst(head);
        }
        node *del = tmp;
        prev->next = nullptr;
        delete tmp;
        return true;
    }
    return false;
}

//xóa sinh viên có id cho trước khỏi danh sách 
bool removeByID(node **head, string id){
    if(*head != nullptr){
        if((*head)->data.id.compare(id) == 0){
            return removeFirst(head);
        }
        else{
            node *tmp = *head;
            node *prev = tmp;
            while(tmp->next != nullptr){
                if(tmp->data.id.compare(id) == 0){
                    break;
                }
                prev = tmp;
                tmp = tmp->next;
            }
            node *del = tmp;
            prev->next = tmp->next;
            delete del;
            return true;
        }
    }
    return false;
}

bool removeWithGpa(node **head, double gpa){
    if(*head != nullptr){
        if((*head)->data.gpa == gpa){
            node *tmp = *head;
            while(tmp != nullptr && tmp->data.gpa == gpa){
                return removeFirst(head);
            }
        }
        else{
            node *tmp = *head;
            node *prev = tmp;
            while(tmp != nullptr){
                if(tmp->data.gpa == gpa){
                    node *del = tmp;
                    prev->next = tmp->next;
                    delete del;
                }
                prev = tmp;
                tmp = tmp->next;
            }
            return true;
        }
    }
    return false;
}

//sắp xếp các phần tử trong danh sách
void sort(node **head){
    for(node *i = *head; i != nullptr; i = i->next){
        for(node *j = i->next; j != nullptr; j = j->next){
            if(i->data.gpa < j->data.gpa){// điểm giảm dần
                swap(i->data, j->data);
            }
            else if(i->data.gpa == j->data.gpa){
                if(i->data.firstName.compare(j->data.firstName) > 0){
                    swap(i->data, j->data);
                }
                else if(i->data.firstName.compare(j->data.firstName) == 0){
                    if(i->data.lastName.compare(j->data.lastName) > 0){
                        swap(i->data, j->data);
                    }
                }
            }
        }
    }
}

void findStudentById(node *head, string id){
    if(head == nullptr){
        cout << "Danh sach rong.\n";
        return;
    }
    else{
        node *tmp = head;
        while(tmp != nullptr){
            if(tmp->data.id.compare(id) == 0){
                header();
                displayInfo(tmp->data);
                break;
            }
            tmp = tmp->next;
        }
        cout << "Not existed!";
    }
}

void updateGpa(node **head, string id, double gpa){
    if(*head == nullptr){
        cout << "Empty linked list.\n";
        return;
    }
    else{
        node *tmp = *head;
        while(tmp != nullptr){
            if(tmp->data.id.compare(id) == 0){
                tmp->data.gpa = gpa;
                break;
            }
            tmp = tmp->next;
        }
    }
}

student createStudent(){
    student s;
    cout << "ID: ";
    getline(cin, s.id);
    cout << "Last name: ";
    getline(cin, s.lastName);
    cout << "Mid name:";
    getline(cin, s.midName);
    cout << "First name: ";
    getline(cin, s.firstName);
    cout << "Address: ";
    getline(cin, s.address);
    cout << "Age: ";
    cin >> s.age;
    cout << "GPA: ";
    cin >> s.gpa;
    cin.ignore();
    return s;
}

int main(){
    node *head = nullptr;
    createFakeNode(&head);
    int choice;
    do{
        cout << "================== MENU ==================\n";
        cout << "1. Add a new student to the top of linked list.\n";
        cout << "2. Add a new student to the bottom of linked list.\n";
        cout << "3. Add a new student with provided ID.\n";
        cout << "4. Update Gpa for a student with provided ID.\n";
        cout << "5. Find a student with provided ID.\n";
        cout << "6. Remove a student on the top of linked list.\n";
        cout << "7. Remove a student at the bottom of linked list.\n";
        cout << "8. Remove a student with provided ID.\n";
        cout << "9. Remove all students having GPA >= x.\n";
        cout << "10. List all students with provided address.\n";
        cout << "11. Sort linked list.\n";
        cout << "12. List all students having GPA >= x.\n";
        cout << "13. Display student list.\n";
        cout << "0. Exit!.\n";
        cin >> choice;
        cin.ignore();
        switch(choice)
        {
            case 0:
            {
                cout << "Program ended!\n";
                break;
            }
            case 1:
            {
                student s = createStudent();
                insertFirst(&head, s);
                break;
            }
            case 2:
            {
                student s = createStudent();
                insertLast(&head, s);
                break;
            }
            case 3:
            {
                student s = createStudent();
                string id;
                cin >> id;
                insertAfterX(&head, s, id);
                break;
            }
            case 4:
            {
                string id;
                double gpa;
                cout << "Enter ID: ";
                getline(cin, id);
                cout << "Enter Gpa: ";
                cin >> gpa;
                updateGpa(&head, id, gpa);
                break;
            }
            case 5:
            {
                string id;
                cout << "Enter Id of student: ";
                getline(cin, id);
                findStudentById(head, id);  
                break;
            }
            case 6:
            {
                if(head != nullptr){
                    removeFirst(&head);
                }
                else{
                    cout << "Empty List!\n";
                }
                break;
            }
            case 7:
            {
                if(head != nullptr){
                    removeLast(&head);
                }
                else{
                    cout << "Empty List!\n";
                }
                break;
            }
            case 8:
            {
                if(head != nullptr){
                    string id;
                    cout << "Enter ID: ";
                    getline(cin, id);
                    removeByID(&head, id);
                }
                else{
                    cout << "Empty List!\n";
                }
                break;
            }
            case 9:
            {
                if(head!= nullptr){
                    double gpa;
                    cout << "Enter Gpa: ";
                    cin >> gpa;
                    cin.ignore();
                    removeWithGpa(&head, gpa);
                }
                else{
                    cout << "Empty List!\n";
                }
                break;
            }
            case 10:
            {
                if(head!= nullptr){
                    string address;
                    cout << "Enter address: ";
                    getline(cin, address);
                    displayByAddress(head, address);
                }
                else{
                    cout << "Empty List!\n";
                }
                break;
            }
            case 11:
            {
                if(head!= nullptr){
                    sort(&head);
                    cout << "Linked list after sorted:\n";
                    header();
                    displayNode(head);
                }
                else{
                    cout << "Empty List!\n";
                }
                break;
            }
            case 12:
            {
                if(head!= nullptr){
                    double gpa;
                    cout << "Enter Gpa: ";
                    cin >> gpa;
                    cin.ignore();
                    displayByGpa(head, gpa);
                }
                else{
                    cout << "Empty List!\n";
                }
                break;
            }
            case 13:
            {
                if(head!= nullptr){
                    header();
                    displayNode(head);
                }
                else{
                    cout << "Empty List!\n";
                }
                break;
            }
            default:
            {
                cout << "Wrong function. Please choose function 1-13.\n";
                break;
            }
        }
    }while(choice != 0);

    return 0;
}