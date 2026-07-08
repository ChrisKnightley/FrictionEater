void driveMotor() {
  if (!toStepping) return;
  toStepping = false;
  switch (currentMode) {
    default:
      break;
    case MODE_SEARCHING:
    case MODE_LOST:
    case MODE_STRAIGHT:
      Motor_Left(FORWARD);
      Motor_Right(FORWARD);
      break;
    case MODE_GENTLE_LEFT:
      Motor_Left(FORWARD);
      break;
    case MODE_GENTLE_RIGHT:
      Motor_Right(FORWARD);
      break;
    case MODE_TIGHT_LEFT:
      Motor_Left(FORWARD);
      Motor_Right(REVERSE);
      break;
    case MODE_TIGHT_RIGHT:
      Motor_Left(REVERSE);
      Motor_Right(FORWARD);
      break;
  }
}
