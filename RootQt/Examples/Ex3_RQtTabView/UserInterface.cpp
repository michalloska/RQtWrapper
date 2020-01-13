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
    mainWindow->setWindowTitle("RQtGeo - Two Canvases - One window");

    mainWindow->setMinimumSize(620, 470);

    centralWidget = new QWidget(mainWindow);
    centralWidget->setObjectName(QStringLiteral("centralWidget"));
    centralWidget->setMinimumSize(mainWindow->width(), mainWindow->height());
    createMainMenuActions(mainWindow);

    verticalLayout = new QVBoxLayout(centralWidget);
    mainWindow->setCentralWidget(centralWidget); // good track does not work

    verticalLayoutWidget = new QWidget(centralWidget);
    verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
    verticalLayoutWidget->setMinimumSize(centralWidget->width(), centralWidget->height());
    verticalLayout->addWidget(verticalLayoutWidget);

    horizontalLayout = new QHBoxLayout(verticalLayoutWidget);
    horizontalLayout->setSpacing(6);
    horizontalLayout->setContentsMargins(11, 11, 11, 11);
    horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
    horizontalLayout->setContentsMargins(0, 0, 0, 0);

    tabWidget = new QTabWidget(verticalLayoutWidget);
    horizontalLayout->addWidget(tabWidget);
    canvasMap["tab1"] = new RQtWidget(verticalLayoutWidget);
    canvasMap["tab2"] = new RQtWidget(verticalLayoutWidget);

    auto histogramWidget = new QWidget(verticalLayoutWidget);
    histogramButton = new QPushButton(histogramWidget);
    histogramButton->setText("Histogram");
    histogramButton->setFixedSize(QSize(150, 50));

    auto histogramLayout = new QVBoxLayout(histogramWidget);
    histogramLayout->setAlignment(Qt::AlignCenter);
    histogramLayout->addWidget(histogramButton);

    tabWidget->addTab( canvasMap.at("tab1"), "Plot" );
    tabWidget->addTab( canvasMap.at("tab2"), "Candle" );
    tabWidget->addTab( histogramWidget, "Histogram" );

    DrawPlot(canvasMap.at("tab1"));
    Candleplot(canvasMap.at("tab2"));

    QObject::connect(histogramButton, &QPushButton::clicked, mainWindow, [=](){DrawHistogram();});
}

void UserInterface::DrawPlot(RQtWidget* p_rqtWidget){
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

void UserInterface::Candleplot(RQtWidget* p_rqtWidget){
    std::cout<< "[INFO]:: DrawCandle" << std::endl;

    p_rqtWidget->getCanvas()->getCanvas()->Clear();
    p_rqtWidget->getCanvas()->getCanvas()->cd();
    p_rqtWidget->getCanvas()->getCanvas()->SetBorderMode(0);

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

    p_rqtWidget->getCanvas()->getCanvas()->Modified();
    p_rqtWidget->getCanvas()->getCanvas()->Update();
}

void UserInterface::DrawHistogram(){
    std::cout<< "[INFO]:: DrawHistogram" << std::endl;
    auto c1 = new TCanvas();
    gStyle->SetOptStat(0);
    auto h1 = new TH1D("histogram1", "histogram1", 50, -5, 5);

    TRandom3 r;
    for (int i=0;i<10000;i++) {
        h1->Fill(r.Gaus(0,1));
    }
    h1->Draw();
    h1->GetXaxis()->SetTitle("x");
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

    QAction *helpAboutProject = helpMenu->addAction(QPushButton::tr("Changelog"), mainWindow, [=](){mainWindow->aboutProject();});
    helpAboutProject->setStatusTip(QPushButton::tr("Show the project's About box"));

    mainWindow->menuBar()->move(100, 10);
    appMenu->move(100, 10);
}
