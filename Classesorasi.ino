/**
 * @file Classesorasi.ino
 * @author Diego Abarca Robles y Luis Oropeza (no se como te llames la neta)
 * @brief Programa de prueba del primer prototipo de Master FX4OS donde tres configuraciones pre-hechas del orden de activación y desactivación de efectos de guitarra.
 * @version 0.1
 * @date 2026-08-26
 * 
 * @copyright Copyright (c) 2026
 * 
 */
//entradas de señales digitales
#define entrada1 2
#define entrada2 3
#define entrada3 4
//salidas de señales digitales
#define sal1 5
#define sal2 6
#define sal3 7
#define clk 8 //salida de reloj
const unsigned long bounce = 50; //tiempo de rebote

class Bank //Clase de banco de configuraciones
{
  private:
  int set[3];
  public:
  Bank(int p1, int p2, int p3)
  {
    this->set[0] = p1;
    this->set[1] = p2;
    this->set[2] = p3;
  }
  
  void begin()
  {
    pinMode(sal1, OUTPUT);
    pinMode(sal2, OUTPUT);
    pinMode(sal3, OUTPUT);
  }
  
  void sett()
  {
    for(int i=0; i<3; i++)
    {
      int pinOutput = sal1 + i;
      digitalWrite(pinOutput, this->set[i] ? HIGH : LOW);
      delayMicroseconds(10);
      digitalWrite(clk, HIGH);
      delayMicroseconds(10);
      digitalWrite(clk, LOW);
      delayMicroseconds(10);
    }
  }
};

Bank bnk[3] = { //Banco creado para la prueba
  Bank(1,1,1),
  Bank(0,1,1),
  Bank(0,0,1),
};

int idbnk = 0;

bool estadoAnterior1 = LOW;
bool estadoAnterior2 = LOW;

unsigned long tiempoRebote = 0;

void setup() 
{
  pinMode(entrada1, INPUT);
  pinMode(entrada2, INPUT);
  pinMode(entrada3, INPUT);
  pinMode(clk, OUTPUT);

  for(int i = 0; i < 3; i++)
  {
    bnk[i].begin();
  }
  
  bnk[idbnk].sett();
}

void loop() 
{
  bool lectura1 = digitalRead(entrada1);
  bool lectura2 = digitalRead(entrada2);
  
  unsigned long tiempoActual = millis();
  
  if((tiempoActual - tiempoRebote) > bounce)
  {
    if(lectura1 == HIGH && estadoAnterior1 == LOW)
    {
      idbnk++;
      if(idbnk >= 3) idbnk = 0;
      bnk[idbnk].sett();
      tiempoRebote = tiempoActual;
    }

    if(lectura2 == HIGH && estadoAnterior2 == LOW)
    {
      idbnk--;
      if(idbnk < 0) idbnk = 2;
      bnk[idbnk].sett();
      tiempoRebote = tiempoActual;
    }
  }
  estadoAnterior1 = lectura1;
  estadoAnterior2 = lectura2;
}
