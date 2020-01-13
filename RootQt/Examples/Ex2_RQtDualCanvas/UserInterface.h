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

    //DEBUG PURPOSES ONLY:
    void displayMemberSizes();

protected:
    QWidget *centralWidget;
    QWidget *verticalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;

    std::map<const char *, RQtWidget*> canvasMap;

    void Initialize();
    void CreateMenu();
    void DrawPlot(RQtWidget* p_rqtWidget);
    void Candleplot(RQtWidget* p_rqtWidget);
    void setMainBackground(MainWindow* MainWindow);
    void createMainMenuActions(MainWindow* MainWindow);

};

#endif //QRT_CANVASES_H
