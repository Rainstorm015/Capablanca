/*** primitives_listes.c ************************************************/
/*                                                                      */
/*     Subject  : primitives_listes.h implementation                    */
/*                                                                      */
/************************************************************************/

#include "../model/primitives_listes.h"

void initList(MoveList *l) {
	(*l) = NULL;
}

int isEmpty(MoveList l) {
	if(l == NULL) {
		return 1;
	}
	else {
		return 0;
	}
}

int isInTheList(Move elt, MoveList l) {
	while(!isEmpty(l)) {
		if(moveComparison(elt,*l)) {
			return 1;
		}
		else {
			l = l->next;
		}
	}
	return 0;
}

int hasMoved(Coordinates elt, MoveList l) {
	while(!isEmpty(l)) {
		if(coordinatesComparison(elt,l->start)) {
			return 1;
		}
		else {
			l = l->next;
		}
	}
	return 0;
}

void displayList(MoveList l) {
	if(isEmpty(l)) {
		printf("Vide\n");
	}
	else while(!isEmpty(l)) {
		printf("%c%d en %c%d\n",'a'+l->start.c,1+l->start.r,'a'+l->end.c,1+l->end.r);
		l = l->next;
	}
	printf("\n");
}

void insertInList(Move elt, MoveList *l) {
	MoveList buffer;
	if(!isEmpty(*l)) {
		buffer = *l;
		while(buffer->next != NULL) buffer = buffer->next;
		buffer->next = malloc(sizeof(Move));
		buffer = buffer->next;
	}
	else {
		*l = malloc(sizeof(Move));
		buffer = *l;
	}
	buffer->start = elt.start;
	buffer->end = elt.end;
	buffer->next = NULL;
}

void insert(Chessboard ec, Move elt) {
	if(ec[elt.end.r][elt.end.c].piece == ' ') ec[elt.end.r][elt.end.c].piece = 'X';
}

void removeInList(Move elt, MoveList *l) {
	MoveList buffer = *l; 
	MoveList t1; 
	MoveList before;
	int test;
	if(moveComparison(*buffer,elt)) {
		*l = (*l)->next;
	}
	else {
		t1 = before = buffer;
		test = 0;
		while(!isEmpty(buffer)) {
			if(moveComparison(*buffer,elt)) {
				t1 = before;
				test = 1;
			}
			before = buffer;
			buffer = buffer->next;
		}
		if(test) t1->next = t1->next->next;
	}
	free(buffer);
}

void removePiece(Chessboard ec, Move elt, MoveList *l) {
	if(ec[elt.end.r][elt.end.c].piece == 'X') {
		ec[elt.end.r][elt.end.c].piece = ' ';
	}
	removeInList(elt,l);
}

void destroyList(Chessboard ec, MoveList *l) {
	MoveList buffer = *l;
	while(!isEmpty(buffer)) {
		if(ec[buffer->end.r][buffer->end.c].piece == 'X') {
			ec[buffer->end.r][buffer->end.c].piece = ' ';
		}
		buffer = buffer->next;
	}
	while(!isEmpty(*l)){
		free(*l);
		*l = (*l)->next;
	}
}

/*=================================================================*/

void insertInOpponentList(Chessboard ec, Coordinates pos,OpponentList *eatenPiece) {
	OpponentList buffer;
	if(*eatenPiece != NULL) {
		buffer = *eatenPiece;
		while(buffer->next != NULL) {
			buffer = buffer->next;
		}
		buffer->next = malloc(sizeof(Opponent));
		buffer = buffer->next;
	}
	else {
		*eatenPiece = malloc(sizeof(Opponent));
		buffer = *eatenPiece;
	}
	buffer->enemy.piece = ec[pos.r][pos.c].piece;
	buffer->enemy.color = ec[pos.r][pos.c].color;
	buffer->position = pos;
	buffer->promotion = ' ';
	buffer->next = NULL;
}

void addOpponentInformations(Chessboard ec, Coordinates pos, OpponentList *eatenPiece) {
	OpponentList buffer;
	if(*eatenPiece != NULL) {
		buffer = *eatenPiece;
		while(buffer->next != NULL) {
			buffer = buffer->next;
		}
		buffer->enemy.piece = ec[pos.r][pos.c].piece;
		buffer->enemy.color = ec[pos.r][pos.c].color;
		buffer->position = pos;
	}
}

void addPromotionInformation(Chessboard ec, Coordinates pos, OpponentList *eatenPiece) {
	OpponentList buffer;
	if(*eatenPiece != NULL) {
		buffer = *eatenPiece;
		while(buffer->next != NULL) {
			buffer = buffer->next;
		}
		buffer->promotion = ec[pos.r][pos.c].piece;
	}
}

void removeInOpponentList(Opponent elt, OpponentList *l) {
	OpponentList buffer = *l; 
	OpponentList before = buffer;
	int test = 0;
	while(buffer->next != NULL) {
		before = buffer;
		buffer = buffer->next;
		test = 1;
	}
	if(test) {
		before->next = buffer->next;
	}
	else if((*l)->next != NULL) {
		*l = (*l)->next;
	}
	else {
		(*l) = NULL;
	}
	free(buffer);
}

void destroyOpponentList(OpponentList *l) {
	while(*l != NULL){
		free(*l);
		*l = (*l)->next;
	}
}
