//MAMADA DE CODIGO TODO ESTUDIPO
#define entrada1 2
#define entrada2 3
#define entrada3 4
//salidas
#define sal1 5
#define sal2 6
#define sal3 7
#define clk 8 //salida de reloj
int bnk = 0;
int mat[3][3]= {{1,1,1},{0,1,1},{0,0,1}};


void setup() 
{
  pinMode(entrada1, INPUT);
  pinMode(entrada2, INPUT);
  pinMode(entrada3, INPUT);
  pinMode(sal1, OUTPUT);
  pinMode(sal2, OUTPUT);
  pinMode(sal3, OUTPUT);
  pinMode(clk, OUTPUT);
}
void espera(){
  /*esta funcion nos permite hacer un proceso de espera para evitar "un doble toque en falso"*/
  while(digitalRead(entrada1) == LOW){
    delay(50);

  }
}

  void sett(int pedalito, int matr[3][3])
  {
    for(int i = 0; i<=2;i++)
    {
      int a;
        if(matr[pedalito][i] == 1)
        {
          a=0;
          a=a+i;
          digitalWrite(a, HIGH); //prende salida penesito
          delay(50);
          digitalWrite(clk, HIGH); //prende clk
          delay(50);
          digitalWrite(clk, LOW); //apaga clk
          delay(50);
        } else 
        {
          a=5;
          a=a+i;
          digitalWrite(a, LOW); //prende salida penesito
          delay(50);
          digitalWrite(clk, HIGH); //prende clk
          delay(50);
          digitalWrite(clk, LOW); //apaga clk
          delay(50);
        }
    }
    return;
  }

void loop()
{
  
  if(digitalRead(entrada1) == HIGH){
  bnk++;
  if(bnk>3)
  bnk=0;
  sett(bnk,mat);
  while(digitalRead(entrada1) == HIGH)
  espera();
  } else if(digitalRead(entrada2) == HIGH){
  bnk--;
  if(bnk<0)
  bnk=2;
  sett(bnk,mat);
  while(digitalRead(entrada2) == HIGH)
  espera();
  }

}