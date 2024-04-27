#include"Livre.h"
#include<iostream>
#include<string>
#include <vector>
#include <algorithm>
#include<fstream>
#include<sstream>

using namespace std;



vector<Livre> Livre::initialiserVecteurLivres(){
    vector<Livre> livres;
    ifstream fichier("bd/liste_livres");
    if (fichier.is_open()) {
        string ligne;
        while (getline(fichier, ligne)) {
            stringstream ss(ligne);
            string code, auteur, titre, editeur, isbn, etats;
            getline(ss, code, ';');
            getline(ss, auteur, ';');
            getline(ss, titre, ';');
            getline(ss, editeur, ';');
            getline(ss, isbn, ';');
            getline(ss, etats, ';');
            livres.push_back(Livre(stoi(code), auteur, titre, editeur, isbn, etats));
        }
        fichier.close();
    } else {
        std::cerr << "Erreur : Impossible d'ouvrir le fichier." << std::endl;
    }
    return livres;
}

Livre::Livre(){
}

Livre::Livre(int code, string auteur, string titre, string editeur, string isbn, string etats){
    this->code = code;
    this->auteur = auteur;
    this->titre = titre;
    this->editeur = editeur;
    this->isbn = isbn;
    this->etats = etats;
    this->categorie = "";
}

void Livre::affiche(){
    cout<< "\ncode : "<< code <<endl;
    cout<< "auteur : "<< auteur <<endl;
    cout<< "titre : "<< titre <<endl;
    cout<< "editeur : "<< editeur <<endl;
    cout<< "isbn : "<< isbn <<endl;
    cout<< "etats : "<< etats <<endl;
}

int Livre::getCode(){
    return code;
}

string Livre::getAuteur(){
    return this->auteur;
}

string Livre::getTitre(){
    return this->titre;
}
string Livre::getEditeur(){
    return this->editeur;
}

string Livre::getIsbn(){
    return this->isbn;
}
string Livre::getEtats(){
    return this->etats;
}
string Livre::getCategorie(){
    return categorie;
}

void Livre::setCode(int c){
    code = c;
}

void Livre::setAuteur(string auteur){
    this->auteur = auteur;
}                                                                            
void Livre::setTitre(string titre){
    this->titre = titre;
}                                                                            
void Livre::setEditeur(string editeur){
    this->editeur = editeur;
}    
void Livre::setIsbn(string isbn){
    this->isbn = isbn;
}                                  
void Livre::setEtats(string etats){
    this->etats = etats;
}         
void Livre::setCategorie(string categorie){
    this->categorie = categorie;
}

bool Livre::etatExiste(string etatPropose){
    
    vector<string>etatsExistants;
    etatsExistants.push_back("libre");
    etatsExistants.push_back("emprunte");
    etatsExistants.push_back("prete");

    return find(etatsExistants.begin(),etatsExistants.end(), etatPropose) != etatsExistants.end();
}