void loop() {
  static unsigned char prevHalfSec = 0;
  static unsigned char pastHalfSec = 0;
  batteryCheck();
  if (isScanned) analyzeData();

  switch (currentMode) {

    case MODE_AWAKENING:
      {
        if ((unsigned char)(timeHalfSec - prevHalfSec) >= 1) {
          pastHalfSec++;
          prevHalfSec = timeHalfSec;
          if (prevHalfSec & 0x01) {
            LED_Left(0, 255, 0);
            LED_Right(0, 255, 0);
            ledUpdate();
          } else {
            LED_Left(0, 0, 0);
            LED_Right(0, 0, 0);
            ledUpdate();
          }
          if (pastHalfSec >= 4) {
            LED_Left(255, 255, 0);
            LED_Right(255, 255, 0);
            ledUpdate();
            pastHalfSec = 0;
            currentMode = MODE_LIFTED;
          }
        }
      } break;

    case MODE_LIFTED:
      {
        Heater_OFF();
        digitalWriteFast(OPT_LED, LOW);
        if (isLanding) {
          pastHalfSec = 0;
          currentMode = MODE_SEARCHING;
        }
        if ((unsigned char)(timeHalfSec - prevHalfSec) >= 1) {
          prevHalfSec = timeHalfSec;
          if (prevHalfSec & 0x01) {
            LED_Left(255, 255, 0);
            LED_Right(0, 0, 0);
            ledUpdate();
          } else {
            LED_Left(0, 0, 0);
            LED_Right(255, 255, 0);
            ledUpdate();
          }
        }
      } break;

    case MODE_SEARCHING:
    case MODE_LOST:
      {
        digitalWriteFast(OPT_LED, HIGH);
        Heater_OFF();
        if (!isLanding) {
          pastHalfSec = 0;
          currentMode = MODE_LIFTED;
        }
        if ((unsigned char)(timeHalfSec - prevHalfSec) >= 1) {
          pastHalfSec++;
          prevHalfSec = timeHalfSec;
          if (prevHalfSec & 0x01) {
            LED_Left(255, 0, 255);
            LED_Right(0, 0, 0);
            ledUpdate();
          } else {
            LED_Left(0, 0, 0);
            LED_Right(255, 0, 255);
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
        digitalWriteFast(OPT_LED, HIGH);
        Heater_ON();
        if (!isLanding) {
          pastHalfSec = 0;
          currentMode = MODE_LIFTED;
        }
        if ((unsigned char)(timeHalfSec - prevHalfSec) >= 1) {
          prevHalfSec = timeHalfSec;
          LED_Left(0, 0, 255);
          LED_Right(0, 0, 255);
          ledUpdate();
        }
      } break;

    case MODE_GENTLE_LEFT:
    case MODE_TIGHT_LEFT:
      {
        digitalWriteFast(OPT_LED, HIGH);
        Heater_ON();
        if (!isLanding) {
          pastHalfSec = 0;
          currentMode = MODE_LIFTED;
        }
        if ((unsigned char)(timeHalfSec - prevHalfSec) >= 1) {
          prevHalfSec = timeHalfSec;
          LED_Left(0, 0, 255);
          LED_Right(0, 0, 0);
          ledUpdate();
        }
      } break;

    case MODE_GENTLE_RIGHT:
    case MODE_TIGHT_RIGHT:
      {
        digitalWriteFast(OPT_LED, HIGH);
        Heater_ON();
        if (!isLanding) {
          pastHalfSec = 0;
          currentMode = MODE_LIFTED;
        }
        if ((unsigned char)(timeHalfSec - prevHalfSec) >= 1) {
          prevHalfSec = timeHalfSec;
          LED_Left(0, 0, 0);
          LED_Right(0, 0, 255);
          ledUpdate();
        }
      } break;

    case MODE_COMPLETION:
      {
        digitalWriteFast(OPT_LED, LOW);
        Heater_OFF();
        if (!isLanding) {
          pastHalfSec = 0;
          currentMode = MODE_LIFTED;
        }
      } break;

    default:
    case MODE_LOWBATTERY:
      {
        digitalWriteFast(OPT_LED, LOW);
        MotorPower(MOTOR_OFF);
        Heater_OFF();
        if ((unsigned char)(timeHalfSec - prevHalfSec) >= 1) {
          prevHalfSec = timeHalfSec;
          if (prevHalfSec & 0x01) {
            LED_Left(0, 255, 0);
            LED_Right(0, 0, 0);
            ledUpdate();
          } else {
            LED_Left(0, 0, 0);
            LED_Right(0, 0, 0);
            ledUpdate();
          }
        }
      } break;
  }
}
