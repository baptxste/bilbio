#include "ListePretBib.h"
#include "Livre.h"

ListePretBib::ListePretBib(){
    head = nullptr;
}

ListePretBib::ListePretBib(const ListePretBib& liste_pret_bib){
    head = liste_pret_bib.head;
}

ListePretBib::~ListePretBib() {
    PretBib* current = head;

    while( current != nullptr ) {
        PretBib* step = current;
        current = current->getSuivant();
        delete step;
    }
}

PretBib* ListePretBib::getHead(){
    return head;
}


void ListePretBib::setHead(PretBib* newhead) {
    head = newhead;
}

void ListePretBib::ajoute(Livre l, Bibliotheque b) {

    PretBib* nouveauPret = new PretBib(l, b);     // on peut le construire comme ceci comme on le delete dans le destructeur

    if( head == nullptr ) {
        nouveauPret->setSuivant(head);
        head = nouveauPret;
    }

    else {
        PretBib* current = head;

        while ( current->getSuivant() != nullptr ) {
            current = current->getSuivant();
        }
        // nouveauPret->setSuivant(current->getSuivant());
        current->setSuivant(nouveauPret);
    }
}

void ListePretBib::enleve(Livre livre_a_supprimer, Bibliotheque bib_a_supprimer ) {
    if ( (livre_a_supprimer.getIsbn() == "") || (head == nullptr) ) {
        return;
    }

    if ( livre_a_supprimer.getIsbn() == head->getLivre().getIsbn() && bib_a_supprimer.getNom() == head->getBibliotheque().getNom()) {
        PretBib* temporaire = head;
        head = head->getSuivant();
        delete temporaire;
    } 
    else {
        PretBib* precedent = head;
        while ( ((precedent != nullptr) && (precedent->getSuivant()->getLivre().getIsbn() != livre_a_supprimer.getIsbn())) && (precedent->getSuivant()->getBibliotheque().getNom() != bib_a_supprimer.getNom()) ){
            precedent = precedent->getSuivant();
        }

        if (precedent == nullptr) {
            return;
        }
        PretBib* temporaire = precedent->getSuivant();
        precedent->setSuivant(temporaire->getSuivant());
        delete temporaire;
    }
    // delete livre_a_supprimer; Cette ligne la je ne suis pas sur et elle me fait peur
}

void ListePretBib::affiche() {
    
    PretBib* current = head;

    if ( current == nullptr ) {
        printf("\nVotre liste_pret_bib est vide\n");
    }

    else {
        while ( current->getSuivant() != nullptr ) {
            current->getLivre().affiche();
            current->getBibliotheque().affiche();
            current = current->getSuivant();
        }

        current->getLivre().affiche();
        current->getBibliotheque().affiche();
    }

}