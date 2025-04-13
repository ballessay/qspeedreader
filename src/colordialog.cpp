#include "colordialog.h"
#include "ui_colordialog.h"
#include <QColorDialog>

CColorDialog::CColorDialog(const QColor& _foreground,
                           const QColor& _background,
                           QWidget* _pParent)
  : QDialog(_pParent),
    m_spUi(std::make_unique<Ui::CColorDialog>()),
    m_foreground(_foreground),
    m_background(_background)
{
  m_spUi->setupUi(this);

  m_spUi->pForegroundButton->setStyleSheet(QString("background-color: %1").arg(_foreground.name()));
  connect(m_spUi->pForegroundButton, &QToolButton::clicked, this, &CColorDialog::OnForegroundButtonClicked);

  m_spUi->pBackgroundButton->setStyleSheet(QString("background-color: %1").arg(_background.name()));
  connect(m_spUi->pBackgroundButton, &QToolButton::clicked, this, &CColorDialog::OnBackgroundButtonClicked);
}

CColorDialog::~CColorDialog()
{
}

void CColorDialog::changeEvent(QEvent* _pEvent)
{
  QDialog::changeEvent(_pEvent);
  switch(_pEvent->type()) {
  case QEvent::LanguageChange:
      m_spUi->retranslateUi(this);
      break;
  default:
      break;
  }
}

void CColorDialog::OnBackgroundButtonClicked()
{
  QColorDialog dialog;
  dialog.setCurrentColor(m_background);
  if(dialog.exec())
  {
    m_background = dialog.currentColor();
    m_spUi->pBackgroundButton->setStyleSheet(QString("background-color: %1").arg(m_background.name()));
    emit backgroundChanged(m_background);
  }
}

void CColorDialog::OnForegroundButtonClicked()
{
  QColorDialog dialog;
  dialog.setCurrentColor(m_foreground);
  if(dialog.exec())
  {
    m_foreground = dialog.currentColor();
    m_spUi->pForegroundButton->setStyleSheet(QString("background-color: %1").arg(m_foreground.name()));
    emit foregroundChanged(m_foreground);
  }
}

