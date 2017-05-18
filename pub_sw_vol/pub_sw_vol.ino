#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#define VOL A0
#define SW D0
#define RED D1
#define GREEN D2
#define BLUE D3

// Update these with values suitable for your network.
const char* ssid = "TOPPY@6s";
const char* password = "qwerty";
const char* mqtt_server = "161.246.38.29";

WiFiClient espClient;
PubSubClient client(espClient);

long count = 0;
long lastMsg = 0;
char destinationTopic[]   = "doikum";

void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    String clientId = "IoT-Workshop-";
    clientId += String(random(0xffff), HEX);
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish(destinationTopic, "hello, world");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(1000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  pinMode(VOL, INPUT);
  pinMode(SW, INPUT);
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
}

void loop() {
  String buffer = "";
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  int vol = analogRead(VOL);
  int sw = digitalRead(SW);

  buffer.concat("Value = ");
  buffer.concat(vol);
  buffer.concat(" and Button = ");
  buffer.concat(sw);
  Serial.print("Publishing... : ");
  Serial.println(buffer);
  client.publish(destinationTopic, buffer.c_str());
  delay(2000);
}

