/*
 * Bataille Navale
 * Christopher Pardo
 * 03.03.2019
 */
#include <stdio.h>
#include <windows.h>
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
#define DTLC 201 // ╔, Double Top Left Corner
#define DTRC 187 // ╗, Double Top Right Corner
#define DBLC 200 // ╚, Double Bottom Left Corner
#define DBRC 188 // ╝, Double Bottom Right Corner
#define DVSB 186 // ║, Double Vertical Simple Border
#define DVRB 185 // ╣, Double Vertical Right Border
#define DVLB 204 // ╠, Double Vertical Left Border
#define DHSB 205 // ═, Double Horizontal Simple Border
#define DHBB 202 // ╩, Double Horizontal Bottom Border
#define DHTB 203 // ╦, Double Horizontal Top Border
#define DC   206 // ╬, Double Center
#define MaxGrile 10

void Game(){
    int grille[MaxGrile][MaxGrile];

    for(int i = 0;i < MaxGrile;i++){
        for (int j = 0; j < MaxGrile;j++) {
            grille[i][j] = 0;
        }
    }
    printf("\n\n    A   B   C   D   E   F   G   H   I   J\n");
    for (int i = 0; i < MaxGrile;i++){
        printf("  ");
        if(i == 0){
            printf("%c",STLC);
        }
        else{
            printf("%c",SVLB);
        }
        if(i == 0){
            for (int k = 0; k < MaxGrile-1; ++k) {
                printf("%c%c%c",SHSB,SHSB,SHSB);
                printf("%c",SHTB);
            }
            printf("%c%c%c",SHSB,SHSB,SHSB);
        }
        else{
            for (int k = 0; k < MaxGrile-1; ++k) {
                printf("%c%c%c",SHSB,SHSB,SHSB);
                printf("%c",SC);
            }
            printf("%c%c%c",SHSB,SHSB,SHSB);
        }
        if(i == 0){
            printf("%c",STRC);
        }
        else{
            printf("%c",SVRB);
        }
        printf("\n%d",i+1);
        if(i < 9) {
            printf(" ");
        }
        for (int j = 0; j < MaxGrile; ++j) {
            printf("%c %d ",SVSB,grille[i][j]);
        }
        printf("%c\n",SVSB);
    }
    printf("  %c",SBLC);
    for (int l = 0; l < MaxGrile-1; ++l) {
        printf("%c%c%c",SHSB,SHSB,SHSB);
        printf("%c",SHBB);
    }
    printf("%c%c%c",SHSB,SHSB,SHSB);
    printf("%c",SBRC);

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