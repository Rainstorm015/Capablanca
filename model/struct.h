/*** struct.h **************************************************************/
/*                                                                         */
/*     Objet  : data structure and general type for modelisation of a game */
/*              pour la modelisation d'une partie                          */
/*                                                                         */
/***************************************************************************/

#ifndef _TYPES_IMPO_H
#define _TYPES_IMPO_H

#include <stdio.h>
#include <stdlib.h>

/* Types imposes */

/* pices : 'P'awn, 'K' Knight, 'F' bishop, 'T' Rook, 'D' Queen, 'R'ing, 'A' Archbishop ou 'C' Chancelor */
typedef char Piece;

/* Color of a tile :  'B' white,  'N' black ou  'V' void */
typedef char Color;

/* Content of a tile */
typedef struct case_{
	Color color;
	Piece piece;
} chessTile;

/* Chessboard : tile index [0][0] indicate the tile (1,A) */

typedef chessTile Chessboard [8][10];

/* tile coordinates in the chessboard*/
typedef struct Coordinates_{
	int r; // row
	int c; // column
} Coordinates;

/* List of every possible moves */
typedef struct cellule {
	Coordinates start, end;
	struct cellule *next;
} Move;

typedef Move *MoveList;

MoveList historic;

/* player */
typedef struct{
	char name[20];
	int type, time;
} Player;

typedef struct {
	Player white, black;
} Type;

typedef struct cell {
	Piece promotion;
	chessTile enemy;
	Coordinates position;
	struct cell *next;
} Opponent;

typedef Opponent *OpponentList;

#endif
