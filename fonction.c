// functions.c
// functions.c
// Ce fichier contient les définitions des fonctions pour le jeu UDBL - DACTYLOGICIEL.
// Il inclut des fonctions pour l'affichage de l'écran de démarrage, les menus, le chargement de mots, et le jeu lui-même.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "fonction.h"

#define MAX_WORDS 100
#define WORD_LENGTH 100
#define PASSWORD "admin123"
#define WORDS_FILE "words.txt"
#define MAX_WORD_LENGTH 100
// Fonction pour introduire un délai en secondes.
// Utilise une boucle basée sur le temps pour attendre le nombre spécifié de secondes.

void delay(int seconds) {
    int milli_seconds = 1000 * seconds;
    clock_t start_time = clock();
    while (clock() < start_time + milli_seconds);
}
// Affiche l'écran les noms des menbres du groupe et le nom du logiciel.

void displayLaunchScreen() {
    printf("\n\n\n\t\t\tUDBL - DACTYLOGICIEL\n");
    printf("\t\t\tMembres de l'Equipe:\n");
    printf("\t\t\tNGOY KASONGO EPIPHANIE\n");
    printf("\t\t\tNGOY KIMBA GLODI\n");
    printf("\t\t\tTUMBA KASEMWANA ARSENE\n");
    printf("\t\t\tMUMBA MULUMBWA ZANELA\n");
    delay(5);
    system("clear");  // Attend quelques secondes avant de nettoyer l'écran.
}

 // Affiche le menu principal du jeu et gère les choix de l'utilisateur.
// Permet de démarrer le jeu, configurer, obtenir de l'aide ou quitter.

void displayMainMenu() {
    int choice;
    do {
        printf("\nMenu Principal\n");
        printf("1. DEMARAGE\n");
        printf("2. CONFIGURER\n");
        printf("3. AIDE\n");
        printf("4. QUITTER\n");
        printf("Choisissez une option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                startGame();
                break;
            case 2:
                displayConfigMenu();
                break;
            case 3:
                displayHelpMenu();
                break;
            case 4:
                printf("AU REVOIR!\n");
                exit(0);
            default:
                printf("Choix INVALIDE. REESSEYEZ.\n");
        }
    } while (choice != 4);
}
// Affiche le menu d'aide avec des informations sur l'application et ses concepteurs.


void displayHelpMenu() {
    printf("\nAIDE\n");
    printf("Description de l'application: Amelioration de la saisie rapide au clavier\n");
    printf("Version du Jeu: 1.0\n");
    printf("Concepteurs: NGOY KASONGO EPIPHANIE,NGOY KIMBA GLODI,TUMBA KASEMWANA ARSENE, MUMBA MULUMBWA ZANELA\n");
    printf("Date de conception: 2024\n");
    printf("Autres informations: Utilisation de C pour la programmation\n");
}
// Affiche le menu de configuration où l'utilisateur peut ajouter des mots au jeu après authentification.


void displayConfigMenu() {
    char password[20];
    char word[MAX_WORD_LENGTH];

    printf("Entrez le mot de passe: ");
    scanf("%s", password);

    if (strcmp(password, PASSWORD) == 0) {
        FILE *file = fopen(WORDS_FILE, "a");
        if (!file) {
            printf("Erreur d'ouverture du fichier\n");
            return;
        }

        printf("Entrez les mots � ajouter (entrez 'fin' pour terminer): \n");
        while (1) {
            printf("Mot: ");
            scanf("%s", word);
            if (strcmp(word, "fin") == 0) break;
            fprintf(file, "%s\n", word);
        }

        fclose(file);
    } else {
        printf("Mot de passe incorrect\n");
    }
}


// Charge les mots à partir du fichier spécifié dans une matrice de chaînes de caractères.
// Retourne le nombre de mots chargés avec succès.


int loadWords(char words[MAX_WORDS][WORD_LENGTH]) {
    FILE *file = fopen(WORDS_FILE, "r");
    if (!file) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return 0;
    }

    int count = 0;
    while (fscanf(file, "%s", words[count]) != EOF && count < MAX_WORDS) {
        count++;
    }

    fclose(file);
    return count;
}

// Démarre le jeu principal où deux joueurs entrent des mots tapés à partir d'un fichier de mots.
// Chronomètre le temps et calcule les scores pour chaque joueur.




void startGame() {
    int numWords;
    char words[MAX_WORDS][WORD_LENGTH];
    int wordCount = loadWords(words);
    time_t start1, end1, start2, end2;
    char player1[50], player2[50];
    char word[MAX_WORD_LENGTH];
    char input[MAX_WORD_LENGTH];
    int score1 = 0, score2 = 0;
    // Démarre le jeu principal où deux joueurs entrent des mots tapés à partir d'un fichier de mots.



    if (wordCount == 0) {
        printf("Aucun mot trouvé. Veuillez configurer le jeu d'abord.\n");
        return;
    }

    FILE *file = fopen(WORDS_FILE, "r");

    if (!file) {
        printf("Erreur d'ouverture du fichier des mots\n");
        return;
    }

    printf("Entrez le nombre de mots � saisir: ");
    scanf("%d", &numWords);

    printf("Entrez le pseudo du joueur 1: ");
    scanf("%s", player1);
    printf("Entrez le pseudo du joueur 2: ");
    scanf("%s", player2);

    srand(time(NULL));
    printf("\nJeu commence pour %s\n", player1);
    int i;
    start1 = time(NULL);
    for (i = 0; i < numWords; i++) {
        fseek(file, 0, SEEK_SET);
        int r = rand() % wordCount;
        int j;
        for (j = 0; j <= r; j++) {
            fscanf(file, "%s", word);
        }
        printf("Mot %d: %s\n", i + 1, word);
        printf("Tapez le mot: ");
        scanf("%s", input);
        while (strcmp(input, word) != 0) {
            score1 += 1;
            printf("Incorrect, retapez le mot: ");
            scanf("%s", input);
        }
        score1 += 1;
    }
    end1 = time(NULL);

    printf("\nAttente de 1 minute avant le prochain joueur\n");
    delay(5);

    printf("\nJeu commence pour %s\n", player2);
    int a;
    start2 = time(NULL);
    for (a = 0; a < numWords; a++) {
        fseek(file, 0, SEEK_SET);
        int r = rand() % wordCount;
        int j;
        for (j = 0; j <= r; j++) {
            fscanf(file, "%s", word);
        }
        printf("Mot %d: %s\n", a + 1, word);
        printf("Tapez le mot: ");
        scanf("%s", input);
        while (strcmp(input, word) != 0) {
            score2 += 1;
            printf("Incorrect, retapez le mot: ");
            scanf("%s", input);
        }
        score2 += 1;
    }
    end2 = time(NULL);

    fclose(file);

     // Affichage des resultats la personne qui a etait plus rapide que l'autre
     // Démarre le jeu principal où deux joueurs entrent des mots tapés à partir d'un fichier de mots.
// Chronomètre le temps et calcule les scores pour chaque joueur.

    double time1 = difftime(end1, start1);
    double time2 = difftime(end2, start2);
    printf("\nR�sultats:\n");
    printf("%s: %.2f secondes\n", player1, time1);
    printf("%s: %.2f secondes\n", player2, time2);

    printf("\nScores:\n%s: %d\n%s: %d\n", player1, score1, player2, score2);
    //Affiche les resultats qui cadre avec less temps
    if (time1 < time2) {
        printf("%s est plus rapide!\n", player1);
    } else if (time2 < time1) {
        printf("%s est plus rapide!\n", player2);
    } else {
        printf("Les deux joueurs sont aussi rapides!\n");
    }
}








