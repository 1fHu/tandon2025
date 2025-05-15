#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

int main(){
    ifstream fileRead("Warriors.txt");
    string word;
    fileRead >> word;
    cout << word << endl;
    string word2;
    fileRead >> word2;
    cout << word2 << endl;
    int strength;
    fileRead >> strength;
    cout << strength << endl;
    string word4;
    fileRead >> word4;
    cout << word4 << endl;
    // string eachLine;
    // getline(fileRead, eachLine);
    // cout << eachLine << endl;
    // istringstream ss(eachLine);
    // string first;
    // ss >> first;
    // cout << first << endl;
    // string second;
    // int third;
    // ss >> second >> third;
    // cout << second << endl;
    // cout << third << endl;
    fileRead.close();
}