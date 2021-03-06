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
