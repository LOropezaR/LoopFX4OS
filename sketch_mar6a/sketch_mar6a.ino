//definimos puertos
//entradas
#define entrada1 1
#define entrada2 2
#define entrada3 3
//salidas
#define sal1 4
#define sal2 5
#define sal3 6
#define clk 7 //salida de reloj

//definimos variables globales
/*
bool avanza = false; 
bool retrocede = false;
*/
bool inc[3]={false, false, false};//inicializa puertos en cero
bool tst[3][3]={{false, false, false},{ false, true, true},{ true, false, true}};//definimos los puertos que se usarán
bool band[3];//variable para gusrdar los puertos a usar -- cambiar nombre a carry o algo parecido
int num=1; //puerto numero de banco
// clase ------------------------------------------------------------------------------------------------------
//clase a usar para guardar los datos

//funciones ---------------------------------------------------------------------------------------------------
//funcion para activar o desactivar salidas del arduino
void setout(bool entradas[3]){
  //puerto 1
if (entradas[1] == true){
  digitalWrite(sal1, HIGH); //prende salida 1
    delay(50);
    digitalWrite(clk, HIGH); //prende clk
    delay(50);
    digitalWrite(clk, LOW); //apaga clk
    delay(50);
} else {
  digitalWrite(sal1, LOW); //apaga salida 1
    delay(50);
    digitalWrite(clk, HIGH);//prende clk
    delay(50);
    digitalWrite(clk, LOW); //apaga clk
    delay(50);
}
//repetimos con las demás salidas
if(entradas[2] == true){
  digitalWrite(sal2, HIGH);
    delay(50);
    digitalWrite(clk, HIGH);
    delay(50);
    digitalWrite(clk, LOW);
    delay(50);

} else {
  digitalWrite(sal2, LOW);
    delay(50);
    digitalWrite(clk, HIGH);
    delay(50);
    digitalWrite(clk, LOW);
    delay(50);

}
if(entradas[3] == true){
  digitalWrite(sal3, HIGH);
    delay(50);
    digitalWrite(clk, HIGH);
    delay(50);
    digitalWrite(clk, LOW);
    delay(50);

} else {
  digitalWrite(sal3, LOW);
    delay(50);
    digitalWrite(clk, HIGH);
    delay(50);
    digitalWrite(clk, LOW);
    delay(50);

}

return;
}



void espera(){
  /*esta funcion nos permite hacer un proceso de espera para evitar "un doble toque en falso"*/
  while(digitalRead(entrada1) == LOW || digitalRead(entrada2) == LOW){
    delay(50);

  }
  return;
}


//------------------------------------------------------------------------------------------------------------------
void setup() {
  // put your setup code here, to run once:
  pinMode(entrada1, INPUT_PULLUP);
  pinMode(entrada2, INPUT_PULLUP);
  pinMode(entrada3, INPUT_PULLUP);
  setout(inc);/*posteriormente se cambiará para que inicialice en el banco en el que se dejó anteriormente
  de momento solo incializará en ceros*/
  num = 1;
}

void loop() {
  if (digitalRead(entrada1) == LOW && digitalRead(entrada2) == LOW){
    espera();/*por si a caso xd*/
  }
  if (digitalRead(entrada1) == LOW ) {   // LOW = botón presionado
    //avanza = true;
    num++; //aumenta en uno nuestra variable de indicacion de banco
    if(num >= 4){
      num = 1; //si num sobrepasa 3, regresamos al banco 1
    }
    
    for(int i = 1; i < 3 ; i++){
      band[i]=tst[i][num]; //igualamos una variable a la otra en una fila/banco en concreto/banco
    }
    setout(band);//le pasamos nuestro vector a la funcion

    espera();//evita que se realice más de un proceso al dejar este en espera
  }
  
  if (digitalRead(entrada2) == LOW)  {   // LOW = botón presionado
   //avanza = false;
    num--; //reduce en uno nuestra variable de indicacion de banco
    if(num <= 0){
      num = 3; //si num queda debajo de 1, regresamos al banco 3
    }

    for(int i = 1; i < 3 ; i++){
      band[i]=tst[i][num]; //igualamos una variable a la otra en una fila/banco en concreto/banco
    }
    setout(band);//le pasamos nuestro vector a la funcion

    espera();//evita que se realice más de un proceso al dejar este en espera
  }

}