# OpenAlarm bill of materials

## Modules & enclosure

| Component | Specification or purpose |
| --- | --- |
| Li-ion battery | 3.7 to 4.2 V power source |
| Step-up converter | Set the output to 5 V before connecting the main board |
| Charging circuit | Include overcharge & discharge protection |
| Enclosure & keypad | Print the parts in [dimensions/stl](../dimensions/stl) |
| OpenAlarm motherboard | Components listed below |

## Motherboard components

| Quantity | Component | Notes |
| --- | --- | --- |
| 1 | Buzzer | 10 to 15 mm diameter |
| 11 | 10 kΩ resistor | Pull-up or pull-down logic |
| 5 | 400 Ω resistor | LED current limiting |
| 1 | 3 mm LED | `LED5`, status indicator |
| 4 | 5 mm LED | `LED1` to `LED4`, digit display |
| 12 | Tactile push button | 6 × 6 mm |
| 1 | IRF3205 MOSFET | Optional external 12 V siren switching; requires a separate siren supply |
| 1 | Arduino Nano | Or a compatible board with USB & the same pinout |
| As needed | Wire | Module & sensor connections |

The PCB measures 65 × 98 mm & fits the supplied enclosure. PCB manufacturing files are in [schematics](../schematics).

## Assembly tools & materials

- Small screws & a screwdriver for mounting the board & enclosure.
- Double-sided tape or hot glue for securing internal modules.
- A 3D printer or printing service for the enclosure.
- A computer & USB cable for uploading the [firmware](../code/NNOpenAlarm/NNOpenAlarm.ino).
- A soldering iron & solder for components, wires & headers.
- A multimeter for continuity checks & setting the step-up output.
- Nickel strips & access to a spot welder for the cell connections.

An optional 5 V charger provides permanent power, with the battery used as backup.

## LED resistor selection

The build uses high-sensitivity 5 mm yellow LEDs & a 3 mm red LED that operate at 5 to 10 mA. Select current-limiting resistors for the LEDs you fit:

```text
R = (V_supply - V_LED) / I_LED
```

For a 5 V supply, a 2 V LED forward voltage & a 20 mA target current, the calculation gives `(5 - 2) / 0.02 = 150 Ω`. Choose the closest higher standard resistor value. That example uses a different current from the build's 5 to 10 mA LEDs; don't substitute 150 Ω without checking the LED specification.
