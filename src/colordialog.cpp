#include "colordialog.h"
#include "ui_colordialog.h"
#include <QColorDialog>

CColorDialog::CColorDialog(const QColor& _foreground,
                           const QColor& _background,
                           QWidget* _pParent)
  : QDialog(_pParent),
    m_pUi(new Ui::CColorDialog),
    m_foreground(_foreground),
    m_background(_background)
{
  m_pUi->setupUi(this);
  m_pUi->pForegroundButton->setStyleSheet(QString("background-color: %1").arg(_foreground.name()));
  m_pUi->pBackgroundButton->setStyleSheet(QString("background-color: %1").arg(_background.name()));
}

CColorDialog::~CColorDialog()
{
  delete m_pUi;
}

void CColorDialog::changeEvent(QEvent* _pEvent)
{
  QDialog::changeEvent(_pEvent);
  switch( _pEvent->type()) {
  case QEvent::LanguageChange:
      m_pUi->retranslateUi(this);
      break;
  default:
      break;
  }
}

void CColorDialog::on_pBackgroundButton_clicked()
{
  QColorDialog dialog;
  dialog.setCurrentColor(m_background);
  if(dialog.exec())
  {
    m_background = dialog.currentColor();
    m_pUi->pBackgroundButton->setStyleSheet(QString("background-color: %1").arg(m_background.name()));
    emit backgroundChanged(m_background);
  }
}

void CColorDialog::on_pForegroundButton_clicked()
{
  QColorDialog dialog;
  dialog.setCurrentColor(m_foreground);
  if(dialog.exec())
  {
    m_foreground = dialog.currentColor();
    m_pUi->pForegroundButton->setStyleSheet(QString("background-color: %1").arg(m_foreground.name()));
    emit foregroundChanged(m_foreground);
  }
}

