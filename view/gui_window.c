/*** gui_window.c *******************************************************/
/*                                                                      */
/*     Subject  : gui_window.h implementation                           */
/*                                                                      */
/************************************************************************/

#include "../view/gui_window.h"

int gui(int argc, char *argv[]) {
	GtkWidget *menu, *tools, *Table, *eventBox, *Frame, *SBar;
	GtkWidget *VBox[5], *HBox[5];
	GtkItemFactory *ItemFactory;
	GtkAccelGroup *Accel;
	char S[40];
	int i, j;
	static int NbMenuItem;

	/* Window creation */
	gtk_init(&argc,&argv);
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window),"Capablanca");
	gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
	gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);
	g_signal_connect(G_OBJECT(window),"destroy",G_CALLBACK(closeProgram),NULL);
	g_signal_connect(G_OBJECT(window),"delete_event",G_CALLBACK(closeProgram),NULL);
	gtk_container_set_border_width(GTK_CONTAINER(window),0);

	/* GtkVBox creation */
	VBox[0] = gtk_vbox_new(FALSE,0);

	/* Menu creation */
	static GtkItemFactoryEntry MenuItem[] = {
		{"/_File",NULL,NULL,0,"<Branch>" },
		{"/_File/_New","<CTRL>N",newGame,0,"<StockItem>",GTK_STOCK_NEW},
		{"/_File/_Open","<CTRL>O",openSavedGame,0,"<StockItem>",GTK_STOCK_OPEN},
		{"/_File/sep",NULL,NULL,0,"<Separator>"},
		{"/_File/_Save","<CTRL>S",saveGame,0,"<StockItem>",GTK_STOCK_SAVE},
		{"/_File/_Save under...","<ALT>S",saveGame,0,"<StockItem>",GTK_STOCK_SAVE},
		{"/_File/_Close the game","<CTRL>F",G_CALLBACK(closeGame),0,"<StockItem>",GTK_STOCK_CLOSE},
		{"/_File/sep",NULL,NULL,0,"<Separator>"},
		{"/_File/_Quit","<CTRL>Q",closeProgram,0,"<StockItem>",GTK_STOCK_QUIT},
		{"/_Settings",NULL,NULL,0,"<Branch>"},
		{"/_Settings/_Undo","<CTRL>Z",undoMove,0,"<StockItem>",GTK_STOCK_UNDO},
		{"/_Settings/_Redo","<CTRL>R",redoMove,0,"<StockItem>",GTK_STOCK_REDO},
		{"/_Settings/sep",NULL,NULL,0,"<Separator>"},
		{"/_Settings/_Type",NULL,NULL,0,"<Branch>"},
		{"/_Settings/_Type/_Human vs Human","<ALT>1",changeType,0,"<RadioItem>"},
		{"/_Settings/_Type/_Human vs AI","<ALT>2",changeType,1,"/Settings/Type/Human vs Human"},
		{"/_Settings/sep",NULL,NULL,0,"<Separator>"},
		{"/_Settings/_Advice","<CTRL>H",aiHelp,0,"<StockItem>",GTK_STOCK_EXECUTE},
		{"/_About",NULL,NULL,0,"<Branch>"},
		{"/_About/_About...",NULL,about,0,"<StockItem>",GTK_STOCK_HELP},
	};
	NbMenuItem = sizeof(MenuItem) / sizeof(MenuItem[0]);
	Accel = gtk_accel_group_new();
	ItemFactory = gtk_item_factory_new(GTK_TYPE_MENU_BAR,"<main>",Accel);
	gtk_item_factory_create_items(ItemFactory,NbMenuItem,MenuItem,NULL);
	gtk_window_add_accel_group(GTK_WINDOW(window),Accel);
	menu = gtk_item_factory_get_widget(ItemFactory,"<main>");
	gtk_box_pack_start(GTK_BOX(VBox[0]),menu,FALSE,FALSE,0);

	/* Tools bar creation */
	tools = gtk_toolbar_new();
	gtk_toolbar_insert_stock(GTK_TOOLBAR(tools),GTK_STOCK_NEW,"New",NULL,G_CALLBACK(newGame),NULL,-1);
	gtk_toolbar_insert_stock(GTK_TOOLBAR(tools),GTK_STOCK_OPEN,"Open",NULL,G_CALLBACK(openSavedGame),NULL,-1);
	gtk_toolbar_insert_stock(GTK_TOOLBAR(tools),GTK_STOCK_SAVE,"Save",NULL,G_CALLBACK(saveGame),NULL,-1);
	gtk_toolbar_append_space(GTK_TOOLBAR(tools));
	gtk_toolbar_insert_stock(GTK_TOOLBAR(tools),GTK_STOCK_UNDO,"Undo",NULL,G_CALLBACK(undoMove),NULL,-1);
	gtk_toolbar_insert_stock(GTK_TOOLBAR(tools),GTK_STOCK_REDO,"Redo",NULL,G_CALLBACK(redoMove),NULL,-1);
	gtk_toolbar_append_space(GTK_TOOLBAR(tools));
	gtk_toolbar_insert_stock(GTK_TOOLBAR(tools),GTK_STOCK_EXECUTE,"Advice",NULL,G_CALLBACK(aiHelp),NULL,-1);
	gtk_toolbar_append_space(GTK_TOOLBAR(tools));
	gtk_toolbar_insert_stock(GTK_TOOLBAR(tools),GTK_STOCK_HELP,"About",NULL,G_CALLBACK(about),NULL,-1);
	gtk_toolbar_set_icon_size(GTK_TOOLBAR(tools),GTK_ICON_SIZE_BUTTON);
	gtk_toolbar_set_style(GTK_TOOLBAR(tools),GTK_TOOLBAR_ICONS);
	gtk_box_pack_start(GTK_BOX(VBox[0]),tools,FALSE,FALSE,0);

	/* Main window creation */
	HBox[0] = gtk_hbox_new(FALSE,0);

	/* Chessboard */
	Table = gtk_table_new(8,11,TRUE);
	
	/* Letters and number around the chessboard */
	for(i = 0 ; i < 8 ; i++) {
		sprintf(S,"%d",8-i);
		gtk_table_attach_defaults(GTK_TABLE(Table),gtk_label_new(S),0,1,i,i+1);
	}
	for(i = 1 ; i < 11 ; i++) {
		sprintf(S,"%c",'A'+i-1);
		gtk_table_attach_defaults(GTK_TABLE(Table),gtk_label_new(S),i,i+1,8,9);
	}

	/* Chessboard's tile placement */
	gtkColor = gtk_image_new();
	gtk_table_attach_defaults(GTK_TABLE(Table),gtkColor,0,1,8,9);
	for(i = 0 ; i < 8 ; i++) {
		for(j = 0 ; j < 10 ; j++) {
			if((i + j) % 2 == 0) {
				Grid[i][j] = gtk_image_new_from_file("./view/image/Tile_w.png");
			}
			else {
				Grid[i][j] = gtk_image_new_from_file("./view/image/Tile_b.png");
			} 
			eventBox = gtk_event_box_new();
			gtk_container_add(GTK_CONTAINER(eventBox),Grid[i][j]);
			g_signal_connect(G_OBJECT(eventBox),"button_press_event",G_CALLBACK(pieceMove),(gpointer)(70-i*10+j));
			gtk_table_attach_defaults(GTK_TABLE(Table),eventBox,j+1,j+2,i,i+1);
		}
	}
	gtk_box_pack_start(GTK_BOX(HBox[0]),Table,TRUE,FALSE,0);

	/* Space */
	gtk_box_pack_start(GTK_BOX(HBox[0]),gtk_vseparator_new(),FALSE,FALSE,1);

	/* Informations */
	VBox[1] = gtk_vbox_new(FALSE,0);

	/* Score */
	Frame = gtk_frame_new("Score :");
	Evaluation = gtk_label_new("");
	gtk_container_add(GTK_CONTAINER(Frame),Evaluation);
	gtk_box_pack_start(GTK_BOX(VBox[1]),Frame,FALSE,FALSE,5);

	/* List */
	Frame = gtk_frame_new("Move list :");


	/* Storage of the list of moves */
	Liste = gtk_list_store_new(4,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,-1);


	/* Affichage */
	View = gtk_tree_view_new_with_model(GTK_TREE_MODEL(Liste));
	gtk_tree_view_append_column(GTK_TREE_VIEW(View),gtk_tree_view_column_new_with_attributes("Piece",gtk_cell_renderer_text_new(),"text",0,NULL));
	gtk_tree_view_append_column(GTK_TREE_VIEW(View),gtk_tree_view_column_new_with_attributes("Start",gtk_cell_renderer_text_new(),"text",1,NULL));
	gtk_tree_view_append_column(GTK_TREE_VIEW(View),gtk_tree_view_column_new_with_attributes("-->",gtk_cell_renderer_text_new(),"text",2,NULL));
	gtk_tree_view_append_column(GTK_TREE_VIEW(View),gtk_tree_view_column_new_with_attributes("End",gtk_cell_renderer_text_new(),"text",3,NULL));
	
	
	/* scrollbar */
	SBar =  gtk_scrolled_window_new(NULL,NULL);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(SBar),GTK_POLICY_NEVER,GTK_POLICY_AUTOMATIC);
	gtk_container_add(GTK_CONTAINER(SBar),View);
	gtk_container_add(GTK_CONTAINER(Frame),SBar);
	gtk_box_pack_start(GTK_BOX(VBox[1]),Frame,TRUE,TRUE,5);

	gtk_box_pack_start(GTK_BOX(HBox[0]),VBox[1],TRUE,FALSE,0);
	
	gtk_box_pack_start(GTK_BOX(VBox[0]),HBox[0],FALSE,FALSE,10);

	
	/* Status bar */
	Status = gtk_statusbar_new();
	gtk_statusbar_push(GTK_STATUSBAR(Status),GPOINTER_TO_INT(gtk_statusbar_get_context_id(GTK_STATUSBAR(Status),"Welcome !")),"Welcome in Capablanca! CTRL + N to start a new game.");
	gtk_box_pack_end(GTK_BOX(VBox[0]),Status,FALSE,FALSE,0);

	gtk_container_add(GTK_CONTAINER(window),VBox[0]);

	gtk_widget_show_all(window);
	gtk_main();
	
	return 0;
}

void tile(Chessboard ec, int i, int j) {
	char S[40];
	if(ec[i][j].color == 'V') {
		if((i + j) % 2) {
			sprintf(S,"./view/image/Tile_w.png");
		} 
		else {
			sprintf(S,"./view/image/Tile_b.png");
		}
	}
	else {
		if((i + j) % 2) {
			sprintf(S,"./view/image/%c_%c_b.png",ec[i][j].piece,ec[i][j].color);
		}
		else {
			sprintf(S,"./view/image/%c_%c_n.png",ec[i][j].piece,ec[i][j].color);
		}
	}
	gtk_image_set_from_file(GTK_IMAGE(Grid[7-i][j]),S);
}

void moveMoving(Chessboard ec, Move elt) {
	tile(ec,elt.start.r,elt.start.c);
	tile(ec,elt.end.r,elt.end.c);
	addMove(ec,elt);
}

void helpWithHighlight(Chessboard ec, MoveList l) {
	Coordinates start = l->start;
	while(!isEmpty(l)) {
		highlight(ec,l->end, start);
		l = l->next;
	}
}

void highlight(Chessboard ec, Coordinates pos, Coordinates start) {
	char S[40];
	if(ec[pos.r][pos.c].color == 'V') {
		sprintf(S, "./view/image/Tile_s.png");
	}
	else {
		if((start.r != pos.r) || (start.c != pos.c)){
			sprintf(S,"./view/image/%c_%c_attacked.png",ec[pos.r][pos.c].piece,ec[pos.r][pos.c].color);
		} else {
			sprintf(S,"./view/image/%c_%c_selected.png",ec[pos.r][pos.c].piece,ec[pos.r][pos.c].color);
		}
	}
	gtk_image_set_from_file(GTK_IMAGE(Grid[7-pos.r][pos.c]),S);
}

void moveListErase(MoveList l) {
	while(!isEmpty(l)) {
		tile(ec,l->end.r,l->end.c);
		l = l -> next;
	}
}

void displayColor(char color) {
	char S[40];
	if(color == 'B') {
		sprintf(S,"./view/image/Tile_w.png");
	}
	else if(color == 'N') {
		sprintf(S,"./view/image/Tile_b.png");
	}
	else {
		sprintf(S,"./view/image/empty.png");
	}
	gtk_image_set_from_file(GTK_IMAGE(gtkColor),S);
}

void addMove(Chessboard ec, Move cp) {
	char S[4][30];
	sprintf(S[0],"%c",ec[cp.end.r][cp.end.c].piece);
	sprintf(S[1],"%c%d",'a'+cp.start.c,1+cp.start.r);
	sprintf(S[2],"-->");
	sprintf(S[3],"%c%d",'a'+cp.end.c,1+cp.end.r);
	gtk_list_store_prepend(Liste,&Iter);
	gtk_list_store_set(Liste,&Iter,0,S[0],1,S[1],2,S[2],3,S[3],-1);
	gtk_tree_view_scroll_to_point(GTK_TREE_VIEW(View),0,0);
}

void statusChange(char *message, int Contexte) {
	message = g_locale_to_utf8(message,-1,NULL,NULL,NULL);
	gtk_statusbar_push(GTK_STATUSBAR(Status),GPOINTER_TO_INT(Contexte),message);
	g_free(message);
}

void informationsDisplay(Color color) {
	char S[40];
	if(gameColor == 'B') {
		sprintf(S,"White turn");
	}
	else {
		sprintf(S,"Black turn");
	}
	statusChange(S,0);
	displayColor(color);
	sprintf(S,"%d points",evaluation(ec));
	gtk_label_set_text(GTK_LABEL(Evaluation),S);
}

void Promotion(Chessboard ec, Coordinates pos, Color color, int ai) {
	GtkWidget *box, *Tab, *Bouton;
	GSList *group = NULL;
	char car=' ', path[25];
	int i = 0, colorName;
	if(ai) {
		ec[pos.r][pos.c].piece = 'D';
	}
	else {
		box = gtk_dialog_new_with_buttons("Promotion",GTK_WINDOW(window),GTK_DIALOG_MODAL,GTK_STOCK_OK,GTK_RESPONSE_OK,NULL);
		Tab =  gtk_table_new(2, 4, FALSE);
		for(i = 0 ; i < 6 ; i++){
			if(i == 0) {
				car = 'A';
			}
			if(i == 1) {
				car = 'C';
			}
			if(i == 2) {
				car = 'K';
			}
			if(i == 3) {
				car = 'F';
			}
			if(i == 4) {
				car = 'T';
			}
			if(i == 5) {
				car = 'D';
			}
			sprintf(path,"./view/image/%c_%c.png",car,ec[pos.r][pos.c].color);
			gtk_table_attach_defaults(GTK_TABLE(Tab),gtk_image_new_from_file (path),i,i+1,0,1);
			Bouton = gtk_radio_button_new(group);
			group = gtk_radio_button_get_group(GTK_RADIO_BUTTON(Bouton));
			gtk_table_attach_defaults(GTK_TABLE(Tab),Bouton,i,i+1,1,2);
		}
		gtk_box_pack_start(GTK_BOX(GTK_DIALOG(box)->vbox),Tab,TRUE,FALSE,0);
		gtk_widget_show_all(GTK_DIALOG(box)->vbox);
		if(gtk_dialog_run(GTK_DIALOG(box)) == GTK_RESPONSE_OK) {
			i = 0;
			while(!gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(group->data))) {
				i++;
				group = g_slist_next(group);
			}
			if(color == 'B') {
				colorName = 32;
			}
			else {
				colorName = 0;
			}
			if(i == 5) {
				ec[pos.r][pos.c].piece = 'A' + colorName;
			}
			if(i == 4) {
				ec[pos.r][pos.c].piece = 'C' + colorName;
			}
			if(i == 3) {
				ec[pos.r][pos.c].piece = 'K' + colorName;
			}
			else if(i == 2) {
				ec[pos.r][pos.c].piece = 'F' + colorName;
			}
			else if(i == 1) {
				ec[pos.r][pos.c].piece = 'T' + colorName;
			}
			else if(i == 0) {
				ec[pos.r][pos.c].piece = 'D' + colorName;
			}
		}
		else {
			if(color == 'B') {
				colorName = 32;
			}
			else {
				colorName = 0;
			}
			ec[pos.r][pos.c].piece = 'D' + colorName;
		}
		gtk_widget_destroy(box);
	}
	tile(ec,pos.r,pos.c);
}
