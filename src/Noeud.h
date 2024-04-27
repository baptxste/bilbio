#ifndef NOEUD_H
#define NOEUD_H

#include "Livre.h"

class Noeud {

private: 
    Livre     livre;
    Noeud*  suivant;

public: 
            Noeud       (Livre livre);
            Noeud       (Livre livre, Noeud* next);
    Livre   getLivre    ();
    Noeud*  getSuivant  ();
    void    setLivre    (Livre livre);
    void    setSuivant  (Noeud* next);
};

#endif /* NOEUD_H */