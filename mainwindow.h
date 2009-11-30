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
