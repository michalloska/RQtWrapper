#ifndef EX2_APPLICATION_H
#define EX2_APPLICATION_H

#include <iostream>
#include <stdio.h>
#include <memory>

#include <QMainWindow>
#include <QDialog>
#include <QVBoxLayout>


class UserInterface;

class MainWindow : public QMainWindow {

    Q_OBJECT

public:

    MainWindow(QWidget *parentWidget = nullptr);
    ~MainWindow();

public slots:

    void about();
    void aboutRoot();
    void aboutProject();
    void createMainMenuActions(MainWindow* MainWindow);

protected:

    UserInterface *ui;
};

#endif //EX2_APPLICATION_H
