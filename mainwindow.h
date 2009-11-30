/*
| author:   Christian Balles
| email:    code@ballessay.de
| date:     2009/11/28
| version:  0.1
| copyright 2009 Christian Balles
|
|   This file is part of qspeedreader.
|   qspeedreader is free software: you can redistribute it and/or modify it
|   under the terms of the GNU General Public License as published by the Free
|   Software Foundation, either version 2 of the License, or (at your option)
|   any later version.
|   qspeedreader is distributed in the hope that it will be useful, but
|   WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
|   or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
|   more details.
|   You should have received a copy of the GNU General Public License along with
|   qspeedreader. If not, see http://www.gnu.org/licenses/.
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "settings.h"

namespace Ui {
    class CMainWindow;
}

class CMainWindow : public QMainWindow
{
  Q_OBJECT

public:
  CMainWindow(QWidget* _pParent = 0);
  ~CMainWindow();

signals:
  void finished();

protected slots:
  void on_pStartButton_clicked(bool _checked);
  void on_pFontButton_clicked();
  void on_pWPMspinBox_valueChanged(int _value);
  void on_pColorsButton_clicked();
  void on_pRepeatCheckBox_clicked(bool _checked);
  void displayNext();

  void backgroundChanged(const QColor& _color);
  void foregroundChanged(const QColor& _color);

  void toggleFullscreen();
  void quitApplication();

protected:
  void changeEvent(QEvent* _pEvent);
  void connectMenu();

private:
  Ui::CMainWindow*  m_pUi;
  QTimer            m_timer;
  QStringList       m_tokens;
  long              m_index;
  CSettings         m_settings;
  Qt::WindowStates  m_lastState;
};

#endif // MAINWINDOW_H
