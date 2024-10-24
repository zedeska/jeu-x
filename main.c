#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <Windows.h>
#include <unistd.h>
#include <stdbool.h>

#define KRED  "\x1B[31m"
#define KBLU  "\x1B[34m"
#define RESET "\x1B[0m"

bool isEven(int a)
{
    if (a % 2 == 0)
    {
        return true;
    } else
    {
        return false;
    }
}

void arrayPrint(int lignes, int colonnes, int tableau[lignes][colonnes][2])
{
    printf("\n");
    for (int i = 0; i < lignes; i++)
    {
        for (int l = 0; l < colonnes; l++)
        {
            printf("----");
            if (l == colonnes-1)
            {
                printf("-");
            }
        }
        printf("\n");

        for (int y = 0; y < colonnes; y++)
        {
            printf("|");

            if (tableau[i][y][0] == 1)
            {
                printf(" %s%d " RESET, KRED,tableau[i][y][1]);
            } else if (tableau[i][y][0] == 2)
            {
                printf(" %s%d " RESET, KBLU,tableau[i][y][1]);
            } else
            {
                printf("   ", tableau[i][y][1]);
            }
            
            if (y == colonnes-1)
            {
                printf("|\n");
            }
            
        }
    }

    for (int l = 0; l < colonnes; l++)
    {
        printf("----");
        if (l == colonnes-1)
        {
            printf("-");
        }
    }

    printf("\n\n");
}

void findEmpty(int lignes, int colonnes, int tableau[lignes][colonnes][2], int vide[2])
{
    for (int i = 0; i < lignes; i++)
    {
        for (int y = 0; y < colonnes; y++)
        {
            if (tableau[i][y][1] == 0)
            {
                vide[0] = i;
                vide[1] = y;
            }
        }
    }
}

void pointCounter(int lignes, int colonnes, int tableau[lignes][colonnes][2], int points[2], int vide[2])
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
}


int main()
{
    SetConsoleOutputCP(CP_UTF8);
    int lignes, colonnes, tour, case_ligne, case_colonne, success, turn = 0;
    int jeton = 1;

    //int lignes,colonnes = 0;
    
    while (1)
    {
        fflush(stdin);
        system("cls");

        printf("Bienvenue sur le jeu X !!1!11!!1!!1 OMG\nCe jeu est joué à 2 joueurs (J1 rouge, J2 bleu).\n");
        printf("\nVeuillez entrer le nombres de lignes : ");
    
        if (scanf(" %d", &lignes) == 1)
        {
            if (isEven(lignes))
            {
                printf("Le numéro doit être impair.\n");
                Sleep(2000);
            } else
            {
                printf("\nEt de colonnes : ");

                if (scanf(" %d", &colonnes) == 1)
                {
                    if (isEven(colonnes))
                    {
                        printf("Le numéro doit être impair.\n");
                        Sleep(2000);
                    } else
                    {
                        break;
                    }
                } else{
                    printf("\nLe numéro saisi est incorrect.");
                    Sleep(2000);
                }
            }
        } else
        {
            printf("\nLe numéro saisi est incorrect.");
            Sleep(2000);
        }
    }

    int tableau[lignes][colonnes][2];
    memset(tableau, 0 , lignes*colonnes*2*sizeof(int));
    tour = (lignes * colonnes - 1) / 2;

    printf("\nChaque joueur a %d jetons.", tour);
    Sleep(2000);
    
    //printf("%d, %d", lignes, colonnes);
    //tableau[0][0] = 1;
    //printf("%d", tableau[0][0]);

    while (jeton <= tour)
    {
        turn = 0;
        //system("cls");

        //arrayPrint(lignes, colonnes, tableau);

        while (turn < 2)
        {
            turn++;
            system("cls");
            arrayPrint(lignes, colonnes, tableau);

            while (1)
            {
                fflush(stdin);
                system("cls");
                arrayPrint(lignes, colonnes, tableau);

                printf("C'est au joueur %d.\nDonnez la ligne de la case : ", turn);
                if (scanf("%d", &case_ligne) != 1)
                {
                    printf("Le numéro saisi est incorrect.\n");
                    Sleep(1000);
                    continue;
                }

                printf("\n La colonne : ");
                
                if (scanf("%d", &case_colonne) != 1)
                {
                    printf("Le numéro saisi est incorrect.\n");
                    Sleep(1000);
                    continue;
                }
                
                if (case_ligne > lignes || case_colonne > colonnes)
                {
                    printf("La position sort du tableau.\n");
                    Sleep(1000);
                } else if (tableau[case_ligne-1][case_colonne-1][0] != 0)
                {
                    printf("La case n'est pas vide.\n");
                    Sleep(1000);
                } else
                {
                    break;
                }
            }
        
            tableau[case_ligne-1][case_colonne-1][0] = turn;
            tableau[case_ligne-1][case_colonne-1][1] = jeton;

        }
        jeton++;
    }

    system("cls");
    arrayPrint(lignes, colonnes, tableau);
    
    int vide[2], points[2] = {0};

    findEmpty(lignes, colonnes, tableau, vide);
    pointCounter(lignes, colonnes, tableau, points, vide);

    printf("\nLe joueur 1 a : %d points\nle joueur 2 a : %d points\n", points[0], points[1]);
    printf("Le joueur %d remporte la partie !\n", (points[0] < points[1]) ? 1 : 2);
    
    return 0;
}