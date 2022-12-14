//------------------------------------------------------------------------
//  Copyright (C) Gabriel Taubin
//  Time-stamp: <2021-11-14 21:46:11 taubin>
//------------------------------------------------------------------------
//
// WrlViewerApp.cpp
//
// Software developed for the Fall 2021 Brown University course
// ENGN 2912B Scientific Computing in C++
// Copyright (c) 2021, Gabriel Taubin
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
//     * Neither the name of the Brown University nor the
//       names of its contributors may be used to endorse or promote products
//       derived from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL GABRIEL TAUBIN BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include <QApplication>
#include "WrlMainWindow.hpp"
#include "WrlToolsWidget.hpp"
#include <QSurfaceFormat>
#include <QScreen>
#include <iostream>

using namespace std;

int main( int argc, char ** argv ) {
  // cout << "WrlViewerApp::main() {\n";

  QApplication app( argc, argv );

  QString platformName = QGuiApplication::platformName();
  cout << "  platformName = \"" << qPrintable(platformName) << "\"" << endl;
  WrlMainWindow::setPlatformName(platformName);

  QList<QScreen *> screens = QGuiApplication::screens();
  int nScreens = screens.size();
  cout << "  nScreens = " << nScreens << endl;
  for(int i=0;i<nScreens;i++) {
      cout << "  screen[" << i << "].name = \""
           << qPrintable(screens[i]->name()) << "\"" << endl;
  }
  QScreen* primaryScreen = QGuiApplication::primaryScreen();
  cout << "  primaryScreen = "
       << primaryScreen->size().width() << "x"
       << primaryScreen->size().height() << endl;
  qreal lDPI = primaryScreen->logicalDotsPerInch();
  cout << "  lDPI = " << lDPI << endl;
  WrlMainWindow::setLogicalDotsPerInch(static_cast<int>(lDPI+0.5));

  QSurfaceFormat format;
  format.setDepthBufferSize(24);
  format.setStencilBufferSize(8);
  if (QCoreApplication::arguments().contains(QStringLiteral("--multisample")))
    format.setSamples(4);

  // format.setRenderableType(QSurfaceFormat::OpenGLES);
  QSurfaceFormat::setDefaultFormat(format);

#ifdef _WIN32
  WrlToolsWidget::setLocalDotsPerInch(static_cast<int>(lDPI+0.5));
#endif
  WrlMainWindow::setLogicalDotsPerInch(static_cast<int>(lDPI+0.5));
  WrlMainWindow::setPlatformName(platformName);

  WrlMainWindow mw;
  int tHeight = (lDPI<=96)?600:(lDPI<=144)?900:1200;
  int tWidth  = (lDPI<=96)?400:(lDPI<=144)?600:800;
  int gWidth  = 5*tHeight/4;
  mw.setMinimumSize(gWidth+tWidth,tHeight);
  mw.show();
  mw.updateGeometry();

  // cout << "}\n";

  return app.exec();
}
