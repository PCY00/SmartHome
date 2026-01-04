#pragma once
#include <Arduino.h>

namespace I2CBus{
  void begin(int sda, int scl, uint32_t freq_hz = 100000);
  void scan(Stream &out);
}
