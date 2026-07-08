INLINE void ledDataSend() {
  SPI0.INTCTRL = SPI_DREIE_bm;
}

void ledUpdate() {
  LedSendData[5] = Led_L[2];
  LedSendData[4] = Led_L[1];
  LedSendData[3] = Led_L[0];
  LedSendData[2] = Led_R[2];
  LedSendData[1] = Led_R[1];
  LedSendData[0] = Led_R[0];
  ledDataSend();
}

INLINE void LED_Left(unsigned char r, unsigned char g, unsigned char b) {
  Led_L[0] = b;
  Led_L[1] = r;
  Led_L[2] = g;
}
INLINE void LED_Right(unsigned char r, unsigned char g, unsigned char b) {
  Led_R[0] = b;
  Led_R[1] = r;
  Led_R[2] = g;
}
