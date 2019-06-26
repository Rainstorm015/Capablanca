/*** Primitive_pieces.h ************************************************/
/*                                                                      */
/*     Subject  : Primitive for pieces management                      */
/*                                                                      */
/************************************************************************/

#ifndef Primitive_PIECES_H
#define Primitive_PIECES_H

#include "../model/struct.h"
#include "../model/primitives.h"

/************************************************************************/
/*                                                                      */
/*  Subject : Primitive for Pawn management                             */
/*                                                                      */
/************************************************************************/

/*  Subject  : Test moove forward                                  */
/*  Spec : Returns 1 if the pawn in pos can move, 0 otherwise      */
int pawnMov(Chessboard ec, Coordinates pos);
int pawnTake(Chessboard ec, Move test);
int pawnColorTest(Chessboard ec, Move test);


/*  Subject  : Test of the left socket                                */
/*  Spec : Returns 1 if the pawn in pos can take left, 0 otherwise    */
int pawnTakeLeft(Chessboard ec, Coordinates pos);


/*  Subject  : Test of the right socket                               */
/*  Spec : Returns 1 if the pawn in pos can take right, 0 otherwise    */
int pawnTakeRight(Chessboard ec, Coordinates pos);


/*  Subject  : Calculating possible hits for a pawn                            */
/*  Spec : Constructed the list *l containing the authorized shots of the pawn */
void pawnMoves(Chessboard ec, Coordinates pos, MoveList *l);


/*  Subject  : Promotion of the pawn                                         */
/*  Spec : Takes care of the transformation of the pawn during a promotion   */
void switchPawn(Chessboard ec, Coordinates pos, int i);

/*  Subject  : Choice of pawn promotion                                 */
/*  Spec : Proposes the possible choices for transformation of the pawn */
void pawnPromotion(Chessboard ec, Coordinates pos);


/*  Subject  : En passant                                                  */
/*  Spec : Constructed the list *l containing the blows taken "en passant" */
void moveEnPassant(Chessboard ec, Coordinates pos, MoveList *l, MoveList previousMoves);


/*  Subject  : Test "en passant"                                                      */
/*  Spec : Returns the coordinates of the room is taken "en passant" (and removes it) */
Coordinates isTakenEnPassant(Chessboard ec, Move cp);


/************************************************************************/
/*                                                                      */
/*  Subject : Primitive for Knight management                           */
/*                                                                      */
/************************************************************************/


/*  Subject  : Calculating possible hits for a knight                            */
/*  Spec : Constructed the list *l containing the authorized shots of the knight */
void knightMoves(Chessboard ec, Coordinates pos, MoveList *l);


/************************************************************************/
/*                                                                      */
/*  Subject : Primitive for Bishop management                           */
/*                                                                      */
/************************************************************************/


/*  Subject  : Calculating possible hits for a bishop                            */
/*  Spec : Constructed the list *l containing the authorized shots of the knight */
void bishopMoves(Chessboard ec, Coordinates pos, MoveList *l);


/************************************************************************/
/*                                                                      */
/*  Subject : Primitive for Rook management                             */
/*                                                                      */
/************************************************************************/


/*  Subject  : Calculating possible hits for a rook                            */
/*  Spec : Constructed the list *l containing the authorized shots of the rook */
void rookMoves(Chessboard ec, Coordinates pos, MoveList *l);

/************************************************************************/
/*                                                                      */
/*  Subject : Primitive for Archbishop management                       */
/*                                                                      */
/************************************************************************/

/*  Subject  : Calculating possible hits for a archbishop                            */
/*  Spec : Constructed the list *l containing the authorized shots of the archbishop */
void archbishopMoves(Chessboard ec, Coordinates pos, MoveList *l);

/************************************************************************/
/*                                                                      */
/*  Subject : Primitive for Chancellor management                       */
/*                                                                      */
/************************************************************************/


/*  Subject  : Calculating possible hits for a chancellor                            */
/*  Spec : Constructed the list *l containing the authorized shots of the chancellor */
void chancellorMoves(Chessboard ec, Coordinates pos, MoveList *l);

/************************************************************************/
/*                                                                      */
/*  Subject : Primitive for Queen management                            */
/*                                                                      */
/************************************************************************/


/*  Subject  : Calculating possible hits for a queen                            */
/*  Spec : Constructed the list *l containing the authorized shots of the queen */
void queenMoves(Chessboard ec, Coordinates pos, MoveList *l);


/************************************************************************/
/*                                                                      */
/*  Subject : Primitive for King management                             */
/*                                                                      */
/************************************************************************/


/*  Subject  : Calculating possible hits for a king                            */
/*  Spec : Constructed the list *l containing the authorized shots of the king */
void kingMoves(Chessboard ec, Coordinates pos, MoveList *l);

/*  Subject  : Management of small and large castling                          */
void castling(Chessboard ec, Coordinates pos, MoveList *l, MoveList historic);

/*  Subject  : Insertion of the blow castling                                   */
/*  Spec : addition of the small or large castling if legal in the list *l      */
void insertCastling(Chessboard ec, Move cp, MoveList *l, MoveList historic);


/*  Subject  : Moves the rook during a castling              */
/*  Spec : Returns the new rook position                     */
Coordinates doACastling(Chessboard ec, Move cp);


/*  Subject  : Management of the chess                       */
/*  Spec : Returns 1 if the king is in chess, 0 otherwise    */
int check(Chessboard ec, Color kingColor);


/*  Subject  : Management of the pin                    */
/*  Spec : Remove the move if he fails his king                 */
void pin(Chessboard ec, Move elt, MoveList *l);


/*  Subject  : Management of checkmate                          */
/*  Spec : Returns 1 if the camp hit list is empty, 0 otherwise */
int checkmate(Chessboard ec, Color color);


/*  Subject  : Global pin management               */
/*  Spec : Delete every stroke of *l failing his king  */
void removeCheck(Chessboard ec, MoveList *l);


/*  Subject  : Test chess, pat and checkmate                           */
/*  Spec : Returns the situation of this player (ex : 2 for the Pat)   */
int checkmateTest(Chessboard ec, Color color);

#endif
