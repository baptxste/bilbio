#ifndef PRETBIB_H
#define PRETBIB_H

#include "Livre.h"
#include"Bibliotheque.h"

class PretBib {

private: 
    Livre     livre;
    Bibliotheque    bibliotheque;
    PretBib*  suivant;

public: 
            PretBib       (Livre livre, Bibliotheque bibliotheque);
            PretBib       (Livre livre, Bibliotheque bibliotheque, PretBib* next);
    Livre   getLivre    ();
    Bibliotheque getBibliotheque();
    PretBib*  getSuivant  ();
    void    setLivre    (Livre livre);
    void setBibliotheque    (Bibliotheque bibliotheque);
    void    setSuivant  (PretBib* next);
};

#endif /* PRET_H */