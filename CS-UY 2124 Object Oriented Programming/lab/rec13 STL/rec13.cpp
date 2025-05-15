// rec13.cpp
// Simon

#include <iostream>
#include <fstream>
#include <vector>      // task 1
#include <list>        // task 2
#include <algorithm>   // task 3
#include <string>      // task 21
#include <set>         // task 22
#include <map>         // task 23
using namespace std;

// task 9
void printList(const list<int>& rhs){
    for (list<int>::const_iterator it = rhs.begin(); it != rhs.end(); ++it){
        cout << *it <<' '; 
    }
}
// task 10
void printList2(const list<int>& rhs){
    for (int each : rhs){
        cout << each << ' ';
    }
}

// task 11
void autoPrintList(const list<int>& rhs){
    // bool printFlag = true;
    for (auto it = rhs.begin(); it != rhs.end(); ++++it){
        // if (printFlag){
        cout << *it << ' '; 
        // }
        // printFlag = !printFlag;
    }
}

// task 12
list<int>::const_iterator findItemInList(const list<int>& aList, int stuff){
    for (list<int>::const_iterator it = aList.begin(); it != aList.end(); ++it){
        if (*it == stuff){
            return it;
        }
    }
    return aList.end();
}

// task 13
auto autoFindItemInList(const list<int>& aList, int stuff){
    for (auto it = aList.begin(); it != aList.end(); ++it){
        if (*it == stuff){
            return it;
        }
    }
    return aList.end();
}

// task 15
bool isEven(int num){
    return num % 2 == 0;
}

// task 19
list<int>::iterator ourFind(list<int>::iterator start,
     list<int>::iterator stop, int target){
        cout << "In my find function"<< endl; 
        for (list<int>::iterator cur = start; cur != stop; ++cur){
            if (*cur == target){
                return cur;
            }
        }
        return stop; 
}

// task 20
template <typename T, typename U>
T ourFind(T start, T stop, U target){
    for (T cur = start; cur != stop; ++cur){
        if (*cur == target){
            return cur;
        }
    }
    return stop; 
}

int main() {
    // 1. Create a vector with some values and display using ranged for
    cout << "Task 1:\n";
    vector<int> vecInt = {1, 4, 2, 3, 6, 5};
    for (int each : vecInt){
        cout << each << ' ';
    }

    cout << "\n=======\n";

    // 2. Initalize a list as a copy of values from the vector
    cout << "Task 2:\n";
    list<int> listInt(vecInt.begin(), vecInt.end());
    for (list<int>::iterator it = listInt.begin(); it != listInt.end(); ++it){
        cout << *it <<' '; 
    }
    cout << "\n=======\n";

    // 3. Sort the original vector.  Display both the vector and the list
    cout << "Task 3:\n";
    sort(vecInt.begin(), vecInt.end());
    for (int each : vecInt){
        cout << each << ' ';
    }
    cout << endl;
    for (list<int>::iterator it = listInt.begin(); it != listInt.end(); ++it){
        cout << *it <<' '; 
    }
    cout << "\n=======\n";

    // 4. print every other element of the vector.
    cout << "Task 4:\n";
    for (size_t i = 0; i < vecInt.size(); i += 2){
        cout << vecInt[i] << ' ';
    }

    cout << "\n=======\n";

    // 5. Attempt to print every other element of the list using the
    //    same technique.
    cout << "Task 5:\n";
    // for (size_t i = 0; i < listInt.size(); i += 2){
    //     cout << listInt[i] << ' ';
    // }
    cout << "\n=======\n";

    //
    // Iterators
    //

    // 6. Repeat task 4 using iterators.  Do not use auto;
    cout << "Task 6:\n";
    for (vector<int>::iterator it = vecInt.begin(); it != vecInt.end(); it += 2){
        cout << *it << ' '; 
    }
    cout << "\n=======\n";

    // 7. Repeat the previous task using the list.  Again, do not use auto.
    //    Note that you cannot use the same simple mechanism to bump
    //    the iterator as in task 6.
    cout << "Task 7:\n";

    for (list<int>::iterator it = listInt.begin(); it != listInt.end(); ++++it){
        cout << *it << ' ';        
    }
    cout << "\n=======\n";

    // 8. Sorting a list
    cout << "Task 8:\n";
    listInt.sort();
    for (list<int>::iterator it = listInt.begin(); it != listInt.end(); ++it){
        cout << *it <<' '; 
    }
    cout << "\n=======\n";

    // 9. Calling the function to print the list
    cout << "Task 9:\n";
    printList(listInt);
    cout << "\n=======\n";

    // 10. Calling the function that prints the list, using ranged-for
    cout << "Task 10:\n";
    printList2(listInt);
    cout << "\n=======\n";

    //
    // Auto
    //

    // 11. Calling the function that, using auto, prints alterate
    // items in the list
    cout << "Task 11:\n";
    autoPrintList(listInt);
    cout << "\n=======\n";
    
    
    // 12.  Write a function find that takes a list and value to search for.
    //      What should we return if not found
    cout << "Task 12:\n";
    int test = 6;
    list<int>::const_iterator it1 = findItemInList(listInt, test);
    if (it1 != listInt.end()){
        cout << *it1; 
    } else {
        cout << "Not Found"; 
    }

    cout << "\n=======\n";

    // 13.  Write a function find that takes a list and value to search for.
    //      What should we return if not found
    cout << "Task 13:\n";
    int test2 = 6;
    auto it2 = autoFindItemInList(listInt, test);
    if (it2 != listInt.end()){
        cout << *it2; 
    } else {
        cout << "Not Found"; 
    }
    cout << "\n=======\n";

    //
    // Generic Algorithms
    //

    // 14. Generic algorithms: find
    cout << "Task 14:\n";

    list<int>::iterator it3= find(listInt.begin(), listInt.end(), 10);
    if (it3 != listInt.end()){
        cout << *it3; 
    } else {
        cout << "Not Found"; 
    }

    cout << "\n=======\n";

    // 15. Generic algorithms: find_if
    cout << "Task 15:\n";
    // vector

    vector<int>::iterator it4 = find_if(vecInt.begin(), vecInt.end(), isEven);
    
    if (it4 != vecInt.end()) {
        cout << "First even number in vector: " << *it4 << endl;
    } else {
        cout << "No even number found in vector" << endl;
    }
    
    // list 
    list<int>::iterator itList = find_if(listInt.begin(), listInt.end(), isEven);
    
    if (itList != listInt.end()) {
        cout << "First even number in list: " << *itList << endl;
    } else {
        cout << "No even number found in list" << endl;
    }

    cout << "\n=======\n";


    // 16. Lambda
    cout << "Task 16:\n";
    [] { cout << "Hello Lambda!"; }();
    cout << endl; 
    int result = [] (int a, int b) { return a + b; } (4, 5);
    cout << "the result is: " << result << endl;

    int result2 = [] (int a, int b) -> int { return a + b; } (4, 5);
    cout << "the result is: " << result2 << endl;

    find_if(listInt.begin(), listInt.end(), [](int a) { return a % 2 == 0;});

    cout << "\n=======\n";

    // 17. Lambda capture
    cout << "Task 17:\n";

    int divisor = 1; 
    cout << "Enter a divisor: ";
    // cin >> divisor;

    int testN = 0;
    cout << "Enter a number to test: ";
    // cin >> testN;

    cout << [divisor](int n) { return n % divisor == 0; }(testN);

    cout << "\n=======\n";

    // 18. Generic algorithms: copy to an array
    cout << "Task 18:\n";
    int* arrVec = new int[vecInt.size()];
    copy(vecInt.begin(), vecInt.end(), arrVec);

    
    for (size_t i = 0; i < vecInt.size(); ++i) {
        cout << arrVec[i] << " ";
    }
    cout << endl;

    int* found = find(arrVec, arrVec + vecInt.size(), 10);
    if (found != arrVec + vecInt.size()){
        cout << *found; 
    } else {
        cout << "Not found. "; 
    }
    
    delete[] arrVec;

    cout << "\n=======\n";

    //
    // Templated Functions
    //

    // 19. Implement find as a function for lists
    cout << "Task 19:\n";


    list<int>::iterator itOF = ourFind(listInt.begin(), 
    listInt.end(), 3); 
    if (itOF != listInt.end()){
        cout << *itOF; 
    } else {
        cout << "Not Found"; 
    }

    cout << "\n=======\n";
    
    // 20. Implement find as a templated function
    cout << "Task 20:\n";
    list<int>::iterator itT = ourFind(listInt.begin(), 
    listInt.end(), 3); 
    if (itT != listInt.end()){
        cout << *itT; 
    } else {
        cout << "Not Found"; 
    }
    cout << "\n=======\n";

    //
    // Associative collections
    //

    // 21. Using a vector of strings, print a line showing the number
    //     of distinct words and the words themselves.
    cout << "Task 21:\n";
    
    ifstream inputFile("pooh-nopunc.txt");
    vector<string> allWords; 
    string each; 
    while (inputFile >> each){
        bool bolFind; 

        if (find(allWords.begin(), allWords.end(), each)
         != allWords.end()){
            bolFind = true;
        } else {
            bolFind = false;
        }

        if (bolFind == false){
            allWords.push_back(each);
        }
    }
    inputFile.close();
    cout << allWords.size()<< endl; 
    for (const string& wd : allWords) {
        cout << wd << ' ';
    }


    cout << "\n=======\n";

    // 22. Repeating previous step, but using the set
    cout << "Task 22:\n";
    ifstream ifs("pooh-nopunc.txt");
    set<string> setWords; 
    string eachS; 
    while (ifs >>eachS){
        setWords.insert(eachS);

    }
    ifs.close();
    cout << setWords.size()<<endl; 
    for (set<string>::iterator it = setWords.begin(); it != setWords.end(); ++it) {
        cout << *it << " ";
    }

    cout << "\n=======\n";

    // 23. Word co-occurence using map
    cout << "Task 23:\n";
    ifstream ifs2("pooh-nopunc.txt");
    map<string, vector<int>> wordMap;
    string last; 
    int tokenNumber = 0;
    while (ifs2 >> last)
    {
        ++tokenNumber;
        wordMap[last].push_back(tokenNumber);
    }
    for (const pair<const string, vector<int>>& entry
         : wordMap) {
        cout << entry.first << ": ";
        for (int pos : entry.second) {
            cout << pos << " ";
        }
        cout << endl;
    }

    cout << "\n=======\n";
}
