#pragma once
#include <Arduino.h>

class PCA9685 {
public:
  explicit PCA9685(uint8_t i2c_addr = 0x40);

  bool begin();                     // 초기화 + 모드 설정
  bool setPWMFreq(float hz);        // PWM 주파수 설정(서보=50Hz)
  bool setPWM(uint8_t ch, uint16_t on, uint16_t off);  // raw tick

private:
  uint8_t _addr;

  bool write8(uint8_t reg, uint8_t val);
  bool read8(uint8_t reg, uint8_t &val);
};
