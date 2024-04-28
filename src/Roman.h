#ifndef ROMAN_H_
#define ROMAN_H_

#include <iostream>

#include "Livre.h"

using namespace std;

class Roman : public Livre {

private:
    string genre;

public: 
            Roman();
            Roman   (string auteur, string titre, string editeur, string isbn, string etats, string genre)  ;// ok 
    string  getGenre()                                                                                                                                      ;// ok
    void    setGenre(string genre)                                                                                                                          ;// ok
    void    affiche ()                                                                                                                                      ;// ok
    static vector<Roman> initialiserVecteurRomans();// ok 
    void enregistrerVecteurRomans(vector<Roman> liste);// ok 
};

#endif /* ROMAN_H_ */