//task_management_system.cpp
//written by William Vu, San Jose State University
//Dec 9, 2024

#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include <tuple>
#include <algorithm>
using namespace std;

class Date{
public:
    int month;
    int day;
    int year;

    int hour;
    int minute;
    bool AM; //true for AM, false for PM

    Date();
    Date(int mon,int d,int y, int h, int min, bool AM_PM);
    Date(const Date&);

    bool checkDate() const;
    Date& operator = (const Date& temp);
    void createDate();
    void display() const;

    bool operator >  (const Date&);
    bool operator >= (const Date&);
    bool operator == (const Date&);
    bool operator <= (const Date&);
    bool operator <  (const Date&);
};

Date::Date(){
    month = day = year = hour = minute = AM = 0;
}

Date::Date(int mon,int d,int y, int h, int min, bool am){
    month  = mon;
    day    =   d;
    year   =   y;
    hour   =   h;
    minute = min;
    AM     =  am;
}

Date::Date(const Date& temp){
    month  =  temp.month;
    day    =    temp.day;
    year   =   temp.year;
    hour   =   temp.hour;
    minute = temp.minute;
    AM     =     temp.AM;
}

bool Date::checkDate() const{
    if(month < 1  ||  month > 12) return false;
    
    switch(month){
        case 1:
            if(day < 1  ||  day > 31){
                return false;
            }break;
        case 2:
            if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
                if(day < 1  ||  day > 29) return false;
            }else {
                if(day < 1  ||  day > 28) return false;
            }
            break;
        case 3:
            if(day < 1  ||  day > 31){
                return false;
            }break;
        case 4:
            if(day < 1  ||  day > 30){
                return false;
            }break;
        case 5:
            if(day < 1  ||  day > 31){
                return false;
            }break;
        case 6:
            if(day < 1  ||  day > 30){
                return false;
            }break;
        case 7:
            if(day < 1  ||  day > 31){
                return false;
            }break;
        case 8:
            if(day < 1  ||  day > 31){
                return false;
            }break;
        case 9:
            if(day < 1  ||  day > 30){
                return false;
            }break;
        case 10:
            if(day < 1  ||  day > 31){
                return false;
            }break;
        case 11:
            if(day < 1  ||  day > 30){
                return false;
            }break;
        case 12:
            if(day < 1  ||  day > 31){
                return false;
            }break;
    }

    if(hour < 1  ||  hour > 12) return false;
    
    if(minute < 0  ||  minute > 59) return false;

    return true;
}

Date& Date::operator = (const Date& temp){
    if(this != &temp){
        month  =  temp.month;
        day    =    temp.day;
        year   =   temp.year;
        hour   =   temp.hour;
        minute = temp.minute;
        AM     =     temp.AM;
    }
    return *this;
}

bool validate_cin(){
    if(cin.fail()){
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return false;
    }
    return true;
}

void Date::createDate(){
    int mon,d,y,h,min;
    do{
        cout << "Enter date input as INTEGERS" << endl;
        cout << "Enter month (1-12): ";
        cin >> mon;
        if(!validate_cin()){
            cerr << "\nInvalid input. Integer input is only accepted\n\n";
            continue;
        }
        cout << "Enter day: ";
        cin >> d;
        if(!validate_cin()){
            cerr << "\nInvalid input. Integer input is only accepted\n\n";
            continue;
        }
        cout << "Enter year: ";
        cin >> y;
        if(!validate_cin()){
            cerr << "\nInvalid input. Integer input is only accepted\n\n";
            continue;
        }
        cout << "Enter hour: ";
        cin >> h;
        if(!validate_cin()){
            cerr << "\nInvalid input. Integer input is only accepted\n\n";
            continue;
        }
        cout << "Enter minute: ";
        cin >> min;
        if(!validate_cin()){
            cerr << "\nInvalid input. Integer input is only accepted\n\n";
            continue;
        }

        string input;
        do{
            cout << "Enter \"AM\" or \"PM\": ";
            cin >> input;
            if(input != "AM"  &&  input != "PM"){
                cout << "Invalid AM/PM" << endl;
            }else break;
        }while(true);

        bool AM_PM = (input == "AM") ? true : false;

        Date temp(mon,d,y,h,min,AM_PM);
        if(temp.checkDate()){
            *this = temp;
            break;
        }else{
            cout << "\nInvalid date. Please check date and try again\n\n";
        }
    }while(true);
}

void Date::display() const{
    cout << month << '/' << day << '/' << year << ", ";
    cout << hour << ':';
    if(minute / 10 == 0){
        cout << '0';
    }
    cout << minute;
    cout << (AM ? "AM" : "PM");
}

bool Date::operator > (const Date& other){
    if(year > other.year) return true;
    else if(year == other.year){
        if(month > other.month) return true;
        else if(month == other.month){
            if(day > other.day) return true;
            else if(day == other.day){
                if(AM == other.AM){
                    if(hour > other.hour) return true;
                    else if(hour == other.hour){
                        if(minute > other.minute) return true;
                        else return false;
                    }
                    else return false;
                }else if(AM && !other.AM) return false;
                else return true;
            }
            else return false;
        }
        else return false;
    }
    else return false;
}

bool Date::operator == (const Date& other){
    if(month != other.month)return false;
    if(day != other.day)return false;
    if(year != other.year)return false;
    if(hour != other.hour)return false;
    if(minute != other.minute)return false;
    if(AM != other.AM)return false;
    return true;
}

bool Date::operator >= (const Date& other){
    if(*this > other  ||  *this == other) return true;
    return false;
}

bool Date::operator < (const Date& other){
    if(*this >= other) return false;
    return true;
}

bool Date::operator <= (const Date& other){
    if(*this < other  ||  *this == other) return true;
    return false;
}

class Task{
public:
    string title;
    string description;
    Date date;

    Task();
    Task(const Task&);
    void createTask();
    void editTask();
    void display() const;
};

Task::Task() : title(""), description(""), date(Date()) {}

Task::Task(const Task& temp) :
title(temp.title), description(temp.description), date(temp.date) {}

void Task::createTask(){
    string input;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Enter task title: ";
        getline(cin,input);
        title = input;

        cout << "Enter task description: ";
        getline(cin,input);
        description = input;

        date.createDate();
}

void Task::editTask(){
    string input;

    do{
        cout << "To edit title, enter \"yes\" or \"no\": ";
        cin >> input;
        for(char& c : input)c = tolower(c);
        if(input != "yes"  &&  input != "no"){
            cerr << "\nInvalid input, try again\n\n";
            continue;
        }else break;
    }while(true);
    if(input == "yes"){
        cout << "Enter new title: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin , title);
    }

    do{
        cout << "To edit description, enter \"yes\" or \"no\": ";
        cin >> input;
        for(char& c : input)c = tolower(c);
        if(input != "yes"  &&  input != "no"){
            cerr << "\nInvalid input, try again\n\n";
            continue;
        }else break;
    }while(true);
    if(input == "yes"){
        cout << "Enter new description: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin , description);
    }

    do{
        cout << "To edit date, enter \"yes\" or \"no\": ";
        cin >> input;
        for(char& c : input)c = tolower(c);
        if(input != "yes"  &&  input != "no"){
            cerr << "\nInvalid input, try again\n\n";
            continue;
        }else break;
    }while(true);
    if(input == "yes"){
        cout << "Current date: ";
        date.display(); 
        cout << endl;
        date.createDate();
    }
}

void Task::display() const{
    cout << title << endl;
    cout << "Description:" << endl << description << endl;
    cout << "Date:" << endl; date.display();
}

class ListNode{
public:
    Task task;
    ListNode* previous;
    ListNode* next;
    ListNode();
    ListNode(Task);
};

ListNode::ListNode() : previous(nullptr),next(nullptr),task() {}

ListNode::ListNode(Task t) : previous(nullptr),next(nullptr),task(t) {}

//doubly-linked list
class TaskList{
private:
    ListNode* head;
    ListNode* tail;
public:
    TaskList();
    void prepend(Task);
    void append(Task);
    Task remove(int index);
    void insertAfter(Task newTask, int index);
    void swap(int indexOne, int indexTwo);
    Task at(int index);
    Task edit(int index);
    void display() const;
    void replace(Task, int index);
private:
    //helper functions
    void prepend(ListNode* newNode);
    void append(ListNode* newNode);
    ListNode* search(Task) const;
    void remove(ListNode* target);
    void insertAfter(ListNode* current, ListNode* newNode);
    void swap(pair<ListNode*,ListNode*>);
};

TaskList::TaskList() : head(nullptr) , tail(nullptr) {}

void TaskList::prepend(ListNode* newNode){
    if(head == nullptr){
        head = newNode;
        tail = newNode;
    }
    else{
        newNode->next = head;
        head->previous = newNode;
        head = newNode;
    }
}

void TaskList::prepend(Task t){
    ListNode* newNode = new ListNode(t);
    prepend(newNode);
}

void TaskList::append(ListNode* newNode){
    if(head==nullptr){
        head = newNode;
        tail = newNode;
    }
    else{
        newNode->previous = tail;
        tail->next = newNode;
        tail = newNode;
    }
}

void TaskList::append(Task t){
    ListNode* newNode = new ListNode(t);
    append(newNode);
}

ListNode* TaskList::search(Task t) const{
    ListNode* current = head;
    while(current){
        if(current->task.title == t.title || current->task.date == t.date){
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

void TaskList::remove(ListNode* target){
    ListNode* predecessor = target->previous;
    ListNode* successor = target->next;
    if(successor){
        successor->previous = predecessor;
    }
    if(predecessor){
        predecessor->next = successor;
    }
    if(target == head){
        head = successor;
    }
    if(target == tail){
        tail = predecessor;
    }
    delete target;
}

Task TaskList::remove(int index){
    //assumes index <= the number of nodes
    //the fifth node corresponds to index = 5
    ListNode* current = head;
    int i = 1;
    while(i < index){
        current = current->next;
        ++i;
    }
    Task temp = current->task;
    remove(current);
    return temp;
}

void TaskList::insertAfter(ListNode* current, ListNode* newNode){
    if(head == nullptr){
        head = newNode;
        tail = newNode;
    }
    else if(current == tail){
        newNode->previous = tail;
        tail->next = newNode;
        tail = newNode;
    }
    else{
        ListNode* successor = current->next;
        newNode->next = successor;
        newNode->previous = current;
        current->next = newNode;
        successor->previous = newNode;
    }
}

void TaskList::insertAfter(Task newTask,int index){
    ListNode* current = head;
    int i = 1;
    while(i < index){
        current = current->next;
        ++i;
    }
    ListNode* newNode = new ListNode(newTask);
    insertAfter(current, newNode);
}

void TaskList::swap(pair<ListNode*,ListNode*> pair){
    std::swap(pair.first->task , pair.second->task);
}

void TaskList::swap(int index1 , int index2){
    //assumes index1 and index2 are valid.
    //checking index1 and index2 is done in TaskManager class
    int index = 1;
    ListNode* current = head;
    ListNode* node1, *node2;
    while(index <= max(index1,index2)){
        if(index == index1){
            node1 = current;
        }
        else if(index == index2){
            node2 = current;
        }
        current = current->next;
        ++index;
    }
    pair<ListNode*,ListNode*> p(node1, node2);
    swap(p);
}

Task TaskList::at(int index){
    //checking whether index is valid is done in TaskManager class
    int i = 1;
    ListNode* current = head;
    while(current && i < index){
        ++i;
        current = current->next;
    }
    return current->task;
}

Task TaskList::edit(int index){
    Task newTask;
    int i = 1;
    ListNode* current = head;
    while(current && i < index){
        ++i;
        current = current->next;
    }
    current->task.editTask();
    newTask = current->task;
    return newTask;
}

void TaskList::display() const{
    ListNode* current = head;
    int index = 1;
    while(current){
        cout << '[' << index << ']' << endl;
        current->task.display();
        cout << endl << endl;
        ++index;
        current = current->next;
    }
}

void TaskList::replace(Task newTask, int index){
    int i = 1;
    ListNode* current = head;
    while(current && i < index){
        current = current->next;
        ++i;
    }
    current->task = newTask;
}

class BSTNode{
public:
    Task task;
    BSTNode* left;
    BSTNode* right;
    BSTNode();
    BSTNode(Task t);
};

BSTNode::BSTNode() : task() , left(nullptr) , right(nullptr) {}

BSTNode::BSTNode(Task t) : task(t) , left(nullptr) , right(nullptr) {}

//does not support duplicates
class TaskDateBST{
private:
    BSTNode* root;
public:
    TaskDateBST();
    BSTNode* search(Date date);
    //returns true if newTask does not exist yet in the tree
    bool insert(Task newTask);
    //returns true if newTask exists and is removed
    bool remove(Task target);
    void displayInOrder() const;
    void replace(Task oldTask, Task newTask);
private:
    void insert(BSTNode* newNode);
    void displayInOrder(BSTNode* current, int& index) const;
};

TaskDateBST::TaskDateBST() : root(nullptr) {}

BSTNode* TaskDateBST::search(Date date){
    BSTNode* current = root;
    while(current){
        if(current->task.date < date){
            current = current->right;
        }
        else if(current->task.date > date){
            current = current->left;
        }
        else{
            return current;
        }
    }
    return nullptr;
}

void TaskDateBST::insert(BSTNode* newNode){
    if (root == nullptr) {
      root = newNode;
   }
   else {
      BSTNode* current = root;
      while (current) {
         if (newNode->task.date < current->task.date) {
            if (current->left == nullptr) {
               current->left = newNode;
               current = nullptr;
            }
            else {
               current = current->left;
            }
         }
         else {
            if (current->right == nullptr) {
               current->right = newNode;
               current = nullptr;
            }
            else {
               current = current->right;
            }
         }
      }
   }
}

bool TaskDateBST::insert(Task newTask){
    if(search(newTask.date) != nullptr){
        return false;
    }
    BSTNode* newNode = new BSTNode(newTask);
    insert(newNode);
    return true;
}

bool TaskDateBST::remove(Task target){
    BSTNode* parent = nullptr;
   BSTNode* current = root;

   while (current) {
      if (current->task.date == target.date) {
         if (current->left == nullptr && current->right == nullptr) {
            if (parent == nullptr) {
               root = nullptr;
            }
            else if (parent->left == current) { 
               parent->left = nullptr;
            }
            else {
               parent->right = nullptr;
            }
            delete current;
            return true;
         }
         else if (current->left && current->right == nullptr) {
            // Remove node with only left child
            if (parent == nullptr) {
               root = current->left;
            }
            else if (parent->left == current) {
               parent->left = current->left;
            }
            else {
               parent->right = current->left;
            }
            delete current;
            return true;
         }
         else if (current->left == nullptr && current->right) {
            // Remove node with only right child
            if (parent == nullptr) {
               root = current->right;
            }
            else if (parent->left == current) {
               parent->left = current->right;
            }
            else {
               parent->right = current->right;
            }
            delete current;
            return true;
         }
         else {
            // Remove node with two children
            BSTNode* successor = current->right;
            while (successor->left) {
               successor = successor->left;
            }
            current->task = successor->task;
            parent = current;

            current = current->right;
            target = successor->task;
         }
      }
      else if (current->task.date < target.date) {
         parent = current;
         current = current->right;
      }
      else {
         parent = current;
         current = current->left;
      }
   }
   return false;
}

void TaskDateBST::displayInOrder() const{
    int index = 1;
    displayInOrder(root,index);
}

void TaskDateBST::displayInOrder(BSTNode* current, int& index) const{
    if(current == nullptr) return;

    displayInOrder(current->left,index);

    cout << "[" << index << ']' << endl;
    current->task.display();
    cout << endl << endl;

    ++index;

    displayInOrder(current->right,index);
}

void TaskDateBST::replace(Task oldTask, Task newTask){
    BSTNode* current = root;
    while(current){
        if(oldTask.date < current->task.date){
            current = current->left;
        }else if(oldTask.date > current->task.date){
            current = current->right;
        }else{
            current->task = newTask;
            return;
        }
    }
}

//does not support duplicates
class TaskTitleBST{
private:
    BSTNode* root;
public:
    TaskTitleBST();
    BSTNode* search(string title);
    bool insert(Task newTask);
    //returns true if newTask does not exist yet in the tree
    bool remove(Task target);
    //returns true if newTask exists and is removed
    void displayInOrder() const;
    void replace(Task oldTask, Task newTask);
private:
    void insert(BSTNode* newNode);
    void displayInOrder(BSTNode* current, int& index) const;
};

TaskTitleBST::TaskTitleBST() : root(nullptr) {}

BSTNode* TaskTitleBST::search(string title){
    BSTNode* current = root;
    while(current){
        if(current->task.title < title){
            current = current->right;
        }
        else if(current->task.title > title){
            current = current->left;
        }
        else{
            return current;
        }
    }
    return nullptr;
}

void TaskTitleBST::insert(BSTNode* newNode){
    if (root == nullptr) {
      root = newNode;
   }
   else {
      BSTNode* current = root;
      while (current) {
         if (newNode->task.title < current->task.title) {
            if (current->left == nullptr) {
               current->left = newNode;
               current = nullptr;
            }
            else {
               current = current->left;
            }
         }
         else {
            if (current->right == nullptr) {
               current->right = newNode;
               current = nullptr;
            }
            else {
               current = current->right;
            }
         }
      }
   }
}

bool TaskTitleBST::insert(Task newTask){
    if(search(newTask.title) != nullptr){
        return false;
    }
    BSTNode* newNode = new BSTNode(newTask);
    insert(newNode);
    return true;
}

bool TaskTitleBST::remove(Task target){
    BSTNode* parent = nullptr;
   BSTNode* current = root;

   while (current) {
      if (current->task.title == target.title) {
         if (current->left == nullptr && current->right == nullptr) {
            if (parent == nullptr) {
               root = nullptr;
            }
            else if (parent->left == current) { 
               parent->left = nullptr;
            }
            else {
               parent->right = nullptr;
            }
            delete current;
            return true;
         }
         else if (current->left && current->right == nullptr) {
            // Remove node with only left child
            if (parent == nullptr) {
               root = current->left;
            }
            else if (parent->left == current) {
               parent->left = current->left;
            }
            else {
               parent->right = current->left;
            }
            delete current;
            return true;
         }
         else if (current->left == nullptr && current->right) {
            // Remove node with only right child
            if (parent == nullptr) {
               root = current->right;
            }
            else if (parent->left == current) {
               parent->left = current->right;
            }
            else {
               parent->right = current->right;
            }
            delete current;
            return true;
         }
         else {
            // Remove node with two children
            BSTNode* successor = current->right;
            while (successor->left) {
               successor = successor->left;
            }
            current->task = successor->task;
            parent = current;

            current = current->right;
            target = successor->task;
         }
      }
      else if (current->task.title < target.title) {
         parent = current;
         current = current->right;
      }
      else {
         parent = current;
         current = current->left;
      }
   }
   return false;
}

void TaskTitleBST::displayInOrder() const{
    int index = 1;
    displayInOrder(root,index);
}

void TaskTitleBST::displayInOrder(BSTNode* current, int& index) const{
    if(current == nullptr) return;

    displayInOrder(current->left,index);

    cout << "[" << index << ']' << endl;
    ++index;
    current->task.display();
    cout << endl << endl;

    displayInOrder(current->right,index);
}

void TaskTitleBST::replace(Task oldTask, Task newTask){
    BSTNode* current = root;
    while(current){
        if(oldTask.title < current->task.title){
            current = current->left;
        }else if(oldTask.title > current->task.title){
            current = current->right;
        }else{
            current->task = newTask;
            return;
        }
    }
}

//commands that correspond to the TaskManager class
//Commands and CommandStack exist for undo functionality for TaskManager
class Command{
public:
    virtual ~Command(){}
    virtual void undo() = 0;
};

class InsertCommand : public Command{
private:
    //the index of the task that has inserted, deleted, or changed
    int index; 
    //pointer to size member of the task manager
    int* size;
    //pointer to list member of the task manager
    TaskList* list;
    //pointer to dateTree member of the task manager
    TaskDateBST* dateTree;
    //pointer to titleTree member of the task manager
    TaskTitleBST* titleTree;
public:
    InsertCommand(int, int*, TaskList*, TaskDateBST*, TaskTitleBST*);
    void undo() override;
};

InsertCommand::InsertCommand(int i, int* s, TaskList* l, TaskDateBST* dt, TaskTitleBST* tt) : 
index(i) , size(s) , list(l) , dateTree(dt) , titleTree(tt) {}

void InsertCommand::undo(){
    //to undo this insert command, the inserted task should be removed
    if(*size == 0) return;
    Task removedTask = list->remove(index);
    dateTree->remove(removedTask);
    titleTree->remove(removedTask);
    --(*size);
}

class RemoveCommand : public Command{
private:
    Task removedTask;
    //the index before the removedTask's index
    int index; 
    int* size;
    TaskList* list;
    TaskDateBST* dateTree;
    TaskTitleBST* titleTree;
public:
    RemoveCommand(Task, int, int*, TaskList*, TaskDateBST*, TaskTitleBST*);
    void undo() override;
};

RemoveCommand::RemoveCommand(Task t, int i, int* s, TaskList* l, TaskDateBST* dt, TaskTitleBST* tt) : 
removedTask(t) , index(i) , size(s) , list(l) , dateTree(dt) , titleTree(tt) {}

void RemoveCommand::undo(){
    //to undo this remove command, the removed task should be inserted
    if(index == 0){
        list->prepend(removedTask);
    }else if(index == *size){
        list->append(removedTask);
    }else{
        list->insertAfter(removedTask , index);
    }
    dateTree->insert(removedTask);
    titleTree->insert(removedTask);
    ++(*size);
}

class EditCommand : public Command{
private:
    //the original task before it was edited
    Task previousTask;
    //the current task that will be switched after undo
    Task currentTask;
    //the index of the task that has been edited
    int index;
    TaskList* list;
    TaskDateBST* dateTree;
    TaskTitleBST* titleTree;
public:
    EditCommand(Task, Task, int, TaskList*, TaskDateBST*, TaskTitleBST*);
    void undo() override;
};

EditCommand::EditCommand(Task pt, Task ct, int i, TaskList* l, TaskDateBST* dt, TaskTitleBST* tt) : 
previousTask(pt) , currentTask(ct) , index(i) , list(l) , dateTree(dt) , titleTree(tt) {}

void EditCommand::undo(){
    list->replace(previousTask , index);
    dateTree->replace(currentTask , previousTask);
    titleTree->replace(currentTask , previousTask);
}

class SwapCommand : public Command{
private:
    int index1;
    int index2;
    TaskList* list;
public:
    SwapCommand(int, int, TaskList*);
    void undo() override;
};

SwapCommand::SwapCommand(int i1, int i2, TaskList* l) : 
index1(i1) , index2(i2) , list(l) {}

void SwapCommand::undo(){
    list->swap(index1 , index2);
}

//Duplicate Tasks will not be inserted
class TaskManager{
private:
    int size;
    TaskList list;
    stack<Command*> commandStack;
    //Binary Search Tree sorted by Task dates
    TaskDateBST dateTree;
    //Binary Search Tree sorted by Task Titles
    TaskTitleBST titleTree;
public:
    TaskManager();
    int length() const;
    bool prepend(Task);
    bool append(Task);
    bool insertAfter(Task, int index);
    bool remove(int index);
    bool swap(int index1, int index2);
    bool edit(int index);
    Task* search(Date date);
    Task* search(string title);
    void display() const; //list
    void displayByDate() const; //dateTree
    void displayByTitle() const; //titleTree
    void undo();
};

TaskManager::TaskManager() : size(0), list(),commandStack(), titleTree(), dateTree() {}

int TaskManager::length() const{
    return size;
}

bool TaskManager::prepend(Task t){
    if(!dateTree.insert(t)) return false;
    ++size;
    list.prepend(t);
    titleTree.insert(t);
    commandStack.push(new InsertCommand(1, &size, &list, &dateTree, &titleTree));
    return true;
}

bool TaskManager::append(Task t){
    if(!dateTree.insert(t)) return false;

    ++size;
    list.append(t);
    titleTree.insert(t);

    commandStack.push(new InsertCommand(size, &size, &list, &dateTree, &titleTree));

    return true;
}

bool TaskManager::insertAfter(Task t, int index){
    if(dateTree.search(t.date) != nullptr) return false;
    if(index < 1 || index > size) return false;

    list.insertAfter(t , index);
    dateTree.insert(t);
    titleTree.insert(t);
    ++size;

    commandStack.push(new InsertCommand(index, &size, &list, &dateTree, &titleTree));

    return true;
}

bool TaskManager::remove(int index){
    if(index < 1  ||  index > size) return false;

    Task removedTask = list.remove(index);
    dateTree.remove(removedTask);
    titleTree.remove(removedTask);
    --size;

    commandStack.push(new RemoveCommand(removedTask, index-1, &size, &list, &dateTree, & titleTree));

    return true;
}

bool TaskManager::swap(int index1, int index2){
    if(index1 == index2)return false;
    if(index1 < 1  ||  index1 > size) return false;
    if(index2 < 1  ||  index2 > size) return false;

    list.swap(index1,index2);

    commandStack.push(new SwapCommand(index1, index2, &list));

    return true;
}

bool TaskManager::edit(int index){
    if(index < 1  || index > size) return false;

    Task editedTask = list.at(index);

    Task newTask = list.edit(index);
    dateTree.replace(editedTask, newTask);
    titleTree.replace(editedTask, newTask);

    commandStack.push(new EditCommand(editedTask, newTask, index, &list, &dateTree, &titleTree));

    return true;
}

Task* TaskManager::search(Date date){
    if(dateTree.search(date) == nullptr){
        return nullptr;
    }

    Task* t = new Task(dateTree.search(date)->task);
    return t;
}

Task* TaskManager::search(string title){
    if(titleTree.search(title) == nullptr){
        return nullptr;
    }

    Task* t = new Task(titleTree.search(title)->task);
    return t;
}

void TaskManager::display() const{
    list.display();
}

void TaskManager::displayByDate() const{
    dateTree.displayInOrder();
}

void TaskManager::displayByTitle() const{
    titleTree.displayInOrder();
}

void TaskManager::undo(){
    if(commandStack.empty()) return;

    commandStack.top()->undo();
    commandStack.pop();
}

void printNewLines(int n){
    for(int i=0;i<n;++i){
        cout << endl;
    }
}

int main(){
    TaskManager manager;
    cout << "Welcome to the Task Management System!" << endl << endl;
    cout << "Info: Duplicate Tasks are not accepted." << endl;
    cout << "      The Task List is 1-indexed," << endl;
    cout << "      so the index of the first task is 1, not 0" << endl << endl;
    cout << "To get started, let's create your first task." << endl;
    cout << "Press enter to get started" << endl << endl;
    Task firstTask;
    firstTask.createTask();
    manager.append(firstTask);
    printNewLines(3);

    bool runProgram = true;
    while(runProgram){
        manager.display(); printNewLines(2);

        cout << "Enter any key to open options: " << endl;
        string openOptions;
        cin >> openOptions; cout << endl;

        cout << "Options:" << endl;
        cout << "Add Task to Beginning [1]" << endl;
        cout << "Add Task to End [2]" << endl;
        cout << "Add Task Somewhere Else Inside the List [3]" << endl;
        cout << "Remove a Task [4]" << endl;
        cout << "Swap Two Tasks [5]" << endl;
        cout << "Edit a Task [6]" << endl;
        cout << "Search for a Task by Date [7]" << endl;
        cout << "Search for a Task by Title [8]" << endl;
        cout << "View Tasks in Chronological Order [9]" << endl;
        cout << "View Tasks in Alphabetical Order [10]" << endl;
        cout << "Undo Previous insert/remove/swap/edit Command [11]" << endl;
        cout << "Exit Program [12]" << endl;

        int input;

        do{
            cout << "ENTER HERE (1-12): ";
            cin >> input;
            if(!validate_cin()){
                cerr << "ERROR: INVALID INPUT, TRY AGAIN" << endl;
                continue;
            }
            if(input < 1  ||  input > 12){
                cerr << "Invalid number, please try again" << endl;
                continue;
            }
            break;
        }while(true);

        switch(input){
            case 1: {
                //Task insertion at list start
                Task newTask;
                newTask.createTask();
                manager.prepend(newTask);
                break;
            }
            case 2: {
                //Task insertion at list end
                Task newTask;
                newTask.createTask();
                manager.append(newTask);
                break;
            }
            case 3: {
                //Task insertion after a certain index
                int index;
                while(true){
                    cout << "After which index will the task be inserted? ";
                    cin >> index;
                    if(!validate_cin()){
                        cerr << "Enter a valid number, Try again" << endl;
                        continue;
                    }
                    if(index < 1  ||  index > manager.length()){
                        cerr << "Invalid index, Try again" << endl;
                        continue;
                    }
                    break;
                }

                Task newTask;
                newTask.createTask();
                manager.insertAfter(newTask, index);
                break;
            }
            case 4: {
                //Task Removal
                if(manager.length() == 0){
                    cerr << "Task manager is empty, cannot remove task" << endl;
                    break;
                }
                int index;
                do{
                    cout << "Enter the task number for removal: ";
                    cin >> index;
                    if(!validate_cin()){
                        cerr << "Enter a valid number, Try again" << endl;
                        continue;
                    }
                    if(index < 1  ||  index > manager.length()){
                        cerr << "Invalid index, Try again" << endl;
                        continue;
                    }
                    break;
                }while(true);

                manager.remove(index);
                if(manager.length() == 0){
                    cout << "The manager is now empty. You must now create a task" << endl;
                    Task newTask;
                    newTask.createTask();
                    manager.prepend(newTask);
                }
                break;
            }
            case 5: {
                //Swap two tasks
                int index1, index2;
                while(true){
                    cout << "Enter index #1: ";
                    cin >> index1;
                    if(!validate_cin()){
                        cerr << "Enter input as integers. Try again." << endl;
                        continue;
                    }
                    if(index1 < 1  ||  index1 > manager.length()){
                        cerr << "invalid task number, try again" << endl;
                        continue;
                    }
                    break;
                }
                while(true){
                    cout << "Enter index #2: ";
                    cin >> index2;
                    if(!validate_cin()){
                        cerr << "Enter input as integers. Try again." << endl;
                        continue;
                    }
                    if(index2 < 1  ||  index2 > manager.length()){
                        cerr << "invalid task number, try again" << endl;
                        continue;
                    }
                    break;
                }
                manager.swap(index1 , index2);
                break;
            }
            case 6: {
                //edit a task
                int index;
                while(true){
                    cout << "Enter the index of the task you wish to edit: ";
                    cin >> index;
                    if(!validate_cin()){
                        cerr << "ERROR: Please enter a number" << endl;
                        continue;
                    }
                    if(index < 1  ||  index > manager.length()){
                        cerr << "Invalid task number, try again" << endl;
                        continue;
                    }
                    break;
                }
                manager.edit(index);
                break;
            }
            case 7: {
                //search for a task by date
                Date d;
                d.createDate();
                Task* t = manager.search(d);
                if(t == nullptr){
                    cerr << "No task with this date exists" << endl;
                }else{
                    printNewLines(5);
                    t->display();
                    printNewLines(2);
                    string exitInput;
                    cout << "Enter any key to exit task view: ";
                    cin >> exitInput;
                }
                break;
            }
            case 8: {
                //search for a task by title
                string s;
                cout << "Enter task title for search: ";

                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                getline(cin,s);
                if(s.back() == '\n'){
                    s.pop_back();
                }
                cout << "FOR DEBUGGING PURPOSES (end one NL): " << s << endl;
                Task* t = manager.search(s);

                if(t == nullptr){
                    cerr << "No task with this title exists" << endl;
                    string contInput;
                    cout << "Enter any key to continue: ";
                    cin >> contInput;
                }
                else{
                    printNewLines(5);
                    t->display();
                    printNewLines(2);
                    string exitInput;
                    cout << "Enter any key to exit task view: ";
                    cin >> exitInput;
                }
                break;
            }
            case 9: {
                //Display dates chronologically
                printNewLines(2);
                manager.displayByDate();
                string exitInput;
                cout << "Enter any key to exit chronological view: ";
                cin >> exitInput;
                break;
            }
            case 10: {
                //Display dates alphabetically
                printNewLines(2);
                manager.displayByTitle();
                string exitInput;
                cout << "Enter any key to exit alphabetical view: ";
                cin >> exitInput;
                break;
            }
            case 11: {
                //Undo Command
                manager.undo();
                break;
            }
            case 12: {
                //exit program;
                runProgram = false;
                break;
            }
            default: {
                //this will not occur since input validation was conducted before
                cerr << endl << "An Error Occurred" << endl;
                break;
            }
        }
        printNewLines(3);
    }

    return 0;
}
