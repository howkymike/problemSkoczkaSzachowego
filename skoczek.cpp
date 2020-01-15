#include "skoczek.h"

// jezeli mozna sie ruszyc to zwracam 1, jezeli nie da sie to 0
int move(int** pChessBoard, int nDim, int move, int x, int y, int* px, int* py, Point* pHorseMoves)
{
	*px = x + pHorseMoves[move].x;
	*py = y + pHorseMoves[move].y;
	if (*px < nDim && *px >= 0 && *py < nDim && &py >= 0
		&& pChessBoard[*px][*py] == 0)
		return 1;
	return 0;
}

int root(int** pChessBoard, int nDim, int moveNo, int x, int y, Point* pHorseMoves)
{
	static int count = 0;

	//wstawic kolejny numer ruchu
	pChessBoard[x][y] = moveNo;

	//jesli koniec to zwracamy 1
	if (moveNo == nDim * nDim)
	{
		printf("Number of trials: %d\n\n", count);
		return 1;
	}

	//else
	//zdefiniowac wszystkie mozliwosci ruchu
	int newX, newY;
	int moveIndex = 0;
	while (moveIndex < HORSE_MOVES)
	{
		if (move(pChessBoard, nDim, moveIndex, x, y, &newX, &newY, pHorseMoves) == 1)
		{
			count++;
			//jesli ruch do nowej pozycji mozliwy
			// to rekurencyjnie wykonac ruch moveNo+1
			int rootReturn = root(pChessBoard, nDim, moveNo + 1, newX, newY, pHorseMoves);
			// jesli zwrocono 1 z rekurencji to zwrocic 1
			if (rootReturn == 1)
				return 1;
			// jezeli wracamy to ustawiamy w pChessBoard[x][y] na 0 bo ten ruch byl zly
			pChessBoard[newX][newY] = 0;
		}
		moveIndex++;
	}
	return 0;
}

int** createChessboard(int nDim)
{
	int** rows = (int**)calloc(nDim, sizeof(int*));
	if (!rows)
		return NULL;
	for (int i = 0; i < nDim; i++)
	{
		rows[i] = (int*)calloc(nDim, sizeof(int));
		if (!rows[i])
			return NULL;
	}
	return rows;
}

void printChessBoard(int** pChessBoard, int nDim)
{
	for (int i = 0; i < nDim; i++)
	{
		for (int j = 0; j < nDim; j++)
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
