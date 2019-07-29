
#define stripPinR 15
#define stripPinG 16
#define stripPinB 18
#define stripFrequency 5000
#define stripResolution 8

enum channels 
{
  RED, GREEN, BLUE
};

void setup() 
{
    ledcsetup(0, stripFrequency, stripResolution);
    ledcAttachPin(stripPinR,RED);
    ledcAttachPin(stripPinG,GREEN);
    ledcAttachPin(stripPinB,BLUE);
}

void loop() {
  ledcWrite(RED,255);
  ledcWrite(GREEN,255);
  ledcWrite(BLUE,255);
}
