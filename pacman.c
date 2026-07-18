#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

void maingrid();

int main() {

    printf("Welcome to the Classic Pacman Mini\n");
    
    int uiInput;
    printf("1. New Game\n2. Options\n3. Exit");
    do {
    printf("Enter your choice: (1-3): ");
    scanf("%d", &uiInput);

    switch (uiInput)
    {
    case 1:
        printf("Loading....");
        system("cls");
        maingrid();
        break;
    case 2:
        printf("Under Maintenece\nSorry for the inconvenience\n");
        break;
    case 3:
        printf("Thanks for playing\nSee you next time!\n");
        return 0;
        break;
    default:
        printf("Invalid Choice\n");
        break;
    }
    } while (uiInput < 0 || uiInput > 3 || uiInput == 2);   // option 2 is hre temporarily. Need to remove this after coding option 2.

}

void maingrid() {

    char grid[10][20];

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 20; j++){
            grid[i][j] = '*';

        }
    }

    for (int a = 0; a < 10; a++) {

        grid[a][a] = '#';

        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 20; j++)
                printf(" %c ", grid[i][j]);
            printf("\n");
        }

        Sleep(2000);
        if (a == 9){ continue;}
        system("cls");
    }

}