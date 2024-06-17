#include <stdio.h>
#include <stdlib.h>

void prtBoard(int board[][6]);              // Prints the board to the console
int input(int board[][6], int player);      // Gets input from the players
int checkWin(int board[][6], int player);   // Checks if someone has won
void playGame();                            // This loops through the game

int main(void) {
  char usr;
  system("clear");
  playGame();
  for(;;) {
    printf("Do you want to play again? [Y/N]\n");
    scanf(" %c%*c", &usr);
    if (usr == 'Y' || usr == 'y') {
      playGame();
    }
    else {
      return 0;
    }
  }
}

void prtBoard(int board[][6]) {
  system("clear");
  printf(" 1  2  3  4  5  6  7 \n");
  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 7; j++) {
      if (board[j][i] == 1) {
        printf("\033[0;31m[%d]", board[j][i]);
      }
      else if (board[j][i] == 2) {
        printf("\033[0;34m[%d]", board[j][i]);
      }
      else {
        printf("\033[0;37m[%d]", board[j][i]);
      }
    }
    printf("\033[0;37m\n");
  }
}

int input(int board[][6], int player) {
  int usr;
  scanf("%d", &usr);
  if (usr > 7 || usr < 1) {
    system("clear");
    prtBoard(board);
    printf("bad input, try again\n");
    input(board, player);
    player = !player;
    return player;
  }
  for (int i = 5; i >= 0; i--) {
    if (board[usr - 1][i] == 0) {
      board[usr - 1][i] = player + 1;
      break;
    }
  }
  player = !player;
  return player;
}

int checkWin(int board[][6], int player) {
  // Horizontal win
  for (int j=0; j<6; j++) {
    for (int i=0; i<4; i++) {
      if (board[i][j] == board[i+1][j] && board[i+2][j] == board[i+3][j] && board[i+1][j] == board[i+2][j] && board[i][j] != 0) {
        return 1;
      }
    }
  }
  // Vertical Win
  for (int j = 0; j < 7; j++) {
    for (int i = 0; i < 3; i++) {
      if (board[j][i] == board[j][i + 1] && board[j][i + 2] == board[j][i + 3] && board[j][i+1] == board[j][i+2] && board[j][i] != 0) {
        return 1;
      }
    }
  }

  // Diagonal Win (Top-Left to Bottom-Right)
  for (int j = 0; j < 3; j++) {
    for (int i = 0; i < 4; i++) {
      if (board[i][j] == board[i + 1][j + 1] && board[i + 1][j + 1] == board[i + 2][j + 2] && board[i + 2][j + 2] == board[i + 3][j + 3] && board[i][j] != 0) {
        return 1;
      }
    }
  }
  // Diagonal Win (Top-Right to Bottom-Left)
  for (int j = 3; j < 6; j++) {
    for (int i = 0; i < 4; i++) {
      if (board[i][j] == board[i + 1][j - 1] && board[i + 1][j - 1] == board[i + 2][j - 2] && board[i + 2][j - 2] == board[i + 3][j - 3] && board[i][j] != 0) {
        return 1;
      }
    }
  }


  return 0;
}

void playGame() {
  int board[7][6] = {0};
  int player = 0;

  prtBoard(board);
  for (;;) {
    player = input(board, player);
    prtBoard(board);
    if (checkWin(board, player) == 1) {
      printf("Player ");
      if (player == 1) {
        printf("\033[0;31m1 ");
      }
      else {
        printf("\033[0;34m2 ");
      }
      printf("\033[0;37mwon the game\n");
      return;
    }
  }
}
