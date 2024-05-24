#include <LiquidCrystal_I2C.h>
#include <wire.h>

LiquidCrystal_I2C lcd_1(0x27,16,2);  

int SensorPin = A0; 
int Suelo = 0;
int state;
int flag=0; //makes sure that the serial only prints once the state


void setup() {
//pantalla
  pinMode(7, OUTPUT); 

      // Inicializar el LCD
  lcd_1.init();
  
  //Encender la luz de fondo.
  lcd_1.backlight();
  
  //Prepar display 
  lcd_1.display();
  
  lcd_1.print("Humedad");
  

  Serial.begin(9600); /* Iniciamos el puerto serie, de esta forma podemos visualizar las lecturas en el monitor serie */
  
}
void loop() {
//if some date is sent, reads it and saves in state

  int humedad = analogRead(SensorPin); 
    Serial.println(humedad);
  if(Serial.available() > 0){
  state = Serial.read();
  flag=0;
  }
//parqueo 1
if (state == '1') {
    if (humedad >= 80) /* Agreagamos una condicion de funcionamiento en base a las lecturas */
    {
        digitalWrite(7, LOW); /* Si se cumple la condicion la salida se desactiva, estado bajo */
        lcd_1.setCursor(0, 0);
        lcd_1.print("no es permitido regar");
    }
    else {
        digitalWrite(7, HIGH); /* Si no se cumple la condicion la salida se activa, estado alto */
        lcd_1.setCursor(0, 0);
        lcd_1.print("regando");
    }

    int Suelo = analogRead(SensorPin); // asignar los valores //
    Suelo = constrain(Suelo, 0, 876);  /* Rango de medición */
    Suelo = map(Suelo, 0, 876, 0, 100); /* valores porcentuales dentro del rango */

    lcd_1.setCursor(0, 1); // Posición inicial del texto
    lcd_1.print(Suelo);    // Mostrar números finales
    lcd_1.print("%");      // imprimir el símbolo de porcentaje al final

    delay(1000); // Espere segundos 0,1

    lcd_1.setCursor(0, 1); // Limpiar la segunda línea
    lcd_1.print("        ");

    delay(1);
if(flag == 0){
  lcd_1.setCursor(0, 0);
  lcd_1.print("seleccione una opcion");
 flag=1;
}
}


else if (state == '2') {
digitalWrite(7, LOW);
if(flag == 0){
 lcd_1.setCursor(0, 0);
 lcd_1.print("seleccione una opcion");

flag=1;
}
}
}
