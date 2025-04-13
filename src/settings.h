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
  void setForeground(const QColor& _color) { m_foreground = _color; }

  QColor background() const { return m_background; }
  void setBackground(const QColor& _color) { m_background = _color; }

  QFont font() const { return m_font; }
  void setFont(const QFont& _font) { m_font = _font; }

  int interval() const { return m_interval; }
  void setInterval(int _interval) { m_interval = _interval; }

  int wpm() const { return m_wpm; }
  void setWPM(int _wpm) { m_wpm = _wpm; m_interval = c_maxWPM / m_wpm;}

  bool repeat() const { return m_repeat; }
  void setRepeat(bool _repeat) { m_repeat = _repeat; }

private:
  Q_DISABLE_COPY(CSettings)

  QColor m_foreground;
  QColor m_background;
  QFont  m_font;
  int    m_wpm;
  int    m_interval;
  bool   m_repeat;

  QSettings m_settings;
};

#endif // SETTINGS_H
