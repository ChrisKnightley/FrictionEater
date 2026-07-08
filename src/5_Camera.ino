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
        unsigned char pxCount = 0;
        unsigned int section[5] = {0, 0, 0, 0, 0};
        // Serial.write(0xFF); // Debugger Reset Command Byte
        for (unsigned char px : LineData) {
          // Serial.write(px == 0xFF ? 0xFE : px); // Data Output For Debug
          if (maxValue < px) maxValue = px;
          if (minValue > px) minValue = px;
          if (++pxCount <= 14) {
          } else if (pxCount <= (20 * 1 + 14)) {
            section[0] += px;
          } else if (pxCount <= (20 * 2 + 14)) {
            section[1] += px;
          } else if (pxCount <= (20 * 3 + 14)) {
            section[2] += px;
          } else if (pxCount <= (20 * 4 + 14)) {
            section[3] += px;
          } else if (pxCount <= (20 * 5 + 14)) {
            section[4] += px;
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
          unsigned char darkSection = 0;
          unsigned int tempValue = section[0];
          for (unsigned char i = 1; i < 5; i++) {
            if (section[i] < tempValue) {
              tempValue = section[i];
              darkSection = i;
            }
          }
          switch (darkSection) {
            case 0:
              currentMode = MODE_TIGHT_RIGHT;
              break;
            case 1:
              currentMode = MODE_GENTLE_RIGHT;
              break;
            case 2:
              currentMode = MODE_STRAIGHT;
              break;
            case 3:
              currentMode = MODE_GENTLE_LEFT;
              break;
            case 4:
              currentMode = MODE_TIGHT_LEFT;
              break;
          }
        }
      } break;
  }
}
