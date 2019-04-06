#include "subsystems/IndicatorLights/Morse.h"

#include <algorithm>
#include <iostream>

IndicatorLights::Morse::Morse(std::string message, int speedOfDot, std::vector<uint8_t> onColor, std::vector<uint8_t> offColor) {
  m_message = message;
  std::transform(m_message.begin(), m_message.end(), m_message.begin(), ::tolower);

  m_speedOfDot = speedOfDot;
  m_onColor = onColor;
  m_offColor = offColor;
  m_colors.push_back(m_offColor);

  reset();
}

void IndicatorLights::Morse::run() {
  // Time to change color
  if (m_counter >= m_speedOfDot) {
    // Must get a new code
    if (m_codeIndex >= m_code.length()) {
      // No more codes
      if (m_stringIndex >= m_message.length()) {
        m_done = true;
        return;
      }
    
      // Get a new code
      // Switch statement courtesy of https://program-using-gnu-cpp.blogspot.com/2017/11/program-morse-code-using-switch-case.html
      switch (m_message.at(m_stringIndex)) {
        case 'a':   m_code = " .-  ";      break;
        case 'b':   m_code = " -...  ";    break;
        case 'c':   m_code = " -.-.  ";    break;
        case 'd':   m_code = " -..  ";     break;
        case 'e':   m_code = " .  ";       break;
        case 'f':   m_code = " ..-.  ";    break;
        case 'g':   m_code = " --.  ";     break;
        case 'h':   m_code = " ....  ";    break;
        case 'i':   m_code = " ..  ";      break;
        case 'j':   m_code = " .---  ";    break;
        case 'k':   m_code = " -.-  ";     break;
        case 'l':   m_code = " .-..  ";    break;
        case 'm':   m_code = " --  ";      break;
        case 'n':   m_code = " -.  ";      break;
        case 'o':   m_code = " ---  ";     break;
        case 'p':   m_code = " -.-.  ";    break;
        case 'q':   m_code = " --.-  ";    break;
        case 'r':   m_code = " .-.  ";     break;
        case 's':   m_code = " ...  ";     break;
        case 't':   m_code = " -  ";       break;
        case 'u':   m_code = " ..-  ";     break;
        case 'v':   m_code = " ...-  ";    break;
        case 'w':   m_code = " .--  ";     break;
        case 'x':   m_code = " -..-  ";    break;
        case 'y':   m_code = " -.--  ";    break;
        case 'z':   m_code = " --..  ";    break;
        case ' ':   m_code = "    ";    break;
        case '1':   m_code = " .----  ";   break;
        case '2':   m_code = " ..---  ";   break;
        case '3':   m_code = " ...--  ";   break;
        case '4':   m_code = " ....-  ";   break;
        case '5':   m_code = " .....  ";   break;
        case '6':   m_code = " -....  ";   break;
        case '7':   m_code = " --...  ";   break;
        case '8':   m_code = " ---..  ";   break;
        case '9':   m_code = " ----.  ";   break;
        case '0':   m_code = " -----  ";   break;
        default:    m_code = "";         break;
      }

      // Prep for new code
      m_codeIndex = 0;

      // Next character
      m_stringIndex++;
    }

    // Process code. Dash is twice as long as dot, space is an off
    switch (m_code.at(m_codeIndex)) {
      case '-':
        m_colors[0] = m_onColor;
        m_code[m_codeIndex] = '.';
        break;
      case '.':
        m_colors[0] = m_onColor;
        m_code[m_codeIndex] = ' ';
        break;
      case ' ':
        m_colors[0] = m_offColor;
        m_codeIndex++;
        break;
    }

    // Reset the counter for the next loop
    m_counter = 0;
  }

  // Add to the counter
  m_counter++;
}

void IndicatorLights::Morse::reset() {
  m_done = false;
  m_colors[0] = m_offColor;

  m_counter = 0;
  m_stringIndex = 0;
  m_codeIndex = 0;
  m_code = "";
}