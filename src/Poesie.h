#ifndef POESIE_H_
#define POESIE_H_

#include <iostream>

#include "Livre.h"

using namespace std;

class Poesie : public Livre {

private:
    string vers;

public: 
            Poesie();
            Poesie   (string auteur, string titre, string editeur, string isbn, string etats, string vers)  ;// ok 
    void static creerPoesiegraphique();
    string  getVers()                                                                                                                                      ;// ok
    void    setVers(string vers)                                                                                                                          ;// ok
    void    affiche ()                                                                                                                                      ;// ok
    static vector<Poesie> initialiserVecteurPoesie();// ok 
    void enregistrerVecteurPoesie(vector<Poesie> liste);// ok 
};

#endif /* POESIE_H_ */