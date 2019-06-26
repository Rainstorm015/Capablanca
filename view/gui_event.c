/*** gui_event.c ********************************************************/
/*                                                                      */
/*     Subject  : gui_event.h implementation                            */
/*                                                                      */
/************************************************************************/

#include "../view/gui_event.h"

void newGame(gpointer data) {
	GtkWidget *Dialog, *Table, *VBox, *Radio[2][3];
	const gchar *Label[2];
	int i, j;

	Dialog = gtk_dialog_new_with_buttons("New game",GTK_WINDOW(window),GTK_DIALOG_MODAL,GTK_STOCK_OK,GTK_RESPONSE_OK,GTK_STOCK_CANCEL,GTK_RESPONSE_CANCEL,NULL);

	Table = gtk_table_new(2,2, TRUE);

	/* Color */
	gtk_table_attach_defaults(GTK_TABLE(Table),gtk_label_new("Your color :"),0,1,0,1);
	VBox = gtk_vbox_new(FALSE,0);
	Radio[0][1] = gtk_radio_button_new_with_label(NULL,"White");
	gtk_box_pack_start(GTK_BOX(VBox),Radio[0][1],FALSE,FALSE,0);
	Radio[0][2] = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(Radio[0][1]),"Black");
	gtk_box_pack_start(GTK_BOX(VBox),Radio[0][2],FALSE,FALSE,0);
	gtk_table_attach_defaults(GTK_TABLE(Table),VBox,1,2,0,1);

	/* Opponent */
	gtk_table_attach_defaults(GTK_TABLE(Table),gtk_label_new("Opponent :"),0,1,1,2);
	VBox = gtk_vbox_new(FALSE,0);
	Radio[1][1] = gtk_radio_button_new_with_label(NULL,"Human VS Human");
	gtk_box_pack_start(GTK_BOX(VBox),Radio[1][1],FALSE, FALSE,0);
	Radio[1][2] = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(Radio[1][1]),"Human VS AI");
	gtk_box_pack_start(GTK_BOX(VBox),Radio[1][2], FALSE,FALSE, 0);
	gtk_table_attach_defaults(GTK_TABLE(Table),VBox,1,2,1,2);
 	gtk_box_pack_start(GTK_BOX(GTK_DIALOG(Dialog)->vbox),Table,TRUE,FALSE,10);
	gtk_widget_show_all(GTK_DIALOG(Dialog)->vbox);

	/* Get the dialog box and get the response */
	if(gtk_dialog_run(GTK_DIALOG(Dialog)) == GTK_RESPONSE_OK) {
		for(i = 0 ; i < 2 ; i++) {
			j = 1;
			while(!gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(Radio[i][j]))) j++;
			Label[i] = gtk_button_get_label(GTK_BUTTON(Radio[i][j]));
		}
		players.white.type = players.black.type = 0;
		if(!strcmp(Label[1],"Human VS AI")) {
			if(strcmp(Label[0],"White")) {
				players.white.type = 1;
			}
			else {
				players.black.type = 1;
			}
		}
		if(players.white.type || players.black.type) {
			profMaxChoice();
		}
		closeAll();
		globalVariable();
		startGame();
		if(players.white.type) {
			statusChange("Click on the Chessboard to let the AI to play",0);
		}
	}
	gtk_widget_destroy(Dialog);
}

void openSavedGame() {
	FILE *file;
	GtkWidget *box;
	char *path;
	char startColumn, endColumn, a, b, pieceProm;
	char whitePlayer[10], blackPlayer[10], sline[128];
	int startLine, endLine, result;
	Move elt;
	Coordinates specialMove;
	box = gtk_file_chooser_dialog_new("Open",GTK_WINDOW(window),GTK_FILE_CHOOSER_ACTION_OPEN,GTK_STOCK_CANCEL,GTK_RESPONSE_CANCEL,GTK_STOCK_OPEN,GTK_RESPONSE_ACCEPT,NULL);
	if(gtk_dialog_run(GTK_DIALOG(box)) == GTK_RESPONSE_ACCEPT) {
		path = (char*)gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(box));
		file = fopen(path,"r");
		if(file == NULL) {
			perror("Error");
		}
		else {
			closeAll();
			globalVariable();
			if(fgets(sline,sizeof(sline),file) != NULL) {
				sscanf(sline,"[White \" %s \"]\n",whitePlayer);
			}
			if(fgets(sline,sizeof(sline),file) != NULL) {
				sscanf(sline,"[Black \" %s \"]\n",blackPlayer);
			}
			if(fgets(sline,sizeof(sline),file) != NULL) {
				sscanf(sline,"[Result \" %d \"]\n",&result);
			}
			while(fgets(sline,sizeof(sline),file) != NULL) {
				sscanf(sline,"%c%d %c%d %c\n",&startColumn,&startLine,&endColumn,&endLine,&pieceProm);
				elt.start.c = startColumn - 97;
				elt.start.r = startLine - 1;
				elt.end.c = endColumn - 97;
				elt.end.r = endLine - 1;
				insertInList(elt,&historic);
				insertInOpponentList(ec,elt.end,&eatenPiece);
				specialMove = executeMove(ec,elt);
				
				/* Management of the castling and "en passant" */
				if(specialMove.r > -1) {
					addOpponentInformations(ec,specialMove,&eatenPiece);
					if(specialMove.c == 0) {
						tile(ec,specialMove.r,specialMove.c + 4);
					}
					else if(specialMove.c == 9) {
						tile(ec,specialMove.r,specialMove.c - 3);
					}
					ec[specialMove.r][specialMove.c].piece = ' ';
					ec[specialMove.r][specialMove.c].color = 'V';
				}
				
				/* Promotion management */
				if((ec[elt.end.r][elt.end.c].piece == 'p' && elt.end.r == 7) || (ec[elt.end.r][elt.end.c].piece == 'P' && elt.end.r == 0)) {
					ec[elt.end.r][elt.end.c].piece = pieceProm;
					addPromotionInformation(ec,elt.end,&eatenPiece);
				}
				addMove(ec,elt);
				switchColor(&gameColor);
			}
			
			fclose(file);
			startGame();
			if(!strcmp(whitePlayer,"Human")) {
				players.white.type = 0;
			}
			else {
				players.white.type = 1;
				sscanf(whitePlayer,"%c%c%d",&a,&b,&profmax);
			}
			if(!strcmp(blackPlayer,"Human")) {
				players.black.type = 0;
			}
			else {
				players.black.type = 1;
				sscanf(blackPlayer,"AI%d",&profmax);
			}
			stateGame(ec,gameColor);
		}
	}
	gtk_widget_destroy(box);
}

void saveGame() {
	FILE *file;
	GtkWidget *box;
	char *path;
	MoveList l = historic;
	OpponentList buffer = eatenPiece;
	box = gtk_file_chooser_dialog_new("Save",GTK_WINDOW(window),GTK_FILE_CHOOSER_ACTION_SAVE,GTK_STOCK_CANCEL,GTK_RESPONSE_CANCEL,GTK_STOCK_SAVE,GTK_RESPONSE_ACCEPT,NULL);
	if(gtk_dialog_run(GTK_DIALOG(box)) == GTK_RESPONSE_ACCEPT) {
		path = (char*)gtk_file_chooser_get_filename(GTK_FILE_CHOOSER (box));
		file = fopen(path,"w");
		if(file == NULL) perror("Error");
		else {
			if(players.white.type == 0) {
				fprintf(file,"[White \" Human \"]\n");
			}
			else {
				fprintf(file,"[White \" AI%d \"]\n",profmax);
			}
			if(players.black.type == 0) {
				fprintf(file,"[Black \" Human \"]\n");
			}
			else {
				fprintf(file,"[Black \" AI%d \"]\n",profmax);
			}
			if(init) {
				fprintf(file,"[End \" 0 \"]\n");
			}
			else {
				fprintf(file,"[End \" 1 \"]\n");
			}
			while(!isEmpty(l)) {
				fprintf(file,"%c%d %c%d %c\n",'a'+l->start.c,1+l->start.r,'a'+l->end.c,1+l->end.r,buffer->promotion);
				l = l->next;
				buffer = buffer->next;
			}
			fclose(file);
		}
	}
	gtk_widget_destroy(box);
}

void closeGame() {
	int i,j;
	closeAll();
	for(i = 0 ; i < 8 ; i++) {
		for(j = 0 ; j < 10 ; j++) {
			ec[i][j].piece = ' ';
			ec[i][j].color = 'V';
			tile(ec,i,j);
		}
	}
		
	gtk_label_set_text(GTK_LABEL(Evaluation),"0 point");
	gameColor = 'V';
	displayColor(gameColor);
	init = 0;
	statusChange("Welcome in Capablanca! CTRL + N to start a new game.",0);
}

void closeProgram(GtkWidget* widget, gpointer data) {
	closeAll();
	gtk_main_quit();
}

void undoMove(GtkWidget* widget, gpointer data) {
	MoveList t1;
	OpponentList t2;
	Move back;
	int k = 0;
	if(!isEmpty(historic) && eatenPiece != NULL) {
		t1 = historic;
		t2 = eatenPiece;
		while(t1->next != NULL) {
			t1 = t1->next;
		}
		while(t2->next != NULL) {
			t2 = t2->next;
		}
		back.start = t1->end;
		back.end = t1->start;
		executeMove(ec,back);
		tile(ec,back.end.r,back.end.c);
		ec[t2->position.r][t2->position.c].piece = t2->enemy.piece;
		ec[t2->position.r][t2->position.c].color = t2->enemy.color;
		tile(ec,back.start.r,back.start.c);
		if(!coordinatesComparison(back.start,t2->position)) {
			tile(ec,t2->position.r,t2->position.c);
		}
		if(ec[t1->start.r][t1->start.c].piece == 'r' || ec[t1->start.r][t1->start.c].piece == 'R') {
			if(t1->end.c == t1->start.c - 2) {
				k = -1;
			}
			else if(t1->end.c == t1->start.c + 2) {
				k = 1;
			}
			if(k) {
				deletePiece(ec,t1->start.r,t1->start.c + k*1);
				tile(ec,t1->start.r,t1->start.c + k*1);
			}
		}
		if(t2->promotion != ' ') {
			if(t2->promotion < 'a') {
				ec[t1->start.r][t1->start.c].piece = 'P';
			}
			else {
				ec[t1->start.r][t1->start.c].piece = 'p';
			}
			tile(ec,t1->start.r,t1->start.c);
		}
		insertInList(*t1,&next);
		removeInList(*t1,&historic);
		removeInOpponentList(*t2,&eatenPiece);
		gtk_list_store_remove(Liste,&Iter);
		switchColor(&gameColor);
		informationsDisplay(gameColor);
		init = 1;
	}
}

void redoMove(GtkWidget *widget, gpointer data) {
	MoveList t1;
	if(!isEmpty(next)) {
		t1 = next;
		while(t1->next != NULL) {
			t1 = t1->next;
		}
		pieceMoving(*t1);
		removeInList(*t1,&next);
		stateGame(ec,gameColor);
	}
}

void changeType(GtkWidget *widget, gpointer data) {
	int new_type = (int)data;
	if(init && new_type != players.white.type + players.black.type) {
		if(new_type == 0) {
			players.white.type = players.black.type = 0;
		}
		else {
			players.black.type = 1;
			if(new_type == 2) {
				players.white.type = 1;
			}
			profMaxChoice();
		}
	}
}

void about(GtkWidget* widget, gpointer data) {
	GtkWidget *About;
	About = gtk_message_dialog_new (GTK_WINDOW(window),GTK_DIALOG_MODAL,GTK_MESSAGE_INFO,GTK_BUTTONS_CLOSE,"Capablanca :\nVariant chessboard made in GTK+2\nby  Adrien Legrand, Guillaume Vanhelst, Geoffroy Latour and Aurélien Baillet");
	gtk_dialog_run(GTK_DIALOG(About));
	gtk_widget_destroy(About);
}

void aiHelp(GtkWidget* widget, gpointer data) {
	GtkWidget *box;
	GtkWidget *Label;
	char S[150];
	int test = 0;
	Move mcp;
	int ai = aiTest(gameColor,players);
	if(!ai && init) {
		box = gtk_dialog_new_with_buttons("Help",GTK_WINDOW(window),GTK_DIALOG_MODAL,GTK_STOCK_OK,GTK_RESPONSE_OK,GTK_STOCK_CANCEL,GTK_RESPONSE_CANCEL,NULL);
		moveChoice(ec,gameColor,2,&mcp);
		sprintf(S,"\n  Best trick according the AI (pr : 2) :  \n       %c%d --> %c%d\n\n\nClick on OK to execute it.",'a'+mcp.start.c,1+mcp.start.r,'a'+mcp.end.c,1+mcp.end.r);
		Label = gtk_label_new(S);
		gtk_box_pack_start(GTK_BOX(GTK_DIALOG(box)->vbox),Label,TRUE,FALSE,0);
		gtk_widget_show_all(GTK_DIALOG(box)->vbox);
		gtk_dialog_run(GTK_DIALOG(box));
		if(gtk_dialog_run(GTK_DIALOG(box)) == GTK_RESPONSE_OK) {
			test = 1;
		}
		gtk_widget_destroy(box);
		if(test) {
			MoveEnd(mcp);
			if(gameColor == 'B' && players.white.type) {
				statusChange("Click on the Chessboard to let the AI to play",0);
			}
			else if(gameColor == 'N' && players.black.type) {
				statusChange("Click on the Chessboard to let the AI to play",0);
			}
		}
	}
}

void pieceMove(GtkWidget *event_box, GdkEventButton *event, gpointer data) {
	int ai, test;
	Coordinates pos;
	Move mcp;
	if(init) {
		ai = aiTest(gameColor,players);
		if(!ai) {
			pos.r = ((int)data)/10;
			pos.c = (int)data%10;
			if(cp_move.start.r == -1) {
				if(ec[pos.r][pos.c].color == opponentOf(gameColor)) {
					statusChange("Don't touch my pieces",0);
				}
				else if(!occupationTest(ec,pos)) {
					statusChange("For nothing",0);
				}
				else {
					cp_move.start = pos;
					test = MoveStart(historic);
					if(!test) {
						statusChange("The King can't be sacrified!",0);
						/* Resetting */
						cp_move.start.r = -1;
						destroyList(ec,&l_move);
					}
				}
			}
			else {
				cp_move.end = pos;
				tile(ec,cp_move.start.r,cp_move.start.c);
				moveListErase(l_move);
				if(ec[cp_move.end.r][cp_move.end.c].color == gameColor && !coordinatesComparison(cp_move.start, cp_move.end)) {
					cp_move.start = cp_move.end;
					destroyList(ec,&l_move);
					MoveStart(historic);
				}
				else {
					if(isInTheList(cp_move,l_move)) {
						MoveEnd(cp_move);
						ai = aiTest(gameColor,players);
						destroyList(ec,&next);
					}
					cp_move.start.r = -1; /* Resetting */
					destroyList(ec,&l_move);
				}
			}
		}
		
		if(ai && init) {
			statusChange("Wait: the computer is thinking",0);
			moveChoice(ec,gameColor,profmax,&mcp);
			MoveEnd(mcp);
		}
	}
}

void globalVariable() {
	closeAll();
	init = 1;
	gameColor = 'B';
	cp_move.start.r = -1; 
	initChessboard(ec);
	initList(&historic);
	initList(&next);
	eatenPiece = NULL;
}

void startGame() {
	int i, j;
	for(i = 0 ; i < 8 ; i++) for(j = 0 ; j < 11 ; j++) {
		tile(ec,i,j);
	}
	informationsDisplay(gameColor);
}

void profMaxChoice() {
	GtkWidget *Choix, *box;
	GSList *List;
	int i;
	Choix = gtk_dialog_new_with_buttons("AI level", GTK_WINDOW(window),GTK_DIALOG_MODAL,GTK_STOCK_OK,GTK_RESPONSE_OK,NULL);
	box = gtk_radio_button_new_with_label(NULL,"                    Easy           ");
	gtk_box_pack_start(GTK_BOX(GTK_DIALOG(Choix)->vbox),box,TRUE,FALSE,0);
	List = gtk_radio_button_get_group(GTK_RADIO_BUTTON(box));
	gtk_box_pack_start(GTK_BOX(GTK_DIALOG(Choix)->vbox),gtk_radio_button_new_with_label(List, "                    Medium "),TRUE,FALSE,0);
	List = gtk_radio_button_get_group(GTK_RADIO_BUTTON(box));
	gtk_box_pack_start(GTK_BOX(GTK_DIALOG(Choix)->vbox),gtk_radio_button_new_with_label(List, "                    Hard "),TRUE,FALSE,0);
	List = gtk_radio_button_get_group(GTK_RADIO_BUTTON(box));
	gtk_widget_show_all(GTK_DIALOG(Choix)->vbox);
	if(gtk_dialog_run(GTK_DIALOG(Choix)) == GTK_RESPONSE_OK) {
		i = 0;
		while(!gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(List->data))) {
			i++;
			List = g_slist_next(List);
		}
		if(i == 2) {
			profmax = 1;
		}
		else if(i == 1) {
			profmax = 3;
		}
		else {
			profmax = 5;
		}
	}
	gtk_widget_destroy(Choix);
}

int MoveStart(MoveList previousMove) {
	initList(&l_move);
	possibleMovesTiles(ec,cp_move.start,&l_move,previousMove);
	removeCheck(ec,&l_move);
	if(!isEmpty(l_move)) {
		highlight(ec,cp_move.start,cp_move.start);
		helpWithHighlight(ec, l_move);
		return 1;
	}
	else {
		return 0;
	}
}

void MoveEnd(Move cp) {
	pieceMoving(cp);
	stateGame(ec,gameColor);
}

void pieceMoving(Move elt) {
	int ai;
	Coordinates specialMove, lostPiece;
	lostPiece = elt.end;
	insertInList(elt,&historic);
	insertInOpponentList(ec,elt.end,&eatenPiece);
	specialMove = executeMove(ec,elt);

	/* Management of castling and "en passant" */
	if(specialMove.r > -1) {
		addOpponentInformations(ec,specialMove,&eatenPiece);
		lostPiece = specialMove;
		if(specialMove.c == 0) {
			tile(ec,specialMove.r,specialMove.c + 4);
		}
		else if(specialMove.c == 9) {
			tile(ec,specialMove.r,specialMove.c - 3);
		}
		ec[specialMove.r][specialMove.c].piece = ' ';
		ec[specialMove.r][specialMove.c].color = 'V';
		tile(ec,specialMove.r,specialMove.c);
	}

	/* Promotion management */
	if((ec[elt.end.r][elt.end.c].piece == 'p' && elt.end.r == 7) || (ec[elt.end.r][elt.end.c].piece == 'P' && elt.end.r == 0)) {
		ai = aiTest(gameColor,players);
		Promotion(ec,elt.end,gameColor,ai);
		addPromotionInformation(ec,elt.end,&eatenPiece);
	}

	moveMoving(ec,elt);
	switchColor(&gameColor);
}

void stateGame(Chessboard ec, Color gameColor) {
	GtkWidget *Info;
	char S[100];
	char tmps = gameColor;
	int test = checkmateTest(ec,gameColor);
	if(test > 1) {
		informationsDisplay(gameColor);
		if(test == 2) {
			statusChange("Pat !!",0);
			sprintf(S,"Pat !!\nEquality");
		}
		else 
		{
			sprintf(S,"Checkmate!!!\n");
			statusChange("Checkmate!!!",0);

			if(tmps == 'B') {
				sprintf(S,"Black won!\n click on the button and press CTRL+N for a new game");

			}
			else {
				sprintf(S,"White won!\n click on the button and press CTRL+N for a new game");
			}
		}

		Info = gtk_message_dialog_new (GTK_WINDOW(window),GTK_DIALOG_MODAL,GTK_MESSAGE_INFO,GTK_BUTTONS_OK,S);
		gtk_dialog_run(GTK_DIALOG(Info));
		gtk_widget_destroy(Info);
		init = 0;
	}
	else {
		informationsDisplay(gameColor);
		if(test == 1) statusChange("Check!",0);
	}
}

int aiTest(Color gameColor, Type players) {
	if(gameColor == 'B' && players.white.type) {
		return 1;
	}
	else if(gameColor == 'N' && players.black.type) {
		return 1;
	}
	else {
		return 0;
	}
}

void closeAll() {
	destroyList(ec,&l_move);
	destroyList(ec,&historic);
	destroyList(ec,&next);
	destroyOpponentList(&eatenPiece);
	gtk_list_store_clear(Liste);
}
