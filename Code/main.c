/*
 * Bataille Navale
 * Christopher Pardo
 * 06.04.2019
 */
#include <stdio.h>
#include <windows.h>
#pragma execution_character_set( "utf-8" )

#define STLC 218 // ┌, Single Top Left Corner
#define STRC 191 // ┐, Single Top Right Corner
#define SBLC 192 // └, Single Bottom Left Corner
#define SBRC 217 // ┘, Single Bottom Right Corner
#define SVSB 179 // │, Single Vertical Simple Border
#define SVRB 180 // ┤, Single Vertical Right Border
#define SVLB 195 // ├, Single Vertical Left Border
#define SHSB 196 // ─, Single Horizontal Simple Border
#define SHBB 193 // ┴, Single Horizontal Bottom Border
#define SHTB 194 // ┬, Single Horizontal Top Border
#define SC   197 // ┼, Single Center

#define MaxGrile 10
#define MaxTour 30

int grille[MaxGrile][MaxGrile];
int win = 3;
int time = 0;
int hit[5];

void BateauxFichier(){
    int nombre_aleatoire;
    char c;

    nombre_aleatoire = 1 + rand() % 4;
    FILE *fichier = NULL;
    switch (nombre_aleatoire)
    {
        case 1:
            fichier = fopen("Grilles/Grille_1.txt", "r");
            break;
        case 2:
            fichier = fopen("Grilles/Grille_2.txt", "r");
            break;
        case 3:
            fichier = fopen("Grilles/Grille_3.txt", "r");
            break;
        case 4:
            fichier = fopen("Grilles/Grille_4.txt", "r");
            break;
    }

    for (int i = 0; i < MaxGrile; ++i) {
        for (int j = 0; j < MaxGrile; ++j) {
            do{
                c = fgetc(fichier);
                grille[i][j] = c - 48;
            }while(c <= 32);
        }
    }
    fclose(fichier);
}


void GrilleVide() {
    SetConsoleOutputCP(437);
    printf("\n\n    A   B   C   D   E   F   G   H   I   J\n");
    for (int i = 0; i < MaxGrile; i++) {
        printf("  ");
        if (i == 0) {
            printf("%c", STLC);
        } else {
            printf("%c", SVLB);
        }
        if (i == 0) {
            for (int k = 0; k < MaxGrile - 1; ++k) {
                printf("%c%c%c", SHSB, SHSB, SHSB);
                printf("%c", SHTB);
            }
            printf("%c%c%c", SHSB, SHSB, SHSB);
        } else {
            for (int k = 0; k < MaxGrile - 1; ++k) {
                printf("%c%c%c", SHSB, SHSB, SHSB);
                printf("%c", SC);
            }
            printf("%c%c%c", SHSB, SHSB, SHSB);
        }
        if (i == 0) {
            printf("%c", STRC);
        } else {
            printf("%c", SVRB);
        }
        printf("\n%d", i + 1);
        if (i < 9) {
            printf(" ");
        }
        for (int j = 0; j < MaxGrile; ++j) {
            //printf("test de [%d,%d] %d\n",i,j,grille[i][j]);
            if (grille[i][j] < 10) {
                printf("%c ~ ", SVSB);
            }
            else if(grille[i][j] < 20){
                printf("%c X ", SVSB);
            }
            else if(grille[i][j] == 100){
                printf("%c . ", SVSB);
            }
            else{
                printf("%c * ", SVSB);
            }
        }
        printf("%c\n", SVSB);
    }
    printf("  %c", SBLC);
    for (int l = 0; l < MaxGrile - 1; ++l) {
        printf("%c%c%c", SHSB, SHSB, SHSB);
        printf("%c", SHBB);
    }
    printf("%c%c%c", SHSB, SHSB, SHSB);
    printf("%c", SBRC);
    SetConsoleOutputCP(65001);
}

void Tire() {
    char tir[3];
    int verif = 0;
    int col;
    int ligne;

    while(verif != 1) {
        printf("Choisir une case  ");
        scanf("%s", &tir);
        printf("%d\n",strlen(tir));
        if(strlen(tir) == 3){
            col = 10*(tir[1] - 49) + (tir[2] - 49) + 10; //ICI
        }
        else{
            col = tir[1] - 49;
        }
        ligne = tir[0] - 65;
        while (col < 0 || col > 9 || ligne < 0 || ligne > 9 || strlen(tir) > 3 ) {
            printf("Il n'y a pas de case ici\n\n");
            printf("Choisir une case");
            scanf("%s", &tir);

            if(strlen(tir) == 3){
                col = 10*(tir[1] - 49) + (tir[2] - 49) + 10; //ICI
            }
            else{
                col = tir[1] - 49;
            }
            ligne = tir[0] - 65;
        }

        if (grille[col][ligne] < 10 && grille[col][ligne] > 0) {
            system("cls");
            printf("Touché");
            grille[col][ligne] = grille[col][ligne] + 10;
            verif = 1;
            time += 1;
        } else if (grille[col][ligne] > 9) {
            printf("Vous ne pouvez pas tirer 2 fois sur la même case\n\n");
        } else {
            system("cls");
            printf("À l'eau");
            grille[col][ligne] = 100;
            verif = 1;
            time += 1;
        }
    }
    for (int i = 1; i < 5; ++i) {
        if(grille[col][ligne] == i+10){
            hit[i]++;
            if(hit[i] == i){
                printf(" Coulé");
                win--;
                for (int x = 0; x < MaxGrile; ++x) {
                    for (int y = 0; y < MaxGrile; ++y) {
                        if(grille[x][y] == i+10){
                            grille[x][y] = grille[x][y] + 10;
                        }
                    }
                }
            }
        }
    }
}

int main() {
    SetConsoleOutputCP(65001);
    char choice[1];

    while (1) {
        printf("\n1. Afficher la grille");
        printf("\n2. Afficher les règles");
        printf("\n3. Quitter");
        printf("\n\n\tVotre choix:");
        scanf("%s", &choice);

        if (strcmp(choice, "1")  == 0) {
            system("cls");
            BateauxFichier();
            while(win != 0 && time <= MaxTour) {
                GrilleVide();
                printf("\nIl vous reste %d tours\n\n",MaxTour - time);
                Tire();
            }
            if(win == 0){
                printf("\n\n\t         _________ _______ _________ _______ _________ _______  _______ \n"
                       "\t|\\     /|\\__   __/(  ____ \\\\__   __/(  ___  )\\__   __/(  ____ )(  ____ \\\n"
                       "\t| )   ( |   ) (   | (    \\/   ) (   | (   ) |   ) (   | (    )|| (    \\/\n"
                       "\t| |   | |   | |   | |         | |   | |   | |   | |   | (____)|| (__    \n"
                       "\t( (   ) )   | |   | |         | |   | |   | |   | |   |     __)|  __)   \n"
                       "\t \\ \\_/ /    | |   | |         | |   | |   | |   | |   | (\\ (   | (      \n"
                       "\t  \\   /  ___) (___| (____/\\   | |   | (___) |___) (___| ) \\ \\__| (____/\\\n"
                       "\t   \\_/   \\_______/(_______/   )_(   (_______)\\_______/|/   \\__/(_______/\n"
                       "\t                                                                        \n\n");
            }
            else if(time > MaxTour){
                printf("\nVous avez dépassé le nombre maximal de tours");
                printf("\n\n\t ______   _______  _______  _______ __________________ _______ \n"
                       "\t(  __  \\ (  ____ \\(  ____ \\(  ___  )\\__   __/\\__   __/(  ____ \\\n"
                       "\t| (  \\  )| (    \\/| (    \\/| (   ) |   ) (      ) (   | (    \\/\n"
                       "\t| |   ) || (__    | (__    | (___) |   | |      | |   | (__    \n"
                       "\t| |   | ||  __)   |  __)   |  ___  |   | |      | |   |  __)   \n"
                       "\t| |   ) || (      | (      | (   ) |   | |      | |   | (      \n"
                       "\t| (__/  )| (____/\\| )      | )   ( |___) (___   | |   | (____/\\\n"
                       "\t(______/ (_______/|/       |/     \\|\\_______/   )_(   (_______/\n"
                       "\t                                                               \n\n");
            }
            system("pause");
            return 0;
        } else if (strcmp(choice, "2")  == 0) {
            system("cls");
            printf("\n\nLa bataille navale oppose deux joueurs qui s'affrontent."
                   "\nChacun a une flotte composee de 3 bateaux, qui sont, en general, les suivants :\n1 porte-avion (5 cases)\n1 croiseur (4 cases)"
                   "\nUn a un, les joueurs vont tirer sur une case de l'adversaire.");
            choice[1] = -1;
            printf("\n\n");
            system("pause");
            system("cls");
        } else if (strcmp(choice, "3")  == 0) {
            return 0;
        } else {
            system("cls");
            printf("Ce n'est pas un chois possible"
                   "\n\nEntrez une valeure entre 1 et 3\n");
            choice[1] = -1;
        }
    }
}