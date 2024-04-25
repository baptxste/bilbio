#include"Bibliotheque.h"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

vector<Bibliotheque> listeBibliotheque;

bool Bibliotheque::categorieExiste(string cat){

    vector<string>categoriesExistantes;
    categoriesExistantes.push_back("album");
    categoriesExistantes.push_back("bande-dessinee");
    categoriesExistantes.push_back("roman");
    categoriesExistantes.push_back("poesie");
    categoriesExistantes.push_back("theatre");
    
    return find(categoriesExistantes.begin(), categoriesExistantes.end(), cat) != categoriesExistantes.end();
}

Bibliotheque::Bibliotheque(){
    nom = "Nom par defaut";
    adresse = "La ou elle est";
    inventaire = Inventaire();
    listeBibliotheque.push_back(*this);
}

Bibliotheque::Bibliotheque(string nom, string  adresse){
    this->nom = nom;
    this->adresse = adresse;
    inventaire = Inventaire();
    listeBibliotheque.push_back(*this);
}

string Bibliotheque::getNom(){
    return this->nom;
}

string Bibliotheque::getAdresse(){
    return this->adresse;
}

Inventaire Bibliotheque::getLivres(){
    return this->inventaire;
}

void Bibliotheque::setNom(string nom){
    this->nom = nom;
}

void Bibliotheque::setAdresse(string adresse){
    this->adresse = adresse;
}

void Bibliotheque::addLivre(Livre livre){
    inventaire.ajoute(livre);
}

void Bibliotheque::removeLivre(Livre livre){
    inventaire.enleve(livre);
}

void Bibliotheque::afficheTousLesLivres(){
    inventaire.affiche();
}

ostream& operator<<(ostream& out, Bibliotheque b){
    out << "nom : ";
    out << b.getNom() << endl; 
    out << "adresse : ";
    out << b.getAdresse() << endl;
    return out;
}

void Bibliotheque::afficheLivresParCategorie(string categorie){
    try{
        if( !categorieExiste(categorie) ){
            throw runtime_error("Cette catégorie n'existe pas, essayez de mettre la catégorie en minuscule et sans accent");
        }
        else{

            Noeud* current = inventaire.getHead();
            
            while( current!= nullptr ){
            
                Livre livre = current->getLivre();
            
                if( livre.getCategorie() == categorie ){
                    livre.affiche();
                }
                current = current->getSuivant();
            }
        }
    }
    catch( exception& e){
        cerr << "Erreur : " << e.what() << '\n';
    }
}

bool Bibliotheque::estlibre(Livre livre){
    return livre.getEtats()=="libre";
}

void Bibliotheque::rendreLivre(Livre livre){

    Noeud* current = inventaire.getHead();

    while( current != nullptr){
        Livre current_book = current->getLivre();

        if ( current_book.getCode()==livre.getCode() ){
            livre.setEtats("libre");
        }
    }
}

void Bibliotheque::affiche(){
    cout<<"nom : "<< nom << "adresse : " << adresse << endl;
    inventaire.affiche();
}



bool Bibliotheque::LivreDansLaBiblioteque(string isbn, Bibliotheque biblio) {

    Inventaire inventaireBiblio = biblio.getLivres();

    Noeud* current = inventaireBiblio.getHead();
    while (current != nullptr) {
        if (current->getLivre().getIsbn() == isbn) {
            return true;
        }
        current = current->getSuivant();
    }
    return false;
}

Livre Bibliotheque::livreParIsbn(string isbn){

    if (LivreDansLaBiblioteque(isbn, *this)){

        Noeud* current = inventaire.getHead();
        while (current != nullptr) {
        if (current->getLivre().getIsbn() == isbn) {
            return current->getLivre();
        }
        current = current->getSuivant();
        }
    }
    else{
        throw runtime_error("le livre n'est pas dans cette biblioteque");
    }
}

void Bibliotheque::demandeLivre (string isbn, Bibliotheque nom){
    if (LivreDansLaBiblioteque (isbn, nom)){
        Livre l = livreParIsbn(isbn);
        this->addLivre(l);
        l.setEtats("emprunté");
    }
    else{
        cout << "le livre n'est pas dans cette biblioteque" << endl;
    }
}

void Bibliotheque::preteLivre(string isbn, Bibliotheque nom){
    
    Livre livre = livreParIsbn( isbn );
    
    if (estlibre(livre)){
        nom.addLivre(livre);
        livre.setEtats ("prete");
    }
    else{
        cout << "le livre n'est pas libre" << endl;
    }
}

void Bibliotheque::supprimeLivre (int code){

    Inventaire inventaireBiblio = this->getLivres();

    Noeud* current = inventaireBiblio.getHead();
    while (current != nullptr) {
        if (current->getLivre().getCode() == code) {
            Livre livreCorrespondant = current->getLivre();
            this->removeLivre(livreCorrespondant);
        }
        current = current->getSuivant();
    }
    cout << "le livre n'est pas dans cette biblioteque" << endl;
}


void Bibliotheque::rendLivre(){

    Inventaire inventaireBiblio = this->getLivres();

    Noeud* current = inventaireBiblio.getHead();
    
    while (current != nullptr) {
    
        if (current->getLivre().getNomBiblioOrigine() != this->nom ) {
    
            if (current->getLivre().getEtats() == "libre"){
                inventaireBiblio.enleve(current->getLivre());
                for (Bibliotheque& bibliotheque : listeBibliotheque){
                    auto it = find_if(listeBibliotheque.begin(), listeBibliotheque.end(), [&bibliotheque](Bibliotheque b) { return b.getNom() == bibliotheque.getNom(); });
                    if (it != listeBibliotheque.end()){
                        bibliotheque.livreParIsbn(current->getLivre().getIsbn()).setEtats("libre");
                    }
                }
            }
            else {
                cout << "Le livre n'a pas encore été rendu à notre bibliotheque" << endl;
            }
        }
    }
}


