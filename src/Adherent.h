#ifndef ADHERENT_H
#define ADHERENT_H

#include <iostream>
#include<vector>

#include "Bibliotheque.h"
#include "Inventaire.h"


using namespace std;

class Adherent {
private:
    static int      nb_adherent    ;
    string          nom             ;
    string          prenom          ;
    string          adresse         ;
    int             id_adherent     ;
    int             nb_emprunt_max  ;
    Bibliotheque    bibliotheque    ;
    int             nb_emprunt_en_cours;
    bool            peutEmpruter();
    Inventaire      liste_emprunt_en_cours; // liste des codes des livres empruntés dans sa bilbiothèque

public:
                    Adherent();
                    Adherent(string nom, string prenom, string adresse, int nb_emprunt_max, Bibliotheque bibliotheque)  ; // ok
                    Adherent(int id_adherent, string nom, string prenom, string adresse, int nb_emprunt_max, Bibliotheque bibliotheque, Inventaire liste_emprunt); // ok
                    ~Adherent();
    string          getNom()                                                                                                            ;
    string          getPrenom()                                                                                                         ;
    string          getAdresse()                                                                                                        ;
    int             getId()                                                                                                             ;
    int             getNbEmpruntMax()                                                                                                   ;
    Bibliotheque    getBibliotheque()                                                                                                   ;
    Inventaire      getEmprunts();
    void            setNom(string nom)                                                                                                  ;
    void            setPrenom(string prenom)                                                                                            ;
    void            setAdresse(string adresse)                                                                                          ;
    void            setId(int id_adherent)                                                                                              ;
    void            setNbEmpruntMax(int nb_emprunt_max)                                                                                 ;
    void            setBibliotheque(Bibliotheque bibliotheque)                                                                          ;
    void            emprunte(int code);
    friend ostream& operator<<(ostream& out, const Adherent& a)                                                                         ; // ok
    void            affiche();
    static vector<Adherent> initVecteurAdherent(vector<Bibliotheque> liste_biblio); // semble marcher à tester en profondeur
    static void enregistrerVecteurAdherent(vector<Adherent> listeadh );
};

#endif /* ADHERENT_H */