#ifndef EXAMPLE_H
#define EXAMPLE_H

#include <QWidget>

class QPaintEvent;
class QResizeEvent;
class QMouseEvent;
class QPushButton;
class QTimer;
class TCanvas;

class RQtCanv : public QWidget
{
   Q_OBJECT

public:
    RQtCanv( QWidget *parent = 0);
    virtual ~RQtCanv() {}
    TCanvas* getCanvas() { return m_canvas;}

protected:
   TCanvas*        m_canvas;
   virtual void    mouseMoveEvent( QMouseEvent *e );
   virtual void    mousePressEvent( QMouseEvent *e );
   virtual void    mouseReleaseEvent( QMouseEvent *e );
   virtual void    paintEvent( QPaintEvent *e );
   virtual void    resizeEvent( QResizeEvent *e );
};

class RQtWidget : public QWidget
{
   Q_OBJECT

public:
    RQtWidget( QWidget *parent = 0);
    virtual ~RQtWidget() {}
    virtual void changeEvent(QEvent * e);
    RQtCanv* getCanvas(){ return m_rqtCanvas;}

public slots:
   void handle_root_events();

protected:
    void RemoveLayout(QWidget* widget);
    RQtCanv*        m_rqtCanvas;
    QTimer*         m_rootTimer;
};

#endif


