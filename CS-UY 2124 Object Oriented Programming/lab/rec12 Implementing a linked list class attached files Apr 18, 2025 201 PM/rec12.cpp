// Doubly linked list
// Simon Hu

#include <cstdlib>
#include <iostream>
using namespace std;

class List {
public:
    List(){
        header = new Node{}; 
        trailer = new Node{}; 
        header->next = trailer; 
        trailer->prev = header;
        listSize = 0; 
    }
    void push_back(int data) {
        Node* aNode = new Node{data, trailer->prev, trailer};
        trailer->prev->next = aNode; 
        trailer->prev = aNode;
        ++listSize; 
    }

    void pop_back(){
        if (listSize == 0){ return;}
        Node* del = trailer->prev; 
        trailer->prev = del->prev; 
        del->prev->next = trailer; 
        delete del; 
        --listSize;
    }
    int& front(){
        return header->next->data;
    }

    int front() const {
        return header->next->data; 
    }

    int& back(){
        return trailer->prev->data;
    }

    int back() const {
        return trailer->prev->data; 
    }

    int size() const {
        return listSize;
    }

    void push_front(int data){ 
        Node* aNode = new Node{data, header, header->next};
        header->next->prev = aNode;
        header->next = aNode; 
        ++listSize;
    }

    void pop_front(){
        if (listSize == 0){ return;}
        Node* del = header->next;
        del->next->prev = header; 
        header->next = del->next; 
        delete del; 
        --listSize; 
    }

    void clear(){ 
        Node* curr = header->next; 
        while (curr != trailer) {
            Node* nextNode = curr->next; 
            delete curr; 
            curr = nextNode;
        }
        // curr == trailer
        header->next = trailer; 
        trailer->prev = header; 
        listSize = 0; 
    }

    int& operator[](size_t index){
        Node* begin = header->next; 
        for (size_t i = 0; i < index; i++){
            begin = begin->next;
            
        }
        return begin->data;
    }
    // const int& operator[](size_t index) const {
    int operator[](size_t index) const {
        Node* begin = header->next; 
        for (size_t i = 0; i < index; i++){
            begin = begin->next;
        }
        return begin->data;
    }


private:
    struct Node{
        int data; 
        Node* prev = nullptr;
        Node* next = nullptr; 

        // constructor
        Node (int data = 0, Node* prev = nullptr, Node* next = nullptr)
            : data(data), prev (prev), next(next){} 
    }; 
    friend ostream& operator<<(ostream& os, const List& rhs);

public: 
    class iterator{
    public: 
        iterator(Node* node) : current(node){} 
        int& operator*() const{
            return current->data; 
        }
        iterator& operator++(){
            current = current->next;
            return *this; 
        }
        iterator& operator--(){
            current = current->prev; 
            return *this; 
        }

        bool operator==(const iterator& rhs) const {
            return  (current == rhs.current);
        }
        bool operator!=(const iterator& rhs) const{
            return (current != rhs.current);
        }

    private: 
        Node* current; 
        friend class List; 
    }; 

    iterator begin() { return header->next; }
    iterator end() { return trailer; }

    iterator insert(iterator pos, int data){
        Node* posNode = pos.current;
        Node* aNode = new Node {data, posNode->prev, posNode}; 
        posNode->prev->next = aNode; 
        posNode->prev = aNode; 
        ++listSize;
        return iterator(aNode);
    }

    iterator erase(iterator pos){
        Node* posNode = pos.current; 
        posNode->prev->next = posNode->next; 
        posNode->next->prev = posNode->prev;
        Node* returnNode = posNode->next;
        delete posNode;
        --listSize;
        return iterator(returnNode); 
    }

    // big three
    List(const List& rhs){
        header = new Node(); 
        trailer = new Node(); 
        header->next = trailer; 
        trailer->prev = header; 
        listSize = 0;

        for (Node* curr = rhs.header->next; curr != rhs.trailer;
             curr = curr->next){
            push_back(curr->data);            
        }
    }

    ~List(){
        clear();
        delete header; 
        delete trailer;
    }

    List& operator=(const List& rhs){
        if (this != &rhs){
            this->clear(); 
            for (Node* curr = rhs.header->next; curr != rhs.trailer;
                curr = curr->next){
                push_back(curr->data);            
            }
        }
        return *this; 
    }

private: 
    Node* header; 
    Node* trailer; 
    size_t listSize; 

};

ostream& operator<<(ostream& os, const List& rhs){
    List::Node* curr = rhs.header->next; 
    while (curr != rhs.trailer){
        os << curr->data << ' '; 
        curr = curr->next; 
    }
    return os; 
}


// Task 1
void printListInfo(const List& myList) {
        cout << "size: " << myList.size()
             << ", front: " << myList.front()
             << ", back(): " << myList.back()
             << ", list: " << myList << endl;
}

// The following should not compile. Check that it does not.
/*
void changeFrontAndBackConst(const List& theList) {
    theList.front() = 17;
    theList.back() = 42;
}
*/
void changeFrontAndBack(List& theList) {
    theList.front() = 17;
    theList.back() = 42;
}


// Task 4
void printListSlow(const List& myList) {
    for (size_t i = 0; i < myList.size(); ++i) {
        cout << myList[i] << ' ';
    }
    cout << endl;
}

// Task 8
void doNothing(List aList) {
    cout << "In doNothing\n";
    printListInfo(aList);
    cout << endl;
    cout << "Leaving doNothing\n";
}    

int main() {

    // Task 1
    cout << "\n------Task One------\n";
    List myList;
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        cout << "myList.push_back(" << i*i << ");\n";
        myList.push_back(i*i);
        printListInfo(myList);
    }
    cout << "===================\n";
    
    cout << "Modify the first and last items, and display the results\n";
    changeFrontAndBack(myList);
    printListInfo(myList);
    cout << "===================\n";

    cout << "Remove the items with pop_back\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.pop_back();
    }
    cout << "===================\n";

    // Task 2
    cout << "\n------Task Two------\n";
    cout << "Fill empty list with push_front: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        cout << "myList2.push_front(" << i*i << ");\n";
        myList.push_front(i*i);
        printListInfo(myList);
    }
    cout << "===================\n";
    cout << "Remove the items with pop_front\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.pop_front();
    }
    printListInfo(myList);
    cout << "===================\n";

    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        myList.push_back(i*i);
    }
    printListInfo(myList);
    cout << "Now clear\n";
    myList.clear();
    cout << "Size: " << myList.size() << ", list: " << myList << endl;
    cout << "===================\n";

    // Task 3
    cout << "\n------Task Three------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i)  myList.push_back(i*i);
    cout << "Display elements with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) cout << myList[i] << ' ';
    cout << endl;
    cout << "Add one to each element with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) myList[i] += 1;
    cout << "And print it out again with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) cout << myList[i] << ' ';
    cout << endl;
    cout << "Now calling a function, printListSlow, to do the same thing\n";
    printListSlow(myList);
    cout << "Finally, for this task, using the index operator to modify\n"
         << "the data in the third item in the list\n"
         << "and then using printListSlow to display it again\n";
    myList[2] = 42;
    printListSlow(myList);
    
  
    // Task 4
    cout << "\n------Task Four------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i)  myList.push_back(i*i);
    printListInfo(myList);
    cout << "Now display the elements in a ranged for\n";
    for (int x : myList) cout << x << ' ';
    cout << endl;
    cout << "And again using the iterator type directly:\n";
    // Note you can choose to nest the iterator class or not, your choice.
    //for (iterator iter = myList.begin(); iter != myList.end(); ++iter) {
    for (List::iterator iter = myList.begin(); iter != myList.end(); ++iter) {
        cout << *iter << ' ';
    }
    cout << endl;
    cout << "WOW!!! (I thought it was cool.)\n";
     
    // Task 5
    cout << "\n------Task Five------\n";
    cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
    printListInfo(myList);
    cout << "Filling an empty list with insert at begin(): "
         << "i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.begin(), i*i);
    printListInfo(myList);
    // ***Need test for insert other than begin/end***
    cout << "===================\n";

    // Task 6
    cout << "\n------Task Six------\n";
    cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
    cout << "Erasing the elements in the list, starting from the beginning\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.erase(myList.begin());
    }
    // ***Need test for erase other than begin/end***
    cout << "===================\n";

    // Task 7
    cout << "\n------Task Seven------\n";
    cout << "Copy control\n";
    cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
    printListInfo(myList);
    cout << "Calling doNothing(myList)\n";
    doNothing(myList);
    cout << "Back from doNothing(myList)\n";
    printListInfo(myList);

    cout << "Filling listTwo with insert at begin: i*i for i from 0 to 9\n";
    List listTwo;
    for (int i = 0; i < 10; ++i) listTwo.insert(listTwo.begin(), i*i);
    printListInfo(listTwo);
    cout << "listTwo = myList\n";
    listTwo = myList;
    cout << "myList: ";
    printListInfo(myList);
    cout << "listTwo: ";
    printListInfo(listTwo);
    cout << "===================\n";
    
}
