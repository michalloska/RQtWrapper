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
    ~UserInterface() = default;

private:

    QWidget *centralWidget;
    QWidget *verticalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QTabWidget* tabWidget;
    QPushButton* histogramButton;

    std::map<const char*, QWidget*>     widgetMap;
    std::map<const char *, RQtWidget*>  canvasMap;

    void Initialize();
    void CreateMenu();
    void DrawPlot(RQtWidget* p_rqtWidget);
    void Candleplot(RQtWidget* p_rqtWidget);
    void DrawHistogram();
    void setMainBackground(MainWindow* MainWindow);
    void createMainMenuActions(MainWindow* MainWindow);
};

#endif //QRT_CANVASES_H
