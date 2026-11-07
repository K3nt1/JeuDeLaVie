# Jeu de la vie de Conway

Simulation du **Jeu de la vie**, un automate cellulaire imaginé par le mathématicien John Conway. Le projet a été réalisé en C++ dans le cadre d'un projet de programmation orientée objet à CESI.

## Présentation

Le programme simule l'évolution d'une population de cellules sur une grille en deux dimensions. Chaque cellule possède deux états : vivante ou morte. À chaque génération, son nouvel état dépend de ses huit voisines.

Le projet propose deux modes d'exécution :
- **Console** : affiche les générations dans le terminal et sauvegarde chaque état dans un fichier texte.
- **Graphique** : visualise l'évolution de la grille dans une fenêtre SFML.

La grille utilise des **bords toriques** : les cellules situées sur un bord considèrent les cellules du bord opposé comme voisines.

## Aperçu

Les captures d'écran de l'application seront ajoutées dans `docs/images/` après une exécution locale du programme. Elles doivent montrer l'application réelle, et non une maquette.

<!-- Ajouter les captures réelles ici après les avoir placées dans docs/images/.
Exemple :
![Mode graphique](docs/images/mode-graphique.png)
![Mode console](docs/images/mode-console.png)
-->

## Règles du jeu

Pour chaque génération, les règles de Conway sont appliquées simultanément à toutes les cellules :

| Situation | Règle |
| --- | --- |
| Cellule vivante avec moins de 2 voisines vivantes | Elle meurt (isolement). |
| Cellule vivante avec 2 ou 3 voisines vivantes | Elle survit. |
| Cellule vivante avec plus de 3 voisines vivantes | Elle meurt (surpopulation). |
| Cellule morte avec exactement 3 voisines vivantes | Elle devient vivante (reproduction). |

## Technologies

- **C++17**
- **Programmation orientée objet** : séparation des responsabilités entre les classes `Cellule`, `Grille` et `JeuDeLaVie`
- **SFML 2.x** : affichage graphique
- **GNU Make** : compilation et exécution des tests

## Organisation du dépôt

```text
.
├── Projet/
│   ├── JeuDeLaVie/
│   │   ├── Cellule.h / Cellule.cpp
│   │   ├── Grille.h / Grille.cpp
│   │   └── JeuDeLaVie.h / JeuDeLaVie.cpp
│   ├── tests/
│   │   └── test_grille.cpp
│   ├── main.cpp
│   └── Makefile
├── docs/
│   └── images/                 # Captures d'écran de l'application
└── README.md
```

## Prérequis

- Un compilateur C++17 (par exemple `clang++` ou `g++`)
- **SFML 2.x** avec les composants Graphics, Window et System
- **GNU Make**

Le Makefile fourni utilise `clang++` et les bibliothèques SFML installées sur le système.

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

## Tests unitaires

Des tests automatisés vérifient le comportement du moteur de simulation :

- stabilité d'un bloc de quatre cellules ;
- évolution d'un oscillateur « blinker » sur deux générations ;
- stabilité d'une grille vide ;
- gestion d'un fichier de grille introuvable.

Depuis le dossier `Projet` :

```bash
make test
```

Le programme de test affiche le résultat de chaque vérification et renvoie un code d'erreur si au moins un test échoue. Les tests utilisent SFML car la classe `Grille` inclut actuellement son module graphique.

## Format des fichiers de grille

Les fichiers d'entrée sont des fichiers texte :
1. La première ligne contient la largeur et la hauteur.
2. Les lignes suivantes contiennent les états des cellules : `0` pour morte et `1` pour vivante.

Exemple de grille de 5 × 5 :

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

---

*Projet pédagogique — CESI, cycle préparatoire informatique (A2).*
