#pragma once
#include <Arduino.h>
#include "pca9685.h"

class ServoAxis {
public:
  // minTick/maxTick은 서보 캘리브레이션 값
  ServoAxis(PCA9685 &drv, uint8_t channel,
            uint16_t minTick = 110, uint16_t maxTick = 490);

  void writeAngle(int deg); // 0~180
  void writeUS(int us);     // 펄스폭 직접 제어(고급)
  void setRange(uint16_t minTick, uint16_t maxTick);

private:
  PCA9685 &_drv;
  uint8_t _ch;
  uint16_t _minTick, _maxTick;

  uint16_t angleToTick(int deg) const;
  uint16_t usToTick(int us) const;
};
