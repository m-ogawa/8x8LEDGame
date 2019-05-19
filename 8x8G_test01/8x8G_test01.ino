#define DOT_DIN   12
#define DOT_CS    11
#define DOT_SCK   10

#define KEY_A     6
#define KEY_B     5
#define KEY_C     4
#define KEY_D     3

int count = 0;
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
  pinMode( DOT_DIN, OUTPUT );
  pinMode( DOT_SCK,  OUTPUT );
  pinMode( DOT_CS,   OUTPUT );
  digitalWrite( 13, HIGH );
  maxAll( 0x0b, 0x07 );
  maxAll( 0x09, 0x00 );
  maxAll( 0x0c, 0x01 );
  maxAll( 0x0f, 0x00 );
  for( count = 1; count <= 8; count++ ) {
    maxAll( count,0 );
  }
  maxAll( 0x0a, 0x01 & 0x01 );
  heart();
}
void loop( ) {

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
