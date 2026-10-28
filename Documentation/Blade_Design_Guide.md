# Blade Design Guide — NACA 0018 Helical Geometry

## Airfoil: NACA 0018

The NACA 0018 is a symmetric airfoil with 18% thickness, widely used for Darrieus VAWT blades.

### Airfoil Equation
```
y_t = (t/0.20) × (0.2969√x - 0.1260x - 0.3516x² + 0.2843x³ - 0.1015x⁴)

Where:
  t = 0.18 (18% thickness ratio)
  x = chordwise position (0 to 1)
  y_t = half-thickness at position x
```

### Properties
| Parameter | Value |
|-----------|-------|
| Max thickness | 18% at 30% chord |
| Camber | Zero (symmetric) |
| Design Cl | 1.2 at α=12° |
| Cd at α=0° | 0.008 |
| Stall angle | ±15° |
| Cm | 0.0 (no pitching moment) |
| Re range | 50,000–500,000 |

## Helical Geometry

### Blade Parameters
| Parameter | Value |
|-----------|-------|
| Blade height (H) | 250 mm |
| Rotor radius (R) | 75 mm |
| Chord (c) | 30 mm (constant) |
| Max thickness | 5.4 mm (18% of 30mm) |
| Total helix twist | 180° |
| Twist rate | 0.72°/mm |
| Number of blades | 3 (at 120° phase) |

### Helix Equation
```
For blade station at height z (0 to 250mm):
  azimuth angle θ(z) = (z / H) × 180°    [degrees]
  x-position = R × cos(θ)
  y-position = R × sin(θ)

For blades 2 and 3, add 120° and 240° to θ respectively.
```

### Coordinate Table (Blade 1 — every 25mm)

| z (mm) | Azimuth | X (mm) | Y (mm) | Chord (mm) | Thickness (mm) |
|--------|---------|--------|--------|------------|----------------|
| 0 | 0° | 75.0 | 0.0 | 30 | 5.4 |
| 25 | 18° | 71.3 | 23.2 | 30 | 5.4 |
| 50 | 36° | 60.7 | 44.1 | 30 | 5.4 |
| 75 | 54° | 44.1 | 60.7 | 30 | 5.4 |
| 100 | 72° | 23.2 | 71.3 | 30 | 5.4 |
| 125 | 90° | 0.0 | 75.0 | 30 | 5.4 |
| 150 | 108° | -23.2 | 71.3 | 30 | 5.4 |
| 175 | 126° | -44.1 | 60.7 | 30 | 5.4 |
| 200 | 144° | -60.7 | 44.1 | 30 | 5.4 |
| 225 | 162° | -71.3 | 23.2 | 30 | 5.4 |
| 250 | 180° | -75.0 | 0.0 | 30 | 5.4 |

## CAD Creation Steps (Fusion 360)

1. **Create helix path**: Revolve 180° over 250mm height, radius 75mm
2. **At z=0**: Create NACA 0018 airfoil sketch at (75, 0, 0), chord=30mm, tangent to circle
3. **At z=25mm**: Create same airfoil at (71.3, 23.2, 25), rotated 18°
4. **Continue** at 25mm intervals through z=250mm (11 stations total)
5. **Loft**: Create blade surface through all 11 sections
6. **Add features**: M3 mounting holes at z=0 and z=250mm (Ø3.2mm through-hole)
7. **Export STL**: Maximum resolution for SLA printing
8. **Array**: Copy blade 3 times, rotate 120° each for complete rotor

## Solidity Calculation
```
σ = N × c / (2π × R) = 3 × 30 / (2π × 75) = 0.191

Optimal solidity range for Darrieus: σ = 0.15–0.25
Our value: 0.191 ✓ (well within optimal range)
```
