const int waterSensorPin = 34;   
const int rainSensorPin  = 35;   
const int in1Pin   = 7;   
const int in2Pin   = 8;   
const int enablePin = 9;   
const int relayPin = 10;   
const int limitSwitchPin = 11;   
const int manualSwitchPin = 12;   
const int buzzerPin = 13;   
const int waterThreshold = 100;    
const int rainThreshold  = 150;    
void setup() { 
Serial.begin(9600); 
pinMode(in1Pin, OUTPUT); 
pinMode(in2Pin, OUTPUT); 
pinMode(enablePin, OUTPUT); 
pinMode(relayPin, OUTPUT); 
pinMode(buzzerPin, OUTPUT); 
47 
pinMode(limitSwitchPin, INPUT_PULLUP); 
pinMode(manualSwitchPin, INPUT_PULLUP); 
digitalWrite(in1Pin, LOW); 
digitalWrite(in2Pin, LOW); 
analogWrite(enablePin, 0); 
digitalWrite(relayPin, LOW); 
} 
void loop() { 
int waterLevel = analogRead(waterSensorPin); 
int rainLevel  = analogRead(rainSensorPin); 
bool limitReached = digitalRead(limitSwitchPin) == LOW;   
bool manualOverride = digitalRead(manualSwitchPin) == LOW;  
Serial.print("Water Level: "); 
Serial.print(waterLevel); 
Serial.print(" | Rain: "); 
Serial.println(rainLevel); 
bool floodRisk = (waterLevel > waterThreshold || rainLevel > 
rainThreshold); 
if (manualOverride) { 
liftHouse(); 
Serial.println("Manual Override: Lifting..."); 
48 
49 
 
  } else if (floodRisk && !limitReached) { 
    liftHouse(); 
    Serial.println("Flood Risk Detected: Lifting house..."); 
  } else { 
    lowerHouse(); 
    Serial.println("Safe: Lowering house..."); 
  } 
 
  if (floodRisk) { 
    digitalWrite(buzzerPin, HIGH); 
  } else { 
    digitalWrite(buzzerPin, LOW); 
  } 
  delay(1000); 
} 
 
void liftHouse() { 
  digitalWrite(in1Pin, HIGH); 
  digitalWrite(in2Pin, LOW); 
  analogWrite(enablePin, 255);   
  digitalWrite(relayPin, HIGH);  
} 
void lowerHouse() { 
  digitalWrite(in1Pin, LOW); 
  digitalWrite(in2Pin, HIGH); 
  analogWrite(enablePin, 255);   
digitalWrite(relayPin, LOW);   
}
