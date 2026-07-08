void readCalibration() {
  Serial.write(0xFF);
  for (unsigned char px = 0; px < PIXEL_NUM; px++) {
    CalibrationData[px] = readEEPROM(px);
    Serial.write(CalibrationData[px] == 0xFF ? 0xFE : CalibrationData[px]);
  }
  Serial.write(0xFF);
}

void writeCalibration() {
  cli();
  memcpy(CalibrationData, (const void*)LineData, PIXEL_NUM);
  sei();
  for (unsigned char px = 0; px < PIXEL_NUM; px++) {
    writeEEPROM(px, ~CalibrationData[px]);
  }
}

unsigned char readEEPROM(unsigned char index) {
  return *(volatile uint8_t *)(MAPPED_EEPROM_START + index);
}

void writeEEPROM(unsigned char index, unsigned char value) {
  while (NVMCTRL.STATUS & NVMCTRL_EEBUSY_bm);
  cli();
  *(volatile uint8_t *)(MAPPED_EEPROM_START + index) = value;
  CCP = CCP_SPM_gc;
  NVMCTRL.CTRLA = NVMCTRL_CMD_PAGEERASEWRITE_gc;
  sei();
}
