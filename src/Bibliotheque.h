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
    Bibliotheque();
    Bibliotheque(string nom, string adresse);
    string getNom();
    string getAdresse();
    Inventaire getInventaire();
    void setNom(string nom);
    void setAdresse(string adresse);   
    void affiche();             
    friend ostream& operator<<(ostream& out, const Bibliotheque& b);
};

#endif /* BIBLIOTHEQUE_H */