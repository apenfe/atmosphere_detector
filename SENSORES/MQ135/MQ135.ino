int MQ135 = 2;

void setup() { 
  Serial.begin(9600);
  pinMode(MQ135, INPUT);
}


void loop() {
  
  boolean mq_estado = digitalRead(MQ135);//Leemos el sensor
  if(MQ135) //si la salida del sensor es 1
  {
    Serial.println("Sin presencia de alcohol");
  }
  else //si la salida del sensor es 0
  {
    Serial.println("Alcohol detectado");
  }
  delay(100); 
}