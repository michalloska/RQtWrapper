#include <QtWidgets>
#include <vector>
#include "TROOT.h"
#include "TSystem.h"
#include <stdlib.h>
#include "MainWindow.h"
#include "UserInterface.h"
#include "RQtWidget.h"

MainWindow::MainWindow(QWidget *parentWidget)
        : QMainWindow(parentWidget),
          ui(new UserInterface) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
}

void MainWindow::createMainMenuActions(MainWindow *mainWindow) {

    QMenu *appMenu = mainWindow->menuBar()->addMenu(QPushButton::tr("&Application"));

    const QIcon exitIcon = QIcon::fromTheme("application-exit");
    QAction *exitAct = appMenu->addAction(exitIcon, QPushButton::tr("&Exit"), mainWindow, &QWidget::close);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip(QPushButton::tr("Exit the application"));

    mainWindow->menuBar()->addSeparator();

    QMenu *helpMenu = mainWindow->menuBar()->addMenu(QPushButton::tr("&Help"));

    QAction *helpAboutAct = helpMenu->addAction(QPushButton::tr("About &GreatApp"), mainWindow,
                                                [=]() { mainWindow->about(); });
    helpAboutAct->setStatusTip(QPushButton::tr("Show the application's About box"));

    QAction *helpAboutRootAct = helpMenu->addAction(QPushButton::tr("About &ROOT"), mainWindow,
                                                    [=]() { mainWindow->aboutRoot(); });
    helpAboutRootAct->setStatusTip(QPushButton::tr("Show the ROOT library's About box"));

    QAction *helpAboutQtAct = helpMenu->addAction(QPushButton::tr("About &Qt"), qApp, &QApplication::aboutQt);
    helpAboutQtAct->setStatusTip(QPushButton::tr("Show the Qt library's About box"));

    QAction *helpAboutProject = helpMenu->addAction(QPushButton::tr("Changelog"), mainWindow,
                                                    [=]() { mainWindow->aboutProject(); });
    helpAboutProject->setStatusTip(QPushButton::tr("Show the project's About box"));

    mainWindow->menuBar()->move(100, 10);
    appMenu->move(100, 10);
    appMenu->setEnabled(true);
}

void MainWindow::about() {
    QMessageBox::about(this, tr("About Application"), tr("The <b>Great app</b> project description"));
}

void MainWindow::aboutProject() {
    QMessageBox::about(this, tr("Changelog and changes"), tr("<b>fix / to be fixed</b> list:"));
    std::vector <TString> lines;

    lines.emplace_back("fixed refreshing of the tab switching");
    lines.emplace_back("fixed no delay after pressing plot /histogram buttons");
    lines.emplace_back("RQt base class has a timer which invokes certain actions in cycles");
    lines.emplace_back("ERRORS:");
    lines.emplace_back("ROOT throws an error when closing the app when both plot and histogram are opened");

    std::string innerText;
    for (const auto &line : lines) {
        innerText.append(line.Data());
        innerText.append("\n");
    }
    QMessageBox::about(this, tr("About The Project"), tr(innerText.c_str()));
}

void MainWindow::aboutRoot() {
    std::vector <TString> lines;
    // Here, %%s results in %s after TString::Format():
    lines.emplace_back(TString::Format("Welcome to ROOT %s \t\t https://root.cern", gROOT->GetVersion()));
    lines.emplace_back(TString::Format("(c) 1995-2019, The ROOT Team; conception: R. Brun, F. Rademakers%%s"));
    lines.emplace_back(TString::Format("Built for %s on %s", gSystem->GetBuildArch(), gROOT->GetGitDate()));
    static const char *months[] = {"January", "February", "March", "April", "May",
                                   "June", "July", "August", "September", "October",
                                   "November", "December"};
    Int_t idatqq = gROOT->GetVersionDate();
    Int_t iday = idatqq % 100;
    Int_t imonth = (idatqq / 100) % 100;
    Int_t iyear = (idatqq / 10000);

    lines.emplace_back(TString::Format("Version from %d %s %4d", iday, months[imonth - 1], iyear));

    std::string root_logo;
    for (const auto &line : lines) {
        root_logo.append(line.Data());
        root_logo.append("\n");
    }
    QMessageBox::about(this, tr("About ROOT"), tr(root_logo.c_str()));
}