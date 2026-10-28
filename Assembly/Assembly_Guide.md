# Assembly Guide — Desktop VAWT 50cm

## Tools Required
- Soldering iron (280–350°C)
- Screwdriver set (Phillips #0, #1 + hex 1.5–2.5mm)
- Flush cutters
- Craft knife + cutting mat
- Digital caliper
- Multimeter
- Hot glue gun
- Needle-nose pliers
- Safety glasses + nitrile gloves

## Parts Checklist

Before assembly, verify you have:

### 3D Printed Parts
- [ ] PT-01: Helical Blade ×3
- [ ] PT-02: Bottom Arm Disc ×1
- [ ] PT-03: Top Arm Disc ×1
- [ ] PT-04: Nose Cone ×1
- [ ] PT-05: Base Shell ×1
- [ ] PT-06: Base Top Plate ×1
- [ ] PT-07: Bearing Plate ×2
- [ ] PT-08: Generator Mount ×1
- [ ] PT-09: LED Accent Ring ×1
- [ ] PT-10: Strut Connector ×6

### Purchased Components
- [ ] PMSG Generator (GB4108 or N20)
- [ ] 608ZZ Bearing ×2
- [ ] SS304 Shaft Ø8mm × 380mm
- [ ] Shaft locking collar Ø8mm ×2
- [ ] M3×10 socket head screws ×6
- [ ] M3 nylock nuts ×6
- [ ] M3 brass threaded inserts ×6
- [ ] Bridge rectifier or 4× 1N5819
- [ ] CN3791 MPPT board
- [ ] MT3608 boost converter
- [ ] 18650 battery + holder
- [ ] Arduino Nano
- [ ] OLED display (SSD1306)
- [ ] INA219 current sensor
- [ ] A3144 Hall sensor
- [ ] LEDs (8×) + resistors (8×)
- [ ] USB socket + switch
- [ ] Wiring + perfboard

## Step-by-Step Assembly

### Phase 1: Base Preparation (2 hours)

**Step 1: Install electronics in base shell**
- Solder OLED display, USB socket, power switch, and LEDs into cutout holes
- Wire to perfboard: voltage divider (100K/10K on A0), INA219 on I2C
- Flash Arduino Nano with firmware before installation
- Test: power via USB, verify OLED shows "BOOT" message

**Step 2: Weight the base**
- Mix fine sand with 2-part epoxy to thick paste
- Fill base cavity to ~5mm below top edge
- Target: 1,200g of fill material
- Let cure 24 hours at room temperature

**Step 3: Close the base**
- Place base top plate (PT-06) on base shell
- Secure with 4× M4 screws from underneath
- Apply silicone sealant at tower base joint

### Phase 2: Drivetrain (2 hours)

**Step 4: Install bottom bearing plate**
- Press 608ZZ bearing into bearing plate (PT-07)
- Mount plate on base top with 4× M3 screws
- Verify bearing spins freely

**Step 5: Insert main shaft**
- Slide Ø8mm shaft through bottom bearing
- Install locking collar at generator height (~90mm from base)
- Set collar tight with M3 grub screw

**Step 6: Mount generator**
- Press generator into generator mount (PT-08)
- Slide mount onto shaft below bearing
- Align keyway, secure with set screw
- Route 3-phase wires through tower channel

**Step 7: Install bottom arm disc**
- Slide PT-02 (bottom arm) onto shaft
- Align flat on shaft with disc keyway
- Lock with M3 grub screw
- Verify disc is perpendicular to shaft

### Phase 3: Rotor Assembly (2 hours)

**Step 8: Attach blades to bottom arm**
- Insert blade 1 root into bottom arm disc slot at 0° position
- Secure with M3×10 bolt through disc side + nylock nut
- Repeat for blade 2 at 120° and blade 3 at 240°
- Verify 120° spacing ±1° accuracy

**Step 9: Install top arm disc**
- Slide PT-03 (top arm) onto shaft at blade top height
- Align blade top ends with top arm disc slots
- Insert and secure with M3×10 + nylock nut each
- Verify all blades are taut and aligned

**Step 10: Install top bearing + nose cone**
- Press 608ZZ into top bearing plate
- Mount above rotor on shaft
- Thread M5 nut on shaft end
- Snap nose cone (PT-04) over shaft top

### Phase 4: Electrical & Testing (2 hours)

**Step 11: Wire generator to electronics**
- Generator 3-phase → bridge rectifier (inside base)
- Rectifier DC+ → CN3791 MPPT input
- MPPT output → 18650 battery
- Battery → MT3608 boost → USB socket
- Hall sensor (A3144) → Arduino D2
- Mount N35 magnet on shaft for Hall trigger

**Step 12: Test spin**
- Spin rotor by hand
- Verify OLED shows RPM reading
- Check for smooth rotation (no rubbing)
- Listen for bearing noise

**Step 13: Balance check**
- If vibration observed: identify lightest blade
- Add tiny hot-glue weight to heaviest blade section
- Re-test until vibration-free

**Step 14: Fan test**
- Place desk fan 20cm away on medium
- Verify blades start spinning within 5 seconds
- Check OLED shows V, I, P readings
- Verify USB port shows voltage output
- Connect phone — verify charging begins

**Step 15: Final finishing**
- Touch up any paint damage
- Apply company logo/branding on base front
- Attach 4× rubber feet to base bottom
- Install LED accent ring (PT-09) at base top
- Final visual inspection

## Troubleshooting

| Problem | Cause | Fix |
|---------|-------|-----|
| Blades don't start | Too much friction | Check bearing alignment, reduce shaft tightness |
| Low voltage output | Generator wiring wrong | Verify 3-phase connection to rectifier |
| OLED blank | Power issue | Check battery voltage, I2C address (0x3C) |
| Vibration at speed | Unbalanced blades | Add weight to light blade |
| USB doesn't charge | Boost converter not set | Adjust MT3608 pot to exactly 5.0V |
| RPM reads 0 | Hall sensor issue | Check magnet proximity (< 3mm gap) |
