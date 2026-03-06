#define xVektor A0
#define yVektor A1
#define button 2
#define ledPiros 3
#define ledZold 5
#define ledKek 6
#define ledJobb 7
#define ledBal 8
int xValue;
int yValue;
bool fel=false;
unsigned long start;
unsigned long felkapcsolt;
bool jatekVan=false;
int irany;
int counter=0;
int buttonVege;
int sum;

void setup() {
  pinMode(ledZold, OUTPUT);
  pinMode(ledPiros, OUTPUT);
  pinMode(ledKek, OUTPUT);
  pinMode(ledBal, OUTPUT);
  pinMode(ledJobb, OUTPUT);
  digitalWrite(ledBal,HIGH);
  digitalWrite(ledJobb,HIGH);
  pinMode(button, INPUT_PULLUP);
  
  Serial.begin(9600);
}

void loop() {
  xValue = analogRead(xVektor);
  int buttonValue=digitalRead(button);
  int randomLampa=random(7,9);
  if(jatekVan==false&& counter<=10){
    int randomIdo=random(2000,5000);
    int randomLampa=random(0,2);
    delay(randomIdo);
    if(randomLampa==0){
      digitalWrite(ledBal,LOW);
      felkapcsolt=millis();
      irany=0;
    }else {
      digitalWrite(ledJobb,LOW);
      felkapcsolt=millis();
      irany=1;
    }
    jatekVan=true;
    counter++;
  }

  if(jatekVan==true){
    if(irany==0 && xValue>540){
      digitalWrite(ledBal,HIGH);
      unsigned long reakcio=millis()-felkapcsolt;
      sum+=reakcio;
      Serial.println(reakcio);
      if(reakcio<200){
        digitalWrite(ledZold,HIGH);
        delay(200);
        digitalWrite(ledZold,LOW);
      }
      else if(reakcio>200 && reakcio < 400){
        digitalWrite(ledZold,HIGH);
        digitalWrite(ledPiros,HIGH);
        delay(200);
        digitalWrite(ledZold,LOW);
        digitalWrite(ledPiros,LOW);
      }
      else{
        digitalWrite(ledPiros,HIGH);
        delay(200);
        digitalWrite(ledPiros,LOW);
      }
      jatekVan=false;
    }
    else if(irany==1&& xValue<500){
      digitalWrite(ledJobb,HIGH);
      unsigned long reakcio=millis()-felkapcsolt;
      Serial.println(reakcio);
      sum+=reakcio;
      if(reakcio<200){
        digitalWrite(ledZold,HIGH);
        delay(200);
        digitalWrite(ledZold,LOW);
      }
      else if(reakcio>200 && reakcio < 400){
        digitalWrite(ledZold,HIGH);
        digitalWrite(ledPiros,HIGH);
        delay(200);
        digitalWrite(ledZold,LOW);
        digitalWrite(ledPiros,LOW);
      }
      else{
        digitalWrite(ledPiros,HIGH);
        delay(200);
        digitalWrite(ledPiros,LOW);
      }
      jatekVan=false;
    }
  }
  if(counter==11){
    int atlag= sum/10;
    if(atlag<200){
        digitalWrite(ledZold,HIGH);
        delay(200);
        digitalWrite(ledZold,LOW);
      }
      else if(atlag>200 && atlag < 400){
        digitalWrite(ledZold,HIGH);
        digitalWrite(ledPiros,HIGH);
        delay(200);
        digitalWrite(ledZold,LOW);
        digitalWrite(ledPiros,LOW);
      }
      else{
        digitalWrite(ledPiros,HIGH);
        delay(200);
        digitalWrite(ledPiros,LOW);
      }
    Serial.println(atlag);
    digitalWrite(ledBal,LOW);
    digitalWrite(ledJobb,LOW);
    delay(300);
    digitalWrite(ledBal,HIGH);
    digitalWrite(ledJobb,HIGH);
    delay(300);
  }
  if(buttonValue==LOW && buttonVege==HIGH){
    counter=0;
  }
  buttonVege=buttonValue;
}