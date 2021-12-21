#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
BlynkTimer timer;

char auth[] = "rere8rI0QqPoKc2JqFKiJPgeAGqZEinC";
const char* ssid = "VNPT - BAY";
const char* password =  "bay12345";
int value,real_value;

BLYNK_WRITE(A0){
  int value = param.asInt();
  digitalWrite(34, value);
}

void sendSensor()
{
  for(int i=0;i<=9;i++){
    real_value+=analogRead(34);
  }
  value=real_value/40;
  int percent = map(value, 350, 1023, 0, 100);                                             
  percent=100-percent; 
  int t = percent; 
  Blynk.virtualWrite(V0, t);
}


void setup() {
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
  // Code sensor
  pinMode(5,INPUT_PULLUP); 
  Blynk.begin(auth, ssid, password, IPAddress(192,168,1,5), 8080);
  timer.setInterval(1000L, sendSensor);
}
 
void loop() {
   Blynk.run();
   timer.run();
  Serial.print("Value analog: ");
  Serial.println(value);
  delay(700);
  real_value=0;
  }
