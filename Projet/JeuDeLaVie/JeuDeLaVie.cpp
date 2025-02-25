#include "JeuDeLaVie.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <thread> // Pour la fonction sleep

JeuDeLaVie::JeuDeLaVie(const std::string& filePath, int maxIterations)
    : grille(0, 0), fenetre(sf::VideoMode(503, 503), "Jeu de la Vie"), maxIterations(maxIterations) { // On crée la grille et la fenêtre
    grille.chargerDepuisFichier(filePath); // On charge la grille depuis le fichier
}

// Fonction pour sauvegarder l'état de la grille
void JeuDeLaVie::sauvegarderEtat(int iteration) {
    std::string folderName = "output"; // Nom du dossier de sauvegarde
    std::filesystem::create_directory(folderName); // Créer le dossier s'il n'existe pas

    std::ofstream outFile(folderName + "/iteration_" + std::to_string(iteration) + ".txt"); // Nom du fichier de sauvegarde
    grille.sauvegarderDansFichier(outFile); // Sauvegarder la grille dans le fichier
}

// Fonction pour lancer le jeu en mode console
void JeuDeLaVie::executerModeConsole() {
    for (int iteration = 0; iteration < maxIterations; ++iteration) { // Boucle sur les itérations
        std::cout << "Itération " << iteration << ":" << std::endl; // Afficher l'itération en cours
        grille.afficherConsole(); // Afficher la grille en console

        sauvegarderEtat(iteration); // Sauvegarder l'état de la grille

        if (!grille.mettreAJour()) { // Si la grille est stable, arrêter le jeu
            std::cout << "Aucune évolution. Fin de la simulation." << std::endl; // Afficher le message de fin
            break;
        }
    }
}

// Fonction pour lancer le jeu en mode graphique
void JeuDeLaVie::executerModeGraphique() {
    while (fenetre.isOpen()) { // Boucle sur l'ouverture de la fenêtre
        sf::Event event; // Variable pour stocker les événements
        while (fenetre.pollEvent(event)) { // Boucle sur les événements
            if (event.type == sf::Event::Closed) { // Si l'utilisateur ferme la fenêtre
                fenetre.close(); // Fermer la fenêtre
        }

        grille.mettreAJour(); // Mettre à jour la grille
        afficherGrille(); // Afficher la grille
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Pause entre itérations
        }
    }
}

// Fonction pour afficher la grille
void JeuDeLaVie::afficherGrille() {
    fenetre.clear(); // Effacer l'écran
    grille.afficher(fenetre); // Afficher la grille
    fenetre.display(); // Afficher la fenêtre
}
