#define LED_GREEN 2
#define LED_YELLOW 3
#define LED_RED 4
#define LED_BLUE 5

#define BUTTON_GREEN 7
#define BUTTON_YELLOW 8
#define BUTTON_RED 9
#define BUTTON_BLUE 10

#define SEQUENCE_SIZE 4
#define INTERVAL 1000

int light_sequence[SEQUENCE_SIZE];

void setup(){
    Serial.begin(9600);
    declarePorts();
}

void declarePorts()
{
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_BLUE, OUTPUT); 
  
  pinMode(BUTTON_GREEN,INPUT_PULLUP);
  pinMode(BUTTON_YELLOW,INPUT_PULLUP);
  pinMode(BUTTON_RED,INPUT_PULLUP);
  pinMode(BUTTON_BLUE,INPUT_PULLUP);
}



void loop(){
    Serial.begin(9600);

    /* BOTAO VERDE */
    if(digitalRead(BUTTON_GREEN) == 0){
      digitalWrite(LED_GREEN , HIGH);
    }else{
      digitalWrite(LED_GREEN , LOW);
    }

    /* BOTAO AMARELO */
    if(digitalRead(BUTTON_YELLOW) == 0){
      digitalWrite(LED_YELLOW , HIGH);
    }else{
      digitalWrite(LED_YELLOW , LOW);
    }

    /* BOTAO VERMELHO */
    if(digitalRead(BUTTON_RED) == 0){
      digitalWrite(LED_RED , HIGH);
    }else{
      digitalWrite(LED_RED , LOW);
    }
    
    /* BOTAO AZUL*/
    if(digitalRead(BUTTON_BLUE) == 0){
      digitalWrite(LED_BLUE , HIGH);
    }else{
      digitalWrite(LED_BLUE , LOW);
    }
   
}
