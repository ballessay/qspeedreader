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

  QColor foreground() const { return m_foreground; }
  QColor background() const { return m_background; }
  QFont font() const { return m_font; }
  int interval() const { return m_interval; }
  int wpm() const { return m_wpm; }

  void setForeground(const QColor& _color) { m_foreground = _color; }
  void setBackground(const QColor& _color) { m_background = _color; }
  void setFont( const QFont& _font) { m_font = _font; }
  void setWPM( const int _wpm) { m_wpm = _wpm; m_interval = c_maxWPM / m_wpm;}
  void setInterval( const int _interval) { m_interval = _interval; }

private:
  Q_DISABLE_COPY(CSettings);

  QColor m_foreground;
  QColor m_background;
  QFont  m_font;
  int    m_wpm;
  int    m_interval;

  QSettings m_settings;
};

#endif // SETTINGS_H
