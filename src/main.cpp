#include"Bibliotheque.h"
#include"Livre.h"
#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include"Roman.h"
#include"Inventaire.h"
#include"Adherent.h"
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

Inventaire initLivres(){
    Inventaire liste_tous_livres = Inventaire();

    vector<Roman> listeromans = Roman::initialiserVecteurRomans();
    for (size_t i=0; i < listeromans.size();++i) {
        liste_tous_livres.ajoute(listeromans[i]);
    }
    // repeter ces étapes pour les autres catégories
    return liste_tous_livres;
}
//vector<Bibliotheque> listebiblios = Bibliotheque::initialiserVecteurBibliotheque(&liste_tous_livres);
void menu(){
    bool continuer = true;
    int choix = 0;
    do{
        cout << "===== Menu =====" << endl;
        cout << "1) " << endl;
        cout << "2) " << endl;
        cout << "3) " << endl;

        cout << "Votre choix : ";
        cin >> choix;
        switch(choix){
            case 1:
                //afficherBiblios();
                break;
            case 2:
                //tests();
                break;
            case 3:
                //fixture();
                break;
            default:
                cout << endl <<  "#### Choix invalide." << endl;
        }
        cout << endl;
    }while(continuer);

}
int main (){
    Inventaire liste_tous_livre =initLivres();
    Bibliotheque b = Bibliotheque();
    b.setAdresse("adrrdess");
    b.setNom("noma");
    cout <<b ;

    Adherent a1 = Adherent(24, "jean", "jacques","rua",10,b,liste_tous_livre);

    a1.getEmprunts().affiche();

    return 0;
}