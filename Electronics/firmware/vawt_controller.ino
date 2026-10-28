/*
 * Desktop VAWT 50cm — Wind Turbine Controller Firmware
 * Arduino Nano (ATmega328P)
 * 
 * Features:
 * - OLED display: V, I, P, RPM, cumulative kWh
 * - MPPT: Perturb & Observe algorithm
 * - Hall sensor RPM measurement
 * - INA219 current sensing
 * - LED status indicators
 * - Energy accumulation in EEPROM
 * 
 * Hardware:
 * - A0: Voltage divider (100K/10K)
 * - A4/A5: I2C (INA219 + OLED SSD1306)
 * - D2: Hall sensor (interrupt)
 * - D3: MPPT PWM to MOSFET
 * - D6: LED Green (generating)
 * - D7: LED Blue (USB active)
 * - D8: LED Red (fault)
 * - D13: Heartbeat
 */

#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_INA219.h>
#include <EEPROM.h>

// Display
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Current sensor
Adafruit_INA219 ina219;

// Pins
#define VOLTAGE_PIN   A0
#define HALL_PIN      2
#define MPPT_PIN      3
#define LED_GREEN     6
#define LED_BLUE      7
#define LED_RED       8
#define LED_HB        13

// Voltage divider ratio (100K + 10K)
#define V_DIV_RATIO   11.0

// EEPROM address for cumulative energy (Wh * 100)
#define EEPROM_ADDR_ENERGY  0

// Hall sensor
volatile unsigned long hall_count = 0;
volatile unsigned long last_hall_time = 0;
unsigned long rpm = 0;
unsigned long last_rpm_calc = 0;

// Measurements
float voltage = 0;
float current = 0;
float power = 0;
float energy_wh = 0;
unsigned long last_update = 0;
unsigned long last_mppt = 0;
int mppt_pwm = 128;
int mppt_direction = 1;
float last_power = 0;
bool heartbeat = false;

void setup() {
  Serial.begin(115200);
  
  // Pin modes
  pinMode(VOLTAGE_PIN, INPUT);
  pinMode(HALL_PIN, INPUT_PULLUP);
  pinMode(MPPT_PIN, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_HB, OUTPUT);
  
  // Initialize I2C
  Wire.begin();
  
  // Initialize OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 init failed"));
    for (;;); // Halt
  }
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println(F("VAWT 50cm"));
  display.println(F("Booting..."));
  display.display();
  
  // Initialize INA219
  if (!ina219.begin()) {
    Serial.println(F("INA219 init failed"));
  }
  ina219.setCalibration_16V_400mA();
  
  // Hall sensor interrupt
  attachInterrupt(digitalPinToInterrupt(HALL_PIN), hall_isr, FALLING);
  
  // Load cumulative energy from EEPROM
  unsigned long raw_energy;
  EEPROM.get(EEPROM_ADDR_ENERGY, raw_energy);
  energy_wh = raw_energy / 100.0;
  
  // MPPT PWM init
  analogWrite(MPPT_PIN, mppt_pwm);
  
  delay(1000);
  Serial.println(F("VAWT Controller Ready"));
}

void loop() {
  unsigned long now = millis();
  
  // Read sensors every 500ms
  if (now - last_update >= 500) {
    last_update = now;
    
    // Read voltage via divider
    int raw_adc = analogRead(VOLTAGE_PIN);
    voltage = (raw_adc / 1023.0) * 5.0 * V_DIV_RATIO;
    
    // Read current from INA219
    current = ina219.getCurrent_mA() / 1000.0;  // Convert to Amps
    if (current < 0) current = 0;  // No reverse current
    
    // Calculate power
    power = voltage * current;
    
    // Accumulate energy (Wh)
    // E = P * dt, where dt = 0.5 seconds = 0.000139 hours
    energy_wh += power * 0.000139;
    
    // Save energy to EEPROM every 60 seconds
    if ((now / 1000) % 60 == 0) {
      unsigned long raw_energy = (unsigned long)(energy_wh * 100);
      EEPROM.put(EEPROM_ADDR_ENERGY, raw_energy);
    }
    
    // Update LEDs
    digitalWrite(LED_GREEN, power > 0.1 ? HIGH : LOW);
    digitalWrite(LED_BLUE, voltage > 4.5 ? HIGH : LOW);
    digitalWrite(LED_RED, voltage > 5.5 ? HIGH : LOW);
    
    // Update OLED
    update_display();
    
    Serial.print("V:"); Serial.print(voltage, 2);
    Serial.print(" I:"); Serial.print(current, 3);
    Serial.print(" P:"); Serial.print(power, 3);
    Serial.print(" RPM:"); Serial.print(rpm);
    Serial.print(" kWh:"); Serial.println(energy_wh / 1000.0, 4);
  }
  
  // Calculate RPM every second
  if (now - last_rpm_calc >= 1000) {
    last_rpm_calc = now;
    // RPM = pulses per second * 60 / pulses_per_revolution
    // We assume 1 magnet = 1 pulse per revolution
    unsigned long dt = now - (last_rpm_calc - 1000);
    rpm = hall_count * 60;
    hall_count = 0;
  }
  
  // MPPT update every 500ms
  if (now - last_mppt >= 500) {
    last_mppt = now;
    mppt_update();
  }
  
  // Heartbeat LED
  heartbeat = !heartbeat;
  digitalWrite(LED_HB, heartbeat ? HIGH : LOW);
}

void hall_isr() {
  hall_count++;
}

void mppt_update() {
  // Perturb & Observe MPPT
  float delta_power = power - last_power;
  
  if (abs(delta_power) < 0.001) {
    // Very small change - reduce step size
    mppt_direction = (delta_power > 0) ? mppt_direction : -mppt_direction;
  } else {
    mppt_direction = (delta_power > 0) ? mppt_direction : -mppt_direction;
  }
  
  // Adjust PWM
  mppt_pwm += mppt_direction * 5;
  
  // Clamp PWM
  if (mppt_pwm > 250) mppt_pwm = 250;
  if (mppt_pwm < 10) mppt_pwm = 10;
  
  analogWrite(MPPT_PIN, mppt_pwm);
  last_power = power;
}

void update_display() {
  display.clearDisplay();
  display.setTextSize(1);
  
  // Header
  display.setCursor(15, 0);
  display.println("VAWT TURBINE");
  
  // Voltage & Current
  display.setCursor(0, 16);
  display.print("V:");
  display.print(voltage, 1);
  display.print("V");
  display.setCursor(64, 16);
  display.print("I:");
  display.print(current * 1000, 0);
  display.print("mA");
  
  // Power & RPM
  display.setCursor(0, 28);
  display.print("P:");
  display.print(power * 1000, 1);
  display.print("mW");
  display.setCursor(64, 28);
  display.print(rpm);
  display.print("RPM");
  
  // Cumulative energy
  display.setCursor(0, 40);
  display.print("Total: ");
  if (energy_wh < 1.0) {
    display.print(energy_wh * 1000, 0);
    display.print(" Wh");
  } else {
    display.print(energy_wh / 1000.0, 3);
    display.print(" kWh");
  }
  
  // Status bar
  display.setCursor(0, 54);
  if (power > 0.1) {
    display.print("[GENERATING]");
  } else {
    display.print("[STANDBY]     ");
  }
  
  display.display();
}
