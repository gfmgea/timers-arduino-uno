#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 7, 6, 5, 4);

int button0 = 2; // pino que está ligado o botão 0
int button1 = 8; // pino que está ligado o botão 1
int button2 = 9; // pino que está ligado o botão 2
int Led = 13; // pino que está ligado o LED
bool trava=false; //travar estado do botão, começa com false
int uniseg, dezseg, unimin, dezmin, unihr, dezhr; // variáveis timer1
unsigned int uniseg2, dezseg2, unimin2, dezmin2; // variáveis timer0
int timer, cntx; //variáveis cnt
const byte buzzPin = 10; // pino que está ligado o buzzer transformado em buzzPin
const byte interruptPin = 2; // pino que está ligado o b0 transformado em interruptPin

void setup() {
pinMode(13,OUTPUT); // Configuração do LED como saída 
pinMode(buzzPin,OUTPUT); // Configuração do buzzer como saída
pinMode(interruptPin, INPUT_PULLUP); //configuração da interrupção em b0
attachInterrupt(digitalPinToInterrupt(interruptPin), cont, FALLING); //configuração da interrupção em b0

pinMode(button0, INPUT); // Configuração do botão como Entrada no pi
pinMode(button1, INPUT); // Configuração do botão como Entrada no pino 
pinMode(button2, INPUT); // Configuração do botão como Entrada no pi
digitalWrite(button0, HIGH); // Habilita Resistores Internos de Pull-up 
digitalWrite(button1, HIGH); // Habilita Resistores Internos de Pull-up
digitalWrite(button2, HIGH); // Habilita Resistores Internos de Pull-up

lcd.begin(16, 2); //inicia o LCD
lcd.setCursor(0,0);
lcd.print("  INTERRUPCOES ");
lcd.setCursor(0,1);
lcd.print("    FATEC-SP    ");
delay(5000);

lcd.setCursor(0,0);
lcd.print("    AUTORES    ");
lcd.setCursor(0,1);
lcd.print("GUSTAVO / JACSON");
delay(8000);
lcd.clear();



TCCR0A=(1<<WGM01);
OCR0A=0xF9; // carga inicial para estouro de 1s
TIMSK0|=(1<<OCIE0A); // habilita interrupção do TIMER0
TCCR0B|=(1<<CS01);
TCCR0B|=(1<<CS00); //prescaler para 1/64


TCCR1A = 0;
TCCR1B=0;
TCCR1B|=(1<<CS10)|(1<<CS12); //prescaler para 1024
TCNT1=0XC2F7; // carga inicial para estouro de 1s
TIMSK1 |=(1<<TOIE1); // habilita interrupção do TIMER1
}

void loop() {
  int state0 = digitalRead(button0);
  int state1 = digitalRead(button1); // Verifica o estado do pino 
  int state2 = digitalRead(button2);
  

 lcd.setCursor(0,1);
 lcd.print("Uptime= ");
 lcd.setCursor(13,1);
 lcd.print(":"); 
 lcd.setCursor(15,1);
 lcd.print(uniseg);   
 lcd.setCursor(14,1);
 lcd.print(dezseg);              
 lcd.setCursor(10,1);
 lcd.print(":");
 lcd.setCursor(12,1);
 lcd.print(unimin);
 lcd.setCursor(11,1);
 lcd.print(dezmin);
 lcd.setCursor(9,1);
 lcd.print(unihr);
 lcd.setCursor(8,1);
 lcd.print(dezhr);

 //inicialização do timer1 para Uptime
 if(uniseg==10){
      dezseg++;
      uniseg=0;}
 
  if(dezseg==6){
      unimin++;
      dezseg=0;}
  
 if(unimin==10){
      dezmin++;
      unimin=0;}
    
 if(dezmin==6){
      unihr++;
      dezmin=0;}
      
 if(unihr==10){
      dezhr++;
      unihr=0;
        }


lcd.setCursor(8,0);
lcd.print("T0=");
lcd.setCursor(11,0);
lcd.print(dezmin2);
lcd.setCursor(12,0);
lcd.print(unimin2);
lcd.setCursor(13,0);
lcd.print(":");
lcd.setCursor(14,0);
lcd.print(dezseg2);
lcd.setCursor(15,0);
lcd.print(uniseg2);


if(state2==LOW){   //configuração do botão 2 para trava/despausa do sistema
delay(100);
trava=!trava;
}
  
if(state1==LOW){  //configuração do botão 1 para adicionar +1min
    unimin2++;
    delay(100);
  if(unimin2==10){
    unimin2=0;
    dezmin2++;
  }
   }

  
 if(trava==true){       //se a varíavel trava for true, inicializará o timer0 para contagem regressiva
  if(dezmin2!=0){       //inicialização do timer0 para contagem regressiva
  	if(unimin2==0){
      --dezmin2;
      unimin2=10;}
  }
  
  if(unimin2!=0){
  	if(dezseg2==0){
    --unimin2;
      dezseg2=6;}
  }
  
  if(dezseg2!=0){
 	 if(uniseg2==0){
   	 	--dezseg2;
    	uniseg2=10;	
     } 
  }
  if(uniseg2!=0){
    if(timer>=1000){
      --uniseg2;
      delay(500);
    }
  }
  if((unimin2==0) && (dezmin2==0) && (uniseg2==0) && (dezseg2==0)){     //ao zerar o sistema de timer0, toca buzzer 3 vezes
    	digitalWrite(buzzPin, HIGH);
    	delay(500);
    	digitalWrite(buzzPin, LOW);
    	delay(500);
        digitalWrite(buzzPin, HIGH);
    	delay(500);
    	digitalWrite(buzzPin, LOW);
    	delay(500);
        digitalWrite(buzzPin, HIGH);
    	delay(500);
    	digitalWrite(buzzPin, LOW);
    	delay(500);
  	}
 } 

 	
  
 
  


lcd.setCursor(0,0);
lcd.print("CNT=");
lcd.setCursor(5,0);
lcd.print(cntx);

  if(cntx==10){      //se a cntx (variável da interrupção CNT) chegar a 10, toca buzzer 2 vezes
    tone(buzzPin, 1500);
    delay(500);
    noTone(buzzPin);
    delay(500);
    tone(buzzPin, 1500);
    delay(500);
    noTone(buzzPin);
    delay(500);
    cntx=0;
    }


  digitalWrite(Led, HIGH);  //LED oscila a cada 100ms
  delay(100);
  digitalWrite(Led, LOW);
  delay(100);
 
 
}


ISR(TIMER1_OVF_vect)     //ISR do timer1 para uptime
{
 TCNT1=0xC2F7;
 uniseg++;
   
}

ISR(TIMER0_COMPA_vect){   //ISR do timer0 para contagem regressiva
  timer++; 
}

void cont(){     //void que é acionada a cada vez que o botão 0 é acionado
  cntx=cntx+1;
  delay(100);
}


