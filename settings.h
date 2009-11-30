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

#ifndef SETTINGS_H
#define SETTINGS_H

#include <QColor>
#include <QFont>
#include <QSettings>

class CSettings
{
  // the QTimer needs its interval in msecs and the online speedreader i've seen
  // before had its speed value as 'words per minute'
  static const int c_maxWPM = 60000;

public:
  CSettings();
  ~CSettings();

  void save();

  QColor foreground() const { return m_foreground; }
  QColor background() const { return m_background; }
  QFont font() const { return m_font; }
  int interval() const { return m_interval; }
  int wpm() const { return m_wpm; }
  bool repeat() const { return m_repeat; }

  void setForeground(const QColor& _color) { m_foreground = _color; }
  void setBackground(const QColor& _color) { m_background = _color; }
  void setFont( const QFont& _font) { m_font = _font; }
  void setWPM( const int _wpm) { m_wpm = _wpm; m_interval = c_maxWPM / m_wpm;}
  void setInterval( const int _interval) { m_interval = _interval; }
  void setRepeat( const bool _repeat) { m_repeat = _repeat; }

private:
  Q_DISABLE_COPY(CSettings);

  QColor m_foreground;
  QColor m_background;
  QFont  m_font;
  int    m_wpm;
  int    m_interval;
  bool   m_repeat;

  QSettings m_settings;
};

#endif // SETTINGS_H
