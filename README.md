# Jeu de la vie de Conway

Simulation du **Jeu de la vie**, un automate cellulaire imaginé par le mathématicien John Conway. Le projet a été réalisé en C++ dans le cadre d'un projet de programmation orientée objet à CESI.

## Présentation

Le programme simule l'évolution d'une population de cellules sur une grille en deux dimensions. Chaque cellule possède deux états : vivante ou morte. À chaque génération, son nouvel état dépend de ses huit voisines.

Le projet propose deux modes d'exécution :
- **Console** : affiche les générations dans le terminal et sauvegarde chaque état dans un fichier texte.
- **Graphique** : visualise l'évolution de la grille dans une fenêtre SFML.

La grille utilise des **bords toriques** : les cellules situées sur un bord considèrent les cellules du bord opposé comme voisines.

## Règles du jeu

Pour chaque génération, les règles de Conway sont appliquées simultanément à toutes les cellules :

| Situation | Règle |
| --- | --- |
| Cellule vivante avec moins de 2 voisines vivantes | Elle meurt (isolement). |
| Cellule vivante avec 2 ou 3 voisines vivantes | Elle survit. |
| Cellule vivante avec plus de 3 voisines vivantes | Elle meurt (surpopulation). |
| Cellule morte avec exactement 3 voisines vivantes | Elle devient vivante (reproduction). |

## Technologies

- **C++**
- **Programmation orientée objet** : séparation des responsabilités entre les classes `Cellule`, `Grille` et `JeuDeLaVie`
- **SFML** : affichage graphique
- **Makefile** : compilation du projet

## Organisation du dépôt

```text
.
├── Projet/
│   ├── JeuDeLaVie/
│   │   ├── Cellule.h / Cellule.cpp
│   │   ├── Grille.h / Grille.cpp
│   │   └── JeuDeLaVie.h / JeuDeLaVie.cpp
│   ├── main.cpp
│   ├── Makefile
│   └── *.txt                 # Configurations initiales de grilles
└── README.md
```

## Prérequis

- Un compilateur C++ compatible avec **C++17** (par exemple `clang++` ou `g++`)
- **SFML 2.x** avec les composants Graphics, Window et System
- **GNU Make**

> Le Makefile fourni utilise actuellement `clang++` et les bibliothèques SFML installées sur le système.

## Compilation

Depuis le dossier `Projet` :

```bash
make
```

Pour supprimer les fichiers générés :

```bash
make clean
```

## Exécution

Depuis le dossier `Projet`, lancer le programme avec le chemin d'un fichier de grille, le mode souhaité et, facultativement, le nombre de générations :

```bash
./main glider.txt console 100
./main glider.txt graphique 100
```

Syntaxe :

```text
./main <fichier_grille> <console|graphique> [iterations]
```

Le nombre de générations est fixé à **100** lorsqu'il n'est pas précisé.

## Format des fichiers de grille

Les fichiers d'entrée sont des fichiers texte :
1. La première ligne contient la largeur et la hauteur.
2. Les lignes suivantes contiennent les états des cellules : `0` pour morte et `1` pour vivante.

Exemple de début de fichier pour une grille de 5 × 5 :

```text
5 5
0 1 0 0 0
0 0 1 0 0
1 1 1 0 0
0 0 0 0 0
0 0 0 0 0
```

## Sauvegarde

En mode console, chaque génération affichée est enregistrée dans le dossier `output/`, créé automatiquement à côté du programme lorsqu'il n'existe pas.

## Pistes d'amélioration

- Ajouter des tests automatisés pour les règles de transition.
- Permettre de modifier la vitesse de la simulation graphique.
- Ajouter des commandes pause / reprise et redémarrage.
- Rendre la taille de la fenêtre proportionnelle à celle de la grille.
- Proposer un choix entre bords toriques et bords fixes.

---

*Projet pédagogique — CESI, cycle préparatoire informatique (A2).*
