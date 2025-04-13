#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "settings.h"

#include <QMainWindow>
#include <QTimer>

#include <memory>

namespace Ui {
    class CMainWindow;
}

class CMainWindow : public QMainWindow
{
  Q_OBJECT

public:
  CMainWindow(QWidget* _pParent = nullptr);
  ~CMainWindow();

signals:
  void finished();

protected slots:
  void OnStartButtonClicked(bool _checked);
  void OnFontButtonClicked();
  void OnWPMspinBoxValueChanged(int _value);
  void OnColorsButtonClicked();
  void OnRepeatCheckBoxClicked(bool _checked);
  void displayNext();

  void backgroundChanged(const QColor& _color);
  void foregroundChanged(const QColor& _color);

  void toggleFullscreen();
  void quitApplication();

protected:
  void changeEvent(QEvent* _pEvent);
  void connectMenu();

private:
  std::unique_ptr<Ui::CMainWindow> m_spUi;
  QTimer            m_timer;
  QStringList       m_tokens;
  long              m_index;
  CSettings         m_settings;
  Qt::WindowStates  m_lastState;
};

#endif // MAINWINDOW_H
