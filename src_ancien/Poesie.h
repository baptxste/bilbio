#ifndef POESIE_H
#define POESIE_H

#include <iostream>

#include "Livre.h"

using namespace std;

class Poesie : public Livre {

private:
    string style;

public:
            Poesie  (int code, string auteur, string titre, string editeur, string isbn, string public_vise, string etats, string style)  ;
    string  getStyle()                                                                                                          ;
    void    setStyle(string style)                                                                                                          ;
    void    affiche ()                                                                                                          ;
};

#endif /* POESIE_H */