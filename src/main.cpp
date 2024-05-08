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

Adherent entrezAdherent(vector<Adherent> listeadherents){   
    string nom ; 
    for(int i = 0; i<listeadherents.size();++i){
        nom += listeadherents[i].getNom()+" , ";
    }
    cout << " Choisissez l'adhérent ? ( entrez le nom)"<<endl;
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
    //Initialisation
    Inventaire liste_tous_livres = initLivres();
    vector<Bibliotheque> listebiblios = Bibliotheque::initialiserVecteurBibliotheque(&liste_tous_livres);
    vector<Adherent> listeadherents = Adherent::initVecteurAdherent(&listebiblios);
    Adherent a = entrezAdherent(listeadherents);
    Inventaire inv = a.getBibliotheque()->getInventaire();

    // on affiche les livres libres de la bilbiothèque
    Noeud* current = inv.getHead();
    vector<int> codes;
    int nblivredispo=0;
    while(current != nullptr){
        if (current->getAdresseLivre()->getEtats()=="libre"){
            nblivredispo++;
            cout <<"Titre : "<< current->getAdresseLivre()->getTitre()<<"  code : "<< current->getAdresseLivre()->getCode()<<endl;
            codes.push_back(current->getAdresseLivre()->getCode());
        }
        current = current->getSuivant();
    }
    if(nblivredispo>0){
        bool codevalide = false;
        int code;
        while(codevalide == 0){
            cout << "Entrez le code :";
            cin >> code;
            auto it = find(codes.begin(), codes.end(), code);
            codevalide = (it != codes.end());
        }
        a.emprunte(code);
        cout <<"EMPRUNTS "<<endl;
        a.getEmprunts().affiche();
        Adherent::enregistrerVecteurAdherent(listeadherents);
        Bibliotheque::enregistrerVecteurBibliotheque(listebiblios);
        cout << "L'adhérent "<<a.getNom()<<" a bien emprunté le livre."<<endl;
    }else{
        cout <<"Il n'y a plus de livre disponible à l'emprunt dans la bibliothèque de l'adhérent."<<endl;
        Adherent::enregistrerVecteurAdherent(listeadherents);
        Bibliotheque::enregistrerVecteurBibliotheque(listebiblios);
    }
}

void menu(){
    bool continuer = true;
    int choix = 0;
    do{
        cout << "===== Menu =====" << endl;
        cout << "1) Créer une nouvelle bibliothèque" << endl;
        cout << "2) Effectuer un emprunt de Livre pour un adhérent" << endl;
        cout << "3) " << endl;

        cout << "Votre choix : ";
        cin >> choix;
        switch(choix){
            case 1:
                creerNouvelleBiblio();
                break;
            case 2:
                empruntDeLivre();
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
    // vector<Adherent> listeadherents = Adherent::initVecteurAdherent(&listebiblios);

    // Adherent a = listeadherents[0];
    // cout <<"emprunts avant " << endl;
    // vector<tuple<int,int>> vec = a.getBibliotheque()->getPretAdherent();
    // for(int i =0; i<vec.size();++i){
    //     tuple<int,int> tup = vec[i];
    //     cout <<" code : "<<get<0>(tup) <<" id : "<< get<1>(tup)<<endl;
    // }

   menu();
    



    return 0;
}