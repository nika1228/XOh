#include <stdio.h>
#include <stdbool.h>
#include <conio.h> // Для Windows (_kbhit и _getch)

#define MAX_ROWS 15
#define MAX_COLS 15

void initializeBoard(char board[MAX_ROWS][MAX_COLS], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            board[i][j] = ' ';
        }
    }
}

void printBoard(char board[MAX_ROWS][MAX_COLS], int rows, int cols, int cursorRow, int cursorCol) {
    system("cls");  // Очистка экрана 
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (i == cursorRow && j == cursorCol) {
                printf("[%c]", board[i][j]);
            }
            else {
                printf(" %c ", board[i][j]);
            }
            if (j != cols - 1) {
                printf("|");
            }
        }
        printf("\n");
        if (i != rows - 1) {
            for (int j = 0; j < cols; j++) {
                printf("---");
                if (j != cols - 1) {
                    printf("+");
                }
            }
            printf("\n");
        }
    }
}

bool checkWin(char board[MAX_ROWS][MAX_COLS], int rows, int cols, int winCondition, char player) {
    // Проверка строк
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j <= cols - winCondition; j++) {
            bool win = true;
            for (int k = 0; k < winCondition; k++) {
                if (board[i][j + k] != player) {
                    win = false;
                    break;
                }
            }
            if (win) return true;
        }
    }

    // Проверка столбцов
    for (int i = 0; i <= rows - winCondition; i++) {
        for (int j = 0; j < cols; j++) {
            bool win = true;
            for (int k = 0; k < winCondition; k++) {
                if (board[i + k][j] != player) {
                    win = false;
                    break;
                }
            }
            if (win) return true;
        }
    }

    // Проверка диагоналей (слева направо)
    for (int i = 0; i <= rows - winCondition; i++) {
        for (int j = 0; j <= cols - winCondition; j++) {
            bool win = true;
            for (int k = 0; k < winCondition; k++) {
                if (board[i + k][j + k] != player) {
                    win = false;
                    break;
                }
            }
            if (win) return true;
        }
    }

    // Проверка диагоналей (справа налево)
    for (int i = 0; i <= rows - winCondition; i++) {
        for (int j = winCondition - 1; j < cols; j++) {
            bool win = true;
            for (int k = 0; k < winCondition; k++) {
                if (board[i + k][j - k] != player) {
                    win = false;
                    break;
                }
            }
            if (win) return true;
        }
    }

    return false;
}

// Проверка возможности следующего игрока победить
bool canNextPlayerWin(char board[MAX_ROWS][MAX_COLS], int rows, int cols, int winCondition, char nextPlayer) {
    // Проверка строк
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j <= cols - winCondition; j++) {
            int countPlayer = 0; // Счетчик символов игрока в последовательности
            int countEmpty = 0; // Счетчик пустых ячеек в последовательности
            for (int k = 0; k < winCondition; k++) {
                if (board[i][j + k] == nextPlayer) { // Если ячейка содержит символ следующего игрока
                    countPlayer++; // Увеличиваем счетчик символов игрока
                }
                else if (board[i][j + k] == ' ') { // Если ячейка пуста
                    countEmpty++; // Увеличиваем счетчик пустых ячеек
                }
            }
            if (countPlayer + countEmpty == winCondition) {// Если в последовательности все ячейки заполнены или могут быть заполнены символом следующего игрока
                return true; //игрок может выиграть
            }
        }
    }

    // Проверка столбцов
    for (int i = 0; i <= rows - winCondition; i++) {
        for (int j = 0; j < cols; j++) {
            int countPlayer = 0;
            int countEmpty = 0;
            for (int k = 0; k < winCondition; k++) {
                if (board[i + k][j] == nextPlayer) {
                    countPlayer++;
                }
                else if (board[i + k][j] == ' ') {
                    countEmpty++;
                }
            }
            if (countPlayer + countEmpty == winCondition) {
                return true;
            }
        }
    }

    // Проверка диагоналей (слева направо)
    for (int i = 0; i <= rows - winCondition; i++) {
        for (int j = 0; j <= cols - winCondition; j++) {
            int countPlayer = 0;
            int countEmpty = 0;
            for (int k = 0; k < winCondition; k++) {
                if (board[i + k][j + k] == nextPlayer) {
                    countPlayer++;
                }
                else if (board[i + k][j + k] == ' ') {
                    countEmpty++;
                }
            }
            if (countPlayer + countEmpty == winCondition) {
                return true;
            }
        }
    }

    // Проверка диагоналей (справа налево)
    for (int i = 0; i <= rows - winCondition; i++) {
        for (int j = winCondition - 1; j < cols; j++) {
            int countPlayer = 0;
            int countEmpty = 0;
            for (int k = 0; k < winCondition; k++) {
                if (board[i + k][j - k] == nextPlayer) {
                    countPlayer++;
                }
                else if (board[i + k][j - k] == ' ') {
                    countEmpty++;
                }
            }
            if (countPlayer + countEmpty == winCondition) {
                return true;
            }
        }
    }

    return false;
}

void playGame(int rows, int cols, int winCondition) {
    char board[MAX_ROWS][MAX_COLS];
    initializeBoard(board, rows, cols);
    int cursorRow = 0, cursorCol = 0;
    char currentPlayer = 'X';
    bool gameWon = false;
    while (true) {
        printBoard(board, rows, cols, cursorRow, cursorCol);
        printf("now is player %c", currentPlayer);
        int ch = _getch();
        if (ch == 0 || ch == 224) {
            ch = _getch();  

            switch (ch) {
            case 72: // Вверх
                if (cursorRow > 0) cursorRow--;
                break;
            case 80: // Вниз
                if (cursorRow < rows - 1) cursorRow++;
                break;
            case 75: // Влево
                if (cursorCol > 0) cursorCol--;
                break;
            case 77: // Вправо
                if (cursorCol < cols - 1) cursorCol++;
                break;
            }
        }
        else if (ch == 13) {  // Enter для установки символа
            if (board[cursorRow][cursorCol] == ' ') {
                board[cursorRow][cursorCol] = currentPlayer;

                // Проверка на победу
                if (checkWin(board, rows, cols, winCondition, currentPlayer)) {
                    printBoard(board, rows, cols, cursorRow, cursorCol);
                    printf("Player %c won!\n", currentPlayer);
                    gameWon = true;
                    break;
                }

                // Проверка на ничью (возможность следующего игрока победить)
                char nextPlayer = (currentPlayer == 'X') ? 'O' : 'X';
                if (!canNextPlayerWin(board, rows, cols, winCondition, nextPlayer)) {
                    printBoard(board, rows, cols, cursorRow, cursorCol);
                    printf("Draw! There Are no moves to win!\n");
                    break;
                }

                // Смена игрока
                currentPlayer = nextPlayer;
               
            }
        }
    }

    if (!gameWon) {
        printf("The end.\n");
    }
}

int main() {
    
    int flag = 1;
    while (flag = 1) {
        int rows, cols, winCondition;
        printf("Enter the rows from 3 to 15\n");
        scanf_s("%d", &rows);
        while(rows < 3 || rows > 15) {
            printf("Incorrect! Try again.\n");
            scanf_s("%d", &rows);
        }
        printf("Enter the columns from 3 to 15\n");
        scanf_s("%d", &cols);
        while (cols < 3 || cols > 15) {
            printf("Incorrect! Try again.\n");
            scanf_s("%d", &cols);
        }
        printf("Enter the numbers of X or O for win:");
        scanf_s("%d", &winCondition);
        while (winCondition < 3 || winCondition >(rows > cols ? rows : cols)) {
            printf("Incorrect! Try again.\n");
            scanf_s("%d", &winCondition);
        }

        /*if (rows < 3 || rows > 15 || cols < 3 || cols > 15 || winCondition < 3 || winCondition >(rows > cols ? rows : cols)) {
            printf("Incorrect! Try again.\n");
            return 1;
        }*/

        playGame(rows, cols, winCondition);

        do {
           printf("Do you want to play again? \n Press Y to continue\nPress N to exit\n");
           char choise;
           choise = _getch();
           if (choise == 'n') {
               flag = 0;
               return 0;
           }
           if (choise == 'y') {

               break;
           }
           system("cls");
       } while (flag = 1);
    }
}
