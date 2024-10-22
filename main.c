#include <stdio.h>
#include <memory.h>
#include <stdlib.h>

#define KRED  "\x1B[31m"
#define KBLU  "\x1B[34m"
#define RESET "\x1B[0m"

void arrayPrint(int lignes, int colonnes, int tableau[lignes][colonnes][2])
{
    for (int i = 0; i < lignes; i++)
    {
        for (int y = 0; y < colonnes; y++)
        {
            if (tableau[i][y][0] == 1)
            {
                printf("%s%d " RESET, KRED,tableau[i][y][1]);
            } else if (tableau[i][y][0] == 2)
            {
                printf("%s%d " RESET, KBLU,tableau[i][y][1]);
            } else
            {
                printf("%d ", tableau[i][y][1]);
            }
            
            if (y == colonnes-1)
            {
                printf("\n");
            }
            
        }
    }
}

int findEmpty(int lignes, int colonnes, int tableau[lignes][colonnes][2], int vide[2])
{
    for (int i = 0; i < lignes; i++)
    {
        for (int y = 0; y < colonnes; y++)
        {
            if (tableau[i][y][1] == 0)
            {
                vide[0] = i;
                vide[1] = y;
                return 0;
            }
        }
    }
}

int pointCounter(int lignes, int colonnes, int tableau[lignes][colonnes][2], int points[2], int vide[2])
{
    int comb[8][2] = {{-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}};

    for (int i = 0; i < 8; i++)
    {
        if (vide[0] + comb[i][0] >= 0 && vide[0] + comb[i][0] < lignes && vide[1] + comb[i][1] >= 0 && vide[1] + comb[i][1] < colonnes)
        {
            if (tableau[vide[0]+comb[i][0]][vide[1]+comb[i][1]][0] == 1)
            {
                points[0] = points[0] + tableau[vide[0]+comb[i][0]][vide[1]+comb[i][1]][1];
            } else
            {
                points[1] = points[1] + tableau[vide[0]+comb[i][0]][vide[1]+comb[i][1]][1];
            }
        }
    }
    
    return 0;
}


int main()
{
    int lignes, colonnes, tour, case_ligne, case_colonne, numero, success, turn;

    //int lignes,colonnes = 0;

    printf("Bienvenue sur le jeu X !!1!11!!1!!1 \n Ce jeu est joué à 2 joueurs (J1 bleu, J2 rouge).\n");
    printf("Veuillez entrer le nombres de lignes, puis de colonnes \n");

    scanf("%d",&lignes);
    scanf("%d",&colonnes);

    int tableau[lignes][colonnes][2];
    memset(tableau, 0 , lignes*colonnes*2*sizeof(int));
    tour = (lignes * colonnes - 1) / 2;
    

    //printf("%d, %d", lignes, colonnes);
    //tableau[0][0] = 1;
    //printf("%d", tableau[0][0]);

    while (tour > 0)
    {
        turn = 0;
        //system("cls");

        //arrayPrint(lignes, colonnes, tableau);

        while (turn < 2)
        {
            turn++;
            success = 0;
            system("cls");
            arrayPrint(lignes, colonnes, tableau);

            while (success == 0)
            {
                printf("C'est au joueur %d.\n Donnez la ligne de la case : ", turn);
                scanf("%d", &case_ligne);
                printf("\n La colonne : ");
                scanf("%d", &case_colonne);
                printf("\n Et le numéro : ");
                scanf("%d", &numero);

                if (tableau[case_ligne-1][case_colonne-1][0] != 0)
                {
                    printf("La case n'est pas vide.\n");
                } else if (numero == 0)
                {
                    printf("Il n'est pas possible d'utiliser le numéro 0");
                } else
                {
                    success = 1;
                }
            }
        
            tableau[case_ligne-1][case_colonne-1][0] = turn;
            tableau[case_ligne-1][case_colonne-1][1] = numero;

        }
        tour--;
    }

    system("cls");
    arrayPrint(lignes, colonnes, tableau);
    
    int vide[2] = {0};
    int points[2] = {0};

    findEmpty(lignes, colonnes, tableau, vide);
    pointCounter(lignes, colonnes, tableau, points, vide);

    printf("\n le joueur 1 a : %d points\n le joueur 2 a : %d points", points[0], points[1]);
    
    return 0;
}
