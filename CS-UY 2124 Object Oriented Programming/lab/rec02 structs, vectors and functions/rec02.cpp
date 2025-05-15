/*
  rec02.cpp
  Simon Hu
  This file sort the chemical formulae.
*/

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <utility>

using namespace std;

struct Chemical {
    vector<string> names;
    int carbonAtoms;
    int hydroAtoms;
};



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


size_t checkIndex (int carbon, int hydrogon, const vector<Chemical>& allChemistries){
    for (size_t i = 0; i < allChemistries.size(); ++i){
        if (allChemistries[i].hydroAtoms == hydrogon && 
            allChemistries[i].carbonAtoms == carbon){
            return i;
        }
    }
    return allChemistries.size();
    }

void printChemicals(const Chemical& c){
    cout << 'C' << c.carbonAtoms 
        << 'H' << c.hydroAtoms << ' ';
    for (size_t i = 0; i < c.names.size(); ++i){
        cout << c.names[i] << ' ';
    }
    cout << endl;
}

void display(const vector<Chemical>& allChemicals){
    for (const Chemical& c : allChemicals){
        printChemicals(c);
    }
}

void fillVector(vector<Chemical>& allChemicals, ifstream& formulaStream){
    int carbon;
    int hydrogen;
    char letterC;
    char letterH;
    string cheName;

    while(formulaStream >> cheName >> letterC >> carbon >> letterH >> hydrogen) {
        int checkedNum = checkIndex(carbon, hydrogen, allChemicals);
        if (checkedNum == allChemicals.size()){
            vector<string> oneNameVector;
            oneNameVector.push_back(cheName);
            Chemical aFormula {oneNameVector, carbon, hydrogen};
            allChemicals.push_back(aFormula);
        }
        else{
            allChemicals[checkedNum].names.push_back(cheName);
        }
        
    }
}

void sort(vector<Chemical>& allChemical){
    for (size_t i = 0; i < allChemical.size(); ++i){
        for (size_t j = 0; j < (allChemical.size() - 1); ++j){
            if (allChemical[j].carbonAtoms > allChemical[j+1].carbonAtoms ||
                (allChemical[j].carbonAtoms == allChemical[j+1].carbonAtoms &&
                allChemical[j].hydroAtoms > allChemical[j+1].hydroAtoms)){
                swap(allChemical[j], allChemical[j + 1]);
            }
        }
    }
}

int main(){
    ifstream formulaStream;
    openfile(formulaStream);

    vector<Chemical> allChemicals;
    fillVector(allChemicals, formulaStream);

    cout << "Unsorted: " << endl;
    display(allChemicals);

    sort(allChemicals);

    cout << endl;
    cout << "Sorted: " << endl;

    display(allChemicals);

    formulaStream.close();
    return 0;
}
