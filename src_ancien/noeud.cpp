#include "noeud.h"
#include "Livre.h"

Noeud::Noeud(Livre l) {
    livre = l;
    suivant = nullptr;
}

Noeud::Noeud(Livre l, Noeud* next) {
    livre = l;
    suivant = next;
}

Livre Noeud::getLivre() {
    return livre;
}

Noeud* Noeud::getSuivant() {
    return suivant;
}

void Noeud::setLivre(Livre l) {
    livre = l;
}

void Noeud::setSuivant(Noeud* next) {
    suivant = next;
}