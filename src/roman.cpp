#include"Roman.h"
#include<iostream>
#include<string>
#include"fstream"
#include"sstream"

using namespace std;

Roman::Roman( string auteur, string titre, string editeur, string isbn, string etats, string genre) : Livre( auteur, titre, editeur, isbn, etats){
    this->genre = genre ;
    setCategorie("roman");
}

Roman::Roman(){
}

void Roman::creerRomangraphique(){
    cout << "=== Création d'un roman === "<<endl;
    string auteur, titre, editeur, isbn, genre;
    cout << " - Auteur : ";
    cin >> auteur;
    cout <<" - titre : ";
    cin >> titre;
    cout << " - Editeur : ";
    cin >> editeur;
    cout <<" - ISBN : ";
    cin >>isbn;
    cout <<" - Genre : ";
    cin >> genre;
    string etat = "libre";
    string line = isbn +';'+titre+';'+editeur+';'+auteur+';'+etat+';'+genre+';';
    std::ofstream fichier("bd/livres/liste_romans", std::ios_base::app);
    fichier<<line<<endl;
    fichier.close();

}

string  Roman::getGenre(){
    return this->genre;
}                                                                                                          

void    Roman::setGenre(string genre){
    this->genre = genre;
}                                                                         

void    Roman::affiche (){
    Livre::affiche();
    cout<<"genre : "<< genre<< endl;
}

vector<Roman> Roman::initialiserVecteurRomans(){
    vector<Roman> romans;
    ifstream fichier("bd/livres/liste_romans");
    if (fichier.is_open()) {
        string ligne;
        while (getline(fichier, ligne)) {
            stringstream ss(ligne);
            string isbn, auteur, titre, editeur, etats, genre;
            getline(ss, isbn, ';');
            getline(ss, titre, ';');
            getline(ss, editeur, ';');
            getline(ss, auteur, ';');
            getline(ss, etats, ';');
            getline(ss, genre, ';');
            romans.push_back(Roman( auteur, titre, editeur, isbn, etats, genre));
        }
        fichier.close();
    } else {
        std::cerr << "Erreur : Impossible d'ouvrir le fichier." << std::endl;
    }
    return romans;
}

void    Roman::enregistrerVecteurRomans(vector<Roman> liste){
    fstream fichier("bd/livres/liste_romans", std::ios::in | std::ios::out );
    if (fichier.is_open()) {
        for (size_t i=0; i < liste.size();++i) {
                fichier <<liste[i].getIsbn()<<";"<<liste[i].getAuteur()<<";"<<liste[i].getTitre()<<";"<<liste[i].getEditeur()<<";"<<liste[i].getEtats()<<";"<<liste[i].getGenre()<<";" << std::endl;
        }
    fichier.close();
    } else {
        std::cerr << "Erreur lors de l'ouverture du fichier." << std::endl;
    }

}