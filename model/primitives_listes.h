/*** primitives_listes.h ************************************************/
/*                                                                      */
/*     Subject  : Primitives for the lists management	                */
/*                                                                      */
/************************************************************************/

#ifndef PRIMITIVES_LISTES_H
#define PRIMITIVES_LISTES_H

#include "../model/struct.h"
#include "../controller/divers.h"

/*  Subject  : Initialization of the list *l                             */
void initList(MoveList *l);

/*  Subject  : Test of emptiness                                         */
/*  Spec : Return 1 if list l is empty                                   */
int isEmpty(MoveList l);

/*  Subject  : Ownership test                                            */
/*  Spec : Return 1 if element elt is in list l                          */
int isInTheList(Move elt, MoveList l);

/*  Subject  : Moving test                                               */
/*  Spec : Return 1 if element elt is in begings of l                    */
int hasMoved(Coordinates elt, MoveList l);

/*  Subject  : Display of the list                                       */
void displayList(MoveList l);

/*  Subject  : Insertion of an element at the end                        */
/*  Spec : Adding an element elt at the end of the list *l               */
void insertInList(Move elt, MoveList *l);

/*  Subject  : Insertion of indication                                   */
/*  Spec : Add a piece "X" on the board to indicate                      */
/*           graphicaly move possibilities                               */
void insert(Chessboard ec, Move elt);

/*  Subject  : Element deletion                                          */
/*  Spec : Return 1 if element *l is deleted                             */
void removeInList(Move elt, MoveList *l);

/*  Subject  : Indication Deletion                                       */
/*  Spec : Delete a piece "X" on the board                               */
void removePiece(Chessboard ec, Move elt, MoveList *l);

/*  Subject  : List deletion	                                         */
/*  Spec : Disallocating list *l                                         */
void destroyList(Chessboard ec, MoveList *l);

/*=======================================================================*/

/*  Subject  : Insert an element in the end                              */
/*  Spec : Add the piece pos in the list of eaten pieces                 */
void insertInOpponentList(Chessboard ec, Coordinates pos,OpponentList *eatenPiece);

/*  Subject  : Insert an element following a special move                */
/*  Spec : add the piece pos in the list of eaten pieces                 */
void addOpponentInformations(Chessboard ec, Coordinates pos, OpponentList *eatenPiece);

/*  Subject  : Add choice for the promotion                             */
void addPromotionInformation(Chessboard ec, Coordinates pos, OpponentList *eatenPiece);

/*  Subject  : Element deletion                                          */
/*  Spec : Return 1 if element of *l is deleted                          */
void removeInOpponentList(Opponent elt, OpponentList *l);

/*  Subject  : Deletion of eaten pieces list                             */
/*  Spec : Disallocation of the list *l                                  */
void destroyOpponentList(OpponentList *l);

#endif
