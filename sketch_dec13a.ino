#define LED_GREEN 2
#define LED_YELLOW 3
#define LED_RED 4
#define LED_BLUE 5

#define BUTTON_GREEN 7
#define BUTTON_YELLOW 8
#define BUTTON_RED 9
#define BUTTON_BLUE 10

#define NUMBER_OF_COLORS 3

int number_of_colors = 1;

void setup(){
    Serial.begin(9600);
    declarePorts();
    /* signals start of play */
    begin_game();
}


void loop(){
    Serial.begin(9600);
    
    end_game();

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


void begin_game(){
  /* signals start of play */
  delay(2000);
  float interval = 100;
  while(interval >= 0 ){
    digitalWrite(LED_GREEN , HIGH);
    digitalWrite(LED_YELLOW , HIGH);
    digitalWrite(LED_RED , HIGH);
    digitalWrite(LED_BLUE , HIGH);
    delay(interval);
    digitalWrite(LED_GREEN , LOW);
    digitalWrite(LED_YELLOW , LOW);
    digitalWrite(LED_RED , LOW);
    digitalWrite(LED_BLUE , LOW);
    delay(interval);
    interval = interval - 2.5 ;
  }
  digitalWrite(LED_GREEN , HIGH);
  digitalWrite(LED_YELLOW , HIGH);
  digitalWrite(LED_RED , HIGH);
  digitalWrite(LED_BLUE , HIGH);
  
} 

void end_game(){
  int interval = 300;
  while(1){
    digitalWrite(LED_GREEN , HIGH);
    digitalWrite(LED_YELLOW , LOW);
    digitalWrite(LED_RED , LOW);
    digitalWrite(LED_BLUE , LOW);
    delay(interval);
    digitalWrite(LED_GREEN , LOW);
    digitalWrite(LED_YELLOW , HIGH);
    digitalWrite(LED_RED , LOW);
    digitalWrite(LED_BLUE , LOW);
    delay(interval);
    digitalWrite(LED_GREEN , LOW);
    digitalWrite(LED_YELLOW , LOW);
    digitalWrite(LED_RED , HIGH);
    digitalWrite(LED_BLUE , LOW);
    delay(interval);
    digitalWrite(LED_GREEN , LOW);
    digitalWrite(LED_YELLOW , LOW);
    digitalWrite(LED_RED , LOW);
    digitalWrite(LED_BLUE , HIGH);
    delay(interval);
    digitalWrite(LED_GREEN , LOW);
    digitalWrite(LED_YELLOW , LOW);
    digitalWrite(LED_RED , HIGH);
    digitalWrite(LED_BLUE , LOW);
    delay(interval);
    digitalWrite(LED_GREEN , LOW);
    digitalWrite(LED_YELLOW , HIGH);
    digitalWrite(LED_RED , LOW);
    digitalWrite(LED_BLUE , LOW);
    delay(interval);
  }
}

int *color_sorter(int number_of_colors){
  /* reads analogue port 0 empty*/ 
  /* to feed the random number generator function with a floating value*/
  randomSeed(analogRead(0));
  
  /* allocates 10 memory locations*/
  int *colors = malloc(number_of_colors);
  
  if(!colors){
    return NULL;
  }else{
    /* allocation made successfully */
    for(int a = 0; a < number_of_colors ; a++){
      /* populate the positions with random colors */
      colors[a] = random(LED_GREEN,LED_BLUE + 1);
    }
  }

  return colors;
}

void flashes_led(int led){
  /* keep led access for 1 second*/
  digitalWrite(led , LOW);
  delay(1000);
  digitalWrite(led , HIGH);
  delay(1000);
  digitalWrite(led , LOW);
}

void lights_up_from_the_push_button(){
  /* GREEN BUTTON */
    if(!digitalRead(BUTTON_GREEN)){
      digitalWrite(LED_GREEN , HIGH);
    }else{
      digitalWrite(LED_GREEN , LOW);
    }

    /* YELLOW BUTTON */
    if(!digitalRead(BUTTON_YELLOW)){
      digitalWrite(LED_YELLOW , HIGH);
    }else{
      digitalWrite(LED_YELLOW , LOW);
    }

    /* RED BUTTON */
    if(!digitalRead(BUTTON_RED)){
      digitalWrite(LED_RED , HIGH);
    }else{
      digitalWrite(LED_RED , LOW);
    }
    
    /* BLUE BUTTON */
    if(!digitalRead(BUTTON_BLUE)){
      digitalWrite(LED_BLUE , HIGH);
    }else{
      digitalWrite(LED_BLUE , LOW);
    }
}
