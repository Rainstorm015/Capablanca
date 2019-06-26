/*** primitives.h *******************************************************/
/*                                                                      */
/*     Purpose  : Initialization rules for the chessboard               */
/*              and adding pieces colors			                    */
/*                                                                      */
/************************************************************************/

#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include "../model/struct.h"
#include "../model/primitives_pieces.h"
#include "../model/primitives_listes.h"
#include "../controller/divers.h"

/*  Subject  : Initialization of the Chessboard ec                      */
/*  Spec : Fill the tiles in position at the beggining of the game      */
void initChessboard(Chessboard ec);

/*  Subject  : Allocation of the Chessboard ec                    		*/
/*  Spec : Fill the tiles according to the user                         */
void chessboardAssignment(Chessboard ec);

/*  Subject  : Display of the chessboard ec                             */
/*  Spec : Display the chessboard according to the current setting      */
void chessboardDisplay(Chessboard ec);

/*  Subject  : Loading Chessboard ec                                    */
/*  Spec : Create chessboard and execute moves                          */
void chessboardLoading(Chessboard ec, MoveList l, Color *color);

/*  Subject  : Test on the tiles colors                                 */
/*  Spec : True si pieces in p1 and p2 have opposite color              */ 
int oppositeColor(Chessboard ec, Move test);

/*  Subject  : Switching Intrance color                                 */
/*  Spec : Switch color with *color                                     */
void switchColor(Color *color);

/*  Subject  : Switching color                                          */
/*  Spec : Shows the opposite color of "color"                          */
Color opponentOf(Color color);

/*  Subject  : Shows all moves available for a piece on a tile          */
/*  Spec : Display all available move for a piece on pos                */
void displayMovesTile(Chessboard ec, Coordinates pos, MoveList l);

/*  Subject  : Calculation of the list of possible moves for the piece  */
/*  Spec : Build the list *l which contains  							*/		
/*			all moves available for the piece in pos     				*/
void possibleMovesTiles(Chessboard ec, Coordinates pos, MoveList *l, MoveList historic);

/*  Subject  : List all moves available for a side                      */
/*  Spec : Build the list *l which contains                 	        */
/*           all moves available for the side concerned		            */
void generator(Chessboard ec, Color color, MoveList *l);

/*  Subject  : Display of available moves                               */
/*  Spec : Display the moves contained in the list *l                   */
void displayPossibleMoves(MoveList l);

#endif
