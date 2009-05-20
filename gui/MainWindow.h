#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "DragWidget.h"
#include "Configuration.h"
#include "Generator.h"
#include <QtGui>

class MainWindow : public QMainWindow
{
  Q_OBJECT

  public:
    MainWindow(const std::string &simulationName);
    ~MainWindow();
    
  private:
    struct slabel
    {
      QLabel *label;
      std::string name;
    };
    DragWidget *dw;
    Configuration *config;
    Generator *gen;
    std::vector<slabel> listDrag;
		
  private slots:
    void CreatePc();
    void CreateEmu();
    void CreateTap();
    void CreateAp();
    void CreateStation();
    void CreateHub();
    void CreateSwitch();
    void CreateRouter();
    void deleteObject();
    void ConfigurationMenu();
	    
};

#endif /* END MAINWINDOW_H */
