/* TODO
To implement a 4-in-a-row game using MPI in C++, you will need to follow these
steps:

1. Initialize MPI by calling the MPI_Init function.
2. Get the rank and size of the processes using the MPI_Comm_rank and
MPI_Comm_size functions.
3. Set up the board as a two-dimensional array of integers. Initialize all
elements to 0.
4. Set up the game loop. In each iteration, the current player will choose a
random column to drop their piece into.
5. To make a move, the current player will send a message to the other player
indicating the column they have chosen. The other player will receive this
message using the MPI_Recv function.
6. The receiving player will update the board by adding the current player's
piece to the lowest empty row in the chosen column.
7. Check if the current player has won by calling a function that checks for a
win condition (four in a row). If a player has won, print a message indicating
the winner and exit the game loop.
8. If no player has won and the board is full (i.e. no empty spaces), print a
message indicating a draw and exit the game loop.
9. Alternate the current player and repeat the game loop until one of the
stopping conditions is met.
10. When the game is over, finalize MPI by calling the MPI_Finalize function.
*/

#include <cstdlib>
#include <iostream>
#include <mpi.h>

const int ROWS = 6;
const int COLS = 7;

int board[ROWS][COLS];

bool checkForDraw() {
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      if (board[i][j] == 0) {
        return false;
      }
    }
  }
  return true;
}

int checkForWin(int player) {
  // Check rows
  for (int i = 0; i < ROWS; i++) {
    int count = 0;
    for (int j = 0; j < COLS; j++) {
      if (board[i][j] == player) {
        count++;
        if (count == 4)
          return player;
      } else {
        count = 0;
      }
    }
  }

  // Check columns
  for (int j = 0; j < COLS; j++) {
    int count = 0;
    for (int i = 0; i < ROWS; i++) {
      if (board[i][j] == player) {
        count++;
        if (count == 4)
          return player;
      } else {
        count = 0;
      }
    }
  }

  // Check both diagonals
  for (int i = 0; i < ROWS - 3; i++) {
    for (int j = 0; j < COLS - 3; j++) {
      if (board[i][j] == player && board[i + 1][j + 1] == player &&
          board[i + 2][j + 2] == player && board[i + 3][j + 3] == player) {
        return player;
      }
    }
  }

  for (int i = 0; i < ROWS - 3; i++) {
    for (int j = COLS - 1; j >= 3; j--) {
      if (board[i][j] == player && board[i + 1][j - 1] == player &&
          board[i + 2][j - 2] == player && board[i + 3][j - 3] == player) {
        return player;
      }
    }
  }

  return 0;
}

int main(int argc, char **argv) {
  // Initialize MPI
  MPI_Init(NULL, NULL);

  // Get the number of processes
  int world_size;
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);

  // Get the rank of the process
  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

  // Get the name of the processor
  char processor_name[MPI_MAX_PROCESSOR_NAME];
  int name_len;
  MPI_Get_processor_name(processor_name, &name_len);

  // Seed the random number generator
  srand(time(NULL) + world_rank);

  // Initialize the board to all 0s
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      board[i][j] = 0;
    }
  }

  // Players take turns making moves until the game is over
  int turn = 0;

  while (true) {
    if (world_rank != turn) {
      MPI_Recv(board, ROWS * COLS, MPI_INT, turn, 0, MPI_COMM_WORLD,
               MPI_STATUS_IGNORE);
    } else {
      // It's this process's turn, so choose a random column to drop a piece in
      int column = rand() % COLS;
      // Find the first empty row in the chosen column
      int row = -1;
      for (int i = ROWS - 1; i >= 0; i--) {
        if (board[i][column] == 0) {
          row = i;
          break;
        }
      }
      // If the column is full, try again
      if (row == -1) {
        continue;
      }
      // Make the move
      board[row][column] = turn + 1;
      // Send the updated board to all other processes
      for (int i = 0; i < world_size; i++) {
        if (i != world_rank) {
          MPI_Send(board, ROWS * COLS, MPI_INT, i, 0, MPI_COMM_WORLD);
        }
      }
    }

    // Check if the game is over
    int winner = checkForWin(turn + 1);
    if (winner) {
      std::cout << std::endl << "Player " << winner << "(" << (winner == 1 ? "O" : "X") << ") wins!" << std::endl;
      for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
          if (board[i][j] == 1) {
            std::cout << "O ";
          } else if (board[i][j] == 2) {
            std::cout << "X ";
          } else {
            std::cout << ". ";
          }
        }
        std::cout << std::endl;
      }
      break;
    }

    if (checkForDraw()) {
      std::cout << "It's a draw!" << std::endl;
      break;
    }

    // Change turns
    turn = (turn + 1) % world_size;
  }

  MPI_Finalize();
}
