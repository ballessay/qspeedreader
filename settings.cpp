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

#include "settings.h"

#define DEF_CONST(str) static const char* c_##str = #str

DEF_CONST(foreground);
DEF_CONST(background);
DEF_CONST(font);
DEF_CONST(wordsperminute);
DEF_CONST(interval);
DEF_CONST(repeat);


// constructor loads saved values or sets the defaults
CSettings::CSettings()
  : m_foreground(QColor(0, 0, 0)),
    m_background(QColor(127, 127, 127)),
    m_font(QFont()),
    m_repeat(false),
    m_settings("ballessay", "qspeedrunner")
{
  setWPM(250);

  m_foreground = m_settings.value(c_foreground, QColor(0, 0, 0)).value<QColor>();
  m_background = m_settings.value(c_background, QColor(127, 127, 127)).value<QColor>();
  m_font       = m_settings.value(c_font, QFont()).value<QFont>();
  m_wpm        = m_settings.value(c_wordsperminute, m_wpm).toInt();
  m_interval   = m_settings.value(c_interval, m_interval).toInt();
  m_repeat     = m_settings.value(c_repeat, false).toBool();
}

// destructor saves the current settings
CSettings::~CSettings()
{
  save();
}

void CSettings::save()
{
  m_settings.setValue(c_foreground, m_foreground);
  m_settings.setValue(c_background, m_background);
  m_settings.setValue(c_font, m_font);
  m_settings.setValue(c_wordsperminute, m_wpm);
  m_settings.setValue(c_interval, m_interval);
  m_settings.setValue(c_repeat, m_repeat);
}

