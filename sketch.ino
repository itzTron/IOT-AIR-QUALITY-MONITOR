#include <WiFi.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// ================= USER CONFIGURATION =================
const char* ssid = "Wokwi-GUEST"; // Default Wokwi WiFi
const char* password = "";
const char* apiKey = "YOUR_WRITE_API_KEY"; // PASTE YOUR KEY HERE
const char* server = "api.thingspeak.com";

// ================= HARDWARE PINS =================
#define POT_PM25_PIN 34  // Simulates Dust Sensor
#define POT_CO2_PIN  35  // Simulates CO2 Sensor
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
WiFiClient client;

void setup() {
  Serial.begin(115200);

  // 1. Setup Display
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("Connecting to WiFi...");
  display.display();

  // 2. Setup WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi Connected");
  
  display.clearDisplay();
  display.setCursor(0,0);
  display.println("WiFi Connected!");
  display.display();
  delay(1000);
}

void loop() {
  // --- STEP 1: READ SENSORS (SIMULATED) ---
  // Read Potentiometer 1 (0-4095) and map to PM2.5 range (0-500 ug/m3)
  int rawPM = analogRead(POT_PM25_PIN);
  int pm25Value = map(rawPM, 0, 4095, 0, 500);

  // Read Potentiometer 2 (0-4095) and map to CO2 range (400-5000 ppm)
  int rawCO2 = analogRead(POT_CO2_PIN);
  int co2Value = map(rawCO2, 0, 4095, 400, 5000);

  // --- STEP 2: DISPLAY ON OLED ---
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0,0);
  display.println("AIR QUALITY MONITOR");
  display.drawLine(0, 10, 128, 10, WHITE);
  
  display.setCursor(0, 20);
  display.print("PM2.5: "); display.print(pm25Value); display.println(" ug/m3");
  
  display.setCursor(0, 35);
  display.print("CO2:   "); display.print(co2Value); display.println(" ppm");

  display.setCursor(0, 55);
  display.print("Status: Uploading...");
  display.display();

  // --- STEP 3: SEND TO CLOUD (ThingSpeak) ---
  if (client.connect(server, 80)) {
    String postStr = apiKey;
    postStr += "&field1=";
    postStr += String(pm25Value);
    postStr += "&field2=";
    postStr += String(co2Value);
    postStr += "\r\n\r\n";

    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: " + String(apiKey) + "\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(postStr.length());
    client.print("\n\n");
    client.print(postStr);
    
    Serial.println("Data sent to ThingSpeak:");
    Serial.print("PM2.5: "); Serial.println(pm25Value);
    Serial.print("CO2: "); Serial.println(co2Value);
    
    display.fillRect(0, 55, 128, 10, BLACK); // Clear status line
    display.setCursor(0, 55);
    display.print("Status: Sent!");
    display.display();
  } else {
    Serial.println("Connection to ThingSpeak failed");
    display.fillRect(0, 55, 128, 10, BLACK);
    display.setCursor(0, 55);
    display.print("Status: Error");
    display.display();
  }

  // ThingSpeak free tier requires 15s delay. We wait 15s.
  delay(15000);
}