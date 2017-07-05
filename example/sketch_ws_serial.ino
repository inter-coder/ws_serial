#include <ws_serial.h>
ws_serial ws;

const char *ssid = "ESPap";
const char *password = "thereisnospoon";
int x=0;
void setup() {
  Serial.begin(9600);
  delay(1000);
  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.println("AP started");
  ws.init(80);
  ws.begin();//open html://192.168.4.1/
}

void loop() {
  delay(2000);
  Serial.println(x);  
  ws.println("Loop: "+(String)x);
  x++;
}
