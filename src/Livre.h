#ifndef LIVRE_H
#define LIVRE_H

#include <iostream>

using namespace std;

class Livre {

protected:
    int     code        ;
    string  auteur      ;
    string  titre       ;
    string  editeur     ;
    string  isbn        ;
    string  etats       ;/* libre, emprunté, prêté*/
    string  categorie   ;
    bool    etatExiste (string etatPropose) ;

    /* au vu des autres fonctions demandées il faut peut être faire un argument avec sa biliotheque d'origine*/

public:

    vector<Livre> initialiserVecteurLivres();
            Livre       ()                                                                                          ;
            Livre       (int code, string auteur, string titre, string editeur, string isbn, string etats);
    void    affiche     ()                                                                                          ;
    int     getCode     ()                                                                                          ;
    string  getAuteur   ()                                                                                          ;
    string  getTitre    ()                                                                                          ;
    string  getEditeur  ()                                                                                          ;
    string  getIsbn     ()                                                                                          ;
    string  getEtats    ()                                                                                          ;
    string  getCategorie()                                                                                          ;
    void    setCode     (int code)                                                                                  ;
    void    setAuteur   (string auteur)                                                                             ;
    void    setTitre    (string titre)                                                                              ; 
    void    setEditeur  (string editeur)                                                                            ;
    void    setIsbn     (string isbn)                                                                               ;                                                                       ;
    void    setEtats    (string etats)                                                                              ;
    void    setCategorie(string categorie)                                                                          ;  
};

#endif /* LIVRE_H */