#include "settings.h"

#define DEF_CONST(str) static const char* c_##str = #str

DEF_CONST(foreground);
DEF_CONST(background);
DEF_CONST(font);
DEF_CONST(wordsperminute);
DEF_CONST(interval);


// constructor loads saved values or sets the defaults
CSettings::CSettings()
  : m_foreground(QColor(0, 0, 0)),
    m_background(QColor(127, 127, 127)),
    m_font(QFont()),
    m_settings("ballessay", "qspeedrunner")
{
  setWPM(250);

  m_foreground = m_settings.value(c_foreground, QColor(0, 0, 0)).value<QColor>();
  m_background = m_settings.value(c_background, QColor(127, 127, 127)).value<QColor>();
  m_font       = m_settings.value(c_font, QFont()).value<QFont>();
  m_wpm        = m_settings.value(c_wordsperminute, m_wpm).toInt();
  m_interval   = m_settings.value(c_interval, m_interval).toInt();
}

// destructor saves the current settings
CSettings::~CSettings()
{
  m_settings.setValue(c_foreground, m_foreground);
  m_settings.setValue(c_background, m_background);
  m_settings.setValue(c_font, m_font);
  m_settings.setValue(c_wordsperminute, m_wpm);
  m_settings.setValue(c_interval, m_interval);
}

