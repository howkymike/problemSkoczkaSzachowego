#include "skoczek.h"


int main(int argc, char* argv[])
{
	//odczytywac ustawienie poczatkowe x0, y- konika szachowego z parametrow
	if (argc != 3)
	{
		perror("Invalid number of arguments!\nUsage: SkoczekSzachowy.exe <x0> <y0>");
		return 2;
	}
	int x0 = atoi(argv[1]);
	int y0 = atoi(argv[2]);

	// sprawdzanie czy poprawne
	if (x0 < 0 || y0 < 0 || x0 > CHESSBOARD_SIZE || y0 > CHESSBOARD_SIZE)
	{
		perror("Invalid arguments!");
		return EXIT_FAILURE;
	}

	//wykreowac dynamicznie tablice kwadratowa o rozmiarze CHESSBOARD_SIZE
	int** board = createChessboard(CHESSBOARD_SIZE);
	if(!board)
	{
		perror("Allocation error");
		return EXIT_FAILURE;
	}

	//zdefiniowac tavlice do pamietania mizliwych offsetow ruchow
	Point HorseMove[HORSE_MOVES] = { {-2,1},
									 {-1,2},
									 {1,2},
									 {2,1},
									 {2,-1},
									 {1,-2},
									 {-1,-2},
									 {-2,-1} };


	// jezeli nie znaleziono drogi od (x0,y0) - wypisac
	// "** Nie ma możliwości odwiedzić jjednoczescie każdego pola!!!\n\n";
	int rootReturned = root(board, CHESSBOARD_SIZE, 1, x0, y0, HorseMove);
	if(rootReturned == 0)
		printf("You  can NOT visit every single cell just once!!!\n\n");
	// jesli ok to wypisac szachownice z numerami kolejnych krokow
	else
		printChessBoard(board, CHESSBOARD_SIZE);

	//zwolnic pamiec
	freeChessboard(&board);

	return 0;
}
