#ifndef NOEUD_H
#define NOEUD_H

#include "Livre.h"

class Noeud {

private: 
    Livre     livre;
    Noeud*  suivant;

public: 
            Noeud       (Livre livre);// ok 
            Noeud       (Livre livre, Noeud* next);// ok
            ~Noeud();
    Livre*   getAdresseLivre    ();// ok 
    Livre    getLivre();
    Noeud*  getSuivant  ();// ok
    void    setLivre    (Livre livre);// ok 
    void    setSuivant  (Noeud* next);// ok
};

#endif /* NOEUD_H */