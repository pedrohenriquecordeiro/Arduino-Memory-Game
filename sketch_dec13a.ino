#define LED_GREEN 2
#define LED_YELLOW 3
#define LED_RED 4
#define LED_BLUE 5

#define BUTTON_GREEN 7
#define BUTTON_YELLOW 8
#define BUTTON_RED 9
#define BUTTON_BLUE 10

#define BEGIN 0
#define IN_GAME_SHOW_SEQUENCE 1
#define IN_GAME_PLAYER_TIME 2
#define END_WIN 3
#define END_FAIL 4

#define NUMBER_OF_GAMES 3

int current_state = 0;

int number_of_colors = 0;

int hit_or_miss = 0;
int *sequence_of_colors;

void setup(){
  Serial.begin(9600);
  declarePorts();
  /* sorteia as cores apenas uma vez */
  sequence_of_colors = color_sorter(NUMBER_OF_GAMES);
  
}


void loop(){

  Serial.begin(9600);

  switch(current_state){
    case BEGIN:
      Serial.println("IN BEGIN");
      /* signals start of play */
      begin_game();
      for(;;){
        if(!digitalRead(BUTTON_GREEN) || !digitalRead(BUTTON_RED) || !digitalRead(BUTTON_BLUE) || !digitalRead(BUTTON_YELLOW)){
            Serial.println("GOING TO IN_GAME_SHOW_SEQUENCE ");
            current_state = IN_GAME_SHOW_SEQUENCE;
          break;
        }
      }
      break;
      
    case IN_GAME_SHOW_SEQUENCE:
      Serial.println("IN IN_GAME_SHOW_SEQUENCE ");
      blackout();
      for(int a = 0 ; a < NUMBER_OF_GAMES ; a++){
        flashes_led(sequence_of_colors[a]);
      }
      current_state = IN_GAME_PLAYER_TIME;
      Serial.println("GOING TO IN_GAME_PLAYER_TIME");
      break;

    case IN_GAME_PLAYER_TIME:
      Serial.println("IN IN_GAME_PLAYER_TIME ");
      hit_or_miss = 0;
      for(int a = 0 ; a < NUMBER_OF_GAMES ; a++){
        for(;;){
          if(!digitalRead(BUTTON_GREEN)){
            flashes_led_fast(LED_GREEN);
            delay(500);
            if(sequence_of_colors[a] == 2){
              hit_or_miss = 1;
              break;
            }else{
              hit_or_miss = -1;
              current_state = END_FAIL;
              Serial.println("GOING TO END_FAIL");
              break;
            }
          }else if(!digitalRead(BUTTON_YELLOW)){
            flashes_led_fast(LED_YELLOW);
            delay(500);
            if(sequence_of_colors[a] == 3){
              hit_or_miss = 1;
              break;
            }else{
              hit_or_miss = -1;
              current_state = END_FAIL;
              Serial.println("GOING TO END_FAIL");
              break;
            }
          }else if(!digitalRead(BUTTON_RED)){
            flashes_led_fast(LED_RED);
            delay(500);
            if(sequence_of_colors[a] == 4){
              hit_or_miss = 1;
              break;
            }else{
              hit_or_miss = -1;
              current_state = END_FAIL;
              Serial.println("GOING TO END_FAIL");
              break;
            }
          }else if(!digitalRead(BUTTON_BLUE)){
            flashes_led_fast(LED_BLUE);
            delay(500);
            if(sequence_of_colors[a] == 5){
              hit_or_miss = 1;
              break;
            }else{
              hit_or_miss = -1;
              current_state = END_FAIL;
              Serial.println("GOING TO  END_FAIL");
              break;
            }
          } 
        }
        if( hit_or_miss == -1){
          break;
        }
      }
      if(hit_or_miss != -1 ){
        current_state = END_WIN;
      }else{
        current_state = END_FAIL;
      }
      break;
      
    case END_FAIL:
      Serial.println("IN END_FAIL");
      end_game_fail();
      break;

    case END_WIN:
      Serial.println("IN END_WIN");
      end_game_win();
      break;
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


void begin_game(){
  /* signals start of play */
  digitalWrite(LED_GREEN , HIGH);
  digitalWrite(LED_YELLOW , HIGH);
  digitalWrite(LED_RED , HIGH);
  digitalWrite(LED_BLUE , HIGH);
} 

void end_game_fail(){
  digitalWrite(LED_GREEN , LOW);
  digitalWrite(LED_YELLOW, LOW);
  digitalWrite(LED_RED , HIGH);
  digitalWrite(LED_BLUE , LOW);
}

void blackout(){
  digitalWrite(LED_GREEN , LOW);
  digitalWrite(LED_YELLOW, LOW);
  digitalWrite(LED_RED , LOW);
  digitalWrite(LED_BLUE , LOW);
  delay(3000);
}

void hit(){
  digitalWrite(LED_GREEN , HIGH);
  digitalWrite(LED_YELLOW, HIGH);
  digitalWrite(LED_RED , HIGH);
  digitalWrite(LED_BLUE , HIGH);
  delay(3000);
}

void end_game_win(){
  /* signals send of play */
  digitalWrite(LED_GREEN , HIGH);
  digitalWrite(LED_YELLOW , LOW);
  digitalWrite(LED_RED , LOW);
  digitalWrite(LED_BLUE , LOW);
}

int *color_sorter(int number){
  /* reads analogue port 0 empty*/ 
  /* to feed the random number generator function with a floating value*/
  randomSeed(analogRead(0));
  
  /* allocates number memory locations*/
  int *colors = (int *) malloc(number);
  
  if(!colors){
    return NULL;
  }else{
    /* allocation made successfully */
    for(int a = 0; a < number ; a++){
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

void flashes_led_fast(int led){
  /* keep led access for 1 second*/
  digitalWrite(led , LOW);
  delay(50);
  digitalWrite(led , HIGH);
  delay(50);
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
