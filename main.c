/*
 * Bataille Navale
 * Christopher Pardo
 * 03.03.2019
 */
#include <stdio.h>
#define MaxGrile 10

void Game(){
    float grille[MaxGrile][MaxGrile];

    for(int i = 0;i < MaxGrile;i++){
        for (int j = 0; j < MaxGrile;j++) {
            grille[i][j] = 0;
        }
    }
    printf("\n\n    A B C D E F G H I J\n");
    for (int i = 0; i < MaxGrile;i++){
        printf("\n%d  ",i+1);
        if(i < 9){
            printf(" ");
        }
        for (int j = 0; j < MaxGrile; ++j) {
            printf("%.0f ",grille[i][j]);
        }
    }

}

int main() {
    int choice = 0;
    int test = 0;

    while(1){
        printf("\n1. Afficher la grille");
        printf("\n2. Afficher les regles");
        printf("\n4. Quitter");
        scanf("%d",&choice);

        if (choice == 1) {
            Game();
            scanf("%d",&test);
            return 0;
        }
        else if(choice == 2){
            printf("\n\nLa bataille navale oppose deux joueurs qui s'affrontent."
                   "\nChacun a une flotte composee de 3 bateaux, qui sont, en general, les suivants :\n1 porte-avion (5 cases)\n1 croiseur (4 cases)"
                   "\nUn a un, les joueurs vont tirer sur une case de l'adversaire.");
            choice = -1;
            printf("\n\n");
        }
        else if (choice == 4) {
            return 0;
        }
        else {
            printf("Ce n'est pas un chois possible");
            choice = -1;
        }
    }
}