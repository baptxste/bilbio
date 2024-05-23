#include"Poesie.h"
#include<iostream>
#include<string>
#include"fstream"
#include"sstream"

using namespace std;

Poesie::Poesie( string auteur, string titre, string editeur, string isbn, string etats, string vers) : Livre( auteur, titre, editeur, isbn, etats){
    this->vers = vers ;
    setCategorie("poesie");
}

Poesie::Poesie(){
}

void Poesie::creerPoesiegraphique(){
    cout << "=== Création d'une poesie === "<<endl;
    string auteur, titre, editeur, isbn, vers;
    cout << " - Auteur : ";
    cin >> auteur;
    cout <<" - titre : ";
    cin >> titre;
    cout << " - Editeur : ";
    cin >> editeur;
    cout <<" - ISBN : ";
    cin >>isbn;
    cout <<" - Vers : ";
    cin >> vers;
    string etat = "libre";
    string line = isbn +';'+titre+';'+editeur+';'+auteur+';'+etat+';'+vers+';';
    std::ofstream fichier("bd/livres/liste_poesies", std::ios_base::app);
    fichier<<line<<endl;
    fichier.close();

}

string  Poesie::getVers(){
    return this->vers;
}                                                                                                          

void    Poesie::setVers(string vers){
    this->vers = vers;
}                                                                         

void    Poesie::affiche (){
    Livre::affiche();
    cout<<"vers : "<< vers<< endl;
}

vector<Poesie> Poesie::initialiserVecteurPoesie(){
    vector<Poesie> poesies;
    ifstream fichier("bd/livres/liste_poesies");
    if (fichier.is_open()) {
        string ligne;
        while (getline(fichier, ligne)) {
            stringstream ss(ligne);
            string isbn, auteur, titre, editeur, etats, vers;
            getline(ss, isbn, ';');
            getline(ss, titre, ';');
            getline(ss, editeur, ';');
            getline(ss, auteur, ';');
            getline(ss, etats, ';');
            getline(ss, vers, ';');
            poesies.push_back(Poesie( auteur, titre, editeur, isbn, etats, vers));
        }
        fichier.close();
    } else {
        std::cerr << "Erreur : Impossible d'ouvrir le fichier." << std::endl;
    }
    return poesies;
}

void    Poesie::enregistrerVecteurPoesie(vector<Poesie> liste){
    fstream fichier("bd/livres/liste_poesies", std::ios::in | std::ios::out );
    if (fichier.is_open()) {
        for (size_t i=0; i < liste.size();++i) {
                fichier <<liste[i].getIsbn()<<";"<<liste[i].getAuteur()<<";"<<liste[i].getTitre()<<";"<<liste[i].getEditeur()<<";"<<liste[i].getEtats()<<";"<<liste[i].getVers()<<";" << std::endl;
        }
    fichier.close();
    } else {
        std::cerr << "Erreur lors de l'ouverture du fichier." << std::endl;
    }

}