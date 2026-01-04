#include "servo.h"

ServoAxis::ServoAxis(PCA9685 &drv, uint8_t channel, uint16_t minTick, uint16_t maxTick)
: _drv(drv), _ch(channel), _minTick(minTick), _maxTick(maxTick) {}

void ServoAxis::setRange(uint16_t minTick, uint16_t maxTick) {
  _minTick = minTick;
  _maxTick = maxTick;
}

uint16_t ServoAxis::angleToTick(int deg) const {
  deg = constrain(deg, 0, 180);
  return map(deg, 0, 180, _minTick, _maxTick);
}

uint16_t ServoAxis::usToTick(int us) const {
  // PCA9685 50Hz 기준: period = 20000us
  // tick = us * 4096 / 20000
  us = constrain(us, 500, 2500);
  return (uint16_t)((uint32_t)us * 4096 / 20000);
}

void ServoAxis::writeAngle(int deg) {
  uint16_t tick = angleToTick(deg);
  _drv.setPWM(_ch, 0, tick);
}

void ServoAxis::writeUS(int us) {
  uint16_t tick = usToTick(us);
  _drv.setPWM(_ch, 0, tick);
}
