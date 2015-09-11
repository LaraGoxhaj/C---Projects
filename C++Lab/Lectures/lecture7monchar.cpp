#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class Véhicule {
protected:
    string immatriculation;
    int année;

    string stringification(int no) const {
        ostringstream aux;
        aux << no;
        return aux.str();
    }
public:
    Véhicule(const string &pImm, const int pAnnée): immatriculation(pImm), année(pAnnée) { cerr << "...building a vehicle..." << endl;}

    ~Véhicule() { cout << "...destroying a vehicle..." << endl;}

    const string retDesc() const {
        return immatriculation + " - année " + stringification(année);
    }

    const string &retImmatriculation() const {return immatriculation;}
    const int retAnnée() const {return année;}
};




class Automobile : public Véhicule { // matryoshka : make Automobile inherit from Véhicule
    string modèle;
public:
    Automobile(const string &pImm, const int pAnnée, const string &pModèle) : Véhicule(pImm, pAnnée), modèle(pModèle) {cout << "...building a car..." << endl;}

    ~Automobile() { cout << "...destroying a car..." << endl;}

    //override example!
    const string retDesc() const // Overriding this member function
    {
        return modèle + " année " + stringification(année) + " " +  + ": " + immatriculation;
    }

    const string &retModèle() {return modèle;}
};



int main() {
    Automobile monChar("SEL-6519", 2003, "Subaru");
    cout << monChar.retDesc() << endl;

    Véhicule *vPtr = &monChar;
    cout << vPtr->retDesc() << endl; // why doesn't this print the style?
}

