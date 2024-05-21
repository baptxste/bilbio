#include "Inventaire.h"
#include "Livre.h"

Inventaire::Inventaire(){
    head = nullptr;
}

Inventaire::Inventaire(const Inventaire& inventaire){
    head = inventaire.head;
}

Inventaire::~Inventaire() {
    Noeud* current = head;

    while( current != nullptr ) {
        Noeud* step = current;
        current = current->getSuivant();
        step->~Noeud();
    }
}

Noeud* Inventaire::getHead(){
    return head;
}


void Inventaire::setHead(Noeud* newhead) {
    head = newhead;
}

void Inventaire::ajoute(Livre l) {

    Noeud* nouveauNoeud = new Noeud(l);     // on peut le construire comme ceci comme on le delete dans le destructeur

    if( head == nullptr ) {
        nouveauNoeud->setSuivant(head);
        head = nouveauNoeud;
    }

    else {
        Noeud* current = head;

        while ( current->getSuivant() != nullptr ) {
            current = current->getSuivant();
        }
        // nouveauNoeud->setSuivant(current->getSuivant());
        current->setSuivant(nouveauNoeud);
    }
}

void Inventaire::enleve(int code){
    Noeud* current = head;
    bool trouve = false;
    // le livre à enlever est en tête
    if(head->getLivre().getCode()==code){
        Noeud* suivant = current->getSuivant();
        setHead(suivant);
        trouve = true;
        current->~Noeud();
        return;
    }
    // le livre à enlever est au milieu
    while(current->getSuivant()->getSuivant()!= nullptr){
        if( current->getSuivant()->getLivre().getCode()==code){
            trouve = true;
            Noeud* suivantagarder = current->getSuivant()->getSuivant();
            current->getSuivant()->~Noeud();
            current->setSuivant(suivantagarder);
            return;
        }
        current = current->getSuivant();
    }
    // le livre est a la fin
    if( current->getSuivant()->getSuivant()==nullptr){
        if(current->getSuivant()->getLivre().getCode()==code){
            current->getSuivant()->~Noeud();
            current->setSuivant(nullptr);
            trouve = true;
            return;
        }  
    }
    if( trouve == false){
        cout <<" Problème le livre n'a pas été trouvé."<<endl;
    }
}

void Inventaire::affiche() {
    
    Noeud* current = head;

    if ( current == nullptr ) {
        printf("\nVotre inventaire est vide\n");
    }

    else {
        while ( current->getSuivant() != nullptr ) {
            current->getAdresseLivre()->affiche();
            current = current->getSuivant();
        }

        current->getAdresseLivre()->affiche();
    }

}

Livre* Inventaire::getLivre(string isbn){
    Noeud* current = head;
    while( current != nullptr){
        if( current->getAdresseLivre()->getIsbn() == isbn){
            return current->getAdresseLivre();
        }
        else{
            current =current->getSuivant();
        }
    }
    cout<< "Attention le livre associé à l'isbn " <<isbn <<"n'existe pas, renvoie un livre vide"<< endl; 
    return new Livre();
}