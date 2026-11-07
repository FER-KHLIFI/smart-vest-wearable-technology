#include <WiFi.h>
#include <PubSubClient.h>
#include <DHTesp.h>

const int PIN_DHT=15, PIN_PULSE=34, PIN_BUZZER=18, PIN_GREEN=19, PIN_RED=21;
const char* MQTT_HOST="broker.hivemq.com";
const char* MQTT_TOPIC="demo/smartvest/engineering2026/telemetry";
WiFiClient net;
PubSubClient mqtt(net);
DHTesp dht;
unsigned long lastPublish=0;


void reconnectMQTT() {
  if (mqtt.connected()) return;

  Serial.print("Connexion MQTT... ");

  String clientId = "smartvest-demo-" +
                    String((uint32_t)ESP.getEfuseMac(), HEX);

  if (mqtt.connect(clientId.c_str())) {
    Serial.println("MQTT CONNECTE !");
  } else {
    Serial.print("ECHEC MQTT, code = ");
    Serial.println(mqtt.state());
  }
}

void setup(){
  Serial.begin(115200);
  pinMode(PIN_BUZZER,OUTPUT);pinMode(PIN_GREEN,OUTPUT);pinMode(PIN_RED,OUTPUT);
  dht.setup(PIN_DHT,DHTesp::DHT22);
  WiFi.begin("Wokwi-GUEST","",6);
  Serial.print("WiFi");
  unsigned long start=millis();
  while(WiFi.status()!=WL_CONNECTED && millis()-start<12000){delay(250);Serial.print(".");}
  Serial.println();
  mqtt.setServer(MQTT_HOST,1883);
}
void loop(){
  mqtt.loop();
  if(millis()-lastPublish<2000)return;
  lastPublish=millis();
  TempAndHumidity th=dht.getTempAndHumidity();
  int raw=analogRead(PIN_PULSE);
  int bpm=map(raw,0,4095,50,180); // SIMULATION, not real BPM measurement
  bool valid=!isnan(th.temperature);
  bool alert=(bpm>140)||(valid&&(th.temperature<10||th.temperature>35));
  digitalWrite(PIN_RED,alert);digitalWrite(PIN_GREEN,!alert);
  if(alert)tone(PIN_BUZZER,2000,350);else noTone(PIN_BUZZER);
  String payload="{\"bpm_simule\":"+String(bpm)+",\"temperature_ambiante\":"+(valid?String(th.temperature,1):"null")+",\"alerte\":"+(alert?"true":"false")+"}";
  Serial.println(payload);
  
if (WiFi.status() == WL_CONNECTED) {
  reconnectMQTT();

  if (mqtt.connected()) {
    bool sent = mqtt.publish(MQTT_TOPIC, payload.c_str());

    if (sent) {
      Serial.println("MQTT: PUBLICATION OK");
    } else {
      Serial.println("MQTT: ECHEC PUBLICATION");
    }
  } else {
    Serial.println("MQTT: NON CONNECTE");
  }
} else {
  Serial.println("WiFi: NON CONNECTE");
}
}

