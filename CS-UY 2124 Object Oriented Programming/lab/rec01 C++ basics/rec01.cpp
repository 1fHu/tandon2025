/*
  rec01_start.cpp
  fall 2024
  Simon Hu
*/
#include <iostream>
using namespace std;
#include <fstream>
#include <string>
#include <vector>

//
// main
//
int main() { // Yes, it has to have an int for the return type
    //
    // Output
    //

    // Task 1. Printing hello ...  No use of "using namespace"
  std::cout << "Hello\n";

    // Task 2  Printing hello ...  Using "using namespace"
  cout << "Hello" << endl;

    //
    // Types and variables
    //

    // Task 3  Displaying uninitialized variable
  int x;
  cout << x << endl;

    // Task 4 Use the sizeof function to see the size in bytes of
    //        different types on your machine.
  int y = 17;
  int z = 2000000017;
  double pie = 3.14159;

  cout <<"x size: "<< sizeof(x) << "  y size: " << sizeof(y) << endl;
  cout <<"z size: "<< sizeof(z) << "  pie size: " << sizeof(pie) << endl;
    
    // Task 5  Attempt to assign the wrong type of thing to a variable

  // x = "felix"; // this is a compilation error

    //
    // Conditions
    //

    // Task 6  Testing for a range
  if (y >= 10 && y <= 20) {
    cout << "y is between 10 and 20" << endl;
  }
  else {
    cout << "y is not between 10 and 20" << endl;
  }
    

    //
    // Loops and files
    //

    // Task 7  Looping, printing values 10 to 20 inclusive

    // First with a for loop
  for (int a = 10; a < 21; ++a){
    cout << a << ' ';
  }
  cout << endl; 

    // Then with a while loop
  int b = 10;
  while (b <= 20){
    cout << b << ' ';
    ++b;
  }
  cout << endl;

    // Finally with a do-while loop
  int c = 10;
  do{
    cout << c << ' ';
    ++c;
  } while (c <= 20);
  cout << endl;

    // Task 8  Looping to successfully open a file, asking user for the name
  
  ifstream ifs1;
  string name1;
  do{
    cout << "input a file name: ";
    cin >> name1;
    ifs1.open(name1);
  } while (!ifs1);
  
    // Task 9  Looping, reading file word by "word".
  ifstream ifs;
  string name;
  do{
    cout << "input a file name: ";
    cin >> name;
    ifs.open(name);
  } while (!ifs);
  
  string word;
  while (ifs >> word) {
    cout << word << endl;
  }
  
  ifs.close();


    // Task 10 Open a file of integers, read it in, and display the sum.
  ifstream intfile;
  intfile.open("integers.txt");
  if (!intfile){
    cerr << "failed to open integer.txt";
    exit(1);
  }

  int eachinteger;
  int sum = 0;
  while (intfile >> eachinteger){
    sum += eachinteger;
  }
  cout << "Sum: " << sum << endl;
  intfile.close();

    // Taks 11 Open and read a file of integers and words. Display the sum.
  ifstream mixfile;
  mixfile.open("mixed.txt");
  if (!mixfile){
    cerr << "failed to open integer.txt";
    exit(1);
  }

  int eachelement;
  int sum1 = 0;
  while (mixfile >> eachelement){
    // cout << eachelement << endl;
    sum1 += eachelement;
  }
  cout << "Sum of mix: " << sum1 << endl;
  intfile.close();  

    //
    // Vectors
    //

    // Task 12 Filling a vector of ints
  vector<int> intvector;
  for (int d = 10; d <= 100; d += 2){
      intvector.push_back(d);
  }


  
    
    // Task 13 Displaying the vector THREE times
    //         a) using the indices,
  for (size_t i = 0; i < intvector.size(); ++i){
    cout << intvector[i] << ' ';
  }
  cout << endl;

    //         b) using a "ranged for"
  for (int number : intvector){
    cout << number << ' ';
  }
  cout << endl;

    //         c) using indices again but backwards
  for (size_t i = intvector.size(); i > 0; --i){
    cout << intvector[i-1] << ' ';
  }
  cout << endl;

    // Task 14. Initialize a vector with the primes less than 20. 
  vector<int> vprime{2, 3, 5, 7, 11, 13, 17, 19};
  for (int prime : vprime){
    cout << prime << ' ';
  }
  cout << endl;
    
} // main

