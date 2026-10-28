# 3D Print Settings — Master Configuration

## SLA Settings (Blades, Nose Cone, Struts)

### Recommended Printers
- Elegoo Saturn 3 / Saturn 3 Ultra
- Formlabs Form 3+
- Anycubic Photon Mono M5s
- Phrozen Sonic Mini 8K

### Resin Selection
| Resin | Use | Properties |
|-------|-----|-----------|
| Siraya Tech ABS-Like (80% Fast + 20% Tenacious) | **Blades** | Tough, impact-resistant, smooth |
| Formlabs Tough 2000 | Hub, struts | High strength, precise |
| Standard Resin | Nose cone | Cost-effective, adequate |

### Universal SLA Settings
```
Layer Height:     0.05 mm (50 microns)
Exposure:         2.5–3.5 s (resin & printer dependent — TEST FIRST)
Bottom Exposure:  35–50 s
Bottom Layers:    6
Layer Height:     0.05 mm (same as body)
Lift Height:      5 mm
Lift Speed:       60 mm/s (bottom: 30 mm/s)
Retract Speed:    120 mm/s
Light-off Delay:  1.0 s
Anti-aliasing:    8x (greyscale)
Resin Temp:       25–30°C (warm = better)
```

### Blade-Specific Settings
```
Orientation:    VERTICAL (standing on root end, tip pointing up)
Why:            Layer lines run along blade span = minimal aero penalty
Supports:       Tree supports at trailing edge ONLY (minimal contact)
Wash:           IPA 99%, 10 minutes (ultrasonic preferred)
Cure:           UV chamber, 60°C, 30 minutes
Sanding:        P400 → P800 → P1200 → P2000 (wet sand)
Primer:         Tamiya Fine Surface Primer (grey), 2 light coats
Paint:          Tamiya TS-26 Pure White, 2-3 coats
Clear:          Tamiya TS-7 Gloss Clear, 2 coats
Polish:         P3000 wet sand + Meguiar's rubbing compound
```

## FDM Settings (Base, Arm Discs, Bearing Plates)

### Recommended Printers
- Bambu Lab P1S / X1C
- Prusa MK4
- Creality K1 / K1 Max
- Any printer with 0.4mm nozzle

### Filament Selection
| Part | Material | Why |
|------|----------|-----|
| Base shell + plate | PLA+ Black | Rigid, good surface |
| Arm discs | PLA+ White | Matches blades after paint |
| Bearing plates | PETG Black | Stronger, heat-resistant |
| Generator mount | PETG Black | Structural, vibration |
| LED ring | PLA+ Translucent | Light diffusion |

### Universal FDM Settings
```
Nozzle:           0.4mm
Nozzle Temp:      210°C (PLA+) / 230°C (PETG)
Bed Temp:         60°C
Layer Height:     0.12mm (fine) or 0.16mm (standard) or 0.20mm (fast)
Wall Count:       3 (1.2mm total wall)
Top Layers:       4
Bottom Layers:    4
Infill:           See per-part table
Infill Pattern:   Gyroid (preferred) or Grid
Print Speed:      40 mm/s (walls), 80 mm/s (infill)
Travel Speed:     150 mm/s
Retraction:       4mm @ 40mm/s (Bowden) / 0.8mm @ 35mm/s (Direct Drive)
Cooling:          100% fan after layer 4
First Layer:      0.24mm height, 50% speed, 150% width
Brim:             5mm for tall parts
Bed Adhesion:     Glue stick on glass/PEI
```

## Post-Processing (All Parts)

### Surface Finishing Workflow
1. **Remove supports** — Flush cutters + craft knife
2. **IPA wash** (SLA only) — 99% IPA, 10 min ultrasonic
3. **UV cure** (SLA only) — 30 min at 60°C
4. **Fill gaps** — Automotive filler primer on layer lines
5. **Sand P400** — Remove support marks, level filler
6. **Primer coat** — Tamiya Fine Surface Primer (grey), 2 coats
7. **Sand P800** — Level primer
8. **Sand P1200** — Smooth primer surface
9. **Color coat** — Spray paint, 2-3 light coats, 15 min between
10. **Clear coat** — 2K automotive clear or Tamiya TS-7, 2 coats
11. **Sand P2000** — Wet sand clear coat
12. **Polish** — Rubbing compound for mirror finish

### Target Surface Quality
- Blades: Ra < 1.5 μm (premium)
- Arm discs: Ra < 3 μm (good)
- Base: Ra < 6 μm (matte acceptable)
