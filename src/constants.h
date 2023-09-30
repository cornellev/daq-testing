#pragma once

#include <stdint.h>

// mobile hotspot name (can't contain apostraphes!)
const char* WIFI_SSID = "jasooon";
// mobile hotspot password
const char* WIFI_PASSWORD = "12345678";
// IP address of the phone when in hotspot mode. Always the same
const uint8_t HOST_IP[] = {172, 20, 10, 2};
// port running the WebSocket server
const uint16_t HOST_PORT = 8080;
// how often to try reconnecting to the WebSocket server (in ms)
const unsigned long RECONNECT_INTERVAL = 5000;
