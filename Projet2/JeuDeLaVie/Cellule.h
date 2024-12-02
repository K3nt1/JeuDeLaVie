#ifndef CELLULE_H
#define CELLULE_H

//Classe Cellule
class Cellule {
public:
    Cellule() : vivante(false) {}
    bool estVivante() const { return vivante; } //retourne vrai si la cellule est vivante -> getter
    void setVivante(bool etat) { vivante = etat; } //modifie l'etat de la cellule -> setter

private:
    bool vivante;
};

#endif // CELLULE_H
