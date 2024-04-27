#include "PretBib.h"
#include "Livre.h"
#include"Bibliotheque.h"

Pret::Pret(Livre l, Bibliotheque a) {
    livre = l;
    bibliotheque = b;
    suivant = nullptr;
}

Pret::Pret(Livre l, Bibliotheque b, Pret* next) {
    livre = l;
    bibliotheque = b;
    suivant = next;
}

Livre Pret::getLivre() {
    return livre;
}

Pret* Pret::getSuivant() {
    return suivant;
}
Bibliotheque Pret::getBibliotheque(){
    return bibliotheque;
} 

void Pret::setLivre(Livre l) {
    livre = l;
}
void Pret::setBibliotheque(Bibliotheque a){
    bibliotheque = b;
}
void Pret::setSuivant(Noeud* next) {
    suivant = next;
}