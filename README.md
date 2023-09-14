# DAQ for UC Testing Fall 2023

_Jason Klein, Micah Fisher, Mehdi Heydari_

The competition DAQ didn't work very consistently, so this is some new DAQ code that will be used for the Urban Concept testing on 9/23.

## Todo

- [x] Upload blink sketch to ESP32
- [x] Connect to iPhone hotspot
- [x] Make HTTP request to https://example.com/
- [ ] Batch RPM sensor data to send at ~5 Hz
- [ ] Connect to a locally-hosted server over IP
- [ ] Connect to WebSocket server running on iPhone

## Setup

I would've liked to be able to use PlatformIO or the VSCode arduino extension for this project, but I couldn't figure out how to get them working properly (the ESP32 uploader would fail for no reason). Thus, you'll need to configure it with the Arduino IDE. Follow [these instructions from the ESPRESSIF website](https://docs.espressif.com/projects/arduino-esp32/en/latest/installing.html) to install.

Set the board in Tools > Board to `ESP32 Dev Module` and then verifying and uploading should work properly.
