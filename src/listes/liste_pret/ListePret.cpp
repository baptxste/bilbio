#include "ListePret.h"
#include "Livre.h"

ListePret::ListePret(){
    head = nullptr;
}

ListePret::ListePret(const ListePret& liste_pret){
    head = liste_pret.head;
}

ListePret::~ListePret() {
    Pret* current = head;

    while( current != nullptr ) {
        Pret* step = current;
        current = current->getSuivant();
        delete step;
    }
}

Pret* ListePret::getHead(){
    return head;
}


void ListePret::setHead(Pret* newhead) {
    head = newhead;
}

void ListePret::ajoute(Livre l, Adherent a) {

    Pret* nouveauPret = new Pret(l, a);     // on peut le construire comme ceci comme on le delete dans le destructeur

    if( head == nullptr ) {
        nouveauPret->setSuivant(head);
        head = nouveauPret;
    }

    else {
        Pret* current = head;

        while ( current->getSuivant() != nullptr ) {
            current = current->getSuivant();
        }
        // nouveauPret->setSuivant(current->getSuivant());
        current->setSuivant(nouveauPret);
    }
}

void ListePret::enleve(Livre livre_a_supprimer, Adherent adh_a_supprimer ) {
    if ( (livre_a_supprimer.getIsbn() == "") || (head == nullptr) ) {
        return;
    }

    if ( livre_a_supprimer.getIsbn() == head->getLivre().getIsbn() && adh_a_supprimer == head->getAdherent()) {
        Pret* temporaire = head;
        head = head->getSuivant();
        delete temporaire;
    } 
    else {
        Pret* precedent = head;
        while ( ((precedent != nullptr) && (precedent->getSuivant()->getLivre().getIsbn() != livre_a_supprimer.getIsbn())) && (precedent->getSuivant()->getAdherent() != adh_a_supprimer) ){
            precedent = precedent->getSuivant();
        }

        if (precedent == nullptr) {
            return;
        }
        Pret* temporaire = precedent->getSuivant();
        precedent->setSuivant(temporaire->getSuivant());
        delete temporaire;
    }
    // delete livre_a_supprimer; Cette ligne la je ne suis pas sur et elle me fait peur
}

void ListePret::affiche() {
    
    Pret* current = head;

    if ( current == nullptr ) {
        printf("\nVotre liste_pret est vide\n");
    }

    else {
        while ( current->getSuivant() != nullptr ) {
            current->getLivre().affiche();
            current->getAdherent().affiche();
            current = current->getSuivant();
        }

        current->getLivre().affiche();
        current->getAdherent().affiche()
    }

}