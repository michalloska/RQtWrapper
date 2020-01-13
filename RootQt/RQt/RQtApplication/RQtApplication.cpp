#include "RQtApplication.h"

#include <stdlib.h>

#include "TSystem.h"
#include "Riostream.h"

#include <QtCore/QObject>
#include <QtCore/QTimer>


RQtApplication::RQtApplication(int& rargc, int* pargc, char **argv, int poll)
   : QApplication(rargc,argv, true)
   , TApplication("RootApp", pargc, argv) {

  // connect ROOT via Timer call back
  if (poll == 0) {
    timer = new QTimer(this);
    QObject::connect(timer, &QTimer::timeout, [](){gSystem->ProcessEvents();});
    timer->setSingleShot(false);
    timer->start(20);
  }
}

void RQtApplication::quit()
{
  std::cout <<"[STATUS]:: RQtApplication::quit()" << std::endl;
  gSystem->Exit( 0 );
}