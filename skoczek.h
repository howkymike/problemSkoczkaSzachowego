#pragma once

#include <stdio.h>
#include <stdlib.h>

#define CHESSBOARD_SIZE 7
#define HORSE_MOVES 8

typedef struct tagPoint
{
    int x;
    int y;
} Point;

/* pChessBoard - szachownica (kwadratowa_ - pamieta ruchy
   nDim- rozmiar szachownicy
   move - numer mozliwego ruchu konia szachowego (indeks pHorseMove))
   x,y - indexy w tablicy skad wykonujemy kolejny ruch
   px, py - nowe wspolrzedne
   pHorseMoves - offsety (x i y) dla obliczenia kolejnej możliwości skoku konia z zadanego punktu
*/
int move(int** pChessBoard, int nDim, int move, int x, int y, int* px, int* py, Point* pHorseMoves);

/* pChessBoard - szachownica (kwadratowa o rozmiarze nDim)
   moveNo - numer ruchu (do psrawdzenia czy juz wszystkie pola odwiedzone == nDim*nDim )
   x,y - wspol skad robimy kolejny ruch
   pHorseMoves - offsety (ziy) wszystkich mozliwych skosków konia z zadanej pozycji

    tabl pChessBoard pamieta droge - 0 pole odiwedzone 1..nDim^2 numer kolejnego ruchu
   -krótka funkcja, rekurencyjna!!!!jezeli powracam z wartoscia 0 to mam wyzerowac(bo to byl zły ruch i znowu wstawiam numer i jade dalej)
   */
int root(int** pChessBoard, int nDim, int moveNo, int x, int y, Point* pHorseMoves);

//kreuje i zeruje tablice (chyba ze calloc)
int** createChessboard(int nDim);

//zwalnia tablice
void freeChessboard(int*** pChessBoard);	// nie potrzebny nDim bo robimy wskazniki na tablice

void printChessBoard(int** pChessBoard, int nDim);
