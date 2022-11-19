/*
  Simulador de Terminal de pesaje IND131/331 de la marca METLER TOLEDO.
  
  Envía el peso simulado por comunicación serial en el formato que detalla el manual
  de la IND131/331 para el modo de salida contínua estándar. Más información en la 
  página 120 del manual disponible en el siguiente enlace:
  https://www.mt.com/dam/ind/IND_PDF/2016/manuals/IND131-331_MAN_64067485_08_ES_UG.pdf#page120
  
  Para cambiar el peso se utiliza el eje vertical de un Joystick.
  Con el eje horizontal del Joystick se puede generar un peso aleatorio,
  a la izquierda generaría un peso aleatorio múltiplo de 10 y, a la derecha,
  un peso aleatorio con precisión de 2 decimales.
  
  El peso se refleja en la pantalla LCD del Shield y además se realiza el envío serial para simular ser una IND131.
  
  Proyecto en el GitHub de arturonvz (ElZizouSV en otras plataformas):
  https://github.com/arturonvz/Simulador_IND131_331_Arduino
*/

const int pinJoystick_X = A1;
const int pinJoystick_Y = A0;
const int pinJoystick_SW = 9;

String inString = ""; // String para recepción del peso vía SerialPort
int peso = 0;
unsigned long PeriodoSerial = 50; // (50) Copiando a la IND131 que envía el dato serialmente 20 veces por segundo
unsigned long time_1 = 0;
unsigned long time_2 = 0;

void setup() {
  pinMode(pinJoystick_SW, INPUT_PULLUP);
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
}

void loop() {
  //Captura de valores del Joystick
  int valJoystick_X = analogRead(pinJoystick_X);
  int valJoystick_Y = analogRead(pinJoystick_Y);
  bool valJoystick_SW = !digitalRead(pinJoystick_SW);

  if(valJoystick_Y < 270) {
    // abajo
    peso = peso - 1;
  }

  if(valJoystick_Y > 753) {
    //arriba
    peso = peso + 1;
  }
  
  // While para recibir Peso por el puerto serial:
  while (Serial.available() > 0) {
    int inChar = Serial.read();
    if (isDigit(inChar)) {
      // convert the incoming byte to a char and add it to the string:
      inString += (char)inChar;
    }
    else if(inChar == '-' && inString == ""){
      inString += (char)inChar;
    }
    // if you get a newline, print the string, then the string's value:
    if (inChar == '\n') {
      //Serial.print("Value:");
      //Serial.println(inString.toInt());
      //Serial.print("String: ");
      //Serial.println(inString);
      // clear the string for new input:
      peso = inString.toInt();
      inString = "";
    }
  }
  
  if(millis() >= time_1 + PeriodoSerial){
      Serial.write(0x02);
      Serial.write(B00101100);
      
      if(peso<0) Serial.write(B00110010);
      else Serial.write(B00110000);
      peso = abs(peso);
      
      Serial.write(B00100000);
      
      if (peso<100000) Serial.print(' ');
      if (peso<10000) Serial.print(' ');
      if (peso<1000) Serial.print(' ');
      if (peso<100) Serial.print('0');
      if (peso<10) Serial.print('0');
      Serial.print(peso);
      
      Serial.print("   000");
      
      Serial.write(0x0D);
      time_1 +=PeriodoSerial;
  }
 /*
  if(millis() >= time_2 + PeriodoLCD){
      time_2 +=PeriodoLCD;
      lcd.setCursor(0,1);
      String strPeso = "Peso: ";
      if (peso<100000) strPeso += ' ';
      if (peso<10000) strPeso += ' ';
      if (peso<1000) strPeso += ' ';
      if (peso<100) strPeso += '0';
      if (peso<10) strPeso += '0';
      strPeso += peso;
      strPeso += " Kg ▼";
      lcd.print(strPeso);
  }*/
  
  delay(10);
}
