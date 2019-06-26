/*** ai.h ***************************************************************/
/*                                                                      */
/*     Subject  : bot functions                                         */
/*                                                                      */
/************************************************************************/

#ifndef AI_H
#define AI_H

#include "../model/struct.h"
#include "../model/primitives_listes.h"
#include "../controller/divers.h"

/*  Subject : evalutation function                                         */
/*  Spec : Evaluation of the ec position according to the number of pieces */
/*           and their position                                            */
int evaluation(Chessboard ec);

/*  Subject  : choose the best moves without min-max algo                    */
/*  Spec : calculate the best move mcp for the color camp in the position ec */ 
/*             without min max exploration                                   */
void choix_naif_coup(Chessboard ec, Color camp, Move *mcp);

/*  Subject  : choose the best moves  */
/*  Spec :  Calculate the best moves mcp for the camp color                 */
/*           in the ec position with a min-max or an alpha beta exploration */
/*           with a profmax deep                                            */
void moveChoice(Chessboard ec, Color camp, int profmax, Move *mcp);

/*  Subject  : min-max exploration function                               */
/*  Spec : Evaluate ec position for the camp color until profmax deep     */
/*           with a min-max strategie                                     */
int minMax(Chessboard ec, Color camp, int profmax);

/*  Subject  : alpha-beta exploration function                            */
/*  Spec : Evaluate ec position for the camp color until profmax deep     */
/*           with an alpha-beta strategie                                 */
int alpha_beta(Chessboard ec, Color color, int profmax, int A, int B);

#endif
