#include "JeuDeLaVie.h"

#include <iostream>
#include <thread>
#include <chrono>
#include <filesystem>
#include <fstream>
#include <stdexcept>

JeuDeLaVie::JeuDeLaVie(const std::string& filePath, int maxIterations)
    : grille(0, 0),
      fenetre(sf::VideoMode(503, 503), "Jeu de la Vie"),
      maxIterations(maxIterations) {
    if (maxIterations <= 0) {
        throw std::invalid_argument("Le nombre d'iterations doit etre positif.");
    }

    grille.chargerDepuisFichier(filePath);
}

void JeuDeLaVie::sauvegarderEtat(int iteration) {
    const std::filesystem::path outputDirectory("output");
    std::filesystem::create_directories(outputDirectory);

    std::ofstream outFile(outputDirectory / ("iteration_" + std::to_string(iteration) + ".txt"));
    if (!outFile) {
        throw std::runtime_error("Impossible de sauvegarder l'iteration " + std::to_string(iteration));
    }

    grille.sauvegarderDansFichier(outFile);
}

void JeuDeLaVie::executerModeConsole() {
    for (int iteration = 0; iteration < maxIterations; ++iteration) {
        std::cout << "Iteration " << iteration << ":\n";
        grille.afficherConsole();
        sauvegarderEtat(iteration);

        if (!grille.mettreAJour()) {
            std::cout << "Aucune evolution. Fin de la simulation.\n";
            break;
        }
    }
}

void JeuDeLaVie::executerModeGraphique() {
    fenetre.setFramerateLimit(10);

    int iteration = 0;
    while (fenetre.isOpen() && iteration < maxIterations) {
        sf::Event event;
        while (fenetre.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                fenetre.close();
            }
        }

        if (!fenetre.isOpen()) {
            break;
        }

        afficherGrille();

        if (!grille.mettreAJour()) {
            break;
        }

        ++iteration;
    }
}

void JeuDeLaVie::afficherGrille() {
    fenetre.clear(sf::Color::Black);
    grille.afficher(fenetre);
    fenetre.display();
}
