#include "PretBib.h"
#include "Livre.h"
#include"Bibliotheque.h"

PretBib::PretBib(Livre l, Bibliotheque b) {
    livre = l;
    bibliotheque = b;
    suivant = nullptr;
}

PretBib::PretBib(Livre l, Bibliotheque b, PretBib* next) {
    livre = l;
    bibliotheque = b;
    suivant = next;
}

Livre PretBib::getLivre() {
    return livre;
}

PretBib* PretBib::getSuivant() {
    return suivant;
}
Bibliotheque PretBib::getBibliotheque(){
    return bibliotheque;
} 

void PretBib::setLivre(Livre l) {
    livre = l;
}
void PretBib::setBibliotheque(Bibliotheque b){
    bibliotheque = b;
}
void PretBib::setSuivant(PretBib* next) {
    suivant = next;
}