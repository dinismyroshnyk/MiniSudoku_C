## 1. Goal

The objective of this project is to create a C program that enables users to play a simplified version of Sudoku. The program should store multiple Sudoku problems and present them to the user for solving.

## 2. Requirements

### The program should include the following features:

- a) Store multiple Sudoku problems. These problems should be saved in a file and automatically loaded into memory when the program runs.
- b) Allow the addition of new problems to the problem file. Each problem should have a unique name assigned by the user.
- c) Enable the renaming of a problem, provided no other problem shares the same name.
- d) Present the user with random problems from the existing set. The same problem should not be presented consecutively during a single program execution.
- e) Enable the completion of the Sudoku game. If a move is invalid (see rules in item 3), an error message should be displayed. For each valid move made by the user, the updated game state should be displayed. The game is considered lost if two invalid moves are made.
- f) Allow the removal of a number from the Sudoku grid, unless it is one of the initial numbers of the problem.
- g) Allow the user to abort a game and start a new one.
- h) Provide the following information:
     - A list of existing problems and the number of times each has been played during the current program execution.
     - The total number of games played, the number of games successfully completed, and the success rate (to one decimal place).
- i) Exit the program.

### Additional specifications:

- The program should operate using option menus.
- Appropriate messages should be displayed for each successful or unsuccessful operation (e.g., problem inserted, problem changed, invalid option, invalid number, invalid move, etc.).
- During a game, only number insertion/removal and game abortion should be allowed.
- After completing a game, the user should be given the option to start a new game or return to the main menu.
- The program should be capable of managing up to 100 problems.

## 3. Rules and references:

### The following rules should be checked when validating a move:
- a) Each column must contain the numbers 1 to 4 only once.
- b) Each row must contain the numbers 1 to 4 only once.
- c) Each 2x2 square must contain the numbers 1 to 4 only once.

### References:
- https://pt.wikibooks.org/wiki/Matem%C3%A1tica_divertida/Mini-sudoku
- https://www.sudokuonline.io/pt/criancas/numeros-4-4