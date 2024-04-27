#include"Bibliotheque.h"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

vector<Bibliotheque> listeBibliotheque;

bool Bibliotheque::categorieExiste(string cat){

    vector<string>categoriesExistantes;
    categoriesExistantes.push_back("album");
    categoriesExistantes.push_back("bande-dessinee");
    categoriesExistantes.push_back("roman");
    categoriesExistantes.push_back("poesie");
    categoriesExistantes.push_back("theatre");
    
    return find(categoriesExistantes.begin(), categoriesExistantes.end(), cat) != categoriesExistantes.end();
}

Bibliotheque::Bibliotheque(){
    nom = "Nom par defaut";
    adresse = "La ou elle est";
    inventaire = Inventaire();
    listeBibliotheque.push_back(*this);
}

Bibliotheque::Bibliotheque(string nom, string  adresse){
    this->nom = nom;
    this->adresse = adresse;
    inventaire = Inventaire();
    listeBibliotheque.push_back(*this);
}

string Bibliotheque::getNom(){
    return this->nom;
}

string Bibliotheque::getAdresse(){
    return this->adresse;
}

Inventaire Bibliotheque::getInventaire(){
    return this->inventaire;
}

void Bibliotheque::setNom(string nom){
    this->nom = nom;
}

void Bibliotheque::setAdresse(string adresse){
    this->adresse = adresse;
}
void Bibliotheque::affiche(){
    cout<<"nom : "<< nom << "adresse : " << adresse << endl;
    inventaire.affiche();
}

ostream& operator<<(ostream& out, Bibliotheque b){
    out << "nom : ";
    out << b.getNom() << endl; 
    out << "adresse : ";
    out << b.getAdresse() << endl;
    return out;
}
