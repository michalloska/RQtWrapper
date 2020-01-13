#ifndef QRT_CANVASES_H
#define QRT_CANVASES_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <memory>
#include <QtWidgets>

class QVBoxLayout;
class MainWindow;
class RQtWidget;

class UserInterface{

public:
    void setupUi(MainWindow* MainWindow);
    void updateWindowSize(const QSize & p_mainWindowSize);

protected:

    QWidget*            centralWidget;
    QWidget*            verticalLayoutWidget;
    QVBoxLayout*        verticalLayout;
    QVBoxLayout*        verticalLayout1;
    QVBoxLayout*        verticalLayout2;
    RQtWidget*          mainCanvas;

    void Initialize();
    void CreateMenu();
    void DrawPlot(RQtWidget * p_rqtWidget);
    void CreateOutterWindow();
    void Candleplot(RQtWidget * p_rqtWidget);
    void setMainBackground(MainWindow* MainWindow);
    void createMainMenuActions(MainWindow* MainWindow);

public:

    ~UserInterface() = default;

};

#endif //QRT_CANVASES_H
