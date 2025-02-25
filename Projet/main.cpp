#include "JeuDeLaVie/JeuDeLaVie.h"
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    if (argc < 3) { //Vérifie si l'utilisateur a renseigné suffisamment d'arguments
        std::cerr << "Usage: " << argv[0] << " <file_path> <mode (console/graphique)> [iterations]" << std::endl; //Affiche l'aide si l'utilisateur n'a pas renseigné suffisamment d'arguments
        return 1;
    }

    std::string filePath = argv[1]; //Récupère le chemin du fichier
    std::string mode = argv[2]; //Récupère le mode de jeu
    int maxIterations = (argc == 4) ? std::stoi(argv[3]) : 100; //Récupère le nombre d'itérations s'il est spécifié

    try { //Tente d'ouvrir le fichier
        JeuDeLaVie jeu(filePath, maxIterations); //Crée un objet JeuDeLaVie avec le chemin du fichier et le nombre d'itérations

        if (mode == "console") {
            jeu.executerModeConsole();
        } else if (mode == "graphique") {
            jeu.executerModeGraphique();
        } else { //Si le mode n'est pas reconnu, affiche un message d'erreur
            std::cerr << "Mode inconnu. Utilisez 'console' ou 'graphique'." << std::endl;
            return 1;
        }
    } catch (const std::exception& e) { //Si une exception est levée, affiche le message d'erreur
        std::cerr << "Erreur : " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
