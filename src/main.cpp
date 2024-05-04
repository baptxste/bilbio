#include"Bibliotheque.h"
#include"Livre.h"
#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include"Roman.h"
#include"Inventaire.h"
#include"Adherent.h"
#include<sstream>


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
Adherent entrezAdherent(){   
    Inventaire liste_tous_livres = initLivres();
    vector<Bibliotheque> listebiblios = Bibliotheque::initialiserVecteurBibliotheque(&liste_tous_livres);
    vector<Adherent> listeadherents = Adherent::initVecteurAdherent(listebiblios);
    string nom ; 
    for(int i = 0; i<listeadherents.size();++i){
        nom += listeadherents[i].getNom()+" , ";
    }
    cout << " Quel adhérent veut emprunter un livre ? ( entrez le nom)"<<endl;
    cout << nom<<endl;
    // on récupère l'objet adhérent associé à ce nom
    while(true){
        cin >> nom;
        for(int i = 0; i<listeadherents.size();++i){
            if (listeadherents[i].getNom() == nom){
                Adherent adh = listeadherents[i];
                return adh;
            }
        }
        cout <<" l'adhérent correspondant au nom : "<< nom<<" n'extiste pas."<<endl;
    }
}
void creerNouvelleBiblio(){
    Inventaire liste_tous_livres = initLivres();
    vector<Bibliotheque> listebiblios = Bibliotheque::initialiserVecteurBibliotheque(&liste_tous_livres);
    cout << "Pour créer une nouvelle bliotheque veuillez entrer ces informations :"<< endl;
    string nom, adresse;
    cout << "Nom :";
    cin >> nom;
    cout <<"Adresse : ";
    cin >> adresse;
    Bibliotheque b = Bibliotheque(nom,adresse);
    // ajout de livre à la bibliothèque
    string reponse;
    cout << "Voulez vous ajouter des livres à cette bibliothèque ?(oui/non)"<< endl;
    cin >> reponse;
    if(reponse == "oui"){
        string ssisbn;
        cout << "Entrez la liste des isbn à ajouter à la bibliotèque. (si plusieurs séparer par une virgule)"<<endl;
        cin >>ssisbn;
        vector<string> vecisbnverifie;
        // on vérifie que ces isbn existent bien dans la liste de tous les livres connus.
        vector<string> vecisbn;
        string isbn;
        stringstream ss(ssisbn);
        while(getline(ss, isbn,',')){
            vecisbn.push_back(isbn);
        }
        for( int i = 0; i<vecisbn.size();++i){
            bool existe = false;
            Noeud* current = liste_tous_livres.getHead();
            while( current != nullptr){
                if (current->getLivre().getIsbn() == vecisbn[i]){
                    vecisbnverifie.push_back(vecisbn[i]);
                    existe = true;
                    break;
                }
                else{
                    current = current->getSuivant();
                }
            }
            if (existe == false){
                cout<< " Attention l'isbn :"<< vecisbn[i]<< "n'existe pas et n'est donc pas ajouté à la bilbiothèque."<<endl;
            }
        }
        b.setInventaire(vecisbnverifie,&liste_tous_livres);
        listebiblios.push_back(b);
    }   
    else{
        listebiblios.push_back(b);
    }
    Bibliotheque::enregistrerVecteurBibliotheque(listebiblios);
    cout << " Bibliotheque bien enregistrée."<<endl;
}
void empruntDeLivre(){
    Adherent a = entrezAdherent();


}

void menu(){
    bool continuer = true;
    int choix = 0;
    do{
        cout << "===== Menu =====" << endl;
        cout << "1) Créer une nouvelle bibliothèque" << endl;
        cout << "2) " << endl;
        cout << "3) " << endl;

        cout << "Votre choix : ";
        cin >> choix;
        switch(choix){
            case 1:
                creerNouvelleBiblio();
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
    // Inventaire liste_tous_livres =initLivres();
    // vector<Bibliotheque> listebiblios = Bibliotheque::initialiserVecteurBibliotheque(&liste_tous_livres);
    // vector<Adherent> listeadherents = Adherent::initVecteurAdherent(listebiblios);


    empruntDeLivre();

    return 0;
}