#ifndef PRET_H
#define PRET_H

#include "Livre.h"
#include"Adherent.h"

class Pret {

private: 
    Livre     livre;
    Adherent    adherent;
    Pret*  suivant;

public: 
            Pret       (Livre livre, Adherent adherent);
            Pret       (Livre livre, Adherent adherent, Pret* next);
    Livre   getLivre    ();
    Adherent getAdherent();
    Pret*  getSuivant  ();
    void    setLivre    (Livre livre);
    void setAdherent    (Adherent adherent);
    void    setSuivant  (Pret* next);
};

#endif /* PRET_H */