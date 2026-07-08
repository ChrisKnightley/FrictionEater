#pragma GCC optimize ("O3")
#define FLATTEN __attribute__((__flatten__))
#define INLINED __attribute__((__always_inline__))
#define INLINE INLINED FLATTEN inline
#define ASM __asm__ __volatile__
#define ASM_ISR (true)

static constexpr unsigned char PIXEL_NUM = 128;
volatile unsigned char LineData[PIXEL_NUM]; // Pixel Data Array

static constexpr float LowBatteryThreshold = 3.40;
static constexpr unsigned char LandingDetectThreshold = 25;

static constexpr unsigned int  MinimumExposureTime = 5; // ms
static constexpr unsigned int  MaximumExposureTime = 100; // ms
static constexpr unsigned int  ExposureAdjustSpeed = 2000; // Tick(2us)

static constexpr unsigned int MinimumExposureTick = (unsigned int)(MinimumExposureTime * 500);
static constexpr unsigned int MaximumExposureTick = (unsigned int)(MaximumExposureTime * 500);
volatile unsigned int ExposureTick = MinimumExposureTick;

static constexpr unsigned char LedByteCount = 6;
unsigned char LedSendData[LedByteCount] = {};
unsigned char Led_L[3] = {0, 0, 0};
unsigned char Led_R[3] = {0, 0, 0};

volatile bool isLanding = false;
volatile bool isScanned = false;
volatile bool toStepping = false;

volatile unsigned char timeHalfSec = 0;

enum ModeList {
  MODE_AWAKENING,
  MODE_LIFTED,
  MODE_SEARCHING,
  MODE_STRAIGHT,
  MODE_GENTLE_LEFT,
  MODE_GENTLE_RIGHT,
  MODE_TIGHT_LEFT,
  MODE_TIGHT_RIGHT,
  MODE_LOST,
  MODE_COMPLETION,
  MODE_LOWBATTERY,
} currentMode;
