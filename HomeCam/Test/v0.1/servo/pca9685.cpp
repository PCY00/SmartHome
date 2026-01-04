#include "pca9685.h"
#include <Wire.h>

// PCA9685 레지스터
static const uint8_t MODE1      = 0x00;
static const uint8_t PRESCALE   = 0xFE;
static const uint8_t LED0_ON_L  = 0x06;

PCA9685::PCA9685(uint8_t i2c_addr) : _addr(i2c_addr) {}

bool PCA9685::write8(uint8_t reg, uint8_t val) {
  Wire.beginTransmission(_addr);
  Wire.write(reg);
  Wire.write(val);
  return (Wire.endTransmission() == 0);
}

bool PCA9685::read8(uint8_t reg, uint8_t &val) {
  Wire.beginTransmission(_addr);
  Wire.write(reg);
  if (Wire.endTransmission(false) != 0) return false; // repeated start

  if (Wire.requestFrom((int)_addr, 1) != 1) return false;
  val = Wire.read();
  return true;
}

bool PCA9685::begin() {
  // MODE1: AI(자동증가) ON 권장 (연속 레지스터 쓰기 편함)
  // RESTART는 필요할 때만
  return write8(MODE1, 0x20); // 0b0010_0000 (AI=1)
}

bool PCA9685::setPWMFreq(float hz) {
  // prescale = round(25MHz / (4096*hz)) - 1
  float prescaleval = 25000000.0f;
  prescaleval /= 4096.0f;
  prescaleval /= hz;
  prescaleval -= 1.0f;

  uint8_t prescale = (uint8_t)(prescaleval + 0.5f);

  uint8_t oldmode;
  if (!read8(MODE1, oldmode)) return false;

  uint8_t sleep = (oldmode & 0x7F) | 0x10; // SLEEP=1
  if (!write8(MODE1, sleep)) return false;

  if (!write8(PRESCALE, prescale)) return false;

  // wake
  if (!write8(MODE1, oldmode)) return false;
  delay(5);
  // restart + AI
  return write8(MODE1, oldmode | 0x80 | 0x20);
}

bool PCA9685::setPWM(uint8_t ch, uint16_t on, uint16_t off) {
  uint8_t reg = LED0_ON_L + 4 * ch;
  Wire.beginTransmission(_addr);
  Wire.write(reg);
  Wire.write(on & 0xFF);
  Wire.write(on >> 8);
  Wire.write(off & 0xFF);
  Wire.write(off >> 8);
  return (Wire.endTransmission() == 0);
}
