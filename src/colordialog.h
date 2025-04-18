#ifndef COLORDIALOG_H
#define COLORDIALOG_H

#include <QDialog>
#include <memory>

namespace Ui {
    class CColorDialog;
}

class CColorDialog : public QDialog
{
  Q_OBJECT

public:
  CColorDialog(const QColor& _foreground,
               const QColor& _background,
               QWidget* _pParent = nullptr);
  ~CColorDialog();

  QColor foreground() const { return m_foreground;}
  QColor background() const { return m_background;}

signals:
  void backgroundChanged(const QColor& _color);
  void foregroundChanged(const QColor& _color);

protected slots:
  void OnForegroundButtonClicked();
  void OnBackgroundButtonClicked();

protected:
  void changeEvent(QEvent* _pEvent);

private:
  std::unique_ptr<Ui::CColorDialog> m_spUi;

  QColor            m_foreground;
  QColor            m_background;
};

#endif // COLORDIALOG_H
