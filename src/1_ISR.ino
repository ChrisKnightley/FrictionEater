#if (ASM_ISR)
ISR(ADC0_RESRDY_vect, ISR_NAKED) {
  ASM(
    " out %[GP0], r24     \n\t" // 1 Alternative PUSH
    "  in    r24, %[SRG]  \n\t" // 1
    " out %[GP1], r24     \n\t" // 1
    " out %[GP2], r30     \n\t" // 1
    " out %[GP3], r31     \n\t" // 1

    " ldi    r24, 2            \n\t" // 1 Set Event Channel
    " sts %[EVA], r24          \n\t" // 2 Send Event Strobe to Async (-> TCB START)
    " lds    r30, %[TCA]       \n\t" // 3 Read TCA Counter Value
    " sts %[EVS], r24          \n\t" // 2 Send Event Strobe to Sync (-> TCA COUNT+)
    " lds    r24, %[ADC]       \n\t" // 3 Read ADC Result Value
    " ldi    r31, lo8(%[DAT])  \n\t" // 1 Load Memory Address Low Byte
    " add    r30, r31          \n\t" // 1 Add Fetched Counter Value
    " ldi    r31, hi8(%[DAT])  \n\t" // 1 Load Memory Address High Byte
    "sbci    r31, 0            \n\t" // 1 Add Carry Flag
    "  st     -Z, r24          \n\t" // 1 Decrement 1 and Write to Memory

    "  in    r31, %[GP3]  \n\t" // 1 Alternative POP (Reduce 1 clock per POP)
    "  in    r30, %[GP2]  \n\t" // 1
    "  in    r24, %[GP1]  \n\t" // 1
    " out %[SRG], r24     \n\t" // 1
    "  in    r24, %[GP0]  \n\t" // 1

    "reti                 \n\t" // 4 Return and Set Interrupt
    :
    : [DAT] "o" (LineData)
    , [SRG] "p" _SFR_MEM_ADDR(SREG)
    , [GP0] "p" _SFR_MEM_ADDR(GPIOR0)
    , [GP1] "p" _SFR_MEM_ADDR(GPIOR1)
    , [GP2] "p" _SFR_MEM_ADDR(GPIOR2)
    , [GP3] "p" _SFR_MEM_ADDR(GPIOR3)
    , [ADC] "p" _SFR_MEM_ADDR(ADC0.RESL)
    , [TCA] "p" _SFR_MEM_ADDR(TCA0.SINGLE.CNTL)
    , [EVS] "p" _SFR_MEM_ADDR(EVSYS.SYNCSTROBE)
    , [EVA] "p" _SFR_MEM_ADDR(EVSYS.ASYNCSTROBE)
    : );
}
#else
ISR(ADC0_RESRDY_vect) {
  EVSYS.ASYNCSTROBE = bit(1);
  LineData[TCA0.SINGLE.CNTL - 1] = (unsigned char)ADC0.RESL; // Store 1px Data
  EVSYS.SYNCSTROBE = bit(1);
}
#endif

ISR(ADC1_RESRDY_vect) {
  isLanding = ((unsigned char)ADC1.RESL < LandingDetectThreshold);
}

ISR(TCA0_CMP0_vect) {
  ADC0.CTRLA &= ~ADC_ENABLE_bm;
  TCA0.SINGLE.INTFLAGS = TCA_SINGLE_CMP0_bm;
  isScanned = true;
}

ISR(RTC_CNT_vect) {
  digitalWriteFast(TSL_SI, HIGH);
  EVSYS.SYNCSTROBE = bit(1);
  RTC.INTFLAGS = RTC_OVF_bm;
  ADC0.CTRLA |= ADC_ENABLE_bm;
  digitalWriteFast(TSL_SI, LOW);
}

ISR(RTC_PIT_vect) {
  static unsigned char Period = 244; // 500kHz / 1024 / 2 = 244.140625
  RTC.PITINTFLAGS = RTC_PI_bm;
  if (!--Period) {
    Period = 244;
    timeHalfSec++;
  }
  toStepping = true;
}

ISR(SPI0_INT_vect) {
  static unsigned char SendByte = LedByteCount;
  SPI0.DATA = LedSendData[--SendByte];
  if (!SendByte) {
    SPI0.INTCTRL = 0;
    SendByte = LedByteCount;
  }
}
