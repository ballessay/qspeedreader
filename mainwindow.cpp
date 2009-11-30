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

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "colordialog.h"
#include <QClipboard>
#include <QFontDialog>
#include <QMouseEvent>
#include <QFile>

CMainWindow::CMainWindow(QWidget* _pParent)
  : QMainWindow(_pParent),
    m_pUi(new Ui::CMainWindow),
    m_index(0)
{
  // setup the stuff created with designer
  m_pUi->setupUi(this);

  m_pUi->pTextLabel->setFont(m_settings.font());

  // get the labels palette
  QPalette p(m_pUi->pTextLabel->palette());
  // set background and foreground color
  p.setColor(QPalette::Background, m_settings.background());
  p.setColor(QPalette::Foreground, m_settings.foreground());
  // set modified palette
  m_pUi->pTextLabel->setPalette(p);

  // set words per minute value
  m_pUi->pWPMspinBox->setValue(m_settings.wpm());

  // set check box value
  m_pUi->pRepeatCheckBox->setChecked(m_settings.repeat());

  // connect the timer to the local slot
  connect(&m_timer, SIGNAL(timeout()),
          this, SLOT(displayNext()));

  // connect menu actions and extra stuff
  connectMenu();

  //hide status bar
  statusBar()->setVisible(false);

  // read stdin
  QFile file;
  if(file.open(0, QIODevice::ReadOnly) && file.bytesAvailable())
  {
    m_tokens = QString(file.readAll()).split(" ");
    file.close();
  }

  // quick-n-dirty solution ---------------
  // get arguments
  QStringList args = qApp->arguments();
  for( int i = 0; i < args.size(); ++i)
  {
    // get i-th argument
    QString arg = args.at(i);
    // check for option
    if(arg == "-f" || arg == "--fullscreen")
    {
      toggleFullscreen();
    }
    if(arg == "-h" || arg == "--help")
    {
      qDebug("./qspeedreader -h || -f");
      qApp->quit();
    }
  }

  // if we have tokens at this moment -> start for one run
  if(0 < m_tokens.size())
  {
    on_pStartButton_clicked(true);

    connect(this, SIGNAL(finished()),
            this, SLOT(close()));
  }
}

CMainWindow::~CMainWindow()
{
  delete m_pUi;
}

void CMainWindow::on_pStartButton_clicked(bool _checked)
{
  if(_checked || !m_timer.isActive())
  {
    m_timer.setInterval(m_settings.interval());
    m_settings.save();
    // get text from clipboard and split it to a stringlist
    m_tokens = QApplication::clipboard()->text().split(" ");
    // init the index
    m_index = 0;
    // start the timer
    m_timer.start();
    // change the button text
    m_pUi->pStartButton->setText(tr("Stop"));
    m_pUi->pStartButton->setChecked(true);
  }
  else
  {
    // stop the timer
    m_timer.stop();
    // change the button text
    m_pUi->pStartButton->setText(tr("Start"));
    m_pUi->pStartButton->setChecked(false);
  }
}

void CMainWindow::on_pFontButton_clicked()
{
  // create dialog, set old font, if OK -> set the new font
  QFontDialog dialog;
  dialog.setCurrentFont(m_settings.font());
  if( dialog.exec())
  {
    // if Ok pressed -> set and save the font
    m_pUi->pTextLabel->setFont(dialog.currentFont());
    m_settings.setFont(dialog.currentFont());
    m_settings.save();
  }
}

void CMainWindow::on_pWPMspinBox_valueChanged(int _value)
{
  m_settings.setWPM(_value);
  // set the new interval on demand
  m_timer.setInterval(m_settings.interval());
}

void CMainWindow::on_pColorsButton_clicked()
{
  CColorDialog dialog( m_settings.foreground(), m_settings.background());
  connect( &dialog, SIGNAL(backgroundChanged(const QColor&)),
           this, SLOT(backgroundChanged(const QColor&)));
  connect( &dialog, SIGNAL(foregroundChanged(const QColor&)),
           this, SLOT(foregroundChanged(const QColor&)));
  if(dialog.exec())
  {
    m_settings.setBackground(dialog.background());
    m_settings.setForeground(dialog.foreground());
  }
}

void CMainWindow::on_pRepeatCheckBox_clicked(bool _checked)
{
  m_settings.setRepeat(_checked);
}

void CMainWindow::displayNext()
{
  // display the text at index, then increment index
  m_pUi->pTextLabel->setText(m_tokens.at(m_index++));

  // if index has reached the last element
  if(m_index >= m_tokens.size())
  {
    // signal that the run is finished
    emit finished();
    // if repeating is set...
    if(m_settings.repeat())
    {
      //...start from begin
      m_index = 0;
    }
    else
    {
      // stop the timer
      m_timer.stop();
      // set the button unchecked
      m_pUi->pStartButton->setChecked(false);
      // change the text of the button
      m_pUi->pStartButton->setText(tr("Start"));
    }
  }
}

void CMainWindow::backgroundChanged(const QColor& _color)
{
  m_settings.setBackground(_color);
  QPalette p(m_pUi->pTextLabel->palette());
  p.setColor(QPalette::Background, m_settings.background());
  m_pUi->pTextLabel->setPalette(p);
}

void CMainWindow::foregroundChanged(const QColor& _color)
{
  m_settings.setForeground(_color);
  QPalette p(m_pUi->pTextLabel->palette());
  p.setColor(QPalette::Foreground, m_settings.foreground());
  m_pUi->pTextLabel->setPalette(p);
}

void CMainWindow::toggleFullscreen()
{
  if(isFullScreen())
  {
    // set the last saved state
    setWindowState(m_lastState);
  }
  else
  {
    // save current state
    m_lastState = windowState();
    // set fullscreen
    setWindowState(Qt::WindowFullScreen);
  }
}

void CMainWindow::quitApplication()
{
  close();
}

// standard method for retranslation at runtime
void CMainWindow::changeEvent(QEvent* _pEvent)
{
  QMainWindow::changeEvent(_pEvent);
  switch (_pEvent->type())
  {
  case QEvent::LanguageChange:
    m_pUi->retranslateUi(this);
    break;
  default:
    break;
  }
}

void CMainWindow::connectMenu()
{
  connect(m_pUi->actionQuit, SIGNAL(triggered()),
          this, SLOT(quitApplication()));
  connect(m_pUi->actionFullscreen, SIGNAL(triggered()),
          this, SLOT(toggleFullscreen()));
  connect(m_pUi->actionRun, SIGNAL(triggered(bool)),
          this, SLOT(on_pStartButton_clicked(bool)));
}


