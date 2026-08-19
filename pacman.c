#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAP_ROWS 10
#define MAP_COLS 20

void clearScreen();
void maingrid();
void renderGrid(char grid[MAP_ROWS][MAP_COLS], int playerRow, int playerCol, int score, int foodLeft);
int isWall(char grid[MAP_ROWS][MAP_COLS], int row, int col);
int countFood(char grid[MAP_ROWS][MAP_COLS]);

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
                printf("Under Maintenance\nSorry for the inconvenience\n");
                break;
            case 3:
                printf("Thanks for playing\nSee you next time!\n");
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
    char input;

    for (int i = 0; i < MAP_ROWS; i++) {
        memcpy(grid[i], mapTemplate[i], MAP_COLS);
    }

    if (grid[playerRow][playerCol] == '.') {
        grid[playerRow][playerCol] = ' ';
        score++;
    }

    foodLeft = countFood(grid);

    while (1) {
        clearScreen();
        renderGrid(grid, playerRow, playerCol, score, foodLeft);

        if (foodLeft == 0) {
            printf("You collected all points! Final score: %d\n", score);
            break;
        }

        printf("Use W/A/S/D to move, Q to quit: ");
        scanf(" %c", &input);

        int nextRow = playerRow;
        int nextCol = playerCol;

        if (input == 'w' || input == 'W') {
            nextRow--;
        } else if (input == 's' || input == 'S') {
            nextRow++;
        } else if (input == 'a' || input == 'A') {
            nextCol--;
        } else if (input == 'd' || input == 'D') {
            nextCol++;
        } else if (input == 'q' || input == 'Q') {
            printf("Game exited. Final score: %d\n", score);
            break;
        } else {
            continue;
        }

        if (!isWall(grid, nextRow, nextCol)) {
            playerRow = nextRow;
            playerCol = nextCol;
            if (grid[playerRow][playerCol] == '.') {
                grid[playerRow][playerCol] = ' ';
                score++;
                foodLeft--;
            }
        }
    }
}

void clearScreen() {
    printf("\033[2J\033[H");
}

void renderGrid(char grid[MAP_ROWS][MAP_COLS], int playerRow, int playerCol, int score, int foodLeft) {
    printf("Score: %d  Food left: %d\n\n", score, foodLeft);
    for (int i = 0; i < MAP_ROWS; i++) {
        for (int j = 0; j < MAP_COLS; j++) {
            if (i == playerRow && j == playerCol) {
                printf("P");
            } else {
                printf("%c", grid[i][j]);
            }
        }
        printf("\n");
    }
    printf("\n");
}

int isWall(char grid[MAP_ROWS][MAP_COLS], int row, int col) {
    if (row < 0 || row >= MAP_ROWS || col < 0 || col >= MAP_COLS) {
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