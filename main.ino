#include <LiquidCrystal.h>
#include <DHT.h>

#define DHTPIN A2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int mode=0;

void setup() {
  lcd.begin(16, 1);
  dht.begin();
  pinMode(6,OUTPUT);  
  pinMode(7,OUTPUT);  
  pinMode(8,OUTPUT);  
  pinMode(9,OUTPUT);  
  pinMode(10,OUTPUT); 
  pinMode(13,OUTPUT); 
  pinMode(18,OUTPUT); 
  pinMode(19,INPUT);  
  pinMode(A1,INPUT);  
  pinMode(A3,INPUT);  
}

void displayTemperature(){
  float temperature = dht.readTemperature();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperature);
  lcd.print(" C ");
    
  if(temperature >= 10 && temperature <= 18) {
    digitalWrite(6,HIGH);
    digitalWrite(7,LOW);
    digitalWrite(13,LOW);
  }
  else if(temperature >= 19 && temperature <= 21){
    digitalWrite(6,LOW);
    digitalWrite(7,HIGH);
    digitalWrite(13,LOW);
  }
  else if (temperature>=22){
    digitalWrite(6,LOW);
    digitalWrite(7,LOW);
    digitalWrite(13,HIGH);
  }
}

void resetStates(){
  digitalWrite(18,LOW);
  digitalWrite(9,LOW);
  digitalWrite(6,LOW);
  digitalWrite(7,LOW);
  digitalWrite(13,LOW); 
  digitalWrite(10, LOW);
  digitalWrite(8, LOW);
  lcd.clear();
}

void displayHumidity(){
  int humidity = dht.readHumidity();
  lcd.setCursor(0, 0);
  lcd.print("Humidite: ");
  lcd.print(humidity);
  lcd.print(" %");  
  
  if(humidity >= 40 && humidity <= 70) {
    digitalWrite(18,HIGH);
    digitalWrite(9,LOW);
  }
  else{
    digitalWrite(18,LOW);
    digitalWrite(9,HIGH);
  }  
}

void displayBrightness(){
  int brightness = analogRead(A1);
  lcd.setCursor(0, 0);
  lcd.print("Luminosite: ");
  lcd.print(brightness);
  lcd.print(" %");  
}

void reverseRadar(){
  digitalWrite(10, LOW);
  delayMicroseconds(2);
  digitalWrite(10, HIGH);
  delayMicroseconds(10);
  digitalWrite(10, LOW);
  
  long duration = pulseIn(A3, HIGH);
  int distance = duration * 0.034 / 2;
  
  lcd.setCursor(0, 0);
  lcd.clear();
  lcd.print("Distance: ");
  lcd.print(distance);

  if (distance<10){
    digitalWrite(8, HIGH);
    delay(20);
    digitalWrite(8, LOW);
    delay(50);    
  }
  else if (distance>=10 &&distance <=30){
    digitalWrite(8, HIGH);
    delay(40);
    digitalWrite(8, LOW);
    delay(200);    
  }
  else if (distance>=31 &&distance <=100){
    digitalWrite(8, HIGH);
    delay(20);
    digitalWrite(8, LOW);
    delay(2000);     
  }
  distance=0;
}

void loop() {
  switch (mode){
      case 0:
          displayTemperature();
          break;
      case 1
          displayHumidity();
          break;
      case 2:
          displayBrightness();
          break;
      case 3:
          reverseRadar();
          break;
      default:
          break;
}

    if(digitalRead(19)==HIGH) {
        mode++;
    if(mode > 3){
        mode = 0;
    }
    resetStates();
    delay(200);
    }
}