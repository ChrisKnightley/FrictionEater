static constexpr signed char PG_UPDI = PIN_PA0; // UPDI Programming [UPDI]
static constexpr signed char DBG_TXD = PIN_PA1; // Debug Output [USART0-TXD1*]

static constexpr signed char TSL_LED = PIN_PB6; // Line Scanner IR-LED [GPIO-PB6]
static constexpr signed char TSL_CLK = PIN_PB4; // Line Scanner Clock [LUT0-OUT*]
static constexpr signed char TSL_SI  = PIN_PA5; // Line Scanner Shutter [GPIO-PA5]
static constexpr signed char TSL_AO  = PIN_PA6; // Line Scanner Pixel Data [ADC0-AIN6]
static constexpr signed char ADC0_AINMUX = 6;

static constexpr signed char OPT_LED = PIN_PB3; // Landing Detector IR-LED [GPIO-PB3]
static constexpr signed char OPT_TR  = PIN_PC3; // Landing Detector [ADC1-AIN9]
static constexpr signed char ADC1_AINMUX = 9;

static constexpr signed char HEAT_EN = PIN_PB2; // Eraser Heater Enable MOSFET [AC2-OUT]
static constexpr signed char TEMP_TH = PIN_PB7; // Eraser Heater Thermistor [AC2-AINP3]
static constexpr signed char AC2_AINPMUX = 3;

static constexpr signed char BATT_VM = PIN_PB5; // Battery Voltage Monitor [AC0-AINP1]
static constexpr signed char AC0_AINPMUX = 1;

static constexpr signed char MDRV_LA = PIN_PB0; // Left Motor Phase A [GPIO-PB0]
static constexpr signed char MDRV_LB = PIN_PB1; // Left Motor Phase B [GPIO-PB1]
static constexpr signed char MDRV_RA = PIN_PC4; // Right Motor Phase A [GPIO-PC4]
static constexpr signed char MDRV_RB = PIN_PC5; // Right Motor Phase B [GPIO-PC5]
static constexpr signed char DRV_PWM = PIN_PA4; // 125kHz Motor Power PWM [TCD0-WOA]

static constexpr signed char TCD_OUT = PIN_PA2; // 500kHz Clock Output [EVOUT0(TCD0)]
static constexpr signed char EXT_CLK = PIN_PA3; // RTC External Clock [EXTCLK]

static constexpr signed char NC_SCLK = PIN_PC0; // SPI0 Reserved [SPI0-SCK*]
static constexpr signed char NC_MISO = PIN_PC1; // SPI0 Reserved [SPI0-MISO*]
static constexpr signed char NC_MOSI = PIN_PC2; // SPI0 Reserved [SPI0-MOSI*]
static constexpr signed char LED_OUT = PIN_PA7; // Addressable LED Command [LUT1-OUT]
