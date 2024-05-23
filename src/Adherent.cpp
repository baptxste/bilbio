#include "Adherent.h"
#include "Bibliotheque.h"
#include<iostream>
#include<string>
#include<vector>
#include<sstream>
#include<fstream>

int Adherent::nb_adherent = 1;

Adherent::Adherent(){
}

Adherent::Adherent(string nom, string prenom, string adresse, int nb_emprunt_max, Bibliotheque* bibliotheque){
    this->nom = nom;
    this->prenom = prenom;
    this->adresse = adresse;
    this->id_adherent = nb_adherent;
    this->nb_emprunt_max = nb_emprunt_max;
    this->bibliotheque = bibliotheque;
    nb_emprunt_en_cours = 0;
    nb_adherent++;
    this->liste_emprunt_en_cours = Inventaire();
}

Adherent::Adherent(int id_adherent, string nom, string prenom, string adresse, int nb_emprunt_max, Bibliotheque* bibliotheque, Inventaire inv) : Adherent(nom,prenom, adresse, nb_emprunt_max, bibliotheque){
    this->id_adherent = id_adherent;
    this->liste_emprunt_en_cours = inv;
}

Adherent::~Adherent(){
    nb_adherent--;
}

string Adherent::getNom(){
    return this->nom;
}

string Adherent::getPrenom(){
    return this->prenom;
}

string Adherent::getAdresse(){
    return this->adresse;
}

int Adherent:: getId(){
    return this->id_adherent;
}

int Adherent::getNbEmpruntMax(){
    return this->nb_emprunt_max;
}

Bibliotheque* Adherent::getBibliotheque(){
    return this->bibliotheque;
}

Inventaire Adherent::getEmprunts(){
    return this->liste_emprunt_en_cours;
}

void Adherent::setNom(string nom){
    this->nom = nom;
}

void Adherent::setPrenom(string prenom){
    this->prenom = prenom;
}

void Adherent::setAdresse(string adresse){
    this->adresse = adresse;
}

void Adherent::setId(int id_adherent){
    this->id_adherent = id_adherent;
}

void Adherent::setNbEmpruntMax(int nb_emprunt_max){
    this->nb_emprunt_max = nb_emprunt_max;
}

void Adherent::setBibliotheque(Bibliotheque* biblio){
    this->bibliotheque = biblio;
}

ostream& operator<<(ostream& out, const Adherent& a) {
    out<<"nom : ";
    out<<a.nom<< endl;
    out<<"prenom : ";
    out<<a.prenom<< endl;
    out<<"adresse : ";
    out<<a.adresse<< endl;
    out<<"id adhérent : ";
    out<<a.id_adherent<< endl;
    out<<"nombre d'emprunt max : ";
    out<<a.nb_emprunt_max<< endl;
    return out;
}

bool Adherent::peutEmpruter(){
    if (this->nb_emprunt_en_cours < nb_emprunt_max){
        return true;
    }
    else{
        cout<<"l'adhérent a emprunté trop de livre"<<endl;
        cout <<" refus de l'emprunt"<< endl;
        return false;
    }
}

void Adherent::affiche(){
    cout <<this->nom<<endl;
    cout <<this->prenom<<endl;
    cout << this->adresse << endl;
}

void Adherent::emprunte(int code){
    if(peutEmpruter()){
        // vérifier que le livre est libre
        Inventaire inv = bibliotheque->getInventaire();
        Noeud* current = inv.getHead();
        bool livretrouve = false;
        while(current!=nullptr){
            if(current->getAdresseLivre()->getCode() == code){
                if (current->getAdresseLivre()->getEtats() == "libre"){
                    liste_emprunt_en_cours.ajoute(current->getLivre());
                    current->getAdresseLivre()->setEtats("emprunté");
                    livretrouve = true;
                    bibliotheque->ajouterPret(code,this->getId());
                    cout << "Livre emprunté."<<endl;
                    break;
                }
            }
            else{
                current = current->getSuivant();
            }
        }
        if(!livretrouve){
            cout<<"L'emprunt n'a pas été effectué"<<endl;
            cout<<"Le livre n'est pas disponible ou n'existe pas."<<endl;
        }
    }
}

void Adherent::rend(int code){
    Inventaire* emprunt = &liste_emprunt_en_cours;
    Noeud * current = emprunt->getHead();
    while( current!=nullptr){
        if(current->getAdresseLivre()->getCode() == code){
            current->getAdresseLivre()->setEtats("libre");
            emprunt->enleve(code);
            // on met a jour la liste de la biblio
            vector<tuple<int,int>>* vec = bibliotheque->getAddPretAdherent();
            for(int i=0;i<(*vec).size();++i){
                if(get<0>((*vec)[i])==code && get<1>((*vec)[i])==this->getId()){
                    vec->erase(vec->begin()+i);
                }
            }
            cout << "Livre rendu."<<endl;
            break;
        }
        current = current->getSuivant();
    }
}

vector<Adherent> Adherent::initVecteurAdherent(vector<Bibliotheque>* listebiblios){
    vector<Adherent> adhs;
    ifstream fichier("bd/adherents/liste_adherents");
    if (fichier.is_open()) {
        string ligne;
        while (getline(fichier, ligne)) {
            stringstream ss(ligne);
            string id, nom, prenom, adresse, nb_emprunt_max, biblio,liste_emprunt;
            getline(ss, id, ';');
            getline(ss, nom, ';');
            getline(ss, prenom, ';');
            getline(ss, adresse, ';');
            getline(ss, nb_emprunt_max, ';');
            getline(ss, biblio, ';');
            getline(ss, liste_emprunt, ';');
            // on récupère l'objet bibliotheque 
            Bibliotheque* bib;
            bool bibexiste =false;
            for (int i=0; i<listebiblios->size();++i){
                if( (*listebiblios)[i].getNom() == biblio){
                    bib  = &(*listebiblios)[i];
                    bibexiste = true;
                    break;
                }
            }
            if(!bibexiste){
                cout << "Attention la bibliothèque "<< biblio <<" utilisée pour crée l'adhérent " << nom <<" "<< prenom <<" n'existe pas, ajout d'une bibliothèque par défaut."<<endl;
                bib = new Bibliotheque();
            }
            // liste des emprunts
            Inventaire emprunts;
            if (liste_emprunt.empty()){
                emprunts =Inventaire();
            }
            else{
                Inventaire invbiblio  = bib->getInventaire();
                vector<int> veccode;
                stringstream sscode(liste_emprunt);
                string code;
                while(getline(sscode, code,',')){
                    veccode.push_back(stoi(code));
                }
                for(int i=0; i<veccode.size(); ++i){
                    emprunts.ajoute(bib->getLivre(veccode[i]));
                }
            }
            adhs.push_back(Adherent(stoi(id),nom,prenom,adresse,stoi(nb_emprunt_max),bib,emprunts));
            
        }
        fichier.close();
    } else {
        std::cerr << "Erreur : Impossible d'ouvrir le fichier." << std::endl;
    }
    Adherent::nb_adherent = adhs.size()+1;
    return adhs;
}

void Adherent::enregistrerVecteurAdherent(vector<Adherent> listeadh){
    fstream fichier("bd/adherents/liste_adherents", std::ios::in | std::ios::out);
    if (fichier.is_open()){
        for( int i = 0; i<listeadh.size();++i){
            // on récupère les codes des emprunts
            string listecodes;
            Noeud* current = listeadh[i].getEmprunts().getHead();
            while(current!=nullptr){
                listecodes += to_string(current->getLivre().getCode())+","; //to_string pour éviter le warning de la conversion de l'int
                current = current->getSuivant();
            }
            fichier << listeadh[i].getId()<<";"<<listeadh[i].getNom()<<";"<<listeadh[i].getPrenom()<<";"<<listeadh[i].getAdresse()<<";"<<listeadh[i].getNbEmpruntMax()<<";"<<listeadh[i].getBibliotheque()->getNom()<<";"<<listecodes<<";"<<endl;
        }
        fichier.close();
    }
    else
    {
        cout << "Erreur lors de l'écriture des adhérents"<<endl;
    }
}
