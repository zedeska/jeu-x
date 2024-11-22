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
/* Fonction servant à savoir si le paramètre a est pair ou non */
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
/* Fonction permettant d'afficher le tableau dans le terminal */
{
    printf("\n");
    for (int i = 0; i < lignes; i++) // on parcours chaques lignes
    {
        for (int l = 0; l < colonnes; l++) // et chaques colonnes
        {
            printf("----"); // pour la déco (séparateur de lignes)
            if (l == colonnes-1) // condition pour la déco
            {
                printf("-");
            }
        }
        printf("\n");

        for (int y = 0; y < colonnes; y++)
        {
            printf("|");

            if (tableau[i][y][0] == 1) // si la case "appartient" au joueur 1, on affiche son jeton en rouge
            {
                printf(" %s%d " RESET, KRED,tableau[i][y][1]);

            } else if (tableau[i][y][0] == 2) // si la case "appartient" au joueur 2, on affiche son jeton en bleu
            {
                printf(" %s%d " RESET, KBLU,tableau[i][y][1]);

            } else
            {
                printf("   ", tableau[i][y][1]);
            }
            
            if (y == colonnes-1) // pour la déco, si on arrive à la fin de la colonnes, print un pipe
            {
                printf("|\n");
            }
            
        }
    }

    for (int l = 0; l < colonnes; l++) // afficer la dernière ligne de tirets
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
/* Permet de trouver la case vide du tableau, inclus ses coordonnées dans le tableau 'vide' */
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
/* Permet de compter les points (les huits cases autour de la case vide), inclus la somme des points de chaque joueur dans le tableau points (index 0 = joueur 1, index 1 = joueur 2)*/
{
    int comb[8][2] = {{-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}}; // toutes les combinaisons possible pour faire un carré de 3x3 avec la case vide en son centre

    for (int i = 0; i < 8; i++)
    {
        if (vide[0] + comb[i][0] >= 0 && vide[0] + comb[i][0] < lignes && vide[1] + comb[i][1] >= 0 && vide[1] + comb[i][1] < colonnes) // condition qui permet de vérifier qu'on ne sort pas du tableau
        {
            if (tableau[vide[0]+comb[i][0]][vide[1]+comb[i][1]][0] == 1) // vérfie si le joueur de la n-ième lignes et de la n-ième colonnes par rapport à la case vice est le joueur 1
            {
                points[0] = points[0] + tableau[vide[0]+comb[i][0]][vide[1]+comb[i][1]][1]; // si oui on lui attribue les points
            } else // sinon on attribue les points au joueur 2
            {
                points[1] = points[1] + tableau[vide[0]+comb[i][0]][vide[1]+comb[i][1]][1];
            }
        }
    }
}


int main()
{
    SetConsoleOutputCP(CP_UTF8);
    printf("\e[1;1H\e[2J"); // clear la console
    int lignes, colonnes, tour, case_ligne, case_colonne, success, turn = 0;
    int jeton = 1;
    char joueur1[20]; // Tableau de caractères pour le nom du joueur 1
    char joueur2[20]; // Tableau de caractères pour le nom du joueur 2
    
    printf("Bienvenue sur le jeu X !!1!11!!1!!1 OMG\nCe jeu est joué à 2 joueurs (J1 rouge, J2 bleu).\n");
    printf("Veuillez saisir le nom du joueur 1 : ");
    fgets(joueur1, 20, stdin);
    joueur1[strcspn(joueur1, "\n")] = '\0'; // Enlève le '\n' s'il est présent
    printf("Veuillez saisir le nom du joueur 2 : ");
    fgets(joueur2, 20, stdin);
    joueur2[strcspn(joueur2, "\n")] = '\0';

    while (1)
    {
        fflush(stdin); // vide l'entrée standard
        printf("\e[1;1H\e[2J"); // clear la console

        printf("\nVeuillez entrer le nombres de lignes : ");
    
        if (scanf(" %d", &lignes) == 1)
        {
            if (lignes <= 1 || lignes >= 7) {
                printf("Le numéro de ligne être positif, supérieur à 1 et inférieur à 7.\n");
                Sleep(2000);
            } else if (isEven(lignes))
            {
                printf("Le numéro doit être impair.\n");
                Sleep(2000);
            } else
            {
                printf("\nEt de colonnes : ");

                if (scanf(" %d", &colonnes) == 1)
                {
                    if (colonnes <= 1 || colonnes >= 7) {
                        printf("Le numéro de colonne doit être positif, supérieur à 1 et inférieur à 7.\n");
                    Sleep(2000);
                    } else if (isEven(colonnes))
                    {
                        printf("Le numéro doit être impair.\n");
                        Sleep(2000);
                    } else
                    {
                        break; // si aucune condition n'est validé, il n'y pas d'erreur, on peut sortir de la boucle
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

    int tableau[lignes][colonnes][2]; // création du tableau
    memset(tableau, 0 , lignes*colonnes*2*sizeof(int)); // on alloue de l'espace et on initialise tout à 0
    tour = (lignes * colonnes - 1) / 2;

    printf("\nChaque joueur a %d jetons.", tour);
    Sleep(2000);
    
    while (jeton <= tour) // boucle de jeu principal
    {
        turn = 0; // permet de traquer le tour actuel (première boucle = joueur 1, 2ème boucle = joueur 2, puis on recommence)

        while (turn < 2)
        {
            turn++;
            printf("\e[1;1H\e[2J");
            arrayPrint(lignes, colonnes, tableau);

            while (1)
            {
                fflush(stdin);
                printf("\e[1;1H\e[2J");
                arrayPrint(lignes, colonnes, tableau);

                printf("C'est au tour de %s.\nDonnez la ligne de la case : ", (turn == 1) ? joueur1 : joueur2);
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
                
                if (case_ligne > lignes || case_colonne > colonnes || case_ligne < 1 || case_colonne < 1)
                {
                    printf("La position sort du tableau.\n");
                    Sleep(1000);
                } else if (tableau[case_ligne-1][case_colonne-1][0] != 0)
                {
                    printf("La case n'est pas vide.\n");
                    Sleep(1000);
                } else
                {
                    break; // si aucune condition n'est vérifié, tout est correct, on peut sortir de la boucle
                }
            }
        
            /* On assigne le jeton et le joueur au tableau  */
            tableau[case_ligne-1][case_colonne-1][0] = turn;
            tableau[case_ligne-1][case_colonne-1][1] = jeton;

        }
        jeton++; // au incrémente la valeur du jeton, chaque tour la valeur augmente jusqu'au dernier.
    }

    printf("\e[1;1H\e[2J");
    arrayPrint(lignes, colonnes, tableau);
    
    int vide[2], points[2] = {0}; // on initialise les tableaux qui vont contenir les coordonnées de la case vide et les points de joueurs

    findEmpty(lignes, colonnes, tableau, vide);
    pointCounter(lignes, colonnes, tableau, points, vide);

    printf("Le joueur %s a : %d points\nle joueur %s a : %d points\n", joueur1, points[0], joueur2, points[1]);

    // On compare les points des joueurs pour savoir qui a gagner, celui qui en a le moins l'emporte
    if (points[0] > points[1]) {
        printf(" %s remporte la partie !\n", joueur1);
    } else if (points[0] < points[1]) {
        printf("Le joueur %s remporte la partie !\n", joueur2);
    } else if (points[0] == points[1]) {
        printf("Egalité ! Bravo à vous deux ! !\n");
    }
    
    system("pause");

    return 0;
}