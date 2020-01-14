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
	// jesli ok to wypisac szachownice z numerami kolejnych krokow
	int rootReturned = root(board, CHESSBOARD_SIZE, 1, x0, y0, HorseMove);
	if(rootReturned == 0)
		printf("You  can NOT visit every single cell just once!!!\n\n");
	else
		printChessBoard(board, CHESSBOARD_SIZE);

	//zwolnic pamiec
	freeChessboard(&board);

	return 0;
}


// jezeli mozna sie ruszyc to zwracam 1, jezeli nie da sie to 0
int move(int** pChessBoard, int nDim, int move, int x, int y, int* px, int* py, Point* pHorseMoves)
{
	*px = x + pHorseMoves[move].x;
	*py = y + pHorseMoves[move].y;
	if( *px < nDim && *px >= 0 && *py < nDim && &py >= 0
		&& pChessBoard[*px][*py] == 0 )
		return 1;
	return 0;

}

int root(int** pChessBoard, int nDim, int moveNo, int x, int y, Point* pHorseMoves)
{
	// tabl pChessBoard pamieta droge - 0 pole odiwedzone 1..nDim^2 numer kolejnego ruchu

	//wstawic kolejny numer ruchu
	//jesli koniec to zwracamy 1
	//else
		//zdefiniowac wszystkie mozliwosci ruchu
		//jesli ruch do nowej pozycji mozliwy
		// to rekurencyjnie wykonac ruch moveNo+1
		// jesli zwrocono 1 z rekurencji to zwrocic 1
	// jezeli wracamy to ustawiamy w pChessBoard[x][y] na 0 bo ten ruch byl zly
	pChessBoard[x][y] = moveNo;

	if( moveNo == nDim * nDim )
		return 1;
	
	int newX, newY;
	int moveIndex = 0;
	while( moveIndex < HORSE_MOVES )
	{
		if( move(pChessBoard, nDim, moveIndex, x, y, &newX, &newY, pHorseMoves) == 1 )
		{
			int rootReturn = root(pChessBoard, nDim, moveNo + 1, newX, newY, pHorseMoves);
			if( rootReturn == 1 )
				return 1;
			pChessBoard[newX][newY] = 0;
		}
		moveIndex++;
	}
	return 0;
}

int** createChessboard(int nDim)
{
	int** rows = (int**)calloc(nDim, sizeof(int*));
	if( !rows )
		return NULL;
	for( int i = 0; i < nDim; i++ )
	{
		rows[i] = (int*)calloc(nDim, sizeof(int));
		if( !rows[i] )
			return NULL;
	}
	return rows;
}

void printChessBoard(int** pChessBoard, int nDim)
{
	for( int i = 0; i < nDim; i++ )
	{
		for( int j = 0; j < nDim; j++ )
			printf("%d ", pChessBoard[i][j]);
		printf("\n");
	}
}

void freeChessboard(int*** pChessBoard)
{
	free(*pChessBoard[0]);
	free(*pChessBoard);
	*pChessBoard = NULL;
}
