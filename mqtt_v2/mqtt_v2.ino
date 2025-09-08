#include <WiFi.h>
#include <PubSubClient.h>
#include <M5Core2.h>   // M5Core2 display, buttons, power, etc.


const char *ssid       = "wificlazbloomg";  
const char *password   = "656765011316Sham";      


const char *mqtt_broker   = "broker.emqx.io";
const char *mqtt_topic    = "uat/profprater";
const char *mqtt_username = "emqx";
const char *mqtt_password = "public";
const int   mqtt_port     = 1883;

WiFiClient   espClient;
PubSubClient mqtt_client(espClient);


volatile unsigned long messageCount = 0;
String lastMessage = "";
unsigned long lastRedraw = 0;

void drawStatus(const char* line1, const char* line2 = "") {
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(10, 10);
  M5.Lcd.setTextSize(2);
  M5.Lcd.setTextColor(WHITE, BLACK);
  M5.Lcd.println(line1);
  if (line2 && line2[0]) M5.Lcd.println(line2);
  M5.Lcd.println();
  M5.Lcd.printf("WiFi:   %s\n", (WiFi.isConnected() ? "Connected" : "Not connected"));
  M5.Lcd.printf("Broker: %s:%d\n", mqtt_broker, mqtt_port);
  M5.Lcd.printf("Topic:  %s\n", mqtt_topic);
  M5.Lcd.println();
  M5.Lcd.printf("Total messages: %lu\n", messageCount);
  M5.Lcd.println("-----------------------------");
  if (lastMessage.length()) {
    M5.Lcd.println("Last message:");
    M5.Lcd.println(lastMessage);
  }
}

void drawMessage() {
  // Redraw only the lower portion to avoid flicker
  M5.Lcd.fillRect(0, 110, M5.Lcd.width(), M5.Lcd.height()-110, BLACK);
  M5.Lcd.setCursor(10, 120);
  M5.Lcd.setTextSize(2);
  M5.Lcd.setTextColor(WHITE, BLACK);
  M5.Lcd.printf("Total messages: %lu\n", messageCount);
  M5.Lcd.println("-----------------------------");
  M5.Lcd.println("Last message:");
  M5.Lcd.println(lastMessage);
}


void connectToWiFi() {
  drawStatus("Connecting to WiFi...");
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi");
  drawStatus("WiFi connected");
}

void mqttCallback(char *topic, byte *payload, unsigned int length) {
  // Convert payload to String (not null-terminated by default)
  String msg;
  msg.reserve(length);
  for (unsigned int i = 0; i < length; i++) msg += (char)payload[i];

  Serial.print("Message received on topic: ");
  Serial.println(topic);
  Serial.print("Message: ");
  Serial.println(msg);
  Serial.println("---------------------");

  lastMessage = msg;
  messageCount++;
  drawMessage();   // update screen with new count + message
}

void connectToMQTT() {
  while (!mqtt_client.connected()) {
    String client_id = "esp32-client-" + String(WiFi.macAddress());
    Serial.printf("Connecting to MQTT Broker as %s...\n", client_id.c_str());
    drawStatus("Connecting to MQTT...", client_id.c_str());

    if (mqtt_client.connect(client_id.c_str(), mqtt_username, mqtt_password)) {
      Serial.println("Connected to MQTT broker");
      mqtt_client.subscribe(mqtt_topic);
      mqtt_client.publish(mqtt_topic, "Hi EMQX I'm ESP32 ^^");
      drawStatus("MQTT connected");
    } else {
      Serial.print("Failed, rc=");
      Serial.print(mqtt_client.state());
      Serial.println(" try again in 5 seconds");
      drawStatus("MQTT connect failed", "Retrying in 5s...");
      delay(5000);
    }
  }
}


void setup() {
  M5.begin();                 
  M5.Lcd.setRotation(1);      
  M5.Lcd.setTextWrap(true);
  M5.Lcd.fillScreen(BLACK);

  Serial.begin(115200);

  connectToWiFi();
  mqtt_client.setServer(mqtt_broker, mqtt_port);
  mqtt_client.setKeepAlive(60);
  mqtt_client.setCallback(mqttCallback);
  connectToMQTT();
}

void loop() {
  if (!mqtt_client.connected()) {
    connectToMQTT();
  }
  mqtt_client.loop();

  // (Optional) periodic light refresh to keep status current
  if (millis() - lastRedraw > 15000) {
    drawStatus("Running...");
    lastRedraw = millis();
  }

  M5.update(); 
}
