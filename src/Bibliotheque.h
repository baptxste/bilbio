#ifndef BIBLIOTHEQUE_H
#define BIBLIOTHEQUE_H

#include <iostream>
#include <vector>
#include <tuple>
#include "Livre.h"
#include "Inventaire.h"

using namespace std;
class Adherent;
class Bibliotheque
{

private:
    string nom;
    string adresse;
    Inventaire inventaire;
    vector<tuple<int, int>> listepretAdherent; // ( code du livre, id de l'adhérent)
    bool categorieExiste(string categorie);

public:
    vector<Bibliotheque> listeBibliotheque;
    Bibliotheque();// ok 
    Bibliotheque(string nom, string adresse); // ok 
    ~Bibliotheque();
    string getNom();// ok 
    string getAdresse(); // ok 
    Inventaire getInventaire();// ok 
    Livre getLivre(int code); // ok
    vector<tuple<int, int>> getPretAdherent(); 
    void setNom(string nom);// ok 
    void setAdresse(string adresse);// ok 
    void affiche();// ok 
    void ajouterPret(int code, int id);
    void affichePretAdherent();
    friend ostream& operator<<(ostream& out, Bibliotheque& b);// ok 
    void setInventaire(vector<string> isbn, Inventaire* tous_leslivres); // ok
    static vector<Bibliotheque> initialiserVecteurBibliotheque(Inventaire* tous_les_livres);// ok
    static void enregistrerVecteurBibliotheque(vector<Bibliotheque> liste); //ok
};

#endif /* BIBLIOTHEQUE_H */