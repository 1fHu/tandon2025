/*
  rec14_starter code
 */

#include <iostream>
#include <vector>
#include <algorithm>  // max
using namespace std;


// Node type for the linked list
struct Node {
    int data = 0;
    Node* next = nullptr;
};

// Node type for the ternary tree
struct TNode {
    int data = 0;
    TNode* left = nullptr;
    TNode* mid = nullptr;
    TNode* right = nullptr;
};



/////////////////////////////////////////////////////////////////////////
//
// Provided code for use in testing
//
void listPrint(const Node* headPtr);
void listClear(Node*& headPtr);
Node* listBuild(const vector<int>& vals);


//
// Your functions go here
//
//   Task 1 function:
Node* listSum(Node* one, Node* two){
    if (one == nullptr && two == nullptr){
        return nullptr;
    }
    Node* result = new Node;

    if (one == nullptr && two != nullptr){
        result->data = two->data;
        result->next = listSum(two->next, nullptr);

    }
    else if (one != nullptr && two == nullptr){
        result->data = one->data;
        result->next = listSum(one->next, nullptr);

    }
    else {
        int sum = one->data + two->data;
        result->data = sum; 
        result->next = listSum(one->next, two->next);
        
    }
    return result; 
}

//   Task 2 function:
int treeMax(TNode* tree){
    if (tree == nullptr){
        throw runtime_error("Cannot find max of an empty tree");
    }

    int result = tree->data; 

    if (tree->left != nullptr){

        result = max(result, treeMax(tree->left));
    }
    if (tree->mid != nullptr){

        result = max(result, treeMax(tree->mid));
    }
    if (tree->right != nullptr){

        result = max(result, treeMax(tree->right));
    }
    return result;
}
//   Task 3 function:

bool palindrome(const char* str, int length){
    if (length <= 1) return true;


    return (str[0] == str[length-1]) && palindrome(str + 1, length - 2);
}

//   Task 4 function:

// has an even number of ones in its binary representation
bool parity (int num){
    if (num == 0) return true;

    bool rest = parity(num/2);
    if (num % 2 == 1){
        rest = !rest;
    } else {
        rest = rest;
    }
    return rest;
}

//   Task 5 function:
int towers(int layer, char start, char target, char spare){
    if (layer == 0) return 0;
    int total = 0;
    total += towers(layer-1, start, spare, target);
    total += 1;
    total += towers(layer-1, spare, target, start);
    return total;
}

    
void mystery(int n) { 
    if (n > 1) { 
       cout << 'a'; 
       mystery(n/2); 
       cout << 'b'; 
       mystery(n/2); 
    } 
    cout << 'c'; 
 }

int main() {
    // We have provided some test code to save you time. Certainly feel
    // free to write more!

    // Task 1:
    cout << "\n==============\n#1: Testing listSum\n";
    Node* l1 = listBuild({2, 7, 1, 8});
    cout << "List (l1): ";
    listPrint(l1);
    
    Node* l2 = listBuild({9, 1, 4, 1});
    cout << "List (l2): ";
    listPrint(l2);

    Node* l3 = listBuild({3, 1, 4, 1, 5, 9});
    cout << "List (l3): ";
    listPrint(l3);

    cout << "The sum of l1 and l2: ";
    Node* l4 = listSum(l1, l2);
    listPrint(l4);

    cout << "The sum of l1 and l3: ";
    Node* l5 = listSum(l1, l3);
    listPrint(l5);

    cout << "The sum of l3 and l1: ";
    Node* l6 = listSum(l3, l1);
    listPrint(l6);

    listClear(l1);
    listClear(l2);
    listClear(l3);
    listClear(l4);
    listClear(l5);
    listClear(l6);


    
    // Task 2:
    cout << "\n==============\n"
         << "#2) Testing max of Tree.\n";
    //TNode a{1}, b{2}, c{4}, d{-8, &a, &b, &c}, e{-16}, f{-32, &d, &e};
    TNode a{1}, b{20}, c{4}, d{-8, &a, &b, &c}, e{-16}, f{-32, &d, &e};
    cout << "treeMax(&f): " << treeMax(&f) << endl;

    // How do you keep this from crashing? try/catch! Here in main!
    try{
    cout << treeMax(nullptr) << endl;
    }
    catch (const exception& ex){
        cout << "Exception caught: " << ex.what() << endl;
    }


   
    // Task 3:
    cout << "\n==============\n"
	 << "#3) Testing palindrome\n";
    cout << boolalpha
	 << "palindrome(\"racecar\", 7): " << palindrome("racecar", 7) << endl
	 << "palindrome(\"noon\", 4): " << palindrome("noon", 4) << endl
	 << "palindrome(\"raceXar\", 7): " << palindrome("raceXar", 7) << endl
	 << "palindrome(\"noXn\", 4): " << palindrome("noXn", 4) << endl;
   
    // Task 4:
    cout << "\n==============\n"
	 << "#4) Are there an even number of 1's in binary representation?\n";
    cout << boolalpha;
    for (int i = 0; i < 10; ++i) {
        cout << i << ": " << parity(i) << endl;
    }


        
    // Task 5:
    cout << "\n==============\n"
	 << "#5) How many moves are required for various sized towers?";
    for (int i = 1; i < 30; ++i) {
	cout << "towers(" << i << ", 'a', 'b', 'c'): " 
	     << towers(i, 'a', 'b', 'c') << endl;
    }

    // for (size_t i = 0; i < 11; i++){
    //     mystery(i);
    //     cout << endl;
    // }
}


//
// The provided utility functions:
//

// listPrint prints out the data values in the list.
// All the values are printed on a single line with blanks separating them.
void listPrint(const Node* headPtr)
{
    const Node* curr = headPtr;
    while (curr != nullptr) {
        cout << curr->data << ' ';
        curr = curr->next;
    }
    cout << endl;
} // listPrint

// listClear frees up all of the nodes in list setting the the head
// pointer to null.
void listClear(Node*& headPtr)
{
    while (headPtr) {
        Node* next = headPtr->next;
        delete headPtr;
        headPtr = next;
    }
} // listClear

// listBuild returns a list with the same values as in the vector.
Node* listBuild(const vector<int>& vals)
{
    Node* result = nullptr;
    for (size_t index = vals.size(); index > 0; --index) {
	result = new Node{vals[index-1], result};
    }
    return result;
} // listBuild
