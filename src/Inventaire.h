#ifndef INVENTAIRE_H
#define INVENTAIRE_H

#include "noeud.h"
#include "Livre.h"

class Inventaire {

private:
    Noeud* head;

public:
            Inventaire  ()                              ;
            Inventaire  (const Inventaire& inventaire)  ;
            ~Inventaire ()                              ;
    Noeud*  getHead     ()                              ;
    void    setHead     (Noeud* newHead)                ;
    void    ajoute      (Livre l)                       ;
    void    enleve      (Livre livre_a_supprimer)      ;
    void    affiche     ()                              ;
};

#endif /* INVENTAIRE_H */