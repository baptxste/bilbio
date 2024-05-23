#ifndef BD_H_
#define BD_H_

#include <iostream>

#include "Livre.h"

using namespace std;

class Bd : public Livre{

private:
    string dessinateur;

public: 
            Bd();
            Bd   (string auteur, string titre, string editeur, string isbn, string etats, string dessinateur)  ;// ok 
    void static creerBdgraphique();
    string  getDessinateur()                                                                                                                                      ;// ok
    void    setDessinateur(string dessinateur)                                                                                                                          ;// ok
    void    affiche ()                                                                                                                                      ;// ok
    static vector<Bd> initialiserVecteurBd();// ok 
    void enregistrerVecteurBd(vector<Bd> liste);// ok 
};

#endif /* BD_H_ */