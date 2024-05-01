#ifndef INVENTAIRE_H
#define INVENTAIRE_H

#include "Noeud.h"
#include "Livre.h"

class Inventaire {

private:
    Noeud* head;

public:
            Inventaire  ()                              ;// ok
            Inventaire  (const Inventaire& inventaire)  ;// ok 
            ~Inventaire ()                              ;// ok
    Noeud*  getHead     ()                              ;// ok 
    void    setHead     (Noeud* newHead)                ;// ok 
    void    ajoute      (Livre l)                       ; // ok 
    void    enleve      (Livre livre_a_supprimer)      ; // ok
    void    affiche     ()                              ; // ok
    Livre*   getLivre( string isbn ); // ok
};

#endif /* INVENTAIRE_H */