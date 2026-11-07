#include "../JeuDeLaVie/Grille.h"

#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

namespace {
int testsReussis = 0;
int testsEchoues = 0;

void verifier(bool condition, const std::string& nom) {
    if (condition) {
        ++testsReussis;
        std::cout << "[OK] " << nom << '\n';
    } else {
        ++testsEchoues;
        std::cerr << "[ECHEC] " << nom << '\n';
    }
}

std::string creerGrille(const std::string& nom, const std::string& contenu) {
    const std::string chemin = "test_" + nom + ".txt";
    std::ofstream fichier(chemin);
    fichier << contenu;
    fichier.close();
    return chemin;
}

void testBlocStable() {
    const std::string chemin = creerGrille(
        "bloc",
        "5 5\n"
        "0 0 0 0 0\n"
        "0 1 1 0 0\n"
        "0 1 1 0 0\n"
        "0 0 0 0 0\n"
        "0 0 0 0 0\n");

    Grille grille(0, 0);
    grille.chargerDepuisFichier(chemin);
    verifier(!grille.mettreAJour(), "Un bloc de 2x2 reste stable");
    std::remove(chemin.c_str());
}

void testOscillateurBlinker() {
    const std::string chemin = creerGrille(
        "blinker",
        "5 5\n"
        "0 0 0 0 0\n"
        "0 0 1 0 0\n"
        "0 0 1 0 0\n"
        "0 0 1 0 0\n"
        "0 0 0 0 0\n");

    Grille grille(0, 0);
    grille.chargerDepuisFichier(chemin);

    std::ostringstream premiereGeneration;
    const bool premierChangement = grille.mettreAJour();
    grille.sauvegarderDansFichier(premiereGeneration);
    verifier(premierChangement, "Le blinker evolue a la premiere generation");
    verifier(
        premiereGeneration.str() ==
            "5 5\n"
            "0 0 0 0 0 \n"
            "0 0 0 0 0 \n"
            "0 1 1 1 0 \n"
            "0 0 0 0 0 \n"
            "0 0 0 0 0 \n",
        "Le blinker devient horizontal");

    const bool deuxiemeChangement = grille.mettreAJour();
    std::ostringstream deuxiemeGeneration;
    grille.sauvegarderDansFichier(deuxiemeGeneration);
    verifier(deuxiemeChangement, "Le blinker evolue a la deuxieme generation");
    verifier(
        deuxiemeGeneration.str() ==
            "5 5\n"
            "0 0 0 0 0 \n"
            "0 0 1 0 0 \n"
            "0 0 1 0 0 \n"
            "0 0 1 0 0 \n"
            "0 0 0 0 0 \n",
        "Le blinker retrouve sa forme verticale");
    std::remove(chemin.c_str());
}

void testGrilleVide() {
    const std::string chemin = creerGrille(
        "vide",
        "5 5\n"
        "0 0 0 0 0\n"
        "0 0 0 0 0\n"
        "0 0 0 0 0\n"
        "0 0 0 0 0\n"
        "0 0 0 0 0\n");

    Grille grille(0, 0);
    grille.chargerDepuisFichier(chemin);
    verifier(!grille.mettreAJour(), "Une grille vide reste inchangee");
    std::remove(chemin.c_str());
}

void testFichierAbsent() {
    Grille grille(0, 0);
    bool exceptionLevee = false;
    try {
        grille.chargerDepuisFichier("fichier_de_test_inexistant.txt");
    } catch (const std::runtime_error&) {
        exceptionLevee = true;
    }
    verifier(exceptionLevee, "Le chargement d'un fichier absent signale une erreur");
}
} // namespace

int main() {
    testBlocStable();
    testOscillateurBlinker();
    testGrilleVide();
    testFichierAbsent();

    std::cout << "\nResultat : " << testsReussis << " reussi(s), "
              << testsEchoues << " echoue(s).\n";
    return testsEchoues == 0 ? 0 : 1;
}
