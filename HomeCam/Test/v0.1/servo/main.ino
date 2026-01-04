#include "i2c_bus.h"
#include "pca9685.h"
#include "servo.h"

static PCA9685 pca(0x40);
static ServoAxis pan(pca, 0);   // 채널0
static ServoAxis tilt(pca, 1);  // 채널1

void setup() {
  Serial.begin(115200);

  // 1) I2C 버스 시작
  I2CBus::begin(14, 15, 100000);

  // 2) I2C 스캔 (PCA9685면 보통 0x40)
  I2CBus::scan(Serial);

  // 3) PCA 시작 + 50Hz 설정
  if (!pca.begin()) {
    Serial.println("PCA9685 begin failed");
    while (1) delay(1000);
  }
  if (!pca.setPWMFreq(50.0f)) {
    Serial.println("PCA9685 setPWMFreq failed");
    while (1) delay(1000);
  }

  // 4) 서보 초기 위치
  pan.writeAngle(90);
  tilt.writeAngle(90);
}

void loop() {
  // 간단 테스트 스윕
  for (int a = 30; a <= 150; a += 5) {
    pan.writeAngle(a);
    delay(50);
  }
  for (int a = 150; a >= 30; a -= 5) {
    pan.writeAngle(a);
    delay(50);
  }

  for (int a = 30; a <= 150; a += 5) {
    tilt.writeAngle(a);
    delay(50);
  }
  for (int a = 150; a >= 30; a -= 5) {
    tilt.writeAngle(a);
    delay(50);
  }
}

