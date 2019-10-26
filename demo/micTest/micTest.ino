#define PIN_ANALOG_IN A1
#define PIN_ANALOG_OUT 9
#define PIN_ANALOG_MID_OUT A0
//#define PIN_PWM_OUT_LED 2

void setup()
{
  Serial.begin(9600);
  
  // Display status
  Serial.println("Initialized");

  pinMode(PIN_ANALOG_IN, INPUT);
  pinMode(PIN_ANALOG_OUT, OUTPUT);
  pinMode(PIN_ANALOG_MID_OUT, OUTPUT);
  //pinMode(PIN_PWM_OUT_LED, OUTPUT);

  analogWrite(PIN_ANALOG_MID_OUT, 127);
}

void loop()
{
  // code/idea taken from: https://www.sparkfun.com/tutorials/329
  int value, freq, samples;
  float in, out, sin_step;
  
  // Check the envelope input and use inverse linear mapping
  value = analogRead(PIN_ANALOG_IN);
  value = 1023 - value;
  samples = 50;

  value = max(value, 800);
  
  freq = map(value, 800, 1023, 1, 200);
  //freq = map(value, 0,1023,1,200);
  
  // Convert envelope value into a message
  Serial.print("Status: ");
  Serial.println(value);
  sin_step = 6.283 / samples;

  // sin wave
  for (in = 0; in < 6.283; in = in + sin_step)
  {
    //out = sin(in) * 127.5 + 127.5;
    value = analogRead(PIN_ANALOG_IN);
    //Serial.println(value);
    value = 1023 - value;
    value = max(value, 800);
    freq = map(value, 800,1023,1,200);

    Serial.println(freq);
    out = sin(in)*127.5 + 127.5;
    analogWrite(PIN_ANALOG_OUT,out);
    //analogWrite(PIN_PWM_OUT_LED, out);
    delay(freq);
  }

  delay(10);
}
