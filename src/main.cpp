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
#include <cstdlib> // Pour remove() et rename() de la méthode supprimerLignesCourtes


using namespace std;

Inventaire initLivres(){
    Inventaire liste_tous_livres = Inventaire();

    vector<Roman> listeromans = Roman::initialiserVecteurRomans();
    for (size_t i=0; i < listeromans.size();++i) {
        liste_tous_livres.ajoute(listeromans[i]);
    }
    // repeter ces étapes pour les autres catégories
    return liste_tous_livres;
}

void supprimerLignesCourtes(const string& nomFichier) {
    /*
    Cette fonction est utilisée pour nettoyer les fichiers ( liste adhérents et liste biblios) car quand on 
    rend un livre, de courtes chaînes de caractères sont écrites dedans ce qui pose un problème lors ce que l'on veut réinitialiser ces fichiers.
    */
    ifstream fichierEntree(nomFichier);
    if (!fichierEntree) {
        cout<< "Erreur : Impossible d'ouvrir le fichier en lecture." << endl;
        return;
    }
    string nomFichierTemp = nomFichier + ".temp";
    ofstream fichierTemp(nomFichierTemp);
    if (!fichierTemp) {
        cout << "Erreur : Impossible d'ouvrir le fichier temporaire en écriture." << endl;
        fichierEntree.close();
        return;
    }
    string ligne;
    while (getline(fichierEntree, ligne)) {
        if (ligne.size() >= 10) {
            fichierTemp << ligne << endl;
        }
    }
    fichierEntree.close();
    fichierTemp.close();
    if (remove(nomFichier.c_str()) != 0) {
        cout << "Erreur : Impossible de supprimer le fichier d'origine." << endl;
        return;
    }
    if (rename(nomFichierTemp.c_str(), nomFichier.c_str()) != 0) {
        cout << "Erreur : Impossible de renommer le fichier temporaire." << endl;
        return;
    }
}

Adherent* entrezAdherent(vector<Adherent>* listeadherents){   
    string nom ; 
    for(int i = 0; i<listeadherents->size();++i){
        nom += (*listeadherents)[i].getNom()+" , ";
    }
    cout << " Choisissez l'adhérent ? ( entrez le nom)"<<endl;
    cout << nom<<endl;
    // on récupère l'objet adhérent associé à ce nom
    while(true){
        cin >> nom;
        for(int i = 0; i<listeadherents->size();++i){
            if ((*listeadherents)[i].getNom() == nom){
                return &(*listeadherents)[i];
            }
        }
        cout <<" l'adhérent correspondant au nom : "<< nom<<" n'extiste pas."<<endl;
    }
}

Bibliotheque* entrezBibliotheque(vector<Bibliotheque>* listebiblios){
    vector<string> noms;
    for(int i= 0;i<listebiblios->size();i++){
        cout << "Bibliothèque  :  "<<(*listebiblios)[i].getNom()<<endl;
        noms.push_back((*listebiblios)[i].getNom());
    }
    string nom;
    while(true){
        cout << "Entrez le nom : ";
        cin >>nom;
        for(int i= 0;i<listebiblios->size();i++){
            if((*listebiblios)[i].getNom()==nom){
                return &((*listebiblios)[i]);
            }
        cout <<"Le nom entrez ne correspond pas à une bibliothèque existante."<<endl;
        }
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

Inventaire* creerNouveauLivre(Inventaire* liste_tous_livres){
    vector<string> categories = {"Roman","Poésie","Bande Dessinée"};
    cout << "=== Catégories possibles ==="<<endl;
    for(int i =0;i<categories.size();++i){
        cout<<" "<<(i+1)<<") "<<categories[i]<<endl;
    }
    int cat;
    bool catvalide = false;
    while(!catvalide){
        cout << "Quel type de livre souhaitez-vous créer ? ( entrez le numéro)";
        cin >> cat;
        cout << (cat<1 && cat>(categories.size()+1))<<endl;
        if( cat>=1 && cat<=(categories.size()+1)){
            catvalide = true;
        }
    }
    switch (cat)
    {
    case 1:
        Roman::creerRomangraphique();
        break;
    case 2:
    /* code */
    break;
    case 3:
    /* code */
    break;
    
    default:
        break;
    }
    Inventaire inv = initLivres();
    return &inv;

}
void empruntDeLivre(){
    //Initialisation
    Inventaire liste_tous_livres = initLivres();
    vector<Bibliotheque> listebiblios = Bibliotheque::initialiserVecteurBibliotheque(&liste_tous_livres);
    vector<Adherent> listeadherents = Adherent::initVecteurAdherent(&listebiblios);
    Adherent* a = entrezAdherent(&listeadherents);
    Inventaire inv = a->getBibliotheque()->getInventaire();
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
        a->emprunte(code);
        Adherent::enregistrerVecteurAdherent(listeadherents);
        Bibliotheque::enregistrerVecteurBibliotheque(listebiblios);
        cout << "L'adhérent "<<a->getNom()<<" a bien emprunté le livre."<<endl;
    }else{
        cout <<"Il n'y a plus de livre disponible à l'emprunt dans la bibliothèque de l'adhérent."<<endl;
        Adherent::enregistrerVecteurAdherent(listeadherents);
        Bibliotheque::enregistrerVecteurBibliotheque(listebiblios);
    }
}

void rendreUnLivre(){
    /*
    ATTENTION lors du retour d'un livre des lignes incorrectes sont crées dans liste adherent et liste biblios
    */
    Inventaire liste_tous_livres =initLivres();
    vector<Bibliotheque> listebiblios = Bibliotheque::initialiserVecteurBibliotheque(&liste_tous_livres);
    vector<Adherent> listeadherents = Adherent::initVecteurAdherent(&listebiblios);
    Adherent* a = entrezAdherent(&listeadherents);
    cout << " Quel livre voulez-vous rendre ? "<<endl;
    Inventaire inv = a->getEmprunts();
    Noeud* current = inv.getHead();
    vector<int> codes;
    while(current!=nullptr){
        cout << "Titre : "<<current->getLivre().getTitre()<< "  ==> code : "<<current->getLivre().getCode()<<endl;
        codes.push_back(current->getLivre().getCode());
        current = current->getSuivant();
    }
    if(codes.size()>0){
        cout << "entrez le code du livre à rendre : "<<endl;
        bool codevalide = false;
        int code;
        while(!codevalide){
                cin >> code;
                auto it = find(codes.begin(), codes.end(), code);
                codevalide = (it != codes.end());
        }
        a->rend(code);
        Adherent::enregistrerVecteurAdherent(listeadherents);
        Bibliotheque::enregistrerVecteurBibliotheque(listebiblios);
    }
    else{
        cout<< " Cette adhérent n'a pas d'emprunt en cours."<<endl;
    }
}

void ajoutLivreBiblio(){
    Inventaire liste_tous_livres =initLivres();
    vector<Bibliotheque> listebiblios = Bibliotheque::initialiserVecteurBibliotheque(&liste_tous_livres);
    cout << " Dans quelle bibliothèque voulez-vous ajouter le livre ?"<<endl;
    Bibliotheque* bib = entrezBibliotheque(&listebiblios);
    cout << "=== Liste des livres déjà existant ==="<<endl;
    bool livreexiste = false;
    string isbn;
    vector<string> listeisbn;
    while(!livreexiste){
        Noeud* current = liste_tous_livres.getHead();
        while(current!=nullptr){
            cout <<"Titre : "<<current->getLivre().getTitre()<< "\t\tISBN  : "<<current->getLivre().getIsbn()<<endl;
            listeisbn.push_back(current->getLivre().getIsbn());
            current = current->getSuivant();
        }
        cout << "Le livre que vous souhaitez ajouter est-il déjà existant ? ( oui/non )"<<endl;
        string reponse;
        cin >> reponse;
        if(reponse=="oui"){
            livreexiste = true;
            bool livrevalide = false;
            while(!livrevalide){
                cout << "Entrez l'isbn du livre choisit : ";
                cin>>isbn;
                auto it = find(listeisbn.begin(), listeisbn.end(), isbn);
                livrevalide = (it != listeisbn.end());
            }
        }
        else if(reponse=="non"){
            cout <<"Vous devez d'abord créer le livre avant de l'ajouter."<<endl;
            cout<<"Création du livre : "<<endl;
            liste_tous_livres = *creerNouveauLivre(&liste_tous_livres);
        }
        else{
            cout << "Réponse invalide : retour au menu"<<endl;
            return;
        }
    }
    // on a récupérer l'isbn à ajouter
    bib->acheterLivre(isbn, &liste_tous_livres);
    cout << "Le livre a bien été ajouté à la bibliothèque."<<endl;
    Bibliotheque::enregistrerVecteurBibliotheque(listebiblios);
}

void menu(){
    bool continuer = true;
    int choix = 0;
    do{
        supprimerLignesCourtes("bd/adherents/liste_adherents");
        supprimerLignesCourtes("bd/liste_biblios");
        cout << "===== Menu =====" << endl;
        cout << "1) Créer une nouvelle bibliothèque" << endl;
        cout << "2) Effectuer un emprunt de Livre pour un adhérent" << endl;
        cout << "3) Rendre un livre" << endl;
        cout << "4) Ajouter un nouveau livre dans une bibliothèque." << endl;
        cout << "3) Rendre un livre" << endl;
        cout << "3) Rendre un livre" << endl;

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
                rendreUnLivre();
                break;
            case 4:
                ajoutLivreBiblio();
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

    menu();
    // finir ajoutlivrebiblio
    // il faut créer la methode qui permet de créer un livre.
    // Roman::creerRomangraphique();



    return 0;
}