enum MotorStatus {
  MOTOR_OFF,
  MOTOR_ON,
};

enum Towards {
  FORWARD,
  REVERSE,
};

void MotorPower(bool MotorStatus = MOTOR_OFF) {
  if (MotorStatus) {
    while (!(TCD0.STATUS & TCD_CMDRDY_bm));
    TCD0.DLYVAL = 32 * 4 - 1 - 16; // 500kHz to 125kHz (duty 12.5%) <- 1us/8us
    TCD0.CTRLE = TCD_SYNCEOC_bm;
  } else {
    while (!(TCD0.STATUS & TCD_CMDRDY_bm));
    TCD0.DLYVAL = 32 - 1; // 125kHz PWM OFF
    TCD0.CTRLE = TCD_SYNCEOC_bm;
  }
}

INLINE void Motor_Left(bool towards = FORWARD) {
  static signed char steps = 1;
  switch (towards) {
    case FORWARD:
      if (++steps > 4) steps = 0;
      break;
    case REVERSE:
      if (--steps == 0) steps = 4;
      break;
  }
  switch (steps) {
    case 1:
      digitalWriteFast(MDRV_LA, LOW);
      digitalWriteFast(MDRV_LB, LOW);
      break;
    case 2:
      digitalWriteFast(MDRV_LA, LOW);
      digitalWriteFast(MDRV_LB, HIGH);
      break;
    case 3:
      digitalWriteFast(MDRV_LA, HIGH);
      digitalWriteFast(MDRV_LB, HIGH);
      break;
    case 4:
      digitalWriteFast(MDRV_LA, HIGH);
      digitalWriteFast(MDRV_LB, LOW);
      break;
  }
}

INLINE void Motor_Right(bool towards = FORWARD) {
  static signed char steps = 1;
  switch (towards) {
    case FORWARD:
      if (++steps > 4) steps = 0;
      break;
    case REVERSE:
      if (--steps == 0) steps = 4;
      break;
  }
  switch (steps) {
    case 1:
      digitalWriteFast(MDRV_RA, LOW);
      digitalWriteFast(MDRV_RB, LOW);
      break;
    case 2:
      digitalWriteFast(MDRV_RA, LOW);
      digitalWriteFast(MDRV_RB, HIGH);
      break;
    case 3:
      digitalWriteFast(MDRV_RA, HIGH);
      digitalWriteFast(MDRV_RB, HIGH);
      break;
    case 4:
      digitalWriteFast(MDRV_RA, HIGH);
      digitalWriteFast(MDRV_RB, LOW);
      break;
  }
}
