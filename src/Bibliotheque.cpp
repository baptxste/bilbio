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
    listeempruntbiblio = vector<tuple<string,int>>();
}

Bibliotheque::Bibliotheque(string nom, string  adresse){
    this->nom = nom;
    this->adresse = adresse;
    inventaire = Inventaire();
    listepretAdherent = vector<tuple<int,int>>();
    listeempruntbiblio = vector<tuple<string,int>>();
}

Bibliotheque::~Bibliotheque(){
    inventaire.~Inventaire();
    listepretAdherent.clear();
    listeempruntbiblio.clear();
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

vector<tuple<int, int>>* Bibliotheque::getAddPretAdherent(){
    return &this->listepretAdherent;
}

vector<tuple<string,int>>* Bibliotheque::getPretBiblio(){
    return &this->listeempruntbiblio;
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

void Bibliotheque::ajouterempruntbib(string nom, int code){
    tuple<string, int > tup = make_tuple(nom,code);
    listeempruntbiblio.push_back(tup);
}

void Bibliotheque::supprimeEmpruntBib(int code){
    for(int i=0;i<listeempruntbiblio.size();++i){
        if (get<1>(listeempruntbiblio[i])==code){
            listeempruntbiblio.erase(listeempruntbiblio.begin() +i);
            break;
        }
    }
}

void Bibliotheque::affichePretAdherent(){
    vector<tuple<int,int>> vec = this->listepretAdherent;
    for( int i =0; i<vec.size();++i){
        cout << "code : " << get<0>(vec[i])<<", id de l'adhérent : " << get<1>(vec[i])<<endl;
    }
}

void Bibliotheque::acheterLivre(string isbn,Inventaire* tous_les_livres){
    Noeud* current = tous_les_livres->getHead();
    bool livreexiste = false;
    while(current!=nullptr){
        if(current->getLivre().getIsbn()==isbn){
            livreexiste = true;
            Livre l = current->getLivre();
            // on compte tous les livres présents pour assigner le code
            int i = 0;
            Noeud* tt = inventaire.getHead();
            while(tt!=nullptr && tt->getSuivant()!=nullptr){
                i++;
                tt = tt->getSuivant();
            }
            l.setCode(i);
            inventaire.ajoute(l);
            return;
        }
        current = current->getSuivant();
    }
    if(!livreexiste){
        cout << "Attention le livre demandé n'existe pas."<<endl;
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


void Bibliotheque::empruntLivreBiblio(string isbn, Bibliotheque* bib_qui_prete){
    if(bib_qui_prete->getInventaire().getLivre(isbn)->getEtats()=="libre"){
        Livre ll = *(bib_qui_prete->getInventaire().getLivre(isbn));    bib_qui_prete->getInventaire().getLivre(isbn)->setEtats("prêté");
        string nom_proprio = bib_qui_prete->getNom();
        ll.setEtats("libre");
        int code = 1;
        Noeud* tt = inventaire.getHead();
        while(tt->getSuivant()!=nullptr){
            code++;
            tt = tt->getSuivant();
        }
        code++;
        ll.setCode(code);
        tuple<string, int> tup(nom_proprio, code);
        inventaire.ajoute(ll);
        listeempruntbiblio.push_back(tup);
    }
    else{
        cout << " Attention le livre isbn : "<<isbn<<" n'est pas disponible dans la bibliotheque : "<<bib_qui_prete->getNom()<<endl;
    }
}

void Bibliotheque::rendreLivresEmpruntes(vector<Bibliotheque>* listebiblios){
    for(int i =0; i<listeempruntbiblio.size(); ++i){
        tuple<string, int> tup = listeempruntbiblio[i];
        int code = get<1>(tup);
        Noeud* current = inventaire.getHead();
        string isbn;
        while(current!=nullptr){
            if (current->getLivre().getCode()==code && current->getLivre().getEtats()=="libre"){
                // on retrouve la bilbiothèque avec son nom
                Bibliotheque bib;
                for(int j=0; j<listebiblios->size();++j){
                    if((*listebiblios)[j].getNom()==get<0>(tup)){
                        bib = (*listebiblios)[j];
                    }
                }
                isbn = current->getLivre().getIsbn();
                inventaire.enleve(code);
                bib.getInventaire().getLivre(isbn)->setEtats("libre");
                this->supprimeEmpruntBib(code);
                cout << "livre code : " << code << " rendu"<<endl;
            }
            current = current->getSuivant();

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
            string nom, adresse, listeisbn, listepretadh, listepretbiblio;
            getline(ss, nom,';');
            getline(ss, adresse, ';');
            getline(ss, listeisbn, ';');
            getline(ss, listepretadh,';');
            getline(ss, listepretbiblio,';');
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
                    for(int i=0; i<prets.size(); ++i){
                        stringstream sspret(prets[i]);
                        int code, id;
                        char del = ':'; // Pour stocker le caractère ':'
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
                if(!listepretbiblio.empty()){
                    vector<string> pretbib;
                    stringstream sspret(listepretbiblio);
                    string pret;
                    while(getline(sspret, pret,'|')){
                        pretbib.push_back(pret);
                    }
                    for(int i = 0; i<pretbib.size();++i){
                        stringstream sspret(pretbib[i]);
                        string nom;
                        string strcode;
                        getline(sspret,nom,':');
                        getline(sspret,strcode);
                        // on peut ne pas faire de vérification pour l'initialisation de ce vecteur 
                        // car elle a été faite au moment de l'emprunt
                        int code = stoi(strcode);
                        b.ajouterempruntbib(nom, code);
                    }

                }
                bib.push_back(b);
            } 
        }
    // on itère sur le vecteur de bibliothèque pour venir setEtat sur prêté pour tous les livres
    // qui le sont, on ne peut pas le faire avant car on a seulement la liste des emprunts entre biblio et non 
    // celle des prêts, il faut donc d'abord créer toutes les bibliothèques puis ensuite modifier les inventaires
    for(int i = 0; i<bib.size();++i){
        vector<tuple<string,int>>* empruntbib = bib[i].getPretBiblio();
        for(int j = 0; j<empruntbib->size();++j){
            tuple<string,int> tup = (*empruntbib)[j];
            string nom = get<0>(tup);
            int code = get<1>(tup);
            Noeud* current = bib[i].getInventaire().getHead();
            while( current!= nullptr){
                if ( current->getLivre().getCode()==code){
                    string isbn = current->getLivre().getIsbn();
                    // on a récupéré l'isbn du livre emprunté 
                    // on cherche sa biblio d'origine et on modifie l'état
                    for (int k =0; k<bib.size();++k){
                        if(bib[k].getNom()== nom){
                            bib[k].getInventaire().getLivre(isbn)->setEtats("prêté");
                        }
                    }
                }
                current = current->getSuivant();
            }
        }
    }
    fichier.close();
    }else{
        cout << "Erreur : Impossible d'ouvrir le fichier." << endl;
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
                stringpretadh += to_string(get<0>(tuple))+':'+to_string(get<1>(tuple))+'|';       
            } 
            string stringpretbiblio ;
            for(int j=0; j<vecbib[i].getPretBiblio()->size();++j){
                vector<tuple<string,int>>* vec = vecbib[i].getPretBiblio();
                tuple<string,int> tuple2= (*vec)[j];
                stringpretbiblio += get<0>(tuple2)+':'+to_string(get<1>(tuple2))+'|';       
            } 
            fichier << vecbib[i].getNom()<<";"<<vecbib[i].getAdresse()<<";"<<listeisbn<<";"<<stringpretadh<<";"<<stringpretbiblio<<";"<<endl;
        }
    }
    fichier.close();
}


