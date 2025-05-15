/*
  rec10.cpp

 */

#include <iostream>
#include <vector>
using namespace std;

// 
// Musician class as provided to the students. Requires an Instrument class.
// 

class Instrument{
public:
    virtual void makeSound() const=0;
    virtual void play() const = 0; 
    virtual void display(ostream& os) const =0;
};

void Instrument :: makeSound() const { cout<< "To make a sound... "; }

class Percussion : public Instrument{
public:
    void makeSound() const override {
        Instrument::makeSound();
        cout << "hit me!" << endl;
    }

};

class Drum : public Percussion{
    void display(ostream& os) const {
        os << "Drum" ;
    }
    void play() const override{
        cout << "Boom";
    }
};

class Cymbal : public Percussion{
    void display(ostream& os) const {
        os << "Cymbal";
    }
    void play() const override{
        cout << "Crash";
    }
};

class Brass : public Instrument{
public: 
    Brass (int num) : size(num) {}
    void makeSound () const override{
        Instrument::makeSound();
        cout <<"blow on a mouthpiece of size "
        << size << endl;
    }
    unsigned getSize() const {
        return size;
    }
private: 
    unsigned size; 
};

class Trumpet: public Brass{
public:
    using Brass :: Brass;
    void display(ostream& os) const {
        os << "Trumpet: " << getSize();
    }
    void play() const override{
        cout << "Toot";
    }
};

class Trombone : public Brass{
public:
    using Brass :: Brass;
    void display(ostream& os) const {
        os << "Trombone: " << getSize();
    }
    void play() const override{
        cout << "Blat";
    }
};

class String : public Instrument{
public: 
    String (int num) : pitch (num) {}
    void makeSound () const override {
        Instrument::makeSound();
        cout <<"bow a string with pitch "
        << pitch << endl;
    }
    unsigned getPitch() const {
        return pitch;
    }
private: 
    unsigned pitch;
};

class Violin : public String{
public: 
    using String :: String; 
    void display(ostream& os) const {
        os << "Violin: " << getPitch();
    }
    void play() const override{
        cout << "Screech";
    }
};

class Cello : public String{
public: 
    using String :: String; 
    void display(ostream& os) const {
        os << "Cello: " << getPitch();
    }
    void play() const override{
        cout << "Squawk";
    }
};

ostream& operator<<(ostream& os, const Instrument& rhs){
    rhs.display(os);
    return os;
}

class MILL {
public:
    void receiveInstr(Instrument& newInstr){
        newInstr.makeSound();
        if (allInstr.size() == 0){
            allInstr.push_back( &newInstr);
        } else {
        for (size_t i = 0; i < allInstr.size(); ++i){
            if (allInstr[i] == nullptr){
                allInstr[i] = &newInstr;
                return;
            }
            if (i == allInstr.size()-1){
                buildNew();
                allInstr[i+1] = &newInstr;
                break;
            }
        }


    }
    }

    Instrument* loanOut(){
        for (size_t i = 0; i < allInstr.size(); i++){
            if (allInstr[i] != nullptr){
                Instrument* loanPtr = allInstr[i];
                allInstr[i] = nullptr;
                return loanPtr;
            }
        }
        return nullptr;
    }
    void dailyTestPlay() const {
        if (getNumOfIns() == 0){
            cout << "None";
        } else {
            for(const Instrument* each : allInstr){
                if (each != nullptr){
                    
                    each->makeSound();}
            }
        }
    }



    void buildNew(){
        allInstr.push_back(nullptr);
    }
    int totalSpace() const {
        return allInstr.size();
    }
    int getNumOfIns() const {
        int num = 0;
        for (Instrument* each : allInstr){
            if (each != nullptr){
                num += 1;
            }
        }
        return num; 
    }
    friend ostream& operator<<(ostream& os, const MILL& rhs);
private:
    vector<Instrument*> allInstr;
};

ostream& operator<<(ostream& os, const MILL& rhs){
    os << "The MILL has the following instruments: ";
    if (rhs.getNumOfIns() == 0){
        os << "None";
        return os;
    } else {
        for(const Instrument* each : rhs.allInstr){
            if (each != nullptr){
                os << "\n	";
                each->display(os);}
        }
        return os;}
    
}




class Musician {
public:
    Musician(const string& name) : instr(nullptr), name(name) {}

    // acceptInstr takes in an instrument for the Musician to later play.
    //  "loses" any instrument that it used to have.
    void acceptInstr(Instrument* instPtr) { instr = instPtr; }

    // giveBackInstr: gives the instrument that the Musicial was holding "back"
    Instrument* giveBackInstr() { 
        Instrument* result(instr); 
        instr = nullptr;
        return result;
    }

    // testPlay: testing out my instrument
    void testPlay() const {
        if (instr) instr->makeSound(); 
        else cerr << name << " has no instr\n";
    }

    // play: play the instrument

    //   Not making it const so that Instrument::play method does not
    //   need to be const. Allows the instrument to be modifed in the
    //   process of being played.
    void play() {
        if (instr) instr->play();
        // Don't do anything if we don't have an instrument.
    }
private:
    Instrument* instr;
    string name;
};

class Orch{
public: 
    void addPlayer(Musician& newMusi){
        allMusi.push_back(&newMusi);
    }
    void play(){
        for(size_t i = 0; i < allMusi.size(); i++){
            allMusi[i]->play();
        }
        cout << endl;
    }

private: 
    vector<Musician*> allMusi;

};

int main() {

    //
    // PART ONE
    //
    cout << "P A R T  O N E\n";

    cout << "Define some instruments ---------------------------------------\n";
    Drum drum;
    Cello cello(673);
    Cymbal cymbal;
    Trombone tbone(4);
    Trumpet trpt(12) ;
    Violin violin(567) ;
  
    cout << "Define the MILL -----------------------------------------------\n";
    MILL mill;
    cout << "The MILL before adding instruments:\n" << mill << "\n\n";

    cout << "Put the instruments into the MILL -----------------------------\n";
    mill.receiveInstr(trpt);
    mill.receiveInstr(violin);
    mill.receiveInstr(tbone);
    mill.receiveInstr(drum);
    mill.receiveInstr(cello);
    mill.receiveInstr(cymbal);
    cout << "\nThe MILL after adding some instruments:\n" << mill << "\n\n";
  
    cout << "Daily test ----------------------------------------------------\n"
	 << "dailyTestPlay()" << endl;
    mill.dailyTestPlay();
    cout << endl;
  
    cout << "Define some Musicians------------------------------------------\n";
    Musician harpo("Harpo");
    Musician groucho("Groucho");
  	
    cout << "TESTING: groucho.acceptInstr(mill.loanOut());---------------\n";
    groucho.testPlay();	 // Groucho doesn't have an instrument yet.

    groucho.acceptInstr(mill.loanOut());
    groucho.testPlay();

    cout << "\ndailyTestPlay()" << endl;
    mill.dailyTestPlay();
    cout << endl;
  
    groucho.testPlay();	
    mill.receiveInstr(*groucho.giveBackInstr());
    harpo.acceptInstr(mill.loanOut());
    groucho.acceptInstr(mill.loanOut());
    groucho.testPlay();
    harpo.testPlay();

    cout << "\ndailyTestPlay()" << endl;
    mill.dailyTestPlay();

    cout << "\nThe MILL after giving out some instruments:\n";
    cout << mill << "\n\n";

    cout << "TESTING: mill.receiveInstr(*groucho.giveBackInstr()); ------\n";
    mill.receiveInstr(*groucho.giveBackInstr());

    cout << "TESTING: mill.receiveInstr(*harpo.giveBackInstr()); ------\n";
    mill.receiveInstr(*harpo.giveBackInstr());
    cout << endl;

    cout << "dailyTestPlay()" << endl;
       mill.dailyTestPlay();
  
    cout << "\nThe MILL at the end of Part One:\n";
    cout << mill << endl;

    //
    // PART TWO
    //
    
    cout << "\nP A R T  T W O\n";
    
    Musician bob("Bob");
    Musician sue("Sue");
    Musician mary("Mary");
    Musician ralph("Ralph");
    Musician jody("Judy");
    Musician morgan("Morgan");

    Orch orch;

    // THE SCENARIO

    //Bob joins the orchestra without an instrument.
    orch.addPlayer(bob);

    //The orchestra performs
    cout << "orch performs\n";
    orch.play();

    //Sue gets an instrument from the MIL2 and joins the orchestra.
    sue.acceptInstr(mill.loanOut());
    orch.addPlayer(sue);

    //Ralph gets an instrument from the MIL2.
    ralph.acceptInstr(mill.loanOut());

    //Mary gets an instrument from the MIL2 and joins the orchestra.
    mary.acceptInstr(mill.loanOut());
    orch.addPlayer(mary);

    //Ralph returns his instrument to the MIL2.
    mill.receiveInstr(*ralph.giveBackInstr());

    //Jody gets an instrument from the MIL2 and joins the orchestra.
    jody.acceptInstr(mill.loanOut());
    orch.addPlayer(jody);

    // morgan gets an instrument from the MIL2
    morgan.acceptInstr(mill.loanOut());

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();

    //Ralph joins the orchestra.
    orch.addPlayer(ralph);

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();
	
    // bob gets an instrument from the MIL2
    bob.acceptInstr(mill.loanOut());

    // ralph gets an instrument from the MIL2
    ralph.acceptInstr(mill.loanOut());

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();

    //Morgan joins the orchestra.
    orch.addPlayer(morgan);

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();

    cout << endl << mill << endl;

}

