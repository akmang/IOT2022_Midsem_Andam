#include <LiquidCrystal_I2C.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include "browser.h"
#include <ESPmDNS.h>



WebServer server(80);
#define uS_TO_S_FACTOR 1000000ULL /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP 120         /* Time ESP32 will go to sleep (in seconds) */
#define TRIG_PIN 26               // ESP32 pin GIOP23 connected to Ultrasonic Sensor's TRIG pin
#define ECHO_PIN 25               // ESP32 pin GIOP22 connected to Ultrasonic Sensor's ECHO pin
#define motor 18
#define led_on 19

RTC_DATA_ATTR int bootCount = 0;
int waterheight;
// const char* ssid     = "DUFIE-HOSTEL";
// const char* password = "Duf1e@9723";

const char* ssid = "Galaxy A123052";
const char* password = "ghkf9583";

float duration_us, distance_cm;
// set the LCD number of columns and rows
int lcdColumns = 16;
int lcdRows = 2;
int TankID = 1;
const int led = 13;
int status;

LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);

void setup() {
  lcd.init();            // Initialize LCD
  lcd.backlight();       // Turn on LCD backlight
  Serial.begin(115200);  // Begin serial Monitor
  init_wifi();
  delay(2000);  //Allow for Wi-Fi to start
  configure_pins();
  // sendinformation();
  server_call();  //Begins the server

  //  ++bootCount;
  //  Serial.println("Boot number: " + String(bootCount));

  //   print_wakeup_reason();
}

void loop() {
  ultrasonic();
  //automatic();
  server.handleClient();
  // sendData();

  // esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);

  // Serial.println("Going to sleep now");
  // Serial.flush();
  // esp_deep_sleep_start();
}

void configure_pins() {
  //Trigger pin to output mode
  pinMode(TRIG_PIN, OUTPUT);
  //Echo pin to input mode
  pinMode(ECHO_PIN, INPUT);
  //Configure motor to start
  pinMode(motor, OUTPUT);
  //Configure LED ON
  pinMode(led_on, OUTPUT);
}

void ultrasonic() {
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  duration_us = pulseIn(ECHO_PIN, HIGH);

  distance_cm = 0.017 * duration_us;
  int tank_height = 100;
  waterheight = tank_height - distance_cm;

  // set cursor to first column, first row
  lcd.setCursor(0, 0);
  // print distance
  lcd.print("Distance in cm:");
  // set cursor to first column, second row
  lcd.setCursor(0, 1);
  lcd.print(distance_cm);
  delay(1000);
  lcd.clear();
}
void automatic() {


  if (distance_cm > 100) {

    digitalWrite(motor, HIGH);

    digitalWrite(led_on, HIGH);
    delay(500);
    digitalWrite(led_on, LOW);

  } else {
    digitalWrite(motor, LOW);
    digitalWrite(led_on, LOW);
  }
}


void manual_start() {

  Serial.println("Motor is starting!");
  digitalWrite(motor, HIGH);
  digitalWrite(led_on, HIGH);
  delay(500);
  digitalWrite(led_on, LOW);
}

void init_wifi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  delay(2000);
  Serial.print("Connecting..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(2000);
    WiFi.disconnect();
    WiFi.reconnect();
  }
  Serial.print("\n");
  Serial.println("Connected to");
  Serial.print(ssid);
  Serial.print("    ||  IP address: ");
  Serial.println(WiFi.localIP());
}

void sendData() {
  HTTPClient http;
  Serial.println(" ");
  Serial.println("Sending Reading Request");
  http.begin("http://192.168.102.215/IOT/IOT2022_Midsem_Andam/tanksystemconnect.php?TankID=" + String(TankID) + "&Reading=" + String(distance_cm));
  int httpCode = http.GET();
  String result = http.getString();
  Serial.println(result);
}

void sendinformation() {
  HTTPClient http;
  Serial.println(" ");
  Serial.println("Sending Tank Information Request");

  http.begin("http://192.168.102.215/IOT/IOT2022_Midsem_Andam/tankinformationconnect.php?Owner=AndamEmmanuela&Location=Ashesi_University&TankID=" + String(TankID));
  int httpCode = http.GET();
  String result = http.getString();
  Serial.println(result);
}

void server_call() {

  if (MDNS.begin("esp32")) {
    Serial.println("MDNS responder started");
  }
  server.begin();
  Serial.println("HTTP server started");

  server.on("/browser.html", base);
  server.on("/status/0", manual_stop);
  server.on("/status/1", automatic);
  server.on("/status/2", manual_start);
  server.on("/CurrentReading", sendreading);

  server.onNotFound(handleNotFound);
}
void handleRoot() {
  digitalWrite(led, 1);
  server.send(200, "text/plain", "Hello from Andam's Midsem Project!");
  digitalWrite(led, 0);
}
void handleNotFound() {
  digitalWrite(led, 1);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  digitalWrite(led, 0);
}
void manual_stop() {
  Serial.println("Motor has stopped!");
  digitalWrite(motor, LOW);
  digitalWrite(led_on, LOW);
}
void base() {
  server.send(200, "text/html", page);
}

void sendreading() {
  String str = String(distance_cm);  //only this is sent
  server.send(200, "text/plain", str);
}
void print_wakeup_reason() {
  esp_sleep_wakeup_cause_t wakeup_reason;

  wakeup_reason = esp_sleep_get_wakeup_cause();

  switch (wakeup_reason) {
    case ESP_SLEEP_WAKEUP_EXT0: Serial.println("Wakeup caused by external signal using RTC_IO"); break;
    case ESP_SLEEP_WAKEUP_EXT1: Serial.println("Wakeup caused by external signal using RTC_CNTL"); break;
    case ESP_SLEEP_WAKEUP_TIMER: Serial.println("Wakeup caused by timer"); break;
    case ESP_SLEEP_WAKEUP_TOUCHPAD: Serial.println("Wakeup caused by touchpad"); break;
    case ESP_SLEEP_WAKEUP_ULP: Serial.println("Wakeup caused by ULP program"); break;
    default: Serial.printf("Wakeup was not caused by deep sleep: %d\n", wakeup_reason); break;
  }
}