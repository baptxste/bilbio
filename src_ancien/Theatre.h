#ifndef THEATRE_H_
#define THEATRE_H_

#include <iostream>

#include "Livre.h"

using namespace std;

class Theatre : public Livre {

private:
    string siecle;

public: 
            Theatre   (int code,string auteur, string titre, string editeur, string isbn, string public_vise, string etats, string siecle)  ;
    string  getSiecle()                                                                                                          ;
    void    setSiecle(string siecle)                                                                                              ;
    void    affiche ()                                                                                                          ;
};

#endif /* ROMAN_H_ */