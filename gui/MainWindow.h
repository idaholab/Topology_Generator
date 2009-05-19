#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "DragWidget.h"
#include "Configuration.h"
#include <QtGui>

class MainWindow : public QMainWindow
{
  Q_OBJECT

  public:
    MainWindow();
    ~MainWindow();
    
  private:
    DragWidget *dw;
    Configuration *config;
		
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
	    
	
    
};

#endif /* END MAINWINDOW_H */
