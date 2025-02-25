#include "Grille.h"
#include <iostream>
#include <cstdlib> // Pour les fonctions de manipulation de chaînes de caractères
#include <sstream> // Pour les fonctions de manipulation de chaînes de caractères

Grille::Grille(int largeur, int hauteur) : largeur(largeur), hauteur(hauteur), cellules(largeur, std::vector<Cellule>(hauteur)) {}

// Chargement d'une grille à partir d'un fichier
void Grille::chargerDepuisFichier(const std::string& filePath) {
    std::ifstream inFile(filePath); // Ouvrir le fichier en lecture seule
    if (!inFile)
        throw std::runtime_error("Impossible de lire le fichier : " + filePath);

    inFile >> largeur >> hauteur; // Lecture de la largeur et de la hauteur de la grille
    cellules = std::vector<std::vector<Cellule>>(largeur, std::vector<Cellule>(hauteur)); // Initialisation de la grille avec des cellules vides

    for (int y = 0; y < hauteur; ++y) { // Lecture de chaque ligne du fichier
        for (int x = 0; x < largeur; ++x) { // Lecture de chaque cellule de la ligne
            int etat;
            inFile >> etat; // Lecture de l'état de la cellule (0 ou 1)
            cellules[x][y].setVivante(etat == 1); // Mise à jour de l'état de la cellule
        }
    }
}

// Sauvegarde de la grille dans un fichier
void Grille::sauvegarderDansFichier(std::ostream& out) const { 
    out << largeur << " " << hauteur << "\n"; // Ecriture de la largeur et de la hauteur de la grille
    for (int y = 0; y < hauteur; ++y) { // Ecriture de chaque ligne de la grille
        for (int x = 0; x < largeur; ++x) { // Ecriture de chaque cellule de la ligne
            out << (cellules[x][y].estVivante() ? "1" : "0") << " "; // Ecriture de l'état de la cellule
        }
        out << "\n"; 
    }
}

// Affichage de la grille dans la console
void Grille::afficherConsole() const { 
    for (int y = 0; y < hauteur; ++y) { // Affichage de chaque ligne de la grille
        for (int x = 0; x < largeur; ++x) { // Affichage de chaque cellule de la ligne
            std::cout << (cellules[x][y].estVivante() ? "1" : "0") << " "; // Affichage de l'état de la cellule
        }
        std::cout << "\n";
    }
}

// Mettre à jour la grille selon les règles du jeu de la vie
bool Grille::mettreAJour() { 
    std::vector<std::vector<Cellule>> nouvelleGrille = cellules; // Création d'une copie de la grille actuelle
    bool aChange = false; // Indicateur de changement dans la grille

    for (int x = 0; x < largeur; ++x) { // Mise à jour de chaque cellule de la grille
        for (int y = 0; y < hauteur; ++y) { // Mise à jour de chaque cellule de la ligne
            int voisinsVivants = compterVoisinsVivants(x, y);
            bool etatActuel = cellules[x][y].estVivante(); // Récupération de l'état actuel de la cellule
            bool nouvelEtat = etatActuel; // Initialisation de l'état nouveau de la cellule

            if (etatActuel) { // Si la cellule est vivante
                nouvelEtat = (voisinsVivants == 2 || voisinsVivants == 3); // Application de la règle de survie
            } else {
                nouvelEtat = (voisinsVivants == 3); // Application de la règle de naissance
            }

            nouvelleGrille[x][y].setVivante(nouvelEtat); // Mise à jour de l'état de la cellule

            // Vérifie si l'état de la cellule a changé
            if (etatActuel != nouvelEtat) {
                aChange = true; // Indique que la grille a changé
            }
        }
    }

    cellules = nouvelleGrille; // Mise à jour de la grille actuelle avec la nouvelle grille
    return aChange;
}

// Compte le nombre de voisins vivants de la cellule
int Grille::compterVoisinsVivants(int x, int y) const { 
    int compte = 0;
    for (int dx = -1; dx <= 1; ++dx) { // Boucle sur les directions possibles
        for (int dy = -1; dy <= 1; ++dy) {
            if (dx == 0 && dy == 0) continue; // Ignore la cellule elle-même
            int nx = (x + dx + largeur) % largeur; // Gestion des bords (grille torique)
            int ny = (y + dy + hauteur) % hauteur;
            if (cellules[nx][ny].estVivante()) {
                ++compte;
            }
        }
    }
    return compte;
}

void Grille::afficher(sf::RenderWindow &fenetre) const {
    sf::RectangleShape cellule(sf::Vector2f(9.0f, 9.0f)); // Taille des cellules
    cellule.setFillColor(sf::Color::White); 

    for (int x = 0; x < largeur; ++x) { // Affichage de chaque cellule de la grille
        for (int y = 0; y < hauteur; ++y) { // Affichage de chaque cellule de la ligne
            if (cellules[x][y].estVivante()) { // Si la cellule est vivante
                cellule.setPosition(x * 10, y * 10); // Position de la cellule
                fenetre.draw(cellule); // Affichage de la cellule
            }
        }
    }
}
