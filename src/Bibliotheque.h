#ifndef BIBLIOTHEQUE_H
#define BIBLIOTHEQUE_H

#include <iostream>
#include <vector>

#include "Livre.h"
#include "Inventaire.h"

using namespace std;

class Bibliotheque
{

private:
    string nom;
    string adresse;
    Inventaire inventaire;
    bool categorieExiste(string categorie);

public:
    vector<Bibliotheque> listeBibliotheque;
    Bibliotheque();// ok 
    Bibliotheque(string nom, string adresse); // ok 
    string getNom();// ok 
    string getAdresse(); // ok 
    Inventaire getInventaire();// ok 
    void setInventaire(vector<string> vecisbn);// ok 
    void setNom(string nom);// ok 
    void setAdresse(string adresse);// ok 
    void affiche();// ok 
    friend ostream& operator<<(ostream& out, const Bibliotheque& b);// ok 
    void setInventaire(vector<string> isbn, Inventaire* tous_leslivres); // ok
    static vector<Bibliotheque> initialiserVecteurBibliotheque(Inventaire* tous_les_livres);// ok
    void enregistrerVecteurBibliotheque(vector<Bibliotheque> liste); // a faire
};

#endif /* BIBLIOTHEQUE_H */