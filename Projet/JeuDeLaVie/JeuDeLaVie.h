#ifndef JEUEDELAVIE_H
#define JEUEDELAVIE_H

#include "Grille.h"
#include <SFML/Graphics.hpp>
#include <string>

//Classe JeuDeLaVie
class JeuDeLaVie {
private:
    Grille grille; // grille de jeu
    sf::RenderWindow fenetre; //fenetre graphique
    int maxIterations;

    void afficherGrille();
    void sauvegarderEtat(int iteration);

public:
    JeuDeLaVie(const std::string& filePath, int maxIterations);
    void executerModeConsole();
    void executerModeGraphique();
};

#endif // JEUEDELAVIE_H
