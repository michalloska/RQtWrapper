#include <QPushButton>
#include <QLayout>
#include <QTimer>
#include <QPaintEvent>
#include <QResizeEvent>
#include <QMouseEvent>

#include <stdlib.h>
#include <iostream>

#include <TCanvas.h>
#include <TVirtualX.h>
#include <TSystem.h>
#include <TFormula.h>
#include <TF1.h>
#include <TH1.h>
#include <TFrame.h>
#include <TTimer.h>
#include "RQtWidget.h"


RQtCanv::RQtCanv(QWidget *parent) : QWidget(parent, 0), m_canvas(0)
{
   setAttribute(Qt::WA_PaintOnScreen, false);
   setAttribute(Qt::WA_OpaquePaintEvent, true);
   setAttribute(Qt::WA_NativeWindow, true);
   setUpdatesEnabled(kFALSE);
   setMouseTracking(kTRUE);
   setMinimumSize(parent->width(), parent->height());

   int wid = gVirtualX->AddWindow((ULong_t)winId(), width(), height());
   m_canvas = new TCanvas("Root Canvas", parent->width(), parent->height(), wid);

   TQObject::Connect("TGPopupMenu", "PoppedDown()", "TCanvas", m_canvas, "Update()");
}

void RQtCanv::mouseMoveEvent(QMouseEvent *e)
{
   if (m_canvas) {
      if (e->buttons() & Qt::LeftButton) {
         m_canvas->HandleInput(kButton1Motion, e->x(), e->y());
      } else if (e->buttons() & Qt::MidButton) {
         m_canvas->HandleInput(kButton2Motion, e->x(), e->y());
      } else if (e->buttons() & Qt::RightButton) {
         m_canvas->HandleInput(kButton3Motion, e->x(), e->y());
      } else {
         m_canvas->HandleInput(kMouseMotion, e->x(), e->y());
      }
   }
}

void RQtCanv::mousePressEvent( QMouseEvent *e )
{
   if (m_canvas) {
      switch (e->button()) {
         case Qt::LeftButton :
            m_canvas->HandleInput(kButton1Down, e->x(), e->y());
            break;
         case Qt::MidButton :
            m_canvas->HandleInput(kButton2Down, e->x(), e->y());
            break;
         case Qt::RightButton :
            m_canvas->HandleInput(kButton3Down, e->x(), e->y());
            break;
         default:
            break;
      }
   }
}

void RQtCanv::mouseReleaseEvent( QMouseEvent *e )
{
   if (m_canvas) {
      switch (e->button()) {
         case Qt::LeftButton :
            m_canvas->HandleInput(kButton1Up, e->x(), e->y());
            break;
         case Qt::MidButton :
            m_canvas->HandleInput(kButton2Up, e->x(), e->y());
            break;
         case Qt::RightButton :
            m_canvas->HandleInput(kButton3Up, e->x(), e->y());
            break;
         default:
            break;
      }
   }
}

void RQtCanv::resizeEvent( QResizeEvent *event )
{
   if (m_canvas) {
      m_canvas->SetCanvasSize(event->size().width(), event->size().height());
      m_canvas->Resize();
      m_canvas->Update();
   }
}

void RQtCanv::paintEvent( QPaintEvent * )
{
   if (m_canvas) {
      m_canvas->Resize();
      m_canvas->Update();
   }
}

RQtWidget::RQtWidget(QWidget *parent) : QWidget(parent)
{

    if(parent) {
        this->setMinimumSize(parent->width(), parent->height());
    }
    else {
        this->setWindowTitle("RQtOutterWindow");
        this->setMinimumSize(100,100);
    }

    QVBoxLayout * CanvasLayout = new QVBoxLayout(this);
    CanvasLayout->addWidget(m_rqtCanvas = new RQtCanv(this));
    m_rootTimer = new QTimer( this );
    QObject::connect( m_rootTimer, SIGNAL(timeout()), this, SLOT(handle_root_events()) );
    m_rootTimer->start( 20 );
    this->show();
}

void RQtWidget::RemoveLayout(QWidget* widget){
    auto layout = widget->layout();
    if ( layout ) {
        QLayoutItem* item;
        while ( ( item = layout->takeAt( 0 ) ) != NULL ){
            delete item->widget();
            delete item;
        }
        delete layout;
    }
}

void RQtWidget::handle_root_events()
{
    gSystem->ProcessEvents();
    m_rqtCanvas->getCanvas()->Update();
}

void RQtWidget::changeEvent(QEvent * e)
{
   if (e->type() == QEvent ::WindowStateChange) {
      QWindowStateChangeEvent * event = static_cast< QWindowStateChangeEvent * >( e );
      if (( event->oldState() & Qt::WindowMaximized ) ||
          ( event->oldState() & Qt::WindowMinimized ) ||
          ( event->oldState() == Qt::WindowNoState &&
            this->windowState() == Qt::WindowMaximized )) {
         if (m_rqtCanvas->getCanvas()) {
            m_rqtCanvas->getCanvas()->Resize();
            m_rqtCanvas->getCanvas()->Update();
         }
      }
   }
}
