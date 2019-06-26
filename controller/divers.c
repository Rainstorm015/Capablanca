/*** divers.c ***********************************************************/
/*                                                                      */
/*     Auteur : Adrien Legrand                                           */
/*     Objet  : Implementation du divers.h                              */
/*                                                                      */
/************************************************************************/

#include "../controller/divers.h"

int moveComparison(Move source, Move target) {
	if(source.start.r == target.start.r && source.start.c == target.start.c && source.end.r == target.end.r && source.end.c == target.end.c)
		return 1;
	return 0;
}

int coordinatesComparison(Coordinates source, Coordinates target) {
	if(source.r == target.r && source.c == target.c) return 1;
	return 0;
}

void chessboardCopy(Chessboard source, Chessboard target) {
	int i,j;
	for(i = 0 ; i < 8 ; i++) for(j = 0 ; j < 10 ; j++) target[i][j] = source[i][j];
}

void moveDisplay(Move elt) {
	printf("\nDeplacement de %c%d vers %c%d\n\n",'a'+elt.start.c,1+elt.start.r,'a'+elt.end.c,1+elt.end.r);
}

int occupationTest(Chessboard ec, Coordinates pos) {
	if(ec[pos.r][pos.c].color != 'V') return 1;
	else return 0;
}

int colorTest(Chessboard ec, Move cp) {
	if(occupationTest(ec, cp.end) && !oppositeColor(ec,cp)) return 1;
	else return 0;
}

void deletePiece(Chessboard ec, int r, int c) {
	ec[r][c].piece = ' ';
	ec[r][c].color = 'V';
}

Coordinates executeMove(Chessboard ec, Move cp) {
	Coordinates specialMove;
	specialMove = isTakenEnPassant(ec,cp);
	if(specialMove.r == -1) {
		specialMove = doACastling(ec,cp);
	}
	ec[cp.end.r][cp.end.c].color = ec[cp.start.r][cp.start.c].color;
	ec[cp.start.r][cp.start.c].color = 'V';
	ec[cp.end.r][cp.end.c].piece = ec[cp.start.r][cp.start.c].piece;
	ec[cp.start.r][cp.start.c].piece = ' ';
	return specialMove;
}
