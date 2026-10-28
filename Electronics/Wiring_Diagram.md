# Wiring Diagram — Desktop VAWT 50cm

## System Wiring

```
                    ┌─────────────────────────────────────────────┐
                    │              HELICAL ROTOR                  │
                    │    3x Blades → Arm Discs → Ø8mm Shaft      │
                    └──────────────────┬──────────────────────────┘
                                       │
                    ┌──────────────────▼──────────────────────────┐
                    │         PMSG GENERATOR (GB4108)             │
                    │      3-Phase AC Output (3 wires)            │
                    └──────────────────┬──────────────────────────┘
                                       │ 3-phase AC
                    ┌──────────────────▼──────────────────────────┐
                    │         BRIDGE RECTIFIER                     │
                    │      4x 1N5819 Schottky Diodes              │
                    │      AC → DC (smoothed)                     │
                    └──────────────────┬──────────────────────────┘
                                       │ DC bus (up to 32V)
                    ┌──────────────────▼──────────────────────────┐
                    │         CN3791 MPPT CONTROLLER               │
                    │   Arduino D3 (PWM) → MOSFET gate            │
                    │   Tracks max power point                    │
                    └───────────┬──────────────────┬──────────────┘
                                │                  │
                    ┌───────────▼──┐    ┌──────────▼─────────────┐
                    │  18650 LiPo  │    │   MT3608 BOOST CONV    │
                    │  3.7V Buffer │    │   DC-DC → 5.0V Reg    │
                    └──────────────┘    └──────────┬─────────────┘
                                                   │ 5V regulated
                          ┌────────────────────────┼──────────┐
                          │                        │          │
                ┌─────────▼─────┐   ┌──────────────▼──┐  ┌───▼────────┐
                │  USB TYPE-A   │   │  ARDUINO NANO   │  │ OLED 0.96" │
                │  (5V Output)  │   │  (MCU)          │  │ (I2C)      │
                │  → Phone      │   │                 │  └────────────┘
                └───────────────┘   │  A0 → Voltage   │
                                    │  A4/A5 → I2C    │──► INA219
                                    │  D2 → Hall      │──► OLED
                                    │  D3 → MPPT PWM  │
                                    │  D6 → LED Green │
                                    │  D7 → LED Blue  │
                                    │  D8 → LED Red   │
                                    │  D13 → Heartbeat│
                                    └─────────────────┘
```

## Pin Connections

### Arduino Nano Pinout

| Arduino Pin | Connected To | Purpose |
|-------------|-------------|---------|
| A0 | Voltage divider (100K + 10K) | Generator voltage (0–35V → 0–3.2V) |
| A4 (SDA) | I2C bus | INA219 + OLED SSD1306 |
| A5 (SCL) | I2C bus | INA219 + OLED SSD1306 |
| D2 | A3144 Hall sensor (interrupt) | RPM counting |
| D3 | MOSFET gate (via 1K resistor) | MPPT PWM control |
| D6 | LED Green (via 220Ω) | Generating indicator |
| D7 | LED Blue (via 220Ω) | USB active indicator |
| D8 | LED Red (via 220Ω) | Fault/overvoltage |
| D13 | Onboard LED | Heartbeat (1Hz blink) |
| 5V | MT3608 output | Power to Arduino |
| GND | Common ground | All circuits |

### Voltage Divider
```
Generator DC+ ──[100KΩ]──┬──[10KΩ]── GND
                          │
                          └── To Arduino A0
                          
Ratio: 10/(100+10) = 0.0909
Max measurable: 3.3V / 0.0909 = 36.3V ✓
```

### I2C Bus
```
5V ──[4.7K]── SDA ── INA219 (0x40) + OLED (0x3C)
5V ──[4.7K]── SCL ── INA219 (0x40) + OLED (0x3C)
```

### Hall Sensor Wiring
```
5V ──── A3144 (VCC)
D2 ──── A3144 (OUT) ←── 10K pull-up to 5V
GND ─── A3144 (GND)

N35 magnet on shaft → triggers Hall when passing sensor
Gap: < 3mm
```

### Power Path
```
Generator (3-phase) → Bridge Rectifier → DC Bus (up to 32V)
                                              │
                                        CN3791 MPPT
                                              │
                                        18650 Battery (3.7V)
                                              │
                                        MT3608 Boost
                                              │
                                        5V Regulated ──► USB + Arduino
```

## Bill of Materials — Electronics

| Item | Qty | Value | Package | Notes |
|------|-----|-------|---------|-------|
| R1 | 1 | 100KΩ | 1/4W | Voltage divider upper |
| R2 | 1 | 10KΩ | 1/4W | Voltage divider lower |
| R3–R10 | 8 | 220Ω | 1/4W | LED current limiting |
| R11 | 1 | 4.7KΩ | 1/4W | I2C pull-up SDA |
| R12 | 1 | 4.7KΩ | 1/4W | I2C pull-up SCL |
| R13 | 1 | 10KΩ | 1/4W | Hall sensor pull-up |
| R14 | 1 | 1KΩ | 1/4W | MOSFET gate resistor |
| D1–D4 | 4 | 1N5819 | DO-41 | Bridge rectifier |
| Q1 | 1 | IRF540N | TO-220 | MPPT MOSFET |
| U1 | 1 | Arduino Nano | DIP | Microcontroller |
| U2 | 1 | SSD1306 | I2C | OLED display |
| U3 | 1 | INA219 | Breakout | Current sensor |
| U4 | 1 | CN3791 | Breakout | MPPT controller |
| U5 | 1 | MT3608 | Module | Boost converter |
| U6 | 1 | A3144 | TO-92 | Hall sensor |
| LED1 | 1 | Green 3mm | — | Generating |
| LED2 | 1 | Blue 3mm | — | USB active |
| LED3 | 1 | Red 3mm | — | Fault |
| BAT1 | 1 | 18650 + holder | — | LiPo 1200mAh |
| J1 | 1 | USB Type-A female | Panel | 5V output |
| SW1 | 1 | SPDT slide | Panel | Power switch |
