# Engineering Calculations — Desktop VAWT 50cm

## 1. Power Equations (VAWT)

### Wind Power Available
```
P_wind = ½ × ρ × A_frontal × V³

Where:
  ρ = 1.225 kg/m³ (standard air density)
  A_frontal = D × H = 0.15 × 0.25 = 0.0375 m²
  V = free-stream wind speed (m/s)
```

### Rotor Power
```
P_rotor = ½ × ρ × A × V³ × Cp

Where:
  Cp = Power coefficient ≈ 0.25 (helical Darrieus, λ=3.0)
```

### Electrical Power
```
P_elec = P_mech × η_gen × η_elec
       = P_mech × 0.85 × 0.90
       = P_mech × 0.765
```

## 2. Example Calculation at V = 6 m/s

```
P_wind = 0.5 × 1.225 × 0.0375 × 216 = 4.96 W
P_mech = 4.96 × 0.25 = 1.24 W
P_elec = 1.24 × 0.85 × 0.90 = 0.95 W
```

## 3. Tip Speed Ratio & RPM

```
λ = ω × R / V
ω = λ × V / R = 3.0 × 6 / 0.075 = 240 rad/s
N = ω × 60 / (2π) = 2,292 RPM

Blade tip speed = ω × R = 18.0 m/s (Mach 0.05 — virtually silent)
```

## 4. Angle of Attack Analysis

```
α(θ) = arctan(sin(θ) / (λ + cos(θ)))

Maximum α at θ = 90° and 270°:
  α_max = arctan(1/λ) = arctan(1/3.0) = 18.4°

For NACA 0018, stall at α ≈ 15°
→ Some dynamic stall occurs (beneficial for self-regulation)
```

## 5. Structural Checks

### Bearing Life
```
608ZZ bearing: C = 3,250 N
Applied load: ~2 N (rotor weight + wind)
L10 = (C/P)³ × 10⁶ = (3250/2)³ × 10⁶ = 4.3×10¹² rev → ∞ life
Speed rating: 36,000 RPM >> our 2,300 RPM ✓
```

### Blade Centrifugal Force
```
F = m × ω² × R = 0.022 × 240² × 0.075 = 95 N per blade
VAWT blades carry primarily tensile (not bending) load
→ Solid 3D-print blade is adequate
```

### Base Stability
```
Overturn moment at V=10 m/s:
  F_drag = 0.5 × 1.225 × 1.2 × 0.0375 × 100 = 2.76 N
  M_overturn = 2.76 × 0.21 = 0.58 N·m

Restoring moment (1.2 kg sand fill):
  M_restore = 1.2 × 9.81 × 0.075 = 0.88 N·m

Safety factor = 0.88 / 0.58 = 1.52 > 1.0 ✓ STABLE
```

## 6. Generator Sizing (GB4108 100KV)

```
Back-EMF: Ke = KV × 2π/60 = 100 × 0.1047 = 10.47 V/krpm

At N = 2,300 RPM:
  E_L-L = 10.47 × 2.3 = 24.1 V
  V_DC = 24.1 × 1.35 × 0.95 = 30.9 V (after rectification)
  I = P/V = 0.95/30.9 = 31 mA

MPPT controller handles up to 32V → within spec ✓
Buck converter (30V → 5V) more efficient than boost ✓
```
