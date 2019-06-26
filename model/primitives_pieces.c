/*** primitives_pieces.c ************************************************/
/*                                                                      */
/*     Objet  : Implementation du primitives_pieces.h                   */
/*                                                                      */
/************************************************************************/

#include "../model/primitives_pieces.h"

/************************************************************************/
/*                                                                      */
/*  Subject : Primitive for Pawn                                        */
/*                                                                      */
/************************************************************************/

int pawnMov(Chessboard ec, Coordinates pos) {
	int n_time = 1;
	int k_limit = 7; // Variables to manage both colors simultaneously
	
	if(ec[pos.r][pos.c].color == 'N') 
	{
		n_time = -1;
	}
	else {
		k_limit = 0;
	}
	
	if(ec[pos.r+n_time*1][pos.c].color == 'V' && n_time * pos.r < n_time * (7 - k_limit)) 
	{
		if(ec[pos.r+n_time*2][pos.c].color == 'V' && pos.r == k_limit + n_time) 
		{
			return 2; // Case of two tiles at once
		}
		else 
		{
			return 1;
		}
	}
	else 
	{
		return 0;
	}
}

int pawnColorTest(Chessboard ec, Move test) 
{
	if(oppositeColor(ec,test)) 
	{
		return 1;
	}
	else 
	{
		return 0;
	}
}

int pawnTake(Chessboard ec, Move test) 
{
	int n_time = 1;
	int k_limit = 0; // Variables to manage both colors simultaneously
	if(ec[test.start.r][test.start.c].color == 'B') 
	{
		k_limit = 7;
	}
	else {
		n_time = -1;
	}
	if(n_time * test.start.r < n_time * k_limit) 
	{
		test.end.r = test.start.r + n_time;
		return pawnColorTest(ec,test);
	}
	else {
		return 0;
	}
}

int pawnTakeLeft(Chessboard ec, Coordinates pos) 
{
	Move test;
	if(pos.c > 0) 
	{
		test.start = pos;
		test.end.c = test.start.c - 1;
		return pawnTake(ec,test);
	}
	else 
	{
		return 0;
	}
}

int pawnTakeRight(Chessboard ec, Coordinates pos)
 {
	Move test;
	if(pos.c < 9) 
	{
		test.start = pos;
		test.end.c = test.start.c + 1;
		return pawnTake(ec,test);
	}
	else 
	{
		return 0;
	}
}

void pawnMoves(Chessboard ec, Coordinates pos, MoveList *l) 
{
	int i = 1;
	int n_time = 1;
	Move test;
	test.start = pos;
	
	if(ec[pos.r][pos.c].color == 'N') 
	{
		n_time = -1;
	}
	for(i = 1 ; i <= pawnMov(ec,pos) ; i++) 
	{
		test.end.r = test.start.r + n_time * i;
		test.end.c = test.start.c;
		insertInList(test,l);
	}
	
	test.end.r = test.start.r + n_time;
	if(pawnTakeLeft(ec,pos)) 
	{
		test.end.c = test.start.c - 1;
		insertInList(test,l);
	}
	
	if(pawnTakeRight(ec,pos)) 
	{
		test.end.c = test.start.c + 1;
		insertInList(test,l);
	}
}

void switchPawn(Chessboard ec, Coordinates pos, int i)
 {
	int colorName = 0; // Variables to manage both colors simultaneously
	if(ec[pos.r][pos.c].color == 'B')
	{
		colorName = 32;
	}
	switch(i) 
	{
		case 1 : ec[pos.r][pos.c].piece = 'D'+colorName; break;
		case 2 : ec[pos.r][pos.c].piece = 'T'+colorName; break;
		case 3 : ec[pos.r][pos.c].piece = 'F'+colorName; break;
		case 4 : ec[pos.r][pos.c].piece = 'C'+colorName; break;
	}
}

void pawnPromotion(Chessboard ec, Coordinates pos) 
{
	int i;
	printf("\n\t----------------------------");
	printf("\n\t-    PROMOTION DU PION     -");
	printf("\n\t----------------------------");
	printf("\n\t- 1 : Dame                 -");
	printf("\n\t- 2 : Tour                 -");
	printf("\n\t- 3 : Fou                  -");
	printf("\n\t- 4 : Cavalier             -");
	printf("\n\t----------------------------\n");
	
	do
	{
		scanf(" %d",&i);
	} while(i < 1 || i > 4);
	
	switchPawn(ec,pos,i);
}

void moveEnPassant(Chessboard ec, Coordinates pos, MoveList *l, MoveList previousMove) 
{
	Move cp;
	int colorName = 0;
	int n_time = 1;  // Variables to manage both colors simultaneously
	
	if(!isEmpty(previousMove))
		{
		if(ec[pos.r][pos.c].color == 'B') {
			colorName = 32;	
		}
		else {
			n_time = -1;
		}
		
		if((ec[pos.r][pos.c].piece == 'p' && pos.r == 4) || (ec[pos.r][pos.c].piece == 'P' && pos.r == 3)) 
		{
			while(previousMove->next != NULL)
			{
				previousMove = previousMove->next;
			}
			if(ec[previousMove->end.r][previousMove->end.c].piece == 'p'-colorName &&
				previousMove->end.r == previousMove->start.r - n_time * 2 && previousMove->end.r == pos.r &&
				(previousMove->end.c == pos.c - 1 || previousMove->end.c == pos.c + 1)) 
				{
				cp.start = pos;
				cp.end.r = previousMove->end.r + n_time * 1;
				cp.end.c = previousMove->start.c;
				insertInList(cp,l);
				}	
		}
	}
}

Coordinates isTakenEnPassant(Chessboard ec, Move cp) 
{
	int colorName = 0;
	int n_time = 1; // Variables to manage both colors simultaneously
	Coordinates takenEnPassant;
	takenEnPassant.r = -1;
	
	if(ec[cp.start.r][cp.start.c].color == 'B')
	{
		colorName = 32;
	}
	else 
	{
		n_time = -1;
	}
	if(ec[cp.start.r][cp.start.c].piece == 'P'+colorName) 
	{
		if(!occupationTest(ec,cp.end) && (cp.end.c == cp.start.c - 1 || cp.end.c == cp.start.c + 1)) 
		{
			takenEnPassant.r = cp.end.r - n_time;
			takenEnPassant.c = cp.end.c;
		}
	}
	return takenEnPassant;
}


/************************************************************************/
/*                                                                      */
/*  Subject : Primitive for Knight                                      */
/*                                                                      */
/************************************************************************/

void knightMoves(Chessboard ec, Coordinates pos, MoveList *l) 
{
	Move test;
	test.start = pos;
	
	test.end.r = test.start.r + 2;
	test.end.c = test.start.c + 1;
	if(test.end.r < 8 && test.end.c < 10 && !colorTest(ec,test))
	{
		insertInList(test,l);
	}
	
	test.end.c = test.start.c - 1;
	if(test.end.r < 8 && test.end.c > -1 && !colorTest(ec,test)) 
	{
		insertInList(test,l);
	}
	
	test.end.r = test.start.r - 2;
	if(test.end.r > -1 && test.end.c > -1 && !colorTest(ec,test)) 
	{
		insertInList(test,l);
	}
	
	test.end.c = test.start.c + 1;
	if(test.end.r > -1 && test.end.c < 10 && !colorTest(ec,test)) 
	{
		insertInList(test,l);
	}
	
	test.end.r = test.start.r + 1;
	test.end.c = test.start.c + 2;
	if(test.end.r < 8 && test.end.c < 10 && !colorTest(ec,test)) 
	{
		insertInList(test,l);
	}
	
	test.end.r = test.start.r - 1;
	if(test.end.r > -1 && test.end.c < 10 && !colorTest(ec,test))
	{
		insertInList(test,l);
	}
	
	test.end.c = test.start.c - 2;
	if(test.end.r > -1 && test.end.c > -1 && !colorTest(ec,test)) 
	{
		insertInList(test,l);
	}
	
	test.end.r = test.start.r + 1;
	if(test.end.r < 8 && test.end.c > -1 && !colorTest(ec,test)) 
	{
		insertInList(test,l);
	}
}


/************************************************************************/
/*                                                                      */
/*  Subject : Primitive for Bishop                                      */
/*                                                                      */
/************************************************************************/

void bishopMoves(Chessboard ec, Coordinates pos, MoveList *l) 
{
	Move test;
	test.start = pos;
	test.end.r = test.start.r + 1;
	test.end.c = test.start.c + 1;
	
	while(test.end.r < 8 && test.end.c < 10 && !occupationTest(ec, test.end)) 
	{
		insertInList(test,l);
		test.end.r++;
		test.end.c++;
	}
	
	if(test.end.r < 8 && test.end.c < 10 && oppositeColor(ec,test)) 
	{
		insertInList(test,l);
	}
	
	test.end.r = test.start.r + 1;
	test.end.c = test.start.c - 1;
	
	while(test.end.r < 8 && test.end.c > -1 && !occupationTest(ec, test.end))
	{
		insertInList(test,l);
		test.end.r++;
		test.end.c--;
	}
	
	if(test.end.r < 8 && test.end.c > -1 && oppositeColor(ec,test))
	{
		insertInList(test,l);
	}
	
	test.end.r = test.start.r - 1;
	test.end.c = test.start.c + 1;
	
	while(test.end.r > -1 && test.end.c < 10 && !occupationTest(ec, test.end)) 
	{
		insertInList(test,l);
		test.end.r--;
		test.end.c++;
	}
	
	if(test.end.r > -1 && test.end.c < 10 && oppositeColor(ec,test)) 
	{
		insertInList(test,l);
	}
	
	test.end.r = test.start.r - 1;
	test.end.c = test.start.c - 1;
	
	while(test.end.r > -1 && test.end.c > -1 && !occupationTest(ec, test.end)) 
	{
		insertInList(test,l);
		test.end.r--;
		test.end.c--;
	}
	
	if(test.end.r > -1 && test.end.c > -1 && oppositeColor(ec,test))
		{
		insertInList(test,l);
	}
}


/************************************************************************/
/*                                                                      */
/*  Subject : Primitive for Rook                                        */
/*                                                                      */
/************************************************************************/

void rookMoves(Chessboard ec, Coordinates pos, MoveList *l) 
{
	Move test;
	test.start = pos;
	test.end.c = test.start.c;
	test.end.r = test.start.r + 1;
	
	while(test.end.r < 8 && !occupationTest(ec, test.end)) 
	{
		insertInList(test,l);
		test.end.r++;
	}
	
	if(test.end.r < 8 && oppositeColor(ec,test)) 
	{
		insertInList(test,l);
	}
	
	test.end.r = test.start.r - 1;
	
	while(test.end.r > -1 && !occupationTest(ec, test.end))
	{
		insertInList(test,l);
		test.end.r--;
	}
	
	if(test.end.r > -1 && oppositeColor(ec,test)) 
	{
		insertInList(test,l);
	}
	
	test.end.r = test.start.r;
	test.end.c = test.start.c + 1;
	
	while(test.end.c < 10 && !occupationTest(ec, test.end)) 
	{
		insertInList(test,l);
		test.end.c++;
	}
	
	if(test.end.c < 10 && oppositeColor(ec,test)) 
	{
		insertInList(test,l);
	}
	
	test.end.c = test.start.c - 1;
	
	while(test.end.c > -1 && !occupationTest(ec, test.end)) 
	{
		insertInList(test,l);
		test.end.c--;
	}
	
	if(test.end.c > -1 && oppositeColor(ec,test)) 
	{
		insertInList(test,l);
	}
}

/************************************************************************/
/*                                                                      */
/*  Subject : Primitive for Archbishop                                  */
/*                                                                      */
/************************************************************************/

void archbishopMoves(Chessboard ec, Coordinates pos, MoveList *l) 
{
	bishopMoves(ec, pos, l);
	knightMoves(ec, pos, l);
}


/************************************************************************/
/*                                                                      */
/*  Subject : Primitive for Chancellor                                  */
/*                                                                      */
/************************************************************************/

void chancellorMoves(Chessboard ec, Coordinates pos, MoveList *l) 
{
	rookMoves(ec, pos, l);
	knightMoves(ec, pos, l);
}



/************************************************************************/
/*                                                                      */
/*  Subject : Primitive for Queen                                       */
/*                                                                      */
/************************************************************************/

void queenMoves(Chessboard ec, Coordinates pos, MoveList *l) 
{
	bishopMoves(ec, pos, l);
	rookMoves(ec, pos, l);
}


/************************************************************************/
/*                                                                      */
/*  Subject : Primitive for King                                        */
/*                                                                      */
/************************************************************************/

void kingMoves(Chessboard ec, Coordinates pos, MoveList *l) 
{
	Move test;
	test.start = pos;
	
	if(test.start.r < 7)
	{
		test.end.r = test.start.r + 1;
		if(test.start.c > 0) 
		{
			test.end.c = test.start.c - 1;
			if(!colorTest(ec,test)) 
			{
				insertInList(test,l);
			}
		}
		if(test.start.c < 9) 
		{
			test.end.c = test.start.c + 1;
			if(!colorTest(ec,test)) 
			{
				insertInList(test,l);
			}
		}
		test.end.c = test.start.c;
		if(!colorTest(ec,test))
		{
			insertInList(test,l);
		}
	}
	
	test.end.r = test.start.r;
	
	if(test.start.c > 0) 
	{
		test.end.c = test.start.c - 1;
		if(!colorTest(ec,test)) 
		{
			insertInList(test,l);
		}
	}
	if(test.start.c < 9) 
	{
		test.end.c = test.start.c + 1;
		if(!colorTest(ec,test))
		{
			insertInList(test,l);
		}
	}
	if(test.start.r > 0) 
	{
		test.end.r = test.start.r - 1;
		if(test.start.c > 0) 
		{
			test.end.c = test.start.c - 1;
			if(!colorTest(ec,test)) 
			{
				insertInList(test,l);
			}
		}
		test.end.c = test.start.c;
		if(!colorTest(ec,test))			
		{
			insertInList(test,l);
		}
		if(test.end.c < 9) 
		{
			test.end.c = test.start.c + 1;
			if(!colorTest(ec,test))			
			{
				insertInList(test,l);
			}
		}
	}
}

void castling(Chessboard ec, Coordinates pos, MoveList *l, MoveList historic) 
{
	int k_r = 0;
	int colorName = 0;
	Move castling;
	if(ec[pos.r][pos.c].color == 'B') 
	{
		colorName = 32;
	}
	else
	{
		k_r = 9;
	}
	if(pos.r == k_r && pos.c == 5 && ec[pos.r][pos.c].piece == 'R'+colorName) 
	{
		castling.start = pos;
		castling.end.r = pos.r;
		castling.end.c = 0;
		
		if(ec[castling.end.r][castling.end.c].piece == 'T'+colorName) 
		{
			insertCastling(ec,castling,l,historic);
		}
		castling.end.c = 9;
		
		if(ec[castling.end.r][castling.end.c].piece == 'T'+colorName) 
		{
			insertCastling(ec,castling,l,historic);
		}
	}
}

void insertCastling(Chessboard ec, Move cp, MoveList *l, MoveList historic) 
{
	Move test, king;
	int k = 1; // k allows you to manage large and small castling without distinction
	if(!hasMoved(cp.start,historic) && !hasMoved(cp.end,historic)) 
	{
		test.start = test.end = cp.start;
		if(!cp.end.c)
		{
			k = -1;
		}
		do
		{
			test.end.c += k;
		}while(!occupationTest(ec,test.end));
		
		if(test.end.c == 0 || test.end.c == 9) 
		{
			king.start = cp.start;
			king.end.r = king.start.r;
			king.end.c = king.start.c + 2*k;
			insertInList(king,l);
		}
	}
}

Coordinates doACastling(Chessboard ec, Move cp)
 {
	int k = 0;
	char king = 'R';
	Coordinates tour;
	tour.r = -1;
	
	if(ec[cp.start.r][cp.start.c].color == 'B') 
	{
		king = 'r';
	}
	
	if(ec[cp.start.r][cp.start.c].piece == king)
	{
		if(cp.end.c == cp.start.c - 2) 
		{
			k = -1;
			tour.c = 0;
		}
		else if(cp.end.c == cp.start.c + 2) 
		{
			k = 1;
			tour.c = 9;
		}
		
		if(k) 
		{
			tour.r = cp.start.r;
			ec[tour.r][cp.start.c + k].piece = ec[tour.r][tour.c].piece;
			ec[tour.r][cp.start.c + k].color = ec[tour.r][tour.c].color;						
		}
	}
	return tour;
}

int check(Chessboard ec, Color kingColor) 
{
	int test = 0;
	int kingPresence = 1;
	char king = 'R';
	MoveList l, buffer;
	Coordinates kingPosition;
	kingPosition.r = kingPosition.c = 0;
	if(kingColor == 'B') 
	{
		king = 'r';
	}

	while(ec[kingPosition.r][kingPosition.c].piece != king && kingPresence) 
	{
		if(kingPosition.c == 9)
		{
			kingPosition.r++;
			kingPosition.c = 0;
		}
		
		else 
		{
			kingPosition.c++;
		}
		if(kingPosition.r == 8) 
		{
			kingPresence = 0;
		}
	}

	if(kingPresence) // all players must have a king
	{ 
		initList(&l);
		generator(ec,opponentOf(kingColor),&l);
		buffer = l;
		while(!isEmpty(buffer) && !test) 
		{
			if(coordinatesComparison(kingPosition, buffer->end)) 
			{
				test = 1;
			}
			else 
			{
				buffer = buffer->next;
			}
		}
		destroyList(ec,&l);
	}
	
	return test;
}

void pin(Chessboard ec, Move elt, MoveList *l) 
{
	int castling = 1;
	Chessboard buffer;
	chessboardCopy(ec,buffer);
	executeMove(buffer,elt);
	int testCheck = check(buffer,ec[elt.start.r][elt.start.c].color);
	/* test */
	char king = ec[elt.start.r][elt.start.c].piece;
	if(testCheck){
		printf("Check for %c\n", king);
	}
	/* end test */
	if(check(buffer,ec[elt.start.r][elt.start.c].color)) 
	{
		removePiece(ec,elt,l);
		
		if((ec[elt.start.r][elt.start.c].piece == 'R' || ec[elt.start.r][elt.start.c].piece == 'r')) 
		{
			if(elt.end.c == elt.start.c - 1)
			{
				elt.end.c--;
			}
			else if(elt.end.c == elt.start.c + 1)
			{
				elt.end.c++;
			}
			else
			{
				castling = 0;
			}
			if(castling && isInTheList(elt,*l))
			{
				removePiece(ec,elt,l);
			}
		}
	}
}

int checkmate(Chessboard ec, Color color) 
{
	MoveList mat;
	int test = 0;
	initList(&mat);
	generator(ec,color,&mat);
	removeCheck(ec,&mat);
	
	if(isEmpty(mat))
	{
		test = 1;
	}
	
	destroyList(ec,&mat);
	return test;
}

void removeCheck(Chessboard ec, MoveList *l) 
{
	MoveList buffer = *l;
	
	while(!isEmpty(buffer)) 
	{
		pin(ec,*buffer,l);
		buffer = buffer->next;
	}
}

int checkmateTest(Chessboard ec, Color color) 
{
	int test;
	if(checkmate(ec,color)) 
	{
		if(check(ec,color)) test = 3;
		
		else 
		{
			test = 2;
		}
	}
	else 
	{
		if(check(ec,color))
		{
			test = 1;
		}
		else
		{
			test = 0;
		}
	}
	return test;
}
