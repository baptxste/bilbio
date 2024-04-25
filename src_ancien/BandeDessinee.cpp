#include"BandeDessinee.h"

#include<iostream>
#include<string>


BandeDessinee::BandeDessinee(int code, string auteur, string titre, string editeur, string isbn, string public_vise, string etats, string dessinateur) : Livre(code, auteur, titre, editeur, isbn, public_vise, etats){
    this->dessinateur = dessinateur;
    setCategorie("bande-dessinee");
}

string BandeDessinee::getDessinateur (){
     return this->dessinateur;
}

void BandeDessinee::setDessinateur (string dessinateur){
    this->dessinateur = dessinateur;
}

void BandeDessinee::affiche (){
    Livre::affiche(); 
    cout<<"dessinateur : "<< dessinateur <<endl;
}
