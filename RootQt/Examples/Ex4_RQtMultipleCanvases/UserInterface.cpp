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
#include <QGridLayout>

#include "TStyle.h"
#include "TColor.h"
#include "TF2.h"
#include "TExec.h"
#include "TCanvas.h"

#include "TStopwatch.h"
#include "TDatime.h"
#include "TLatex.h"

void UserInterface::setupUi(MainWindow *mainWindow) {
    mainWindow->setWindowModality(Qt::WindowModal);
    mainWindow->setWindowTitle("RQtGeo - Multiple Canvases - One window");

    mainWindow->setMinimumSize(1380, 480);
    createMainMenuActions(mainWindow);

    auto centralWidget = new QWidget(mainWindow);
    centralWidget->setMinimumSize(mainWindow->width(), mainWindow->height());

    centralWidget->setMinimumSize(mainWindow->width()/2, mainWindow->height());
    mainWindow->setCentralWidget(centralWidget);
    centralWidget->setStyleSheet("QWidget { background: green; }");

    auto mainWidget = new QWidget(centralWidget);
    mainWidget->setStyleSheet("QWidget { background: red; }");
    mainWidget->setMinimumSize(centralWidget->width()/2, centralWidget->height() );

    auto centralWidgetLayout = new QVBoxLayout(centralWidget);
    centralWidgetLayout->addWidget(mainWidget);

    auto mainWidgetLayout = new QHBoxLayout(mainWidget);
    auto leftRQtWidget = new RQtWidget(mainWidget);
    leftRQtWidget->setMinimumSize(mainWidget->width()/2, mainWidget->height());
    mainWidgetLayout->addWidget(leftRQtWidget);

    auto rightWidget = new QWidget(mainWidget);
    rightWidget->setMinimumSize(320,240);
    centralWidget->setStyleSheet("QWidget { background: blue; }");
    mainWidgetLayout->addWidget(rightWidget);

    auto rqtCanvas1 = new RQtWidget(rightWidget);
    auto rqtCanvas2 = new RQtWidget(rightWidget);
    auto rqtCanvas3 = new RQtWidget(rightWidget);
    auto rqtCanvas4 = new RQtWidget(rightWidget);

    auto gridRightWidgetLayout = new QGridLayout(rightWidget);
    gridRightWidgetLayout->addWidget(rqtCanvas1, 0, 0);
    gridRightWidgetLayout->addWidget(rqtCanvas2, 0, 1);
    gridRightWidgetLayout->addWidget(rqtCanvas3, 1, 0);
    gridRightWidgetLayout->addWidget(rqtCanvas4, 1, 1);

    ///DRAWING:
    multipalette(leftRQtWidget);
    DrawLandauHistogram(rqtCanvas1);
    DrawPlot(rqtCanvas2);
    Candleplot(rqtCanvas3);
    DrawHistogram(rqtCanvas4);
}

void UserInterface::DrawPlot(RQtWidget *rqtWidget) {
    TH1F *h1f = 0;
    rqtWidget->getCanvas()->getCanvas()->Clear();
    rqtWidget->getCanvas()->getCanvas()->cd();
    rqtWidget->getCanvas()->getCanvas()->SetBorderMode(0);
    rqtWidget->getCanvas()->getCanvas()->SetFillColor(0);
    rqtWidget->getCanvas()->getCanvas()->SetGrid();
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
    rqtWidget->getCanvas()->getCanvas()->Modified();
    rqtWidget->getCanvas()->getCanvas()->Update();
}

void UserInterface::DrawHistogram(RQtWidget * rqtWidget){
    std::cout<< "[INFO]:: DrawHistogram" << std::endl;
    rqtWidget->getCanvas()->getCanvas()->Clear();
    rqtWidget->getCanvas()->getCanvas()->cd();
    rqtWidget->getCanvas()->getCanvas()->SetBorderMode(0);
    rqtWidget->getCanvas()->getCanvas()->SetFillColor(0);
    rqtWidget->getCanvas()->getCanvas()->SetGrid();
    gStyle->SetOptStat(0);
    auto h1 = new TH1D("Gaus Histogram", "Gaus Histogram", 50, -5, 5);

    TRandom3 r;
    for (int i=0;i<10000;i++) {
        h1->Fill(r.Gaus(0,1));
    }
    h1->Draw();
    h1->GetXaxis()->SetTitle("x");
    rqtWidget->getCanvas()->getCanvas()->Modified();
    rqtWidget->getCanvas()->getCanvas()->Update();
}

void UserInterface::DrawLandauHistogram(RQtWidget * rqtWidget){
    std::cout<< "[INFO]:: DrawHistogram" << std::endl;
    rqtWidget->getCanvas()->getCanvas()->Clear();
    rqtWidget->getCanvas()->getCanvas()->cd();
    rqtWidget->getCanvas()->getCanvas()->SetBorderMode(0);
    rqtWidget->getCanvas()->getCanvas()->SetFillColor(0);
    rqtWidget->getCanvas()->getCanvas()->SetGrid();
    gStyle->SetOptStat(0);
    auto h1 = new TH1D("Landau Histogram", "Landau Histogram", 50, -5, 5);

    TRandom3 r;
    for (int i=0;i<10000;i++) {
        h1->Fill(r.Landau(0,1));
    }
    h1->Draw();
    h1->GetXaxis()->SetTitle("x");
    rqtWidget->getCanvas()->getCanvas()->Modified();
    rqtWidget->getCanvas()->getCanvas()->Update();
}

void UserInterface::Candleplot(RQtWidget *rqtWidget) {
    std::cout<< "[INFO]:: DrawCandle" << std::endl;

    rqtWidget->getCanvas()->getCanvas()->Clear();
    rqtWidget->getCanvas()->getCanvas()->cd();
    rqtWidget->getCanvas()->getCanvas()->SetBorderMode(0);

    gStyle->SetTimeOffset(0);
    TDatime dateBegin(2010,1,1,0,0,0);
    TDatime dateEnd(2011,1,1,0,0,0);
    auto h1 = new TH2I("h1","Machine A + B",12,dateBegin.Convert(),dateEnd.Convert(),1000,0,1000);
    auto h2 = new TH2I("h2","Machine B",12,dateBegin.Convert(),dateEnd.Convert(),1000,0,1000);
    h1->GetXaxis()->SetTimeDisplay(1);
    h1->GetXaxis()->SetTimeFormat("%m/%y");
    h1->GetXaxis()->SetTitle("Date [month/year]");
    float Rand;
    for (int i = dateBegin.Convert(); i < dateEnd.Convert(); i+=86400*30) {
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
    gPad->BuildLegend(0.78,0.695,0.980,0.935,"","f");

    rqtWidget->getCanvas()->getCanvas()->Modified();
    rqtWidget->getCanvas()->getCanvas()->Update();
}

void UserInterface::setMainBackground(MainWindow *mainWindow) {
    QPalette palette;
    auto gradient = QLinearGradient(0, 0, 10, 10);
    gradient.setColorAt(0, Qt::white);
    gradient.setColorAt(1, Qt::black);
    gradient.setCoordinateMode(QGradient::StretchToDeviceMode);
    palette.setBrush(QPalette::Background, gradient);
    mainWindow->setPalette(palette);
    mainWindow->setAutoFillBackground(true);
}

void UserInterface::Pal1(){
    static Int_t  colors[50];
    static Bool_t initialized = kFALSE;
    Double_t Red[3]    = { 1.00, 0.00, 0.00};
    Double_t Green[3]  = { 0.00, 1.00, 0.00};
    Double_t Blue[3]   = { 1.00, 0.00, 1.00};
    Double_t Length[3] = { 0.00, 0.50, 1.00 };
    if(!initialized){
        Int_t FI = TColor::CreateGradientColorTable(3,Length,Red,Green,Blue,50);
        for (int i=0; i<50; i++) colors[i] = FI+i;
        initialized = kTRUE;
        return;
    }
    gStyle->SetPalette(50,colors);
}

void UserInterface::Pal2(){
    static Int_t  colors[50];
    static Bool_t initialized = kFALSE;
    Double_t Red[3]    = { 1.00, 0.50, 0.00};
    Double_t Green[3]  = { 0.50, 0.00, 1.00};
    Double_t Blue[3]   = { 1.00, 0.00, 0.50};
    Double_t Length[3] = { 0.00, 0.50, 1.00 };
    if(!initialized){
        Int_t FI = TColor::CreateGradientColorTable(3,Length,Red,Green,Blue,50);
        for (int i=0; i<50; i++) colors[i] = FI+i;
        initialized = kTRUE;
        return;
    }
    gStyle->SetPalette(50,colors);
}

void UserInterface::multipalette(RQtWidget * rqtWidget) {
    rqtWidget->getCanvas()->getCanvas()->Divide(2,1);
    TF2 *f3 = new TF2("f3","0.1+(1-(x-2)*(x-2))*(1-(y-2)*(y-2))",1,3,1,3);
    f3->SetLineWidth(1);
    f3->SetLineColor(kBlack);
    rqtWidget->getCanvas()->getCanvas()->cd(1);
    f3->Draw("surf1");
    TExec *ex1 = new TExec("ex1","Pal1();");
    ex1->Draw();
    f3->Draw("surf1 same");
    rqtWidget->getCanvas()->getCanvas()->cd(2);
    f3->Draw("surf1");
    TExec *ex2 = new TExec("ex2","Pal2();");
    ex2->Draw();
    f3->Draw("surf1 same");
}

void UserInterface::createMainMenuActions(MainWindow *mainWindow) {

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
}