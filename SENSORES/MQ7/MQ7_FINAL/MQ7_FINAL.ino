void setup() {
  Serial.begin(9600);
  
}

void loop() {
  
  int adc_MQ = analogRead(A0); //Lemos la salida analógica  del MQ
  float voltaje = adc_MQ * (5.0 / 1023.0); //Convertimos la lectura en un valor de voltaje
  float Rs=1000*((5-voltaje)/voltaje);  //Calculamos Rs con un RL de 1k
  double CO=102*pow(Rs/4242.424, -1.52); // calculamos la concentración  de alcohol con la ecuación obtenida.
  //-------Enviamos los valores por el puerto serial------------
  Serial.print("adc:");
  Serial.print(adc_MQ);
  Serial.print("    voltaje:");
  Serial.print(voltaje);
  Serial.print("    Rs:");
  Serial.print(Rs);
  Serial.print("    MONOXIDO CARBONICO:");
  Serial.print(CO);
  Serial.println("PPM");
  
  Serial.print(",");
  Serial.println(CO);
  Serial.print(",");
  
  delay(100);
}