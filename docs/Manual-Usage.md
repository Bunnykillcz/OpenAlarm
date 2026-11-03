# OpenAlarm usage manual

These controls follow the [firmware in this repository](../code/NNOpenAlarm/NNOpenAlarm.ino). The PIN & delays are set in the sketch before uploading it; see the [build manual](Manual-Build.md#configure-the-firmware).

## Keypad controls

| Key | Action |
| --- | --- |
| `*` / OK | Start arming when disarmed; submit the PIN when armed |
| `#` / Cancel | Cancel the exit countdown or clear entered digits when armed |
| `0` to `9` | Enter PIN digits when armed |

`#` alone doesn't disarm an armed alarm.

## Arm the alarm

Press & release `*`. The buzzer beeps during the exit countdown. Leave before the countdown finishes; the default exit delay is 8000 ms, followed by the firmware's final beep sequence.

Press `#` during the exit countdown to cancel arming. Once armed, the status LED blinks & the firmware monitors the sensor input on A0.

## Disarm the alarm

Enter your four-digit PIN, then press `*`. The supplied sketch uses `9856`; change it before use. The four display LEDs indicate how many digits you've entered.

If you make a mistake, press `#` to clear the entry & start again. Submitting an incorrect four-digit PIN produces a beep & resets the entry count; the alarm stays armed.

## Sensor trigger & siren

A HIGH signal on A0 starts the entry countdown while the alarm is armed. Enter the PIN & press `*` before the countdown expires. The default entry delay is 8000 ms.

If the countdown expires, the firmware drives the siren output on A2 HIGH. The correct PIN followed by `*` disarms the alarm & returns that output LOW. Entry countdown beeps are controlled by `beep_during_entry_sequence` in the sketch.

## Restart behavior

The firmware starts disarmed after a reset or power cycle. It doesn't restore the armed state from before the restart.

## Serial output

The Serial Monitor uses 9600 baud & reports arming, activation, disarming & PIN checks. It also prints entered PIN digits. Treat access to that output as access to the PIN.
