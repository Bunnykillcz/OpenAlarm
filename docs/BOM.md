# 🧾 Bill of Materials (BOM) – OpenAlarm

This document lists all the components, modules, and tools required to build the **OpenAlarm** system.

---

## 📦 Main Modules & Boards

| Component | Notes |
|----------|-------|
| 🔋 **Li-ion Battery (3.7–4.2 V)** | Power source |
| ⚡ **Step-Up Converter (0–3 V → 5 V+)** | Boosts battery voltage to usable levels |
| 🔌 **Charging Circuit** | Must include **overcharge** and **quick discharge protection IC** |
| 🧩 **3D Printed Case & Keyboard** | STL files available in `/dimensions/stl` |
| 🖧 **NN OpenAlarm Motherboard** | See detailed part list below |

---

## 🧠 NN OpenAlarm Motherboard Components

| Qty | Component | Notes |
|-----|-----------|-------|
| 1x | **Buzzer** | Diameter: 10–15 mm |
| 11x | **Resistor** – 10 kΩ | Pull-down/pull-up logic |
| 5x | **Resistor** – 400 Ω | LED current limiters; optionally lower for higher brightness |
| 1x | **LED (3 mm)** | `LED5`, status indicator |
| 4x | **LED (5 mm)** | `LED1–LED4`, used for display |
| 12x | **Button Switch** | 6×6 mm tactile push buttons |
| 1x | **MOSFET IRF3205** | Optional – used to switch external 12 V siren (requires separate power) |
| 1x | **Arduino Nano** | Or compatible clone with USB and same pinout |
| 🧵 | **Wires** | For connecting all the components |

---

## 📐 Motherboard PCB Dimensions

- Width: **65 mm**  
- Height: **98 mm**

The board fits into the 3D printed case provided in `/dimensions/stl`. You are welcome to make your own as well.

---

## 🛠 Assembly Requirements

| Tool / Material | Notes |
|-----------------|-------|
| 🔩 Small Screws | For mounting case and components |
| 🔧 Screwdriver | |
| 🩹 Sticky Tape / Hot Glue | To secure internal components |
| 🖨 3D Printer | Or find someone to print the case for you |
| 💻 Computer | For uploading firmware from `/code/NNOpenAlarm/` |
| 🔥 Soldering Iron | Required for wiring and headers |
| 🧾 Motherboard PCB | Can be ordered from JLCPCB (see `/schematics/*.zip`) or made at home using monochrome 2-layer printouts |

---

## 🔌 Optional

| Item | Purpose |
|------|---------|
| 🔌 **5 V Charger** | Optional, for permanent power supply (battery acts as backup) |
| ☕ **A Good Spirit** | Required for optimal results 😎 |

---

## 📝 Notes

- If you're using standard LEDs that require ~20mA, calculate exact resistor values using Ohm’s Law:  
  `R = (V_supply - V_LED) / I_LED`  
  Example for 5V supply, red LED (2V), 20 mA:  
  `R = (5 - 2) / 0.02 = 150 Ω`  
  Choose the closest higher standard value.

- 💡 **Note** that this project uses **highly sensitive LEDs** —  
- specifically **5 mm yellow** and **3 mm red** sensitive types that are bright enough at **5–10 mA**.  


---