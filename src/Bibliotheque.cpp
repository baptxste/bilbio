#include"Bibliotheque.h"
#include"Adherent.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include<fstream>
#include<sstream>


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
    nom = "Nom par défaut";
    adresse = "Adresse apr défaut";
    inventaire = Inventaire();
    listepretAdherent = vector<tuple<int,int>>();
}

Bibliotheque::Bibliotheque(string nom, string  adresse){
    this->nom = nom;
    this->adresse = adresse;
    inventaire = Inventaire();
    listepretAdherent = vector<tuple<int,int>>();
}

Bibliotheque::~Bibliotheque(){
    inventaire.~Inventaire();
    listepretAdherent.clear();
}

string Bibliotheque::getNom(){
    return this->nom;
}

string Bibliotheque::getAdresse(){
    return this->adresse;
}

Inventaire Bibliotheque::getInventaire(){
    return this->inventaire;
}

Livre Bibliotheque::getLivre(int code){
    Noeud* current = inventaire.getHead();
    while ( current != nullptr){
        if ( current->getLivre().getCode() == code){
            return current->getLivre();
        }
        current = current->getSuivant();
    } 
    cout <<" le livre code : "<< code<<" n'a pas été trouvé dans la bibliotheque"<< endl;
    return Livre();


}

vector<tuple<int, int>> Bibliotheque::getPretAdherent(){
    return this->listepretAdherent;
}

void Bibliotheque::setNom(string nom){
    this->nom = nom;
}

void Bibliotheque::setAdresse(string adresse){
    this->adresse = adresse;
}

void Bibliotheque::affiche(){
    cout<<"nom : "<< this->nom << "adresse : " << this->adresse << endl;
    inventaire.affiche();
}

void Bibliotheque::ajouterPret(int code, int id){
    tuple<int, int> tup = std::make_tuple(code, id);
    listepretAdherent.push_back(tup);
}
void Bibliotheque::affichePretAdherent(){
    vector<tuple<int,int>> vec = this->listepretAdherent;
    for( int i =0; i<vec.size();++i){
        cout << "code : " << get<0>(vec[i])<<", id de l'adhérent : " << get<1>(vec[i])<<endl;
    }
}
ostream& operator<<(ostream& out, Bibliotheque& b){
    out << "nom : ";
    out << b.getNom() << endl; 
    out << "adresse : ";
    out << b.getAdresse() << endl;
    return out;
}

void Bibliotheque::setInventaire(vector<string> vecisbn, Inventaire* tous_les_livres){
    int j = 1;
    for (int i=0; i<vecisbn.size();++i){
        Livre* l = tous_les_livres->getLivre(vecisbn[i]);
        // on vérifie que le livre existe bien i.e. isbn non défaut
        if (l->getIsbn() !="isbn_defaut"){
            Livre liv = *l;
            liv.setCode(j);
            j++;
            inventaire.ajoute(liv);
        }
        else{
            cout <<"l'isbn : '"<<vecisbn[i] << "' ne correstpond à aucun livre existant"<<endl;
        }
    }
}

vector<Bibliotheque> Bibliotheque::initialiserVecteurBibliotheque(Inventaire* tous_les_livres){
    vector<Bibliotheque> bib;
    ifstream fichier("bd/liste_biblios");
    if (fichier.is_open()){
        string ligne; 
        while(getline(fichier, ligne)){
            stringstream ss(ligne);
            string nom, adresse, listeisbn, listepretadh;
            getline(ss, nom,';');
            getline(ss, adresse, ';');
            getline(ss, listeisbn, ';');
            getline(ss, listepretadh,';');
            if (listeisbn.empty()){
                cout << "pour la biblio " << nom <<" pas d'inventaire"<< endl;
                bib.push_back(Bibliotheque(nom, adresse));
            }
            else{
                vector<string> vecisbn;
                stringstream ssisbn(listeisbn);
                string isbn;
                while(getline(ssisbn, isbn,',')){
                    vecisbn.push_back(isbn);
                }
                Bibliotheque b = Bibliotheque(nom, adresse);
                b.setInventaire(vecisbn, tous_les_livres);
                // initialisation de la liste des prêts adhérents
                vector<tuple<int,int>> vecpret;
                if (!listepretadh.empty()){
                    vector<string> prets;
                    stringstream sspret(listepretadh);
                    string pret;
                    while(getline(sspret, pret,'|')){
                        prets.push_back(pret);
                    }
                    for( int i=0;i<prets.size();++i){
                        cout<<prets[i]<<endl;
                    }
                    for(int i=0; i<prets.size(); ++i){
                        stringstream sspret(prets[i]);
                        int code, id;
                        char del = ':'; // Pour stocker le caractère '|'
                        sspret >> code >> del >> id;
                        b.ajouterPret(code,id);
                        Noeud* current = b.getInventaire().getHead();
                        while(current != nullptr){
                            if(current->getAdresseLivre()->getCode() == code){
                                current->getAdresseLivre()->setEtats("emprunté");
                                break;
                            }
                            current = current->getSuivant();
                        }
                    }
                } 
                bib.push_back(b);
            } 
        }
    fichier.close();
    }else{
        cerr << "Erreur : Impossible d'ouvrir le fichier." << std::endl;
    }
    return bib;
}


void Bibliotheque::enregistrerVecteurBibliotheque(vector<Bibliotheque> vecbib){
    fstream fichier("bd/liste_biblios", std::ios::in | std::ios::out);
    if (fichier.is_open()){
        for(int i=0; i<vecbib.size();i++){
            // on récupère la liste des isbn
            string listeisbn ;
            Noeud* current = vecbib[i].getInventaire().getHead();
            if ( current != nullptr ){
                while ( current->getSuivant() != nullptr ) {
                    listeisbn += current->getLivre().getIsbn()+",";
                    current = current->getSuivant();
                }
                listeisbn += current->getLivre().getIsbn();
            }
            // fin liste isbn
            string stringpretadh ;
            for(int j=0; j<vecbib[i].getPretAdherent().size();++j){
                tuple<int,int> tuple= vecbib[i].getPretAdherent()[j];
                stringpretadh += to_string(std::get<0>(tuple))+':'+to_string(std::get<1>(tuple))+'|';       
            } 
            fichier << vecbib[i].getNom()<<";"<<vecbib[i].getAdresse()<<";"<<listeisbn<<";"<<stringpretadh<<";"<<endl;
        }
    }
    fichier.close();
}


