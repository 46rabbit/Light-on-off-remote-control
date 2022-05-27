#include <Servo.h>
#include <IRremote.h>

#define KEY_1 16753245
#define KEY_2 16736925

int RECV_PIN = A4;
IRrecv irrecv(RECV_PIN);
decode_results results;
unsigned long results_v;
int on = 0;
int readValue;
unsigned long last = millis();

int i = 0;

Servo servo;

void sendSignal()
{
  servo.write(62);
  delay(500);
  servo.write(30);
  delay(500);
  servo.write(62);
  delay(500);
  servo.write(0);
}

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn();

  pinMode(5, INPUT);
  servo.attach(7);
  servo.write(0);
}

void loop()
{
  readValue = digitalRead(5);

  if(readValue == HIGH)
  {
    sendSignal();
    delay(500);
  }
  
  if(irrecv.decode(&results))
  {
    if(millis() - last > 250)
    {
      on = !on;
      results_v = results.value;
      Serial.println(results_v);

      if(results.value == KEY_1)
      {
        sendSignal();
      }
    }

    last = millis();
    irrecv.resume();
  }
}
