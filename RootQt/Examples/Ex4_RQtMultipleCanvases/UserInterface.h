#ifndef QRT_CANVASES_H
#define QRT_CANVASES_H

// Standard libriaries
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <memory>

// Qt libriaries
#include <QtWidgets>

//My libraries
class QVBoxLayout;
class MainWindow;
class RQtWidget;

class UserInterface{

public:
    void setupUi(MainWindow* MainWindow);
    void updateWindowSize(const QSize & p_mainWindowSize);
    ~UserInterface() = default;

protected:
    // ALL WIDGETS ARE DECLARED AND INSTANTIATED IN setupUI!
    
    void Initialize();
    void CreateMenu();
    void DrawPlot(RQtWidget* rqtWidget);
    void Candleplot(RQtWidget* rqtWidget);
    void setMainBackground(MainWindow* MainWindow);
    void createMainMenuActions(MainWindow* MainWindow);

    void multipalette(RQtWidget * rQtWidget);
    void Pal2();
    void Pal1();
    void DrawHistogram(RQtWidget * rqtWidget);
    void DrawLandauHistogram(RQtWidget * rqtWidget);

};

#endif //QRT_CANVASES_H
