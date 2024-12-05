#ifndef GRILLE_H
#define GRILLE_H

#include "Cellule.h"
#include <vector> // Pour utiliser la classe vector
#include <fstream> // Pour utiliser la classe ifstream
#include <SFML/Graphics.hpp> // Pour utiliser la classe sf::RectangleShape

//Classe Grille
class Grille {
private:
    int largeur;
    int hauteur;
    std::vector<std::vector<Cellule>> cellules; //Matrice de cellules
    int compterVoisinsVivants(int x, int y) const; //Compter le nombre de voisins vivants
    
public:
    Grille(int largeur, int hauteur);
    void chargerDepuisFichier(const std::string& filePath); //Charger une grille depuis un fichier
    void sauvegarderDansFichier(std::ostream& out) const; //Sauvegarder une grille dans un fichier
    void initialiser(); //Initialiser la grille
    bool mettreAJour(); //Mettre à jour la grille
    void afficher(sf::RenderWindow &fenetre) const; //Afficher la grille
    void afficherConsole() const; //Afficher la grille dans la console
};

#endif // GRILLE_H
