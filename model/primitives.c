/*** primitives.c *******************************************************/
/*                                                                      */
/*     Auteur : Adrien Legrand                                           */
/*     Objet  : Implementation du primitives.h                          */
/*                                                                      */
/************************************************************************/

#include "../model/primitives.h"

void initChessboard(Chessboard ec) {
	int i,j;
	for(i = 0 ; i < 6 ; i++) {
		for(j = 0 ; j < 10 ; j++) {
			if(i < 2) {
				ec[i][j].color = 'B';
				ec[7-i][j].color = 'N';
				if(i == 1) {
					ec[i][j].piece = 'p';
					ec[7-i][j].piece = 'P';
				}
			}
			else {
				ec[i][j].piece = ' ';
				ec[i][j].color = 'V';
			}
		}
	}
	ec[0][0].piece = ec[0][9].piece = 't';
	ec[7][0].piece = ec[7][9].piece = 'T';
	ec[0][1].piece = ec[0][8].piece = 'k';
	ec[7][1].piece = ec[7][8].piece = 'K';
	ec[0][2].piece = 'a';
	ec[7][2].piece = 'A';
	ec[0][3].piece = ec[0][6].piece = 'f';
	ec[7][3].piece = ec[7][6].piece = 'F';
	ec[0][7].piece = 'c';
	ec[7][7].piece = 'C';
	ec[0][4].piece = 'd';
	ec[7][4].piece = 'D';
	ec[0][5].piece = 'r';
	ec[7][5].piece = 'R';
}

void chessboardAssignment(Chessboard ec) {
	char c;
	int i, j;
	int colorName;
	for(i = 0 ; i < 8 ; i++) {
		for(j = 0,c = 'a' ; j < 11 ; j++,c++) {
			do {
				printf("\nChoose the color on %c%d (B, N ou V) :\n",c,i+1);
				scanf(" %c",&ec[i][j].color);
				if(ec[i][j].color == 'B' || ec[i][j].color == 'N') {
					if(ec[i][j].color == 'B') colorName = 32;
					else colorName = 0;
					do {
						printf("\tChoose the piece on %c%d (%c, %c, %c, %c, %c, ou %c) :\n",c,i+1,'P'+colorName,'C'+colorName,'F'+colorName,'T'+colorName,'D'+colorName,'R'+colorName);
						scanf(" %c",&ec[i][j].piece);
					}
					while(ec[i][j].piece != 'P'+colorName && ec[i][j].piece != 'C'+colorName && ec[i][j].piece != 'F'+colorName && ec[i][j].piece != 'T'+colorName && ec[i][j].piece != 'D'+colorName && ec[i][j].piece != 'R'+colorName);
				}
				else if(ec[i][j].color == 'V') ec[i][j].piece = ' ';
			}
			while(ec[i][j].color != 'V' && ec[i][j].color != 'B' && ec[i][j].color != 'N');
		}
	}		
}

void chessboardLoading(Chessboard ec, MoveList l, Color *color) {
	while(!isEmpty(l)) {
		executeMove(ec,*l);
		switchColor(color);
		l = l->next;
	}
}

void chessboardDisplay(Chessboard ec) {
	int i,j;
	char cols = 'A';
	printf("\n\n\tAffichage de l'echiquier\n");
	printf("\n ---------------------------------\n");
	for(i = 7 ; i > -2 ; i--) {
		printf(" ");
		if(i == -1) for(cols = 'A' ; cols < 'I'; cols++) printf("  %c ",cols);
		else {
			printf("|");
			for(j = 0 ; j < 8 ; j++) printf(" %c |",ec[i][j].piece);
			printf(" %d\n ---------------------------------\n",i+1);
		}
	}
	printf("\n\n");

}

int oppositeColor(Chessboard ec, Move test) {
	if((ec[test.start.r][test.start.c].color == 'B' && ec[test.end.r][test.end.c].color == 'N') || (ec[test.start.r][test.start.c].color == 'N' && ec[test.end.r][test.end.c].color == 'B'))
		return 1;
	else return 0;
}

void switchColor(Color *color) {
	if(*color == 'B') *color = 'N';
	else *color = 'B';
}

Color opponentOf(Color color) {
	if(color == 'B') {
		return 'N';
	}
	else {
		return 'B';
	}
}

void displayMovesTile(Chessboard ec, Coordinates pos, MoveList l) {
	MoveList buffer = l;
	while(!isEmpty(buffer)) {
		insert(ec,*buffer);
		buffer = buffer->next;
	}
	chessboardDisplay(ec);
	displayPossibleMoves(l);
}

void possibleMovesTiles(Chessboard ec, Coordinates pos, MoveList *l, MoveList historic) {
	int colorName = 0;
	if(ec[pos.r][pos.c].color == 'B') colorName = 32;
	if(ec[pos.r][pos.c].piece == 'P'+colorName) {
		pawnMoves(ec,pos,l);
		moveEnPassant(ec,pos,l,historic);
	}
	else if(ec[pos.r][pos.c].piece == 'A'+colorName) archbishopMoves(ec,pos,l);
	else if(ec[pos.r][pos.c].piece == 'C'+colorName) chancellorMoves(ec,pos,l);
	else if(ec[pos.r][pos.c].piece == 'K'+colorName) knightMoves(ec,pos,l);
	else if(ec[pos.r][pos.c].piece == 'F'+colorName) bishopMoves(ec,pos,l);
	else if(ec[pos.r][pos.c].piece == 'T'+colorName) rookMoves(ec,pos,l);
	else if(ec[pos.r][pos.c].piece == 'D'+colorName) queenMoves(ec,pos,l);
	else if(ec[pos.r][pos.c].piece == 'R'+colorName) {
		castling(ec,pos,l,historic);
		kingMoves(ec,pos,l);
	}
}

void generator(Chessboard ec, Color color, MoveList *l) {
	Coordinates pos;
	for(pos.r = 0 ; pos.r < 8 ; pos.r++) {
		for(pos.c = 0 ; pos.c < 10 ; pos.c++){
			if(ec[pos.r][pos.c].color == color) {
				possibleMovesTiles(ec,pos,l,historic);
			}
		}
	}
}

void displayPossibleMoves(MoveList l) {
	printf("LISTE DE COUPS POSSIBLES :\n\n");
	displayList(l);
}
