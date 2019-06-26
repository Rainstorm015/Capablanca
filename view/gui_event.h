/*** gui_event.h ********************************************************/
/*                                                                      */
/*     Subject  : Primitives to manage graphic events                   */
/*                                                                      */
/************************************************************************/

#ifndef GUI_EVENT_H
#define GUI_EVENT_H

#include "../view/gui_window.h"
#include "../model/primitives.h"
#include "../model/primitives_pieces.h"
#include "../controller/divers.h"

MoveList l_move, next;
OpponentList eatenPiece;
Move cp_move;
Color gameColor;
int init, profmax;

/*  Subject  : Game creation management                     */
/*  Spec : Creation of a new game with several options      */
void newGame(gpointer data);

/*  Subject  : Game load management                         */
/*  Spec : Opening a game with choice of the file name      */
void openSavedGame();

/*  Subject  : Management of the game backup                */
/*  Spec : Save the game with choice of file name           */
void saveGame();

/*  Subject  : Management of game closure                   */
/*  Spec : Closing a game with reset of the interface       */
void closeGame();

/*  Subject  : Management of the closure of the program     */
/*  Spec : Clean closing (deleting lists) of the program    */
void closeProgram(GtkWidget* widget, gpointer data);

/*  Subject  : Management of the move cancellation          */
/*  Spec : Cancellation of the last move plays              */
void undoMove(GtkWidget* widget, gpointer data);

/*  Subject  : Management of the move uncancellation        */
/*  Spec : Replay the last move canceled                    */
void redoMove(GtkWidget* widget, gpointer data);

/*  Subject  : Managing the game type change                */
/*  Spec : Changing the type of enemy                    */
void changeType(GtkWidget* widget, gpointer data);

/*  Subject  : Showing a window "About"                     */
void about(GtkWidget* widget, gpointer data);

/*  Subject  : Displaying a visual suggestion               */
/*  Spec : Highlighting an interesting move according the AI*/
void aiHelp(GtkWidget* widget, gpointer data);

/*  Subject  : Management of the pieces moves               */
/*  Spec : Manage the graphic displacement of the pieces    */
/*         from the start tile to the end tile,             */
/*         allows the movement of the pieces by the AI      */    
void pieceMove(GtkWidget *event_box, GdkEventButton *event, gpointer data);

/*  Subject  : Initialization of the variables used during the game    */
void globalVariable();

/*  Subject  : Update the chessboard gui                     */
void startGame();

/*  Subject  : AI level choice                               */
/*  Spec : Displays a dialog box offering                    */
/*         a level of difficulty adjustable (3 levels)       */
void profMaxChoice();

/*  Subject  : Manage the first part of pieceMove()             */
/*  Spec : Create the possibles moves list and remove        */
/*         the pin moves, displays possible positions        */
/*         and return if the selected piece can move         */
int MoveStart();

/*  Subject  : Manage the second part of  pieceMove()           */
/*  Spec : Uses pieceMoving and stateGame            */
/*         to manage the piece move                          */
void MoveEnd(Move cp);

/*  Subject  : Manage the piece moves                        */
/*  Spec : Execute the selected move, manage                 */
/*         the special moves, verify the game state and      */ 
/*         return if the AI has to play                      */
void pieceMoving(Move elt);

/*  Subject  : Test the game's state                         */
/*  Spec : Verification of the game's state,                 */
/*         with display of the game's state in the status bar*/ 
/*         and in a window and returns if the game continues */
/*         or not                                            */
void stateGame(Chessboard ec, Color gameColor);

/*  Subject  : Player's color test                           */
/*  Spec : Return if the player of color gtkColor_jeu            */
/*         is an AI or not                                   */
int aiTest(Color gameColor, Type players);

/*  Subject  : Delete "global" lists                         */
void closeAll();

#endif
