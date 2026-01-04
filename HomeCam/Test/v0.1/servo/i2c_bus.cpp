#include "i2c_bus.h"
#include <Wire.h>

namespace I2CBus {

void begin(int sda, int scl, uint32_t freq_hz) {
  // ESP32는 핀 매핑 가능
  Wire.begin(sda, scl);
  Wire.setClock(freq_hz);
}

void scan(Stream &out) {
  out.println("\n[I2C] scan start...");
  int found = 0;

  for (uint8_t addr = 1; addr < 127; addr++) {
    Wire.beginTransmission(addr);
    uint8_t err = Wire.endTransmission();

    if (err == 0) {
      out.print("[I2C] Found device: 0x");
      if (addr < 16) out.print("0");
      out.println(addr, HEX);
      found++;
    }
  }

  if (found == 0) out.println("[I2C] No devices found");
  out.println("[I2C] scan done.\n");
}

} // namespace
