#include"Poesie.h"
#include<iostream>
#include<string>

using namespace std;

Poesie::Poesie(int code, string auteur, string titre, string editeur, string isbn, string public_vise, string etats, string style) : Livre(code, auteur, titre, editeur, isbn, public_vise, etats){
    this->style = style;
    setCategorie("poesie");
}
string  Poesie::getStyle(){
    return this->style;
}                                                                                                          
void    Poesie::setStyle(string style){
    this->style = style;
}                                                                                                     
void    Poesie::affiche (){
    Livre::affiche();
    cout<<"style : "<< style<< endl;
}