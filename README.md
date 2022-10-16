# Simulador_IND131_331_Joystick
Simulador de Terminal de pesaje IND131/331 de la marca METLER TOLEDO con Arduino y un Joystick.
  
  Envía el peso simulado por comunicación serial en el formato que detalla el manual
  de la IND131/331 para el modo de salida contínua estándar. Más información en la 
  página 120 del manual disponible en el siguiente enlace:
  https://www.mt.com/dam/ind/IND_PDF/2016/manuals/IND131-331_MAN_64067485_08_ES_UG.pdf#page120
  
  Para cambiar el peso se utiliza el eje vertical de un Joystick.
  Con el eje horizontal del Joystick se puede generar un peso aleatorio,
  a la izquierda generaría un peso aleatorio múltiplo de 10 y, a la derecha,
  un peso aleatorio con precisión de 2 decimales.
  
  El peso se refleja en la pantalla LCD del Shield y además se realiza el envío serial para simular ser una IND131.
