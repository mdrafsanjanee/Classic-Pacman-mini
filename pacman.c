#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

#define MAP_ROWS 10
#define MAP_COLS 20
#define ENEMY_COUNT 2

void clearScreen();
void maingrid();

void renderGrid(
    char grid[MAP_ROWS][MAP_COLS],
    int playerRow, int playerCol,
    int enemyRows[], int enemyCols[],
    int score, int foodLeft
);

int isWall(char grid[MAP_ROWS][MAP_COLS], int row, int col);
int countFood(char grid[MAP_ROWS][MAP_COLS]);

void moveEnemy(
    char grid[MAP_ROWS][MAP_COLS],
    int *enemyRow,
    int *enemyCol
);

int main() {
    int uiInput;

    printf("Welcome to the Classic Pacman Mini\n");
    printf("1. New Game\n2. Options\n3. Exit\n");

    do {
        printf("Enter your choice (1-3): ");
        scanf("%d", &uiInput);

        switch (uiInput) {
            case 1:
                maingrid();
                break;

            case 2:
                printf("Under Maintenance\n");
                printf("Sorry for the inconvenience\n");
                break;

            case 3:
                printf("Thanks for playing\n");
                printf("See you next time!\n");
                return 0;

            default:
                printf("Invalid choice\n");
                break;
        }

    } while (uiInput != 1 && uiInput != 3);

    return 0;
}


void maingrid() {

    const char *mapTemplate[MAP_ROWS] = {
        "####################",
        "#........##........#",
        "#.####...##...####.#",
        "#.#..#........#..#.#",
        "#.#..#.######.#..#.#",
        "#..................#",
        "#.###.##.##.##.###.#",
        "#.....##.##.##.....#",
        "#........##........#",
        "####################"
    };

    char grid[MAP_ROWS][MAP_COLS];

    int playerRow = 1;
    int playerCol = 1;

    int score = 0;
    int foodLeft;

    
    int directionRow = 0;
    int directionCol = 1;

    
    int enemyRows[ENEMY_COUNT] = {5, 8};
    int enemyCols[ENEMY_COUNT] = {10, 10};

    srand((unsigned int)time(NULL));

    
    for (int i = 0; i < MAP_ROWS; i++) {
        memcpy(grid[i], mapTemplate[i], MAP_COLS);
    }

    /* Remove starting food */
    if (grid[playerRow][playerCol] == '.') {
        grid[playerRow][playerCol] = ' ';
        score++;
    }

    foodLeft = countFood(grid);

    while (1) {

        
        if (_kbhit()) {

            char input = _getch();

            if (input == 'q' || input == 'Q') {
                printf("Game exited. Final score: %d\n", score);
                break;
            }

            if (input == 'w' || input == 'W') {
                directionRow = -1;
                directionCol = 0;
            }
            else if (input == 's' || input == 'S') {
                directionRow = 1;
                directionCol = 0;
            }
            else if (input == 'a' || input == 'A') {
                directionRow = 0;
                directionCol = -1;
            }
            else if (input == 'd' || input == 'D') {
                directionRow = 0;
                directionCol = 1;
            }
        }


        int nextRow = playerRow + directionRow;
        int nextCol = playerCol + directionCol;

        if (!isWall(grid, nextRow, nextCol)) {

            playerRow = nextRow;
            playerCol = nextCol;

            if (grid[playerRow][playerCol] == '.') {

                grid[playerRow][playerCol] = ' ';

                score++;
                foodLeft--;
            }
        }


        for (int i = 0; i < ENEMY_COUNT; i++) {

            moveEnemy(
                grid,
                &enemyRows[i],
                &enemyCols[i]
            );
        }



        for (int i = 0; i < ENEMY_COUNT; i++) {

            if (playerRow == enemyRows[i] &&
                playerCol == enemyCols[i]) {

                clearScreen();

                renderGrid(
                    grid,
                    playerRow,
                    playerCol,
                    enemyRows,
                    enemyCols,
                    score,
                    foodLeft
                );

                printf("\nGAME OVER!\n");
                printf("You were caught by an enemy.\n");
                printf("Final score: %d\n", score);

                return;
            }
        }


        if (foodLeft == 0) {

            clearScreen();

            renderGrid(
                grid,
                playerRow,
                playerCol,
                enemyRows,
                enemyCols,
                score,
                foodLeft
            );

            printf("\nYou collected all points!\n");
            printf("Final score: %d\n", score);

            break;
        }


        clearScreen();

        renderGrid(
            grid,
            playerRow,
            playerCol,
            enemyRows,
            enemyCols,
            score,
            foodLeft
        );


  
        Sleep(150);
    }
}


void clearScreen() {
    system("cls");
}


void renderGrid(
    char grid[MAP_ROWS][MAP_COLS],
    int playerRow,
    int playerCol,
    int enemyRows[],
    int enemyCols[],
    int score,
    int foodLeft
) {

    printf("Score: %d  Food left: %d\n", score, foodLeft);
    printf("W/A/S/D = Move   Q = Quit\n\n");

    for (int i = 0; i < MAP_ROWS; i++) {

        for (int j = 0; j < MAP_COLS; j++) {

            int printed = 0;

            /*
             * Player
             */
            if (i == playerRow && j == playerCol) {

                printf("P");
                printed = 1;
            }

            /*
             * Enemies
             */
            if (!printed) {

                for (int k = 0; k < ENEMY_COUNT; k++) {

                    if (i == enemyRows[k] &&
                        j == enemyCols[k]) {

                        printf("G");
                        printed = 1;
                        break;
                    }
                }
            }

            /*
             * Normal map
             */
            if (!printed) {
                printf("%c", grid[i][j]);
            }
        }

        printf("\n");
    }
}


int isWall(
    char grid[MAP_ROWS][MAP_COLS],
    int row,
    int col
) {

    if (row < 0 ||
        row >= MAP_ROWS ||
        col < 0 ||
        col >= MAP_COLS) {

        return 1;
    }

    return grid[row][col] == '#';
}


int countFood(char grid[MAP_ROWS][MAP_COLS]) {

    int total = 0;

    for (int i = 0; i < MAP_ROWS; i++) {

        for (int j = 0; j < MAP_COLS; j++) {

            if (grid[i][j] == '.') {
                total++;
            }
        }
    }

    return total;
}


void moveEnemy(
    char grid[MAP_ROWS][MAP_COLS],
    int *enemyRow,
    int *enemyCol
) {


    int directions[4][2] = {
        {-1, 0},
        {1, 0},
        {0, -1},
        {0, 1}
    };

    int possibleDirections[4];
    int possibleCount = 0;



    for (int i = 0; i < 4; i++) {

        int newRow =
            *enemyRow + directions[i][0];

        int newCol =
            *enemyCol + directions[i][1];

        if (!isWall(grid, newRow, newCol)) {

            possibleDirections[possibleCount] = i;
            possibleCount++;
        }
    }



    if (possibleCount > 0) {

        int choice =
            possibleDirections[rand() % possibleCount];

        *enemyRow += directions[choice][0];
        *enemyCol += directions[choice][1];
    }
}