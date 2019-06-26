/*** gui_window.h *******************************************************/
/*                                                                      */
/*     Subject  : Primitives to managing the graphical display          */
/*                                                                      */
/************************************************************************/

#ifndef GUI_WINDOW_H
#define GUI_WINDOW_H

#include <gtk/gtk.h>
#include <string.h>
#include "../model/struct.h"
#include "../view/gui_event.h"

GtkWidget *window, *Grid[9][11], *gtkColor,  *Evaluation, *Status, *View;
GtkListStore *Liste;
GtkTreeIter Iter;
Type players;
Chessboard ec;

/*  Subject  : Graphical interface creation                           */
/*  Spec : Creation of the menu, the state bar, the chessboard,       */
/*         the moves list and the status bar                          */
int gui(int argc, char *argv[]);

/*  Subject  : Chessboard's tile update                               */
/*  Spec : Graphical tile(i,j) update                                 */
void tile(Chessboard ec, int i, int j);

/*  Subject  : Piece's move update                                    */
/*  Spec : Start and end tiles update and moves list update           */
void moveMoving(Chessboard ec, Move elt);

/*  Subject  : Graphical display of the moves possibilities           */
/*  Spec : Highlight the moves of the list l                          */
void helpWithHighlight(Chessboard ec, MoveList l);

/*  Subject  : Highlight a tile                                       */
void highlight(Chessboard ec, Coordinates pos, Coordinates start);

/*  Subject  : Tile highlight removing                                */
/*  Spec : Remove the highlighted tile of the list l                  */
void moveListErase(MoveList l);

/*  Subject  : Display the player who has to play                     */
/*  Spec : Update the player color                                    */
void displayColor(char color);

/*  Subject  : Add a move in the graphical list                       */
void addMove(Chessboard ec, Move cp);

/*  Subject  : Ajout d'un message dans la barre de statut             */
void statusChange(char *message, int Contexte);

/*  Subject  : Display the player who has to play                     */
/*  Spec : Update of various elements specifying                      */
/*         the player who has to play                                 */                            
void informationsDisplay(Color color);

/*  Subject  : Manage the pawn's promotion                              */
/*  Spec : Choice of the future of the promoted pawn and update the box */
void Promotion(Chessboard ec, Coordinates pos, Color color, int ai);

#endif
