#include"Bd.h"
#include<iostream>
#include<string>
#include"fstream"
#include"sstream"

using namespace std;

Bd::Bd( string auteur, string titre, string editeur, string isbn, string etats, string dessinateur) : Livre( auteur, titre, editeur, isbn, etats){
    this->dessinateur= dessinateur ;
    setCategorie("bande dessinee");
}

Bd::Bd(){
}

void Bd::creerBdgraphique(){
    cout << "=== Création d'un roman === "<<endl;
    string auteur, titre, editeur, isbn, dessinateur;
    cout << " - Auteur : ";
    cin >> auteur;
    cout <<" - titre : ";
    cin >> titre;
    cout << " - Editeur : ";
    cin >> editeur;
    cout <<" - ISBN : ";
    cin >>isbn;
    cout <<" - Dessinateur : ";
    cin >> dessinateur;
    string etat = "libre";
    string line = isbn +';'+titre+';'+editeur+';'+auteur+';'+etat+';'+dessinateur+';';
    std::ofstream fichier("bd/livres/liste_bds", std::ios_base::app);
    fichier<<line<<endl;
    fichier.close();

}

string  Bd::getDessinateur(){
    return this->dessinateur;
}                                                                                                          

void    Bd::setDessinateur(string dessinateur){
    this->dessinateur = dessinateur;
}                                                                         

void    Bd::affiche (){
    Livre::affiche();
    cout<<"Dessinateur : "<< dessinateur<< endl;
}

vector<Bd> Bd::initialiserVecteurBd(){
    vector<Bd> bds;
    ifstream fichier("bd/livres/liste_bds");
    if (fichier.is_open()) {
        string ligne;
        while (getline(fichier, ligne)) {
            stringstream ss(ligne);
            string isbn, auteur, titre, editeur, etats, dessinateur;
            getline(ss, isbn, ';');
            getline(ss, titre, ';');
            getline(ss, editeur, ';');
            getline(ss, auteur, ';');
            getline(ss, etats, ';');
            getline(ss, dessinateur, ';');
            bds.push_back(Bd( auteur, titre, editeur, isbn, etats, dessinateur));
        }
        fichier.close();
    } else {
        std::cerr << "Erreur : Impossible d'ouvrir le fichier." << std::endl;
    }
    return bds;
}

void    Bd::enregistrerVecteurBd(vector<Bd> liste){
    fstream fichier("bd/livres/liste_bds", std::ios::in | std::ios::out );
    if (fichier.is_open()) {
        for (size_t i=0; i < liste.size();++i) {
                fichier <<liste[i].getIsbn()<<";"<<liste[i].getAuteur()<<";"<<liste[i].getTitre()<<";"<<liste[i].getEditeur()<<";"<<liste[i].getEtats()<<";"<<liste[i].getDessinateur()<<";" << std::endl;
        }
    fichier.close();
    } else {
        std::cerr << "Erreur lors de l'ouverture du fichier." << std::endl;
    }

}