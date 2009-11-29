#ifndef COLORDIALOG_H
#define COLORDIALOG_H

#include <QDialog>

namespace Ui {
    class CColorDialog;
}

class CColorDialog : public QDialog
{
  Q_OBJECT

public:
  CColorDialog( const QColor& _foreground,
                const QColor& _background,
                QWidget* _pParent = 0);
  ~CColorDialog();

  QColor foreground() const { return m_foreground;}
  QColor background() const { return m_background;}

signals:
  void backgroundChanged(const QColor& _color);
  void foregroundChanged(const QColor& _color);

protected slots:
  void on_pForegroundButton_clicked();
  void on_pBackgroundButton_clicked();

protected:
  void changeEvent(QEvent* _pEvent);

private:
  Ui::CColorDialog* m_pUi;
  QColor            m_foreground;
  QColor            m_background;
};

#endif // COLORDIALOG_H
