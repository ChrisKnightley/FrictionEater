void analyzeData() {
  isScanned = false;
  switch (currentMode) {
    default:
      break;
    case MODE_SEARCHING:
    case MODE_STRAIGHT:
    case MODE_GENTLE_LEFT:
    case MODE_GENTLE_RIGHT:
    case MODE_TIGHT_LEFT:
    case MODE_TIGHT_RIGHT:
    case MODE_LOST:
      {
        unsigned char minValue = 0;
        unsigned char maxValue = 0;
        unsigned char current = 0;
        unsigned int section[7] = {0, 0, 0, 0, 0, 0, 0};
#if (DEBUG_OUTPUT)
        Serial.write(0xFF); // Debugger Flush Command Byte
        for (unsigned char px = 0; px < PIXEL_NUM; px++) {
          Serial.write(LineData[px] == 0xFF ? 0xFE : LineData[px]); // Raw Data Output For Debug
#else
        for (unsigned char px = 0; px < PIXEL_NUM; px++) {
#endif
          if (maxValue < LineData[px]) maxValue = LineData[px];
          if (minValue > LineData[px]) minValue = LineData[px];
          switch (current) {
            case 0:
              if (px >= 19) current++;
              break;
            case 1:
              section[current] += LineData[px] + CalibrationData[px];
              if (px >= 37) current++;
              break;
            case 2:
              section[current] += LineData[px] + CalibrationData[px];
              if (px >= 55) current++;
              break;
            case 3:
              section[current] += LineData[px] + CalibrationData[px];
              if (px >= 71) current++;
              break;
            case 4:
              section[current] += LineData[px] + CalibrationData[px];
              if (px >= 89) current++;
              break;
            case 5:
              section[current] += LineData[px] + CalibrationData[px];
              if (px >= 107) current++;
              break;
            case 6:
              break;
          }
        }
        if (maxValue >= 0xFF) {
          ExposureTick -= ExposureAdjustSpeed;
          if (ExposureTick < MinimumExposureTick) ExposureTick = MinimumExposureTick;
        } else if (maxValue <= 0xEE) {
          ExposureTick += ExposureAdjustSpeed;
          if (ExposureTick > MaximumExposureTick) ExposureTick = MaximumExposureTick;
        }
        cli();
        while (RTC.STATUS & RTC_PERBUSY_bm);
        RTC.PER = ExposureTick;
        sei();
        if ((maxValue - minValue) < 20) {
          currentMode = MODE_LOST;
        } else {
          unsigned char darkSection = 1;
          unsigned int tempValue = section[1];
          for (current = 2; current <= 5; current++) {
            if (section[current] < tempValue) {
              tempValue = section[current];
              darkSection = current;
            }
          }
          switch (darkSection) {
            case 1:
              currentMode = MODE_TIGHT_RIGHT;
              break;
            case 2:
              currentMode = MODE_GENTLE_RIGHT;
              break;
            case 3:
              currentMode = MODE_STRAIGHT;
              break;
            case 4:
              currentMode = MODE_GENTLE_LEFT;
              break;
            case 5:
              currentMode = MODE_TIGHT_LEFT;
              break;
            case 0:
            default:
              currentMode = MODE_LOST;
              break;
          }
        }
      } break;
  }
}
