# DAQ for UC Testing Fall 2023

_Jason Klein, Micah Fisher_

The competition DAQ didn't work very consistently, so this is some new DAQ code that will be used for Urban Concept testing on 9/31. It connects to the iPhone hotspot and communicates data through a WebSocket connection. The WebSocket server is running as a NodeJS application on this laptop (the code for that is in `/server`).

## Progress

- [x] Upload blink sketch to ESP32
- [x] Connect to iPhone hotspot
- [x] Make HTTP request to https://example.com/
- [x] Integrate with Micah's RPM sensor code
- [x] Connect to a locally-hosted server over IP
- [x] Connect to WebSocket server ~~running on iPhone~~
- [x] Send data to the database
- [ ] Verify that the data is sent correctly

## Setup

Starting in commit `6792ffb4a`, this project uses [PlatformIO](https://platformio.org/), an embedded development project that is better than the Arduino IDE type stuff by a lot. I recommend using VSCode with the [PlatformIO extension](https://marketplace.visualstudio.com/items?itemName=platformio.platformio-ide). 

The PlatformIO extension should add a bug-looking item in your VSCode toolbar. Click it, and open this project folder. Running `PlatformIO: Build` from the Command Palette should just work, and it'll install all the dependencies and stuff for you. `PlatformIO: Upload` will automatically find the correct port and compile and upload.
