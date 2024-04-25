#include"Livre.h"
#include<iostream>
#include<string>
#include <vector>
#include <algorithm>

using namespace std;


Livre::Livre(){
}

Livre::Livre(int code, string auteur, string titre, string editeur, string isbn, string public_vise, string etats){
    this->code = code;
    this->auteur = auteur;
    this->titre = titre;
    this->editeur = editeur;
    this->isbn = isbn;
    this->public_vise = public_vise;
    this->etats = etats;
    this->categorie = "";
    this->nomBiblioActuel = "";
    this->nomBiblioOrigine = "";

}

void Livre::affiche(){
    cout<< "\ncode : "<< code <<endl;
    cout<< "auteur : "<< auteur <<endl;
    cout<< "titre : "<< titre <<endl;
    cout<< "editeur : "<< editeur <<endl;
    cout<< "isbn : "<< isbn <<endl;
    cout<< "public visé : "<< public_vise <<endl;
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
 string Livre::getPublic(){
    return this->public_vise;
 }
string Livre::getEtats(){
    return this->etats;
}
string Livre::getCategorie(){
    return categorie;
}

string Livre::getNomBiblioActuel (){
    return nomBiblioActuel;
}

string Livre::getNomBiblioOrigine (){
    return nomBiblioOrigine;
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
void Livre::setPublic(string public_vise){
    this->public_vise = public_vise;
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