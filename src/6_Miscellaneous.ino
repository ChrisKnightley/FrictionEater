INLINE void Heater_OFF() {
  DAC2.DATA = 0xFF;
}
INLINE void Heater_ON() {
  DAC2.DATA = 110;
}
INLINE void batteryCheck() {
  if (AC0.STATUS & AC_STATE_bm) currentMode = MODE_LOWBATTERY;
}
