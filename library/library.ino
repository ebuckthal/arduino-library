// color swirl! connect an RGB LED to the PWM pins as indicated
// in the #defines
// public domain, enjoy!
 
#define REDPIN 3
#define GREENPIN 6
#define BLUEPIN 5

#define POTPIN 0 // select the input pin for the potentiometer

#define FADESPEED 100 //100    // make this higher to slow down
#define AMBIENTVALUE 300

#define WAITTIME 500 //10000

int cr = 0;
int cg = 0;
int cb = 0;

int l = 0;
 
void setup() {
  pinMode(REDPIN, OUTPUT);
  pinMode(GREENPIN, OUTPUT);
  pinMode(BLUEPIN, OUTPUT);
  pinMode(POTPIN, INPUT);
  Serial.begin(115200); // configure serial port baud rate
}

void fade(int r, int g, int b) {
  
  while(cr != r || cg != g || cb != b) {
    
    cr = cr + (cr > r ? -1 : (cr < r ? 1 : 0));
    cg = cg + (cg > g ? -1 : (cg < g ? 1 : 0));
    cb = cb + (cb > b ? -1 : (cb < b ? 1 : 0));
    
    analogWrite(REDPIN, cr);
    analogWrite(BLUEPIN, cg);
    analogWrite(GREENPIN, cb);
    
    delay(FADESPEED);
  }
}

int avgLight() {
  int l = 0;
  
  for(int i = 0; i < 100; i++) {
    l += analogRead(POTPIN) / 100;
  }
  
  Serial.println(l, DEC);
  return l;
}
 
void loop() {
  
  
  fade(0, 0, 255); //blue
  delay(WAITTIME);
  
  l = avgLight();
  
  if(l >= AMBIENTVALUE) {
    fade(0, 255, 0); //green
    delay(WAITTIME);
    fade(127, 170, 0);//yellow
    delay(WAITTIME);
  } else {
    fade(255, 0, 85);
    delay(WAITTIME);
    fade(85, 0, 255);
    delay(WAITTIME);
  }
}
