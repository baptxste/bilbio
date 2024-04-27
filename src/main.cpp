#include"Bibliotheque.h"
#include"Livre.h"
#include<iostream>
#include<string>
#include<fstream>
#include<vector>

using namespace std;


// faire un vecteur avec la liste des bibliotheques
// faire un vecteur avec la liste des adhérents


// Pour la gestion des emprunts etc ... 
// rajouter deux vecteurs à chaque bibliothèques 
// un pour les livres qui sont prétés ( à un adhérent ou à une bibliotèque)
// un pour les livres qui sont empruntés 
// et un vecteur qui est mis à jour à chaque fois qui contient la liste de 
// livre de base - la liste des livres prétés + la liste des livres empruntés.

// si on fait les choses comme ca, la fonction rendre un livre reviendra presque 
// juste à emprunter le livre à la bibliotheque a qui on l'a preté

int main (){
    Livre livres;
    vector<Livre> listelivres = livres.initialiserVecteurLivres();


    for (size_t i=0; i < listelivres.size();++i) {
        listelivres[i].affiche();
    }
    std::cout << std::endl;

    return 0;
}