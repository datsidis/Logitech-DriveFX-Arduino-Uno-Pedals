// Arduino Uno: DriveFX Pedals → vJoySerialFeeder using IBUS
// Gas = CH1, Brake = CH2

const int gasPin    = A0;  // Gas pedal
const int brakePin  = A1;  // Brake pedal

int gasValue, brakeValue;

// IBUS packet (32 bytes)
#define IBUS_LENGTH 32
uint8_t ibusPacket[IBUS_LENGTH];

void setup() {
  Serial.begin(115200); // IBUS default
}

void loop() {
  // --- Read pedals (inverted) ---
  gasValue   = 1023 - analogRead(gasPin);
  brakeValue = 1023 - analogRead(brakePin);

  // --- Deadzones & never zero ---
  if (gasValue <= 80) gasValue = 1;
  if (brakeValue <= 150) brakeValue = 1;

  // --- Scaling ---
  gasValue   = map(gasValue,   20, 850, 1000, 2000);  // channel range
  brakeValue = map(brakeValue, 90, 1023, 1000, 2000);

  // Clamp values
  if (gasValue < 1000) gasValue = 1000;
  if (gasValue > 2000) gasValue = 2000;
  if (brakeValue < 1000) brakeValue = 1000;
  if (brakeValue > 2000) brakeValue = 2000;

  // --- Build IBUS packet ---
  ibusPacket[0] = IBUS_LENGTH;  // length
  ibusPacket[1] = 0x40;         // command = channel data

  // CH1 = Gas
  ibusPacket[2] = lowByte(gasValue);
  ibusPacket[3] = highByte(gasValue);

  // CH2 = Brake
  ibusPacket[4] = lowByte(brakeValue);
  ibusPacket[5] = highByte(brakeValue);

  // Fill remaining channels with 1500 (neutral)
  for (int i = 2; i < 14; i++) {
    int value = 1500;
    ibusPacket[2 + i * 2]     = lowByte(value);
    ibusPacket[2 + i * 2 + 1] = highByte(value);
  }

  // --- Calculate checksum ---
  uint16_t checksum = 0xFFFF;
  for (int i = 0; i < IBUS_LENGTH - 2; i++) {
    checksum -= ibusPacket[i];
  }
  ibusPacket[IBUS_LENGTH - 2] = lowByte(checksum);
  ibusPacket[IBUS_LENGTH - 1] = highByte(checksum);

  // --- Send packet ---
  Serial.write(ibusPacket, IBUS_LENGTH);

  delay(10); // ~100 Hz
}
