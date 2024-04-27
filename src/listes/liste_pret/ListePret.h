#ifndef LISTEPRET_H
#define LISTEPRET_H

#include "Pret.h"
#include "Livre.h"
#include"Adherent.h"

class ListePret {

private:
    Pret* head;

public:
            ListePret  ()                              ;
            ListePret  (const listePret& liste_pret)  ;
            ~ListePret ()                              ;
    Pret*  getHead     ()                              ;
    void    setHead     (Pret* newHead)                ;
    void    ajoute      (Livre l,Adherent a)                       ;
    void    enleve      (Livre livre_a_supprimer, Adherent adh_a_supprimer)      ;
    void    affiche     ()                              ;
};

#endif /* INVENTAIRE_H */