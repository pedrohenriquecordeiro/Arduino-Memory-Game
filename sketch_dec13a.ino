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
int *sequence_of_colors;

int hit_or_miss = 0;

void setup(){
    Serial.begin(9600);
    declarePorts();
    
}


void loop(){
    Serial.begin(9600);

    for(int b = 0 ; b <= NUMBER_OF_GAMES ; b++){

      switch(current_state){
        case BEGIN:
          /* signals start of play */
          begin_game();
          for(;;){
            if(!digitalRead(BUTTON_GREEN) || !digitalRead(BUTTON_RED) || !digitalRead(BUTTON_BLUE) || !digitalRead(BUTTON_YELLOW)){
               current_state = IN_GAME_SHOW_SEQUENCE;
              break;
            }
          }
          break;
          
        case IN_GAME_SHOW_SEQUENCE:
          blackout();
          number_of_colors += 1;
          int *sequence_of_colors = color_sorter(number_of_colors);
          for(int a = 0 ; a < number_of_colors ; a++){
            flashes_led(sequence_of_colors[a]);
          }
          current_state = IN_GAME_PLAYER_TIME;
          break;

        case IN_GAME_PLAYER_TIME:
          hit_or_miss = 0;
          for(int a = 0 ; a < number_of_colors ; a++){
            for(;;){
              if(!digitalRead(BUTTON_GREEN)){
                flashes_led_fast(LED_GREEN);
                if(sequence_of_colors[a] == 2){
                  hit_or_miss = 1;
                  break;
                }else{
                  hit_or_miss = -1;
                  current_state = END_FAIL;
                  break;
                }
              }else if(!digitalRead(BUTTON_YELLOW)){
                flashes_led_fast(LED_YELLOW);
                if(sequence_of_colors[a] == 3){
                  hit_or_miss = 1;
                  break;
                }else{
                  hit_or_miss = -1;
                  current_state = END_FAIL;
                  break;
                }
              }else if(!digitalRead(BUTTON_RED)){
                flashes_led_fast(LED_RED);
                if(sequence_of_colors[a] == 4){
                  hit_or_miss = 1;
                  break;
                }else{
                  hit_or_miss = -1;
                  current_state = END_FAIL;
                  break;
                }
              }else if(!digitalRead(BUTTON_BLUE)){
                flashes_led_fast(LED_BLUE);
                if(sequence_of_colors[a] == 5){
                  hit_or_miss = 1;
                  break;
                }else{
                  hit_or_miss = -1;
                  current_state = END_FAIL;
                  break;
                }
              } 
            }
          }
          current_state = IN_GAME_SHOW_SEQUENCE;
          break;
          
        case END_FAIL:
          end_game_fail();
          break;

      }
    }

    for(;;){
      if(hit_or_miss == 0){
        end_game_fail();
      }else{
        end_game_win();
      }
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

void end_game_fail(){
  digitalWrite(LED_GREEN , LOW);
  digitalWrite(LED_YELLOW, LOW);
  digitalWrite(LED_RED , LOW);
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
