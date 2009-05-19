#ifndef GRAPH_H
#define GRAPH_H

#include "dragwidget.h"
#include "Configuration.h"
#include <QtGui>

class Graph : public QMainWindow
{
 Q_OBJECT

	public:
		Graph();
		
	private slots:
	    void addPC();
	    void addPC_Emu();
	    void addPC_Tap();
	    void addAP();
	    void addStation();
	    void addHub();
	    void addSwitch();
	    void addRouter();
	    void deleteObject();
	    void ConfigurationMenu();
	    
	private:
	    DragWidget *dw;
	    

};


#endif
