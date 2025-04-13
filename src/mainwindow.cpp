#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "colordialog.h"
#include <QClipboard>
#include <QFontDialog>
#include <QMouseEvent>
#include <QFile>

CMainWindow::CMainWindow(QWidget* _pParent)
  : QMainWindow(_pParent),
    m_spUi(std::make_unique<Ui::CMainWindow>()),
    m_index(0)
{
  m_spUi->setupUi(this);

  m_spUi->pTextLabel->setFont(m_settings.font());

  QPalette p(m_spUi->pTextLabel->palette());
  p.setColor(QPalette::Window, m_settings.background());
  p.setColor(QPalette::Text, m_settings.foreground());
  m_spUi->pTextLabel->setPalette(p);

  m_spUi->pWPMspinBox->setValue(m_settings.wpm());

  m_spUi->pRepeatCheckBox->setChecked(m_settings.repeat());


  connect(m_spUi->pStartButton, &QPushButton::clicked,
          this, &CMainWindow::OnStartButtonClicked);

  connect(m_spUi->pFontButton, &QPushButton::clicked,
          this, &CMainWindow::OnFontButtonClicked);

  connect(m_spUi->pWPMspinBox, &QSpinBox::valueChanged,
          this, &CMainWindow::OnWPMspinBoxValueChanged);

  connect(m_spUi->pColorsButton, &QPushButton::clicked,
          this, &CMainWindow::OnColorsButtonClicked);

  connect(m_spUi->pRepeatCheckBox, &QCheckBox::clicked,
          this, &CMainWindow::OnRepeatCheckBoxClicked);


  connect(&m_timer, &QTimer::timeout,
          this, &CMainWindow::displayNext);

  connectMenu();

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
    OnStartButtonClicked(true);

    connect(this, &CMainWindow::finished,
            this, &CMainWindow::close);
  }
}

CMainWindow::~CMainWindow()
{
}

void CMainWindow::OnStartButtonClicked(bool _checked)
{
  if(_checked || !m_timer.isActive())
  {
    m_timer.setInterval(m_settings.interval());
    m_settings.save();
    // get text from clipboard and split it to a stringlist
    m_tokens = QApplication::clipboard()->text().split(" ");
    // init the index
    m_index = 0;

    m_timer.start();

    m_spUi->pStartButton->setText(tr("Stop"));
    m_spUi->pStartButton->setChecked(true);
  }
  else
  {
    m_timer.stop();

    m_spUi->pStartButton->setText(tr("Start"));
    m_spUi->pStartButton->setChecked(false);
  }
}

void CMainWindow::OnFontButtonClicked()
{
  // create dialog, set old font, if OK -> set the new font
  QFontDialog dialog;
  dialog.setCurrentFont(m_settings.font());
  if( dialog.exec())
  {
    // if Ok pressed -> set and save the font
    m_spUi->pTextLabel->setFont(dialog.currentFont());
    m_settings.setFont(dialog.currentFont());
    m_settings.save();
  }
}

void CMainWindow::OnWPMspinBoxValueChanged(int _value)
{
  m_settings.setWPM(_value);
  // set the new interval on demand
  m_timer.setInterval(m_settings.interval());
}

void CMainWindow::OnColorsButtonClicked()
{
  CColorDialog dialog( m_settings.foreground(), m_settings.background());
  connect(&dialog, &CColorDialog::backgroundChanged,
         this, &CMainWindow::backgroundChanged);
  connect(&dialog, &CColorDialog::foregroundChanged,
          this, &CMainWindow::foregroundChanged);
  if(dialog.exec())
  {
    m_settings.setBackground(dialog.background());
    m_settings.setForeground(dialog.foreground());
  }
}

void CMainWindow::OnRepeatCheckBoxClicked(bool _checked)
{
  m_settings.setRepeat(_checked);
}

void CMainWindow::displayNext()
{
  // display the text at index, then increment index
  m_spUi->pTextLabel->setText(m_tokens.at(m_index++));

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
      m_spUi->pStartButton->setChecked(false);
      // change the text of the button
      m_spUi->pStartButton->setText(tr("Start"));
    }
  }
}

void CMainWindow::backgroundChanged(const QColor& _color)
{
  m_settings.setBackground(_color);
  QPalette p(m_spUi->pTextLabel->palette());
  p.setColor(QPalette::Window, m_settings.background());
  m_spUi->pTextLabel->setPalette(p);
}

void CMainWindow::foregroundChanged(const QColor& _color)
{
  m_settings.setForeground(_color);
  QPalette p(m_spUi->pTextLabel->palette());
  p.setColor(QPalette::Text, m_settings.foreground());
  m_spUi->pTextLabel->setPalette(p);
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
    m_spUi->retranslateUi(this);
    break;
  default:
    break;
  }
}

void CMainWindow::connectMenu()
{
  connect(m_spUi->actionQuit, &QAction::triggered,
          this, &CMainWindow::quitApplication);
  connect(m_spUi->actionFullscreen, &QAction::triggered,
          this, &CMainWindow::toggleFullscreen);
  connect(m_spUi->actionRun, &QAction::triggered,
          this, &CMainWindow::OnStartButtonClicked);
}


