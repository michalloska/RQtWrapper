#include <qstatusbar.h>
#include <qmessagebox.h>
#include <qmenubar.h>
#include <qapplication.h>
#include <qimage.h>
#include <qtimer.h>

#include <stdlib.h>
#include <TApplication.h>
#include <TSystem.h>
#include <TROOT.h>
#include <TStyle.h>
#include <TPluginManager.h>
#include <TVirtualGL.h>
#include <TVirtualX.h>
#include "MainWindow.h"

#include "RQtApplication.h"


int main(int argc, char** argv)
{
    RQtApplication rQtApplication(argc, &argc, argv);         // ROOT application is being interfaced to Qt

#if QT_VERSION < 0x050000
   if (!gGLManager) {
      TString x = "win32";
      if (gVirtualX->InheritsFrom("TGX11"))
         x = "x11";
      else if (gVirtualX->InheritsFrom("TGCocoa"))
         x = "osx";
      TPluginHandler *ph = gROOT->GetPluginManager()->FindHandler("TGLManager", x);
      if (ph && ph->LoadPlugin() != -1)
         ph->ExecPlugin(0);
   }
   gStyle->SetCanvasPreferGL(true);
#endif
   MainWindow myapp;

   myapp.show();

   QObject::connect( qApp, SIGNAL(lastWindowClosed()), qApp, SLOT(quit()) );

   return rQtApplication.exec();
}


