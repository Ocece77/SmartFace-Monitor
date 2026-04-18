int trigPin = 5;
int echoPin = 3;
int LEDR = 9;
int LEDG = 10;
int LEDB = 11;

long time;
float distance;

char serData;

void setup()
{
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(LEDR, OUTPUT);
  pinMode(LEDG, OUTPUT);
  pinMode(LEDB, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  if(Serial.available()>0){
   serData = Serial.read();
  }
  // Envoi de l'impulsion ultrason
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Lecture du temps de retour
  time = pulseIn(echoPin, HIGH);

  // Calcul de la distance en cm
  distance = time * 0.0343 / 2;

  // Limiter la distance max pour l'effet de couleur
  if (distance > 60) {
    distance = 60;
  }
  if (distance < 0) {
    distance = 0;
  }
  int redValue = map(distance, 45, 60, 255,0 );
  int greenValue = map(distance, 45, 60, 0, 255);
   if (distance < 45) {
    analogWrite(LEDR, 255);
    analogWrite(LEDG, 0);
    analogWrite(LEDB, 0); 
    Serial.println('1');
   } else { 
   // Plus on est proche de 0, plus c'est vert
    analogWrite(LEDR, redValue);
    analogWrite(LEDG, greenValue);
    analogWrite(LEDB, 0);
    Serial.println('0');

   }
  
  
  

  delay(100);
}