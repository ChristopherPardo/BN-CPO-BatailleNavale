/*
 * Bataille Navale
 * Christopher Pardo
 * 07.04.2019
 */
#include <stdio.h>
#include <windows.h>
#include <time.h>
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

#define MaxGrile 10 //Nombre max de case pas ligne et par colonnes
#define MaxTour 30 //Nombre max de tours

int grille[MaxGrile][MaxGrile]; //Grille en deux dimensions
int win = 3; //Compteur du bateaux qu'il faut toucher
int tour = 0; //Nombre de tours passé
int hit[5]; //Tableau de tir

void BateauxFichier(){
    int nombre_aleatoire; //Nombre aléatoire
    char c;

    srand( (unsigned)time( NULL ) );
    nombre_aleatoire = 1 + rand() % 4; //Choisit un nombre aléatoire entre 1 et 4
    FILE *fichier = NULL;
    switch (nombre_aleatoire)
    {
        //-----------------Grilles possibles-----------------------
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

    //---------------Pour que les caractères autres que des nombres ne soient pas pris en compte---------------
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

//-----------------------Fonction d'affichage de la grille------------------------
void GrilleVide() {
    SetConsoleOutputCP(437);
    //-------------Haut de la grille----------------
    printf("\n\n    A   B   C   D   E   F   G   H   I   J\n");
    for (int i = 0; i < MaxGrile; i++) {
        printf("  ");
        if (i == 0) {
            printf("%c", STLC);
        } else {
            printf("%c", SVLB);
        }
        //-----------------Colonne du haut---------------------
        if (i == 0) {
            for (int k = 0; k < MaxGrile - 1; ++k) {
                printf("%c%c%c", SHSB, SHSB, SHSB);
                printf("%c", SHTB);
            }
            printf("%c%c%c", SHSB, SHSB, SHSB);
        }
        //-----------------Colonnes du milieux------------------
        else {
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
        //-----------------Change le symbole en fonction de la valeur--------------------
        for (int j = 0; j < MaxGrile; ++j) {
            //printf("test de [%d,%d] %d\n",i,j,grille[i][j]);
            if (grille[i][j] < 10) {
                printf("%c   ", SVSB);
            }
            else if(grille[i][j] < 20){
                printf("%c X ", SVSB);
            }
            else if(grille[i][j] == 100){
                printf("%c O ", SVSB);
            }
            else{
                printf("%c * ", SVSB);
            }
        }
        printf("%c\n", SVSB);
    }
    //-----------------------Colonne du bas---------------------------
    printf("  %c", SBLC);
    for (int l = 0; l < MaxGrile - 1; ++l) {
        printf("%c%c%c", SHSB, SHSB, SHSB);
        printf("%c", SHBB);
    }
    printf("%c%c%c", SHSB, SHSB, SHSB);
    printf("%c", SBRC);
    //---------légende des symboles---------
    SetConsoleOutputCP(65001);
    printf("\n\n* : Coulé\n"
           "O : À l'eau\n"
           "X : Touché\n");
}

//-----------------------Fontion de tire-----------------------
void Tire() {
    char tir[3]; //Valeurs du tire
    int verif = 0; //verification de la valeur entrée
    int col; //Valeur de la colonne
    int ligne; //Valeur de la ligne

    while(verif != 1) {
        printf("Choisir une case : ");
        scanf("%s", &tir);
        printf("%d\n",strlen(tir));
        //-------Tire en minuscule-------
        if(tir[0] <= 106 && tir[0] >= 97){
            tir[0] -= 32;
        }
        //---------Changement des valeurs entrées par l'utilisateur-----------
        if(strlen(tir) == 3){
            col = 10*(tir[1] - 49) + (tir[2] - 49) + 10; //ICI
        }
        else{
            col = tir[1] - 49;
        }
        ligne = tir[0] - 65;
        //--------------------si une valeur n'est pas reconnu---------------------------
        while (col < 0 || col > 9 || ligne < 0 || ligne > 9 || strlen(tir) > 3 ) {
            printf("\nIl n'y a pas de case ici\n\n");
            printf("Choisir une case : ");
            scanf("%s", &tir);

            if(tir[0] <= 106 && tir[0] >= 97){
                tir[0] -= 32;
            }

            if(strlen(tir) == 3){
                col = 10*(tir[1] - 49) + (tir[2] - 49) + 10;
            }
            else{
                col = tir[1] - 49;
            }
            ligne = tir[0] - 65;
        }

        //-------------------Touché----------------
        if (grille[col][ligne] < 10 && grille[col][ligne] > 0) {
            system("cls");
            printf("\nTouché");
            grille[col][ligne] = grille[col][ligne] + 10;
            verif = 1;
            if(MaxTour - tour == 1){
                tour += 2;
            }
            else{
                tour += 1;
            }
            //--------------------Si la case n'est pas dans la grille----------------
        } else if (grille[col][ligne] > 9) {
            printf("\nVous ne pouvez pas tirer 2 fois sur la même case\n\n");
            //-------------À l'eau---------------
        }
        else{
            system("cls");
            printf("\nÀ l'eau");
            grille[col][ligne] = 100;
            verif = 1;
            if(MaxTour - tour == 1){
                tour += 2;
            }
            else{
                tour += 1;
            }
        }
    }
    //-----------------Coulé------------------
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

//-----------------------Fontcion principale-----------------------
int main() {
    SetConsoleOutputCP(65001);
    char choice[1];

    while (1) {
        //----------------Image de début--------------------
        printf("\n\t\n"
               "                                             .\n"
               "                           .                 |\n"
               "                           +                 |\n"
               "                  .        |                *+W+-*\n"
               "     .           +y        +W+              . H                 .\n"
               "  .  +y            |I.   y  |               ! H= .           .  ^\n"
               "  !   \\     .     |H '. /   |  ___.        .! H  !   +--.--y !  V\n"
               "  !    \\     \\  +=|H|=='.=+ | |====\\   _  '_H_H__H_. H_/=  J !  !\n"
               ". !     \\'    VVV_HHH_/__'._H |  E  \\_|=|_|========|_|==|____H. ! _______.\n"
               "I-H_I=I=HH_==_|I_IIIII_I_I_=HH|======.I-I-I-=======-I=I=I=I_=H|=H'===I=I/\n"
               "\\                                                                      ,\n"
               " |                                                                    /\n"
               " .___________________________________________________________________'\n");
        //--------------Menu de début--------------------
        printf("\n\n1. Afficher la grille");
        printf("\n2. Afficher les règles");
        printf("\n3. Quitter");
        printf("\n\n\tVotre choix : ");
        scanf("%s", &choice);

        if (strcmp(choice, "1")  == 0) {
            system("cls");
            BateauxFichier();
            while(win != 0 && tour <= MaxTour) {
                GrilleVide();
                printf("\nIl vous reste %d tours\n\n",MaxTour - tour);
                Tire();
            }
            //--------------------Victoire-------------
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
            //---------------------Défaite-----------------
            else if(tour > MaxTour){
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
            //------------------Règles----------------------
        } else if (strcmp(choice, "2")  == 0) {
            system("cls");
            printf("\nLa bataille navale est un jeux dans le but est de coulé tous les bateaux\ndans une grille de"
                   "10 par 10 en 30 tours ou moins.\n\nIl y a une bateau de 2 cases, un bateau de 3 cases et un bateau"
                   "de 4 cases.\n\nIl faut enterer les valeur de la case souhaité pour lui tirer dessus.\n\n"
                   "Exemple : A1\n");
            choice[1] = -1;
            printf("\n\n");
            system("pause");
            system("cls");
            //---------------Quitter----------------
        } else if (strcmp(choice, "3")  == 0) {
            return 0;
            //----------------Le chois n'est pas dans les chois proposés----------------
        } else {
            system("cls");
            printf("Ce n'est pas un chois possible"
                   "\n\nEntrez une valeur entre 1 et 3\n");
            choice[1] = -1;
        }
    }
}