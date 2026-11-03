# OpenAlarm build manual

By NejedNiko.cz. 
Software & documentation are licensed under the [NejedNiko Software Licensing Framework](https://github.com/Bunnykillcz/NejedNiko_Software_Licensing_Framework). 
See [LICENSE](../LICENSE) for scope & full terms.

## Parts & tools

Gather the components in the [bill of materials](BOM.md), a soldering iron, solder, a USB cable & a multimeter. Print the enclosure parts from [dimensions/stl](../dimensions/stl). The [schematics directory](../schematics) contains the PCB manufacturing archive & board references.

## Assemble the board

Solder the small components first, then the larger parts. Fit the Arduino Nano last. Use the board markings & the [mounting photo](img/OA-mounting_detail.jpg) to check component positions.

Leave the LED leads long enough to reach the enclosure openings. Hold the LEDs level with a piece of cardboard while soldering; trim the leads after checking the enclosure fit.

### Set the step-up output

Before connecting the step-up module to the main board:

1. Power the module from the Li-ion battery or a bench supply.
2. Measure its output with a multimeter.
3. Adjust the output to 5 V, within 0.05 V.

### Connect the modules

Wire the modules using the [connection photo](img/OA-mounting_connections.jpg) & schematic. Check continuity with power disconnected. Check supply voltages before powering the main board; a bench supply can be used for this test.

Attach wires or pin headers to the sensor input section at the top left of the board for connecting motion sensors or switches.

### Connect the battery

Use spot-welded nickel strips for the Li-ion cell connections. Don't solder directly onto the cell.

### Check power & fit the enclosure

Connect USB power or a charger to the charging module. Check that the battery charges & that the step-up module supplies the main board. Disconnect power if a component heats up unexpectedly. An LED blink depends on the sketch already installed on the Nano.

Secure the modules with screws through their mounting holes, double-sided tape or glue. Check that the LED positions line up with the enclosure before closing it.

## Configure the firmware

Install [Arduino IDE](https://www.arduino.cc/en/software), then select the board & port for your Nano. Install the board package or USB driver required by your board if it isn't detected.

Open [code/NNOpenAlarm/NNOpenAlarm.ino](../code/NNOpenAlarm/NNOpenAlarm.ino). The settings near the top define the four-digit PIN, entry delay, exit delay & entry beeps:

```cpp
const int n1 = 9;
const int n2 = 8;
const int n3 = 5;
const int n4 = 6;

int delay_time_ms_enter = 8000;
int delay_time_ms_leave = 8000;
bool beep_during_entry_sequence = true;
```

Change the PIN before use. Both delay settings are in milliseconds; `8000` means 8 seconds. Setting `beep_during_entry_sequence` to `false` disables the entry countdown beeps.

## Upload & test

Upload the Blink example first if you need to check communication with the Nano. Then upload the configured OpenAlarm sketch. The firmware sends status messages to the Serial Monitor at 9600 baud.

Disconnect the external siren while testing:

1. Restart the board. The firmware starts disarmed.
2. Press `*` to start the exit countdown. Press `#` during that countdown to cancel arming.
3. Arm it again & let the countdown finish.
4. Trigger the sensor input. Enter your four-digit PIN, then press `*` to disarm before the entry delay expires.
5. Repeat the sensor test without entering the PIN. Check that the siren output activates after the entry delay, then disarm with the PIN & `*`.

Once testing is complete, secure the remaining wiring & close the enclosure. Check that no parts are loose. See the [usage manual](Manual-Usage.md) for keypad controls.
