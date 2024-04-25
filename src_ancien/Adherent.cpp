#include "Adherent.h"
#include "Bibliotheque.h"
#include<iostream>
#include<string>

int Adherent::nb_adherent = 0;

Adherent::Adherent(string nom, string prenom, string adresse, int nb_emprunt_max, Bibliotheque bibliotheque){
    this->nom = nom;
    this->prenom = prenom;
    this->id_adherent = nb_adherent;
    this->nb_emprunt_max = nb_emprunt_max;
    this->bibliotheque = bibliotheque;
    nb_emprunt_en_cours = 0;
    nb_adherent++;
}

Adherent::~Adherent(){
    nb_adherent--;
}

string Adherent::getNom(){
    return this->nom;
}

string Adherent::getprenom(){
    return this->prenom;
}

string Adherent::getAdresse(){
    return this->adresse;
}

int Adherent:: getId(){
    return this->id_adherent;
}

int Adherent::getNbEmpruntMax(){
    return this->nb_emprunt_max;
}

Bibliotheque Adherent::getBibliotheque(){
    return this->bibliotheque;
}

void Adherent::setNom(string nom){
    this->nom = nom;
}

void Adherent::setPrenom(string prenom){
    this->prenom = prenom;
}

void Adherent::setAdresse(string adresse){
    this->adresse = adresse;
}

void Adherent::setId(int id_adherent){
    this->id_adherent = id_adherent;
}

void Adherent::setNbEmpruntMax(int nb_emprunt_max){
    this->nb_emprunt_max = nb_emprunt_max;
}

void Adherent::setBibliotheque(Bibliotheque biblio){
    this->bibliotheque = biblio;
}

ostream& operator<<(ostream& out, const Adherent& a) {
    out<<"nom : ";
    out<<a.nom<< endl;
    out<<"prenom : ";
    out<<a.prenom<< endl;
    out<<"adresse : ";
    out<<a.adresse<< endl;
    out<<"id adhérent : ";
    out<<a.id_adherent<< endl;
    out<<"nombre d'emprunt max : ";
    out<<a.nb_emprunt_max<< endl;
    return out;
}

bool Adherent::peutEmpruter(){
    if (this->nb_emprunt_en_cours < nb_emprunt_max){
        return true;
    }
    else{
        cout<<"l'adhérent a emprunté trop de livre";
        return false;
    }
}

void Adherent::emprunte(int code){

    if (peutEmpruter()){
        cout<<"check1";
        Inventaire inventaire=this->bibliotheque.getLivres();
        inventaire.affiche();
        Livre livre;
        cout<<"check2";
        // récupérer objet Livre à emprunter à partir de son code
        Noeud* current = inventaire.getHead();

            while( current != nullptr){
                Livre current_book = current->getLivre();

                if ( current_book.getCode()==code ){
                    livre = current->getLivre();
                }
            }

        cout<<"check3";
        if (bibliotheque.estlibre(livre)){
            nb_emprunt_en_cours ++;
            bibliotheque.removeLivre(livre);
            livre.setEtats("emprunté");
            cout<<"check4";		
            liste_emprunt_en_cours.ajoute(livre);
        }
    }

}

void Adherent::afficheEmprunt(){
    liste_emprunt_en_cours.affiche();
}
void Adherent::rendlivre(Livre livre){
    Inventaire inv = this->liste_emprunt_en_cours;
     Noeud* current = inv.getHead();

            while( current != nullptr){
                Livre current_book = current->getLivre();

                if ( current_book.getCode()==livre.getCode() ){
                    inv.enleve(current_book);
                }
            }
        livre.setEtats("libre");
}