void loop() {
  static unsigned char prevHalfSec = 0;
  static unsigned char pastHalfSec = 0;
  batteryCheck();
  driveMotor();
  if (isScanned) analyzeData();

  switch (currentMode) {

    case MODE_AWAKENING:
      {
        if ((unsigned char)(timeHalfSec - prevHalfSec) >= 1) {
          pastHalfSec++;
          prevHalfSec = timeHalfSec;
          if (prevHalfSec & 0x01) {
            LED_Left(0, 200, 0);
            LED_Right(0, 200, 0);
            ledUpdate();
          } else {
            LED_Left(0, 0, 0);
            LED_Right(0, 0, 0);
            ledUpdate();
          }
          if (pastHalfSec >= 4) {
            LED_Left(200, 200, 0);
            LED_Right(200, 200, 0);
            ledUpdate();
            pastHalfSec = 0;
            currentMode = MODE_LIFTED;
            digitalWriteFast(OPT_LED, HIGH);
          }
        }
      } break;

    case MODE_LIFTED:
      {
        Heater_OFF();
        CameraLED_OFF();
        if (isLanding) {
          pastHalfSec = 0;
          currentMode = MODE_SEARCHING;
        }
        if ((unsigned char)(timeHalfSec - prevHalfSec) >= 1) {
          prevHalfSec = timeHalfSec;
          if (prevHalfSec & 0x01) {
            LED_Left(200, 100, 0);
            LED_Right(0, 0, 0);
            ledUpdate();
          } else {
            LED_Left(0, 0, 0);
            LED_Right(200, 100, 0);
            ledUpdate();
          }
        }
      } break;

    case MODE_SEARCHING:
    case MODE_LOST:
      {
        CameraLED_ON();
        Heater_OFF();
        if (!isLanding) {
          pastHalfSec = 0;
          currentMode = MODE_LIFTED;
        }
        if ((unsigned char)(timeHalfSec - prevHalfSec) >= 1) {
          pastHalfSec++;
          prevHalfSec = timeHalfSec;
          if (prevHalfSec & 0x01) {
            LED_Left(200, 0, 200);
            LED_Right(0, 0, 0);
            ledUpdate();
          } else {
            LED_Left(0, 0, 0);
            LED_Right(200, 0, 200);
            ledUpdate();
          }
          if (pastHalfSec >= 6) {
            LED_Left(0, 0, 0);
            LED_Right(0, 0, 0);
            ledUpdate();
            pastHalfSec = 0;
            currentMode = MODE_COMPLETION;
          }
        }
      } break;

    case MODE_STRAIGHT:
      {
        CameraLED_ON();
        Heater_ON();
        if (!isLanding) {
          pastHalfSec = 0;
          currentMode = MODE_LIFTED;
        }
        if ((unsigned char)(timeHalfSec - prevHalfSec) >= 1) {
          prevHalfSec = timeHalfSec;
          LED_Left(0, 0, 200);
          LED_Right(0, 0, 200);
          ledUpdate();
        }
      } break;

    case MODE_GENTLE_LEFT:
    case MODE_TIGHT_LEFT:
      {
        CameraLED_ON();
        Heater_ON();
        if (!isLanding) {
          pastHalfSec = 0;
          currentMode = MODE_LIFTED;
        }
        if ((unsigned char)(timeHalfSec - prevHalfSec) >= 1) {
          prevHalfSec = timeHalfSec;
          LED_Left(0, 0, 200);
          LED_Right(0, 0, 0);
          ledUpdate();
        }
      } break;

    case MODE_GENTLE_RIGHT:
    case MODE_TIGHT_RIGHT:
      {
        CameraLED_ON();
        Heater_ON();
        if (!isLanding) {
          pastHalfSec = 0;
          currentMode = MODE_LIFTED;
        }
        if ((unsigned char)(timeHalfSec - prevHalfSec) >= 1) {
          prevHalfSec = timeHalfSec;
          LED_Left(0, 0, 0);
          LED_Right(0, 0, 200);
          ledUpdate();
        }
      } break;

    case MODE_COMPLETION:
      {
        CameraLED_OFF();
        Heater_OFF();
        if (!isLanding) {
          pastHalfSec = 0;
          currentMode = MODE_LIFTED;
        }
      } break;

    case MODE_CALIBRATION:
      {
        MotorPower(MOTOR_OFF);
        Heater_OFF();
        LandingLED_OFF();
        CameraLED_ON();
        if ((unsigned char)(timeHalfSec - prevHalfSec) >= 1) {
          pastHalfSec++;
          prevHalfSec = timeHalfSec;
          if (prevHalfSec & 0x01) {
            LED_Left(200, 0, 100);
            LED_Right(0, 100, 200);
            ledUpdate();
          } else {
            LED_Left(0, 100, 200);
            LED_Right(200, 0, 100);
            ledUpdate();
          }
          if (pastHalfSec >= 6) {
            LED_Left(255, 255, 255);
            LED_Right(255, 255, 255);
            ledUpdate();
            writeCalibration();
            currentMode = MODE_LOWBATTERY;
          }
        }
      } break;

    default:
    case MODE_LOWBATTERY:
      {
        MotorPower(MOTOR_OFF);
        Heater_OFF();
        LandingLED_OFF();
        CameraLED_OFF();
        if ((unsigned char)(timeHalfSec - prevHalfSec) >= 1) {
          prevHalfSec = timeHalfSec;
          if (prevHalfSec & 0x01) {
            LED_Left(100, 0, 0);
            LED_Right(0, 0, 0);
            ledUpdate();
          } else {
            LED_Left(0, 0, 0);
            LED_Right(100, 0, 0);
            ledUpdate();
          }
        }
      } break;
  }
}
