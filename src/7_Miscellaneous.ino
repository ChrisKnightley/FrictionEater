INLINE void batteryCheck() {
#if (BATTERY_CHECK)
  if (AC0.STATUS & AC_STATE_bm) currentMode = MODE_LOWBATTERY;
#endif
}

INLINE void Heater_ON() {
#if (HEATER_ENABLE)
  DAC2.DATA = 110;
#endif
}

INLINE void Heater_OFF() {
  DAC2.DATA = 0xFF;
}

INLINE void CameraLED_ON() {
  digitalWriteFast(TSL_LED, LOW);
}

INLINE void CameraLED_OFF() {
  digitalWriteFast(TSL_LED, HIGH);
}

INLINE void LandingLED_ON() {
  digitalWriteFast(OPT_LED, HIGH);
}

INLINE void LandingLED_OFF() {
  digitalWriteFast(OPT_LED, LOW);
}
