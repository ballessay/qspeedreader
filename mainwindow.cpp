#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "colordialog.h"
#include <QClipboard>
#include <QFontDialog>
#include <QMouseEvent>

CMainWindow::CMainWindow(QWidget* _pParent)
  : QMainWindow(_pParent),
    m_pUi(new Ui::CMainWindow),
    m_index(0)
{
  // setup the stuff created with designer
  m_pUi->setupUi(this);

  m_pUi->pTextLabel->setFont(m_settings.font());

  QPalette p(m_pUi->pTextLabel->palette());
  // Set background and foreground color
  p.setColor(QPalette::Background, m_settings.background());
  p.setColor(QPalette::Foreground, m_settings.foreground());
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
    m_pUi->pTextLabel->setFont(dialog.currentFont());
    m_settings.setFont(dialog.currentFont());
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
    if(m_settings.repeat())
    {
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
    setWindowState(m_lastState);
  }
  else
  {
    m_lastState = windowState();
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


