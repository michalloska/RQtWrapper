
#ifndef RQTAPPLICATION_H
#define RQTAPPLICATION_H


#include <QApplication>
#include "TApplication.h"

class QTimer;

class RQtApplication : public QApplication, public TApplication {
   Q_OBJECT

   public:
      RQtApplication(int& rargc, int* pargc, char **argv, int poll=0);
      virtual ~RQtApplication() = default;

   public slots:
      void quit();

   protected:
      QTimer*   timer;
};

#endif // RQTAPPLICATION_H