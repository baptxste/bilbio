#include "Pret.h"
#include "Livre.h"
#include"Adherent.h"

Pret::Pret(Livre l, Adherent a) {
    livre = l;
    adherent = a;
    suivant = nullptr;
}

Pret::Pret(Livre l, Adherent a, Pret* next) {
    livre = l;
    adherent = a;
    suivant = next;
}

Livre Pret::getLivre() {
    return livre;
}

Pret* Pret::getSuivant() {
    return suivant;
}
Adherent Pret::getAdherent(){
    return adherent;
} 

void Pret::setLivre(Livre l) {
    livre = l;
}
void Pret::setAdherent(Adherent a){
    adherent = a;
}
void Pret::setSuivant(Pret* next) {
    suivant = next;
}