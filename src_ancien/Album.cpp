#include"Album.h"

#include<iostream>
#include<string>

using namespace std;

Album::Album(int code, string auteur, string titre, string editeur, string isbn, string public_vise, string etats, string illustration) : Livre(code, auteur, titre, editeur, isbn, public_vise, etats){
    this->illustration = illustration;
    setCategorie("album");
} 
string Album::getIllustration(){
    return this->illustration;
}                                                     
void    Album::setIllustration(string illustration){
    this->illustration = illustration;
}                                          
void Album::affiche (){
    Livre::affiche();
    cout<<"illustration : "<< illustration<< endl;
}