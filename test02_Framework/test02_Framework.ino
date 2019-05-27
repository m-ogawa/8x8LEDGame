//Framework
//made Framework and roulette game.


//Pin Assign
#define DOT_DIN   12
#define DOT_CS    11
#define DOT_SCK   10
#define KEY_A     6
#define KEY_B     5
#define KEY_C     4
#define KEY_D     3

//Delay time(msec)
#define LOOP_DELAYTIME  5
#define ROULETTE_TIME 5

unsigned int loop_count = 0;    //loop counter
unsigned char gamestatus = 0;   //Game Status Number
byte keyinput[2] = {0,0};
unsigned char selected = 1;
unsigned char roulettestatus = 0;
unsigned char roulette_num = 0;


void putByte( byte data ) {
  byte i = 8;
  byte mask;
  while( i > 0 ) {
    mask = 0x01 << ( i - 1 );
    digitalWrite( DOT_SCK, LOW );
    if( data & mask ){
      digitalWrite( DOT_DIN, HIGH );
    }else{
      digitalWrite( DOT_DIN, LOW );
    }
    digitalWrite( DOT_SCK, HIGH );
    --i;
  }
}
void maxAll( byte reg, byte col ) {
  int c = 0;
  digitalWrite( DOT_CS, LOW );
  for( c = 1; c <= 4; c++ ) {
    putByte( reg );
    putByte( col );
  }
  digitalWrite( DOT_CS, LOW );
  digitalWrite( DOT_CS,HIGH );
}

void setup() {
  //LED Setup
  pinMode( DOT_DIN, OUTPUT );
  pinMode( DOT_SCK,  OUTPUT );
  pinMode( DOT_CS,   OUTPUT );
  digitalWrite( 13, LOW );
  maxAll( 0x0b, 0x07 );
  maxAll( 0x09, 0x00 );
  maxAll( 0x0c, 0x01 );
  maxAll( 0x0f, 0x00 );
  for(int i = 1; i <= 8; i++ ) {
    maxAll( i,0 );
  }
  maxAll( 0x0a, 0x01 & 0x01 );

  //Input Setup
  pinMode( KEY_A, INPUT_PULLUP );
  pinMode( KEY_B, INPUT_PULLUP );
  pinMode( KEY_C, INPUT_PULLUP );
  pinMode( KEY_D, INPUT_PULLUP );

  //Random seed
  randomSeed(analogRead(0));
}
void loop( ) {
  //Refresh Input
  keyinput[1] = keyinput[0];
  keyinput[0] = (digitalRead(KEY_A) << 0) |
                (digitalRead(KEY_B) << 1) |
                (digitalRead(KEY_C) << 2) |
                (digitalRead(KEY_D) << 3);

  //Refresh Game Status
  switch(gamestatus){
    case 0:   //Select Game
      if( (keyinput[1]&1) > (keyinput[0]&1) ){    //push A
        if(selected>1) selected--;
      }
      if( (keyinput[1]&2) > (keyinput[0]&2) ){    //push B
        if(selected<3) selected++;
      }
      if( (keyinput[1]&4) > (keyinput[0]&4) ){    //push C
        if(selected != 1) break;                  //Now there is only one game...
        gameInit(selected);
      }
      break;
    case 1:   //No.1 Fortune roulette
      if( (keyinput[1]&4) > (keyinput[0]&4) ){    //push C
        if(!roulettestatus) roulettestatus = 1;   //stop rolling
        else gameInit(0);                         //reset game
      }
      if(!roulettestatus){    //rolling...
        if(loop_count % ROULETTE_TIME == 0){        //refresh random value
          int i = random(10);
          while(i == roulette_num) i = random(10);
          roulette_num = i;
        }
      }
      break;
  }

  //Refresh Display
  switch(gamestatus){
    case 0:   //Select Game
      displaySelectedGame(selected);
      break;
    case 1:   //No.1 Fortune roulette
      displayRoulette(roulette_num);
      break;
  }

  //loop count & delay
  delay(LOOP_DELAYTIME);
  loop_count++;
}

void gameInit(int __selected){
  gamestatus = __selected;
  switch(gamestatus){
    case 1:
      roulette_num = random(10);
      roulettestatus = 0;
    break;
  }
}

void displaySelectedGame(int __selected){
  switch(__selected){
    case 1:
      face();
      // maxAll( 8,0b00000000 );
      // maxAll( 7,0b00111100 );
      // maxAll( 6,0b01000010 );
      // maxAll( 5,0b01000010 );
      // maxAll( 4,0b01111110 );
      // maxAll( 3,0b01000010 );
      // maxAll( 2,0b01000010 );
      // maxAll( 1,0b00000000 );
      break;
    case 2:
      maxAll( 8,0b00000000 );
      maxAll( 7,0b00111110 );
      maxAll( 6,0b01000010 );
      maxAll( 5,0b00111110 );
      maxAll( 4,0b01000010 );
      maxAll( 3,0b01000010 );
      maxAll( 2,0b00111110 );
      maxAll( 1,0b00000000 );
      break;
    case 3:
      maxAll( 8,0b00000000 );
      maxAll( 7,0b00111100 );
      maxAll( 6,0b01000010 );
      maxAll( 5,0b00000010 );
      maxAll( 4,0b00000010 );
      maxAll( 3,0b01000010 );
      maxAll( 2,0b00111100 );
      maxAll( 1,0b00000000 );
      break;
  }
}
void displayRoulette(int __roulette_num){
  switch(__roulette_num){
    case 0:
      heart();
    break;
    case 1:
      face();
    break;
    case 2:
      star();
    break;
    case 3:
      bomb();
    break;
    case 4:
      happy();
    break;
    case 5:
      unhappy();
    break;
    case 6:
      circle();
    break;
    case 7:
      nogood();
    break;
    case 8:
      invador();
    break;
    case 9:
      explosion();
    break;
  }
}
// ハート
void heart(){
  maxAll( 8, 0b00000000 );
  maxAll( 7, 0b01100110 );
  maxAll( 6, 0b10011001 );
  maxAll( 5, 0b10000001 );
  maxAll( 4, 0b01000010 );
  maxAll( 3, 0b00100100 );
  maxAll( 2, 0b00011000 );
  maxAll( 1, 0b00000000 );
}
void face(){
  maxAll( 8,0b00111100 );
  maxAll( 7,0b01000010 );
  maxAll( 6,0b10000001 );
  maxAll( 5,0b10100101 );
  maxAll( 4,0b10000001 );
  maxAll( 3,0b10100101 );
  maxAll( 2,0b01011010 );
  maxAll( 1,0b00111100 );
}
void circle(){
  maxAll( 8,0b00111100 );
  maxAll( 7,0b01000010 );
  maxAll( 6,0b10000001 );
  maxAll( 5,0b10000001 );
  maxAll( 4,0b10000001 );
  maxAll( 3,0b10000001 );
  maxAll( 2,0b01000010 );
  maxAll( 1,0b00111100 );
}
void nogood(){
  maxAll( 8,0b10000001 );
  maxAll( 7,0b01000010 );
  maxAll( 6,0b00100100 );
  maxAll( 5,0b00011000 );
  maxAll( 4,0b00011000 );
  maxAll( 3,0b00100100 );
  maxAll( 2,0b01000010 );
  maxAll( 1,0b10000001 );
}
void happy(){
  maxAll( 8,0b00000000 );
  maxAll( 7,0b01000010 );
  maxAll( 6,0b10100101 );
  maxAll( 5,0b00000000 );
  maxAll( 4,0b00000000 );
  maxAll( 3,0b01000010 );
  maxAll( 2,0b00100100 );
  maxAll( 1,0b00011000 );
}
void unhappy(){
  maxAll( 8,0b00000000 );
  maxAll( 7,0b01000010 );
  maxAll( 6,0b00100100 );
  maxAll( 5,0b01000010 );
  maxAll( 4,0b00000000 );
  maxAll( 3,0b00011000 );
  maxAll( 2,0b00100100 );
  maxAll( 1,0b00000000 );
}
void star(){
  maxAll( 8,0b00011000 );
  maxAll( 7,0b00011000 );
  maxAll( 6,0b00111100 );
  maxAll( 5,0b11111111 );
  maxAll( 4,0b01111110 );
  maxAll( 3,0b00111100 );
  maxAll( 2,0b01100110 );
  maxAll( 1,0b11000011 );
}
void bomb(){
  maxAll( 8,0b00010000 );
  maxAll( 7,0b01010100 );
  maxAll( 6,0b00111000 );
  maxAll( 5,0b11111110 );
  maxAll( 4,0b00111000 );
  maxAll( 3,0b01010100 );
  maxAll( 2,0b00010000 );
  maxAll( 1,0b00000000 );
}
void explosion(){
  maxAll( 8,0b00000000 );
  maxAll( 7,0b01000010 );
  maxAll( 6,0b00100100 );
  maxAll( 5,0b00000000 );
  maxAll( 4,0b11000011 );
  maxAll( 3,0b00000000 );
  maxAll( 2,0b00100100 );
  maxAll( 1,0b01000010 );
}
void invador(){
  maxAll( 8,0b01000010 );
  maxAll( 7,0b00100100 );
  maxAll( 6,0b00111100 );
  maxAll( 5,0b01011010 );
  maxAll( 4,0b11111111 );
  maxAll( 3,0b11111111 );
  maxAll( 2,0b10100101 );
  maxAll( 1,0b00111100 );
}
void clear(){
  maxAll( 8,0b00000000 );
  maxAll( 7,0b00000000 );
  maxAll( 6,0b00000000 );
  maxAll( 5,0b00000000 );
  maxAll( 4,0b00000000 );
  maxAll( 3,0b00000000 );
  maxAll( 2,0b00000000 );
  maxAll( 1,0b00000000 );
}
