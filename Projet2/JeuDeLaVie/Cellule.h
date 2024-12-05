#ifndef CELLULE_H
#define CELLULE_H

//Classe Cellule
class Cellule {
private:
    bool vivante;
    bool obstacle;
    
public:
    Cellule() : vivante(false), obstacle(false) {}
    bool estVivante() const{
        return vivante;
    } //retourne vrai si la cellule est vivante -> getter
    void setVivante(bool v){ 
        vivante = v; //modifie l'etat de la cellule -> setter
    }
    bool estObstacle() const{
        return obstacle;
    }
    void setObstacle(bool o){
        obstacle = o;
    }
};

#endif // CELLULE_H
