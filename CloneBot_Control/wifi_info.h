//// WiFi Option 1: Setting up Wi-Fi connection to existed network: Replace with your network credentials
//const char* ssid = "RedRover";
//const char* password = NULL;

// WiFi Option 2: Set up your own Wi-Fi network access point with SSID and password
const char* ssid = "MobileHRI-12";
const char* password = "12345678";

//uint8_t softAPgetStationNum();

WiFiServer server(80);
String header;
