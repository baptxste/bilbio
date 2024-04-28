#include"Bibliotheque.h"
#include"Livre.h"
#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include"Roman.h"
#include"Inventaire.h"

#include"sstream"

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
    // Roman romans;
    vector<Roman> listeromans = Roman::initialiserVecteurRomans();
    for (size_t i=0; i < listeromans.size();++i) {
        listeromans[i].affiche();
    }

    Inventaire liste_tous_livres = Inventaire();

    for (size_t i=0; i < listeromans.size();++i) {
        liste_tous_livres.ajoute(listeromans[i]);
    }

    cout <<  endl;
    cout << "test biblio"<< endl;

    Bibliotheque b;
    // vector<Bibliotheque> listebiblios = b.initialiserVecteurBibliotheque(liste_tous_livres);
    vector<Bibliotheque> listebiblios = Bibliotheque::initialiserVecteurBibliotheque(liste_tous_livres);

    cout <<  endl;
    cout << "affichage de la liste biblio"<<endl;
    cout <<  endl;
    // for( int i=0; i<listebiblios.size();++i){
    //     cout << listebiblios[i].getNom() << endl;
    // }


    // stringstream liste("isbn1,isbn2");
    // string isbn;
    // while(getline(liste, isbn,',')){
    //     cout << isbn << endl;
    // }


    return 0;
}