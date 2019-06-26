/*** divers.h ***********************************************************/
/*                                                                      */
/*     Subject  : Primitives pour la gestion des fonctions annexes        */
/*                                                                      */
/************************************************************************/

#ifndef DIVERS_H
#define DIVERS_H

#include "../model/struct.h"
#include "../model/primitives.h"

/*  Subject  : Copy Chessboard                                 */
/*  Spec : Copy Chessboard source to target Chessboard         */
void chessboardCopy(Chessboard source, Chessboard target);


/*  Subject  : Comparison of blow                               */
/*  Spec : Returns 1 if Move are identical, 0 otherwise        */
int moveComparison(Move source, Move target);


/*  Subject  : Comparison coordinates                       */
/*  Spec : Returns 1 if Coordinates are identical, 0 otherwise   */
int coordinatesComparison(Coordinates source, Coordinates target);


/*  Subject  : Display all at once                */
/*  Spec : Displays the components of a Move     */
void moveDisplay(Move elt);


/*  Subject  : Test the occupation of a case                                */
/*  Spec : Returns 1 if the case is occupied (Black or White), 0 otherwise  */
int occupationTest(Chessboard ec, Coordinates pos);


/*  Subject  : Color test                                           */
/*  Spec : Return 1 if starting case and the arrival case           */
/*           contains identical color pieces,0 otherwise            */
int colorTest(Chessboard ec, Move cp);


/*  Subject  : Delete piece                                           */
/*  Spec : Deletes the coordinate piece (r , c) of the Chessboard ec  */
void deletePiece(Chessboard ec, int r, int c);

/*  Subject  : ChessBoard update                                         */
/*  Spec : Plays the move, update the board accordingly and              */
/*         return the coord of the pieces which have made a special move */
Coordinates executeMove(Chessboard ec, Move cp);

#endif
