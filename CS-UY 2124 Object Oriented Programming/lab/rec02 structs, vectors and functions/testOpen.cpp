#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <utility>

using namespace std;

void openStream(ifstream& txtStream){
    cout<<"Enter a filename" << endl;
    string filename;
    cin >> filename;
    txtStream.open(filename);
    while (!txtStream) {
        cout<< "File not found, try again";
        cin >> filename;
        txtStream.open(filename);
    }
}


void openfile(ifstream& file){
    
    string fileName;
    cout << "Please enter file name: ";
    cin >> fileName;
    file.open(fileName);
    while (!file){
        cout << "failed to open " << fileName << endl;
        cout << "Input another file name: " ;
        cin >> fileName;
        file.open(fileName);
    }
}

int main(){
    ifstream textstream;
    // openStream(textstream);
    openfile(textstream);
}