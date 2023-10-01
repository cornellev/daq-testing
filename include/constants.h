#pragma once

#include <stdint.h>

namespace constants {
// mobile hotspot name (can't contain apostraphes!)
constexpr char WIFI_SSID[]{"jasooon"};
// mobile hotspot password
constexpr char WIFI_PASSWORD[]{"12345678"};
// IP address of the phone when in hotspot mode. Always the same
constexpr uint8_t HOST_IP[] = {172, 20, 10, 2};
// port running the WebSocket server
constexpr uint16_t HOST_PORT = 8080;
// how often to try reconnecting to the WebSocket server (in ms)
constexpr unsigned long RECONNECT_INTERVAL = 5000;
// Hall Effect sensor sample period (in ms)
constexpr int SAMPLE_PERIOD = 5000;
// pins used for Hall Effect sensor interrupts
enum RPM { LEFT = 14, RIGHT = 15 };
}  // namespace constants