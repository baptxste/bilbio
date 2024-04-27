#ifndef LISTEPRETBIB_H
#define LISTEPRETBIB_H

#include "PretBib.h"
#include "Livre.h"
#include"Bibliotheque.h"

class ListePretBib {

private:
    PretBib* head;

public:
            ListePretBib  ()                              ;
            ListePretBib  (const listePreBibt& liste_pret_bib)  ;
            ~ListePretBib ()                              ;
    PretBib*  getHead     ()                              ;
    void    setHead     (PretBib* newHead)                ;
    void    ajoute      (Livre l,Bibliotheque b)                       ;
    void    enleve      (Livre livre_a_supprimer, Bibliotheque bib_a_supprimer)      ;
    void    affiche     ()                              ;
};

#endif /* INVENTAIRE_H */