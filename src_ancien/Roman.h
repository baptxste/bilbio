#ifndef ROMAN_H_
#define ROMAN_H_

#include <iostream>

#include "Livre.h"

using namespace std;

class Roman : public Livre {

private:
    string genre;

public: 
            Roman   (int code, string auteur, string titre, string editeur, string isbn, string public_vise, string etats, string genre)  ;
    string  getGenre()                                                                                                                                      ;
    void    setGenre(string genre)                                                                                                                          ;
    void    affiche ()                                                                                                                                      ;
};

#endif /* ROMAN_H_ */