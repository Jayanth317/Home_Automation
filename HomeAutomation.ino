    
#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "Redmi9i";
const char* password = "qwertyuiop";

const char* mqtt_server = "52.14.168.247";

WiFiClient espClient22;
PubSubClient client(espClient22);


// Switch location on ESP32
const int FanSwitch = 17;
const int LightSwitch = 19;
const int CoolerSwitch = 16;
const int PowerSwitch = 4;

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("WiFi connected - NodeMCU IP address: ");
  Serial.println(WiFi.localIP());
}


void Callback(String topic, byte* Message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String MessageInfo;
  
  for (int i = 0; i < length; i++) {
    Serial.print((char)Message[i]);
    MessageInfo += (char)Message[i];
  }
  Serial.println();
 if(topic=="fanIot"){
      Serial.print("Changing Room Fan to ");
      if(MessageInfo == "on"){
        digitalWrite(FanSwitch, LOW);
        Serial.print("On");
      }
      else if(MessageInfo == "off"){
        digitalWrite(FanSwitch, HIGH);
        Serial.print("Off");
      }
  }
  else if(topic=="coolerIot"){
      Serial.print("Changing Room Cooler to ");
      if(MessageInfo == "on"){
        digitalWrite(CoolerSwitch, LOW);
        Serial.print("On");
      }
      else if(MessageInfo == "off"){
        digitalWrite(CoolerSwitch, HIGH);
        Serial.print("Off");
      }
  }
  else if(topic=="lightIot"){
      Serial.print("Changing Room Light to ");
      if(MessageInfo == "on"){
        digitalWrite(LightSwitch, LOW);
        Serial.print("On");
      }
      else if(MessageInfo == "off"){
        digitalWrite(LightSwitch, HIGH);
        Serial.print("Off");
      }
  }
  else if(topic=="powerIot"){
      Serial.print("Changing Room Power to ");
      if(MessageInfo == "on"){
        digitalWrite(PowerSwitch, LOW);
        Serial.print("On");
      }
      else if(MessageInfo == "off"){
        digitalWrite(PowerSwitch, HIGH);
        Serial.print("Off");
      }
  }
  Serial.println();
}


void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    
    if (client.connect("ESP8266Client22")) {
      Serial.println("connected");  
      
      client.subscribe("fanIot");
      client.subscribe("lightIot");
      client.subscribe("coolerIot");
      client.subscribe("powerIot");
  
      
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 1 second");
      delay(1000);
    }
  }
}



void setup() {
  pinMode(FanSwitch, OUTPUT);
  pinMode(LightSwitch, OUTPUT);
  pinMode(CoolerSwitch, OUTPUT);
  pinMode(PowerSwitch, OUTPUT);
  
  Serial.begin(115200);
  setup_wifi();
  
  client.subscribe("fanIot");
  client.subscribe("lightIot");
  client.subscribe("coolerIot");
  client.subscribe("powerIot");
  
  client.setServer(mqtt_server, 1883);
  client.setCallback(Callback);
  
  digitalWrite(FanSwitch, HIGH);
  digitalWrite(LightSwitch, HIGH);
  digitalWrite(CoolerSwitch, HIGH);
  digitalWrite(PowerSwitch, HIGH);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  if(!client.loop())
    client.connect("ESP8266Client22");
  }
