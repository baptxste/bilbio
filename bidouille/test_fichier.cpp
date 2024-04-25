#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;

int main() {
    string entree_utilisateur;
    cout << "Entrez votre texte : ";
    getline(std::cin, entree_utilisateur);
    
    fstream fichier("../bd/test.txt", std::ios::in | std::ios::out | std::ios::app );
    if (fichier.is_open()) {
    // Écrire l'entrée de l'utilisateur dans le fichier
    fichier << entree_utilisateur << std::endl;
    std::cout << "L'entrée a été écrite dans le fichier avec succès." << std::endl;

    // Fermer le fichier
    fichier.close();
    } else {
        std::cerr << "Erreur lors de l'ouverture du fichier." << std::endl;
        return 1;
    }

    return 0;
}