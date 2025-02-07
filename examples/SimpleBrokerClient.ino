#include <TinyMqtt.h>   // https://github.com/hsaturn/TinyMqtt

const char *ssid     = "";
const char *password = "";

std::string sentTopic="data";
std::string receivedTopic="command";
MqttBroker broker(1883);

MqttClient client(&broker);

void receivedMessage(const MqttClient* source, const Topic& topic, const char* payload, size_t length)
{ 
  Serial << endl << "Received message on topic " << receivedTopic.c_str() << " with payload " << payload << endl; 
 // Serial << endl << "Received message on topic " << sentTopic.c_str() << " with payload " << payload << endl;
  }

void setup()
{
  Serial.begin(115200);
  delay(500);
  Serial << "Clients with wifi " << endl;

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {   Serial << '-'; delay(500); }

  Serial << "Connected to " << ssid << "IP address: " << WiFi.localIP() << endl;

  broker.begin();

  // ============= Client Subscribe ================
  client.setCallback(receivedMessage);
  client.subscribe(receivedTopic);
  //client.subscribe(sentTopic);
}

void loop()
{
  broker.loop();  // Don't forget to add loop for every broker and clients
  client.loop();
  delay(10000);
  
  // ============= Client Publish ================
    std::string sentPayload = "Publishing....";
    client.publish(sentTopic, sentPayload);
    Serial << "Client " << sentPayload.c_str() << endl;

    client.publish(sentTopic, std::string(String(millis()).c_str()));
    Serial << "Client published to topic " << sentTopic.c_str() << " with payload " << std::string(String(millis()).c_str()) << endl;
    
}
