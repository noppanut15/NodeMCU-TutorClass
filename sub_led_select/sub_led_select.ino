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

char clientID[15];
char destinationTopic[]   = "doikum";

void callback(char* topic, byte* payload, unsigned int length) {
  String payloadStr = String();
  String topicStr = String(topic);
  
  // Convert byte to String
  for (int i = 0; i < length; i++) {
    payloadStr += (char)payload[i];
  }
  
  Serial.print("Message arrived [");
  Serial.print(topicStr);
  Serial.print("] : ");
  Serial.println(payloadStr);

  if(payloadStr == "red"){
    red();
  }
  else if(payloadStr == "green"){
    green();
  }
  else if(payloadStr == "blue"){
    blue();
  }

}

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
      // Subscribing...
      client.subscribe(destinationTopic);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(1000);
    }
  }
}

void red(){
  digitalWrite(RED, HIGH);
  digitalWrite(GREEN, LOW);
  digitalWrite(BLUE, LOW);
}

void green(){
  digitalWrite(RED, LOW);
  digitalWrite(GREEN, HIGH);
  digitalWrite(BLUE, LOW);
}
void blue(){
  digitalWrite(RED, LOW);
  digitalWrite(GREEN, LOW);
  digitalWrite(BLUE, HIGH);
}

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  pinMode(VOL, INPUT);
  pinMode(SW, INPUT);
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}
