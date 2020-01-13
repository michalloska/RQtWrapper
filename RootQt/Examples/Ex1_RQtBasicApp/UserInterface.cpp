#include "UserInterface.h"
#include "TStyle.h"
#include "TH1D.h"
#include "TRandom3.h"
#include "TF1.h"
#include "TRatioPlot.h"
#include "MainWindow.h"
#include <QMainWindow>
#include <QDialog>
#include "TH2I.h"
#include "TCanvas.h"
#include "TH2.h"
#include "THStack.h"
#include "RQtWidget.h"

void UserInterface::setupUi(MainWindow* mainWindow){
    mainWindow->setWindowModality(Qt::WindowModal);
    mainWindow->setWindowTitle("RQtGeo - Basic App");

    mainWindow->setMinimumSize(620, 470);

    centralWidget = new QWidget(mainWindow);
    centralWidget->setObjectName(QStringLiteral("centralWidget"));
    centralWidget->setMinimumSize(mainWindow->width(), mainWindow->height());
    createMainMenuActions(mainWindow);

    verticalLayout1 = new QVBoxLayout(centralWidget);
    verticalLayout1->addWidget(centralWidget);

    verticalLayoutWidget = new QWidget(centralWidget);
    verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
    verticalLayoutWidget->setMinimumSize(centralWidget->width(), centralWidget->height());
    mainWindow->setCentralWidget(verticalLayoutWidget); // good track does not work

    verticalLayout = new QVBoxLayout(verticalLayoutWidget);
    verticalLayout->setSpacing(6);
    verticalLayout->setContentsMargins(11, 11, 11, 11);
    verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
    verticalLayout->setContentsMargins(0, 0, 0, 0);

    mainCanvas = new RQtWidget(verticalLayoutWidget);
    verticalLayout->addWidget(mainCanvas);

    mainCanvas->setWindowTitle("Qt Example - Canvas");
    mainCanvas->setGeometry( 100, 100, 699, 499 );
    mainCanvas->show();

    ///DRAWING:
    DrawPlot(mainCanvas);
}

void UserInterface::CreateOutterWindow(){
    auto outterRqtWidget = new RQtWidget();
    Candleplot(outterRqtWidget);
}

void UserInterface::DrawPlot(RQtWidget * p_rqtWidget){
    TH1F *h1f = 0;

    p_rqtWidget->getCanvas()->getCanvas()->Clear();
    p_rqtWidget->getCanvas()->getCanvas()->cd();
    p_rqtWidget->getCanvas()->getCanvas()->SetBorderMode(0);
    p_rqtWidget->getCanvas()->getCanvas()->SetFillColor(0);
    p_rqtWidget->getCanvas()->getCanvas()->SetGrid();
    if (h1f == 0) {
        h1f = new TH1F("h1f","Test random numbers", 200, 0, 10);
        new TFormula("form1","abs(sin(x)/x)");
        TF1 *sqroot = new TF1("sqroot","x*gaus(0) + [3]*form1", 0, 10);
        sqroot->SetParameters(10, 4, 1, 20);
    }
    h1f->Reset();
    h1f->SetFillColor(kViolet + 2);
    h1f->SetFillStyle(3001);
    h1f->FillRandom("sqroot", 10000);
    h1f->Draw();
    p_rqtWidget->getCanvas()->getCanvas()->Modified();
    p_rqtWidget->getCanvas()->getCanvas()->Update();

}

void UserInterface::Candleplot(RQtWidget *p_rqtWidget) {
    std::cout << "[INFO]:: DrawCandle" << std::endl;

    p_rqtWidget->getCanvas()->getCanvas()->Clear();
    p_rqtWidget->getCanvas()->getCanvas()->cd();
    p_rqtWidget->getCanvas()->getCanvas()->SetBorderMode(0);

    gStyle->SetTimeOffset(0);
    TDatime dateBegin(2010, 1, 1, 0, 0, 0);
    TDatime dateEnd(2011, 1, 1, 0, 0, 0);
    auto h1 = new TH2I("h1", "Machine A + B", 12, dateBegin.Convert(), dateEnd.Convert(), 1000, 0, 1000);
    auto h2 = new TH2I("h2", "Machine B", 12, dateBegin.Convert(), dateEnd.Convert(), 1000, 0, 1000);
    h1->GetXaxis()->SetTimeDisplay(1);
    h1->GetXaxis()->SetTimeFormat("%m/%y");
    h1->GetXaxis()->SetTitle("Date [month/year]");
    float Rand;
    for (int i = dateBegin.Convert(); i < dateEnd.Convert(); i += 86400 * 30) {
        for (int j = 0; j < 1000; j++) {
            Rand = gRandom->Gaus(500 + sin(i / 10000000.) * 100, 50);
            h1->Fill(i, Rand);
            Rand = gRandom->Gaus(500 + sin(i / 11000000.) * 100, 70);
            h2->Fill(i, Rand);
        }
    }

    h1->SetBarWidth(0.4);
    h1->SetBarOffset(-0.25);
    h1->SetFillColor(kYellow);
    h1->SetFillStyle(1001);
    h2->SetBarWidth(0.4);
    h2->SetBarOffset(0.25);
    h2->SetLineColor(kRed);
    h2->SetFillColor(kGreen);
    h1->Draw("candle2");
    h2->Draw("candle3 same");
    gPad->BuildLegend(0.78, 0.695, 0.980, 0.935, "", "f");

    p_rqtWidget->getCanvas()->getCanvas()->Modified();
    p_rqtWidget->getCanvas()->getCanvas()->Update();
}

void UserInterface::setMainBackground(MainWindow* mainWindow) {
    QPalette palette;
    auto gradient = QLinearGradient(0, 0, 10, 10);
    gradient.setColorAt(0, Qt::white);
    gradient.setColorAt(1, Qt::black);
    gradient.setCoordinateMode(QGradient::StretchToDeviceMode);
    palette.setBrush(QPalette::Background, gradient);
    mainWindow->setPalette(palette);
    mainWindow->setAutoFillBackground(true);
}

void UserInterface::createMainMenuActions(MainWindow* mainWindow) {

    QMenu *appMenu = mainWindow->menuBar()->addMenu(QPushButton::tr("&Application"));

    const QIcon exitIcon = QIcon::fromTheme("application-exit");
    QAction *exitAct = appMenu->addAction(exitIcon, QPushButton::tr("&Exit"), mainWindow, &QWidget::close);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip(QPushButton::tr("Exit the application"));

    mainWindow->menuBar()->addSeparator();

    QMenu *helpMenu = mainWindow->menuBar()->addMenu(QPushButton::tr("&Help"));

    QAction *helpAboutAct = helpMenu->addAction(QPushButton::tr("About &GreatApp"), mainWindow, [=](){mainWindow->about();});
    helpAboutAct->setStatusTip(QPushButton::tr("Show the application's About box"));

    QAction *helpAboutRootAct = helpMenu->addAction(QPushButton::tr("About &ROOT"), mainWindow, [=](){mainWindow->aboutRoot();});
    helpAboutRootAct->setStatusTip(QPushButton::tr("Show the ROOT library's About box"));

    QAction *helpAboutQtAct = helpMenu->addAction(QPushButton::tr("About &Qt"), qApp, &QApplication::aboutQt);
    helpAboutQtAct->setStatusTip(QPushButton::tr("Show the Qt library's About box"));

    QAction *helpAboutProject = helpMenu->addAction(QPushButton::tr("RQtOutterWindow"), mainWindow, [=](){CreateOutterWindow();});
    helpAboutProject->setStatusTip(QPushButton::tr("Show the project's About box"));

    mainWindow->menuBar()->move(100, 10);
    appMenu->move(100, 10);
}
