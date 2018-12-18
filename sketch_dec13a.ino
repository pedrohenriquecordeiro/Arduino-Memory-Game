#define LED_GREEN 2
#define LED_YELLOW 3
#define LED_RED 4
#define LED_BLUE 5

#define BUTTON_GREEN 7
#define BUTTON_YELLOW 8
#define BUTTON_RED 9
#define BUTTON_BLUE 10

#define NUMBER_OF_COLORS 3

void setup(){
    Serial.begin(9600);
    declarePorts();
    int *colors = color_sorter();
    
    for(int a = 0 ; a < NUMBER_OF_COLORS ; a++){
      flashes_led(colors[a]);
    }
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

    lights_up_from_the_push_button();

}

int *color_sorter(){
  /* lê a porta analogica 0 vazia*/ 
  /* para alimentar a funcao geradora de numeros aleatorios com um valor flutuante */
  randomSeed(analogRead(0));
  
  /* aloca 10 posicoes de memoria */
  int *colors = malloc(NUMBER_OF_COLORS);
  
  if(!colors){
    return NULL;
  }else{
    /* alocacao efetuada com sucesso */
    for(int a = 0; a < NUMBER_OF_COLORS ; a++){
      /* popula as posicoes com cores aleatorias */
      colors[a] = random(LED_GREEN,LED_BLUE + 1);
    }
  }

  return colors;
}

void flashes_led(int led){
  /* mantem led acesso por 1 segundo */
  digitalWrite(led , LOW);
  delay(1000);
  digitalWrite(led , HIGH);
  delay(1000);
  digitalWrite(led , LOW);
}

void lights_up_from_the_push_button(){
  /* BOTAO VERDE */
    if(!digitalRead(BUTTON_GREEN)){
      digitalWrite(LED_GREEN , HIGH);
    }else{
      digitalWrite(LED_GREEN , LOW);
    }

    /* BOTAO AMARELO */
    if(!digitalRead(BUTTON_YELLOW)){
      digitalWrite(LED_YELLOW , HIGH);
    }else{
      digitalWrite(LED_YELLOW , LOW);
    }

    /* BOTAO VERMELHO */
    if(!digitalRead(BUTTON_RED)){
      digitalWrite(LED_RED , HIGH);
    }else{
      digitalWrite(LED_RED , LOW);
    }
    
    /* BOTAO AZUL*/
    if(!digitalRead(BUTTON_BLUE)){
      digitalWrite(LED_BLUE , HIGH);
    }else{
      digitalWrite(LED_BLUE , LOW);
    }
}
