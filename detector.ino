#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2

#define LOGO16_GLCD_HEIGHT 16
#define LOGO16_GLCD_WIDTH 16
static const unsigned char PROGMEM logo16_glcd_bmp[] =
{ B00000000, B11000000,
B00000001, B11000000,
B00000001, B11000000,
B00000011, B11100000,
B11110011, B11100000,
B11111110, B11111000,
B01111110, B11111111,
B00110011, B10011111,
B00011111, B11111100,
B00001101, B01110000,
B00011011, B10100000,
B00111111, B11100000,
B00111111, B11110000,
B01111100, B11110000,
B01110000, B01110000,
B00000000, B00110000 };

#if (SSD1306_LCDHEIGHT != 32)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

int MQ135 = 7;
int i;
double AB;
double CD ;
double EF ;
double GH;

void beep(unsigned char pausa){
  analogWrite(6, 20);
  delay(pausa); // Espera
  analogWrite(6, 0); // Apaga
  delay(pausa); } // Espera

void Color(int R, int G, int B){
  analogWrite(9 , R) ; // Red - Rojo
  analogWrite(10, G) ; // Green - Verde
  analogWrite(11, B) ;} // Blue - Azul

//--------------------SETUP------------------------------------------

void setup(){

    pinMode(MQ135, INPUT);
     {for (int i =9 ; i<12 ; i++)
    pinMode(i, OUTPUT);}

{ display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // initialize the I2C addr 0x3C
display.display(); // init done
delay(2000);
display.clearDisplay(); // Clear the buffer.

  beep(50);
  Color(255 ,0 ,0) ; //AZUL
  delay(100);
  beep(50);
  Color(0,255 ,0) ; //VERDE
delay(100);
beep(50);
Color(0 ,0 ,255) ; //ROJO
delay(100);
Color(0,0,0);
delay(500);
beep(200);

display.setTextSize(1);
display.setTextColor(WHITE);
display.setCursor(0,0);
display.println("SOLAS XI-1/7 ");
display.print("I.P.M.P.M.");display.println(" APF");
display.display();
delay(2000);
display.clearDisplay();

if ( ((analogRead(A1) * (5.0 / 1023.0))>= 0.5)||((analogRead(A0) * (5.0 / 1023.0))>= 0.5)){

    for (int i=0; i <= 100; i++){
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(0,0);
      display.print("CALENTANDO... ");
      display.println(" ");
      display.setTextSize(2);
      display.print(i); display.println(" %");
      display.display();
      delay(9000);
      display.clearDisplay();
    }
  
    if ( ((analogRead(A1) * (5.0 / 1023.0))>= 0.5)||((analogRead(A0) * (5.0 / 1023.0))>= 0.5)){
          while(1){
          display.setTextSize(2);
          display.setTextColor(WHITE);
          display.setCursor(0,0);
          display.println("ERROR 001 ");
          display.println("RESET ");
          display.display();}
    }
}
 
for (int i=0; i <= 100; i++){
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(0,0);
      display.print("CALIBRANDO... ");
      display.println(" ");
      display.setTextSize(2);
      display.print(i); display.println(" %");
      display.display();
      delay(200);
      display.clearDisplay();
}
}
  
AB = 3000/(5-(analogRead(A1) * (5.0 / 1023.0)));
CD = -(AB*(analogRead(A1) * (5.0 / 1023.0)));
EF = 10000/(5-(analogRead(A0) * (5.0 / 1023.0)));
GH = -(EF*(analogRead(A0) * (5.0 / 1023.0)));}

//--------------------------------------LOOP-----------------------------------------------------------------------------------

void loop() {
    Color(0,255 ,0) ;
    delay(70);
    Color(0 ,0 ,0) ;
    int MQ7 = analogRead(A1); //Lemos la salida analógica del MQ7
    int MQ9 = analogRead(A0); //Lemos la salida analógica del MQ9
//--------------MQ7-------------------------------------------------------------------------------------------------------------
    float voltajeMQ7 = MQ7 * (5.0 / 1023.0); //Convertimos la lectura en un valor de voltaje
    double CO=(AB*(voltajeMQ7))+(CD);
  
    if (CO < 0){
        CO = 0;
    }
//--------------MQ9-------------------------------------------------------------------------------------------------------------
    float voltajeMQ9 = MQ9 * (5.0 / 1023.0); //Convertimos la lectura en un valor de voltaje
    double METANO=(EF*(voltajeMQ9))+(GH);
  
    if (METANO < 1){
        METANO = 0;
    }
//--------------MQ135---------------------------------------------------------------------------------------------------------
    boolean ESTADOMQ135 = digitalRead(MQ135);//Leemos el sensor
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    display.println("_GAS LEVEL_");
    display.print("LGP: ");display.println(METANO);
    display.print("CO: ");display.println(CO);
    display.print("POLLUTION: ");display.print(ESTADOMQ135);display.println("(1F)(0T)");
    display.display();
    delay(500);
    display.clearDisplay();
  
    if (ESTADOMQ135 == 0){
        beep(100);
        display.setTextSize(2);
        display.setTextColor(WHITE);
        display.setCursor(0,0);
        display.println("_POLLUTION_");
        display.print(ESTADOMQ135);
        display.display();
        display.clearDisplay();
      
            for (int i=0; i <= 50; i++){
                Color(0 ,0 ,255) ; //ROJO
                delay(100);
                Color(0 ,0 ,0) ;
                beep(50);
            }
    }
  
    else if ((CO > 200)||(METANO > 600)){
        display.setTextSize(1);
        display.setTextColor(WHITE);
        display.setCursor(0,0);
        display.println("_ALARM_");
        display.print(CO);display.println(" LGP or CO ");
        display.display();
        display.clearDisplay();
      
        for (int i=0; i <= 50; i++){
            Color(11,225 ,242) ; //AMARILLO
            delay(30);
            beep(10);
            Color(0 ,0 ,0) ;
            delay(30);
            beep(10);
        }
      
        beep(200);
    }
}

