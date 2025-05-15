/*
Author: Simon Hu
Purpose: Decrypt txt file 
*/

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;



char decrypted(char encrypted, int distance);


void change(string& changedStr, int distance);

int main(){
    // store file
    ifstream stringFile;
    stringFile.open("encrypted.txt");
    if (!stringFile){
        cout << "failed to open encrypted.txt";
        exit(1);
    }

    // read integer
    int distance;
    stringFile >> distance;

    // store each line in vector
    string eachLine;
    vector<string> allLines;
    while (getline(stringFile, eachLine)){
        allLines.push_back(eachLine);
    }
    stringFile.close();

    // do modification to allLines
    for (size_t line = 0; line < allLines.size(); ++line){
        string& eachString = allLines[line];
        change(eachString, distance);
    }

    // print the vector reversely
    for (size_t i = allLines.size(); i > 0 ; --i) {
        cout << allLines[i - 1] << endl;
    }
}


/*
    Decrypt one character with the given specific one
    character and using given integer as distance.
    parameters: char encrypted, int distance 
    return type: char
    */
char decrypted(char encrypted, int distance){
    if (distance == 0){ return encrypted;} // revised
    else if (isupper(encrypted)){
        char origin = encrypted - distance;

        if (origin < 'A'){
            return encrypted + 26 - distance;
        }
        else if (origin > 'Z'){
            return encrypted - 26 - distance;
        }

        return origin;
    }
    else {return encrypted;}
}


/* Pass the string by reference 
    to modify original string using integer distance
    parameters: string reference of chargedstring, int distance
    return type: None 
    */ 
void change(string& changedStr, int distance){ 
    for (size_t index = 0; index < changedStr.size(); ++index){
        changedStr[index] = decrypted(changedStr[index], distance);
    }
}
