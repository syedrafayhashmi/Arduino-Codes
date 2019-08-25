float x;
float y;
int z;

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(0));
}

void loop() {
    x = random(97, 99);
    y = random(0.01, 5);
    z = (int)x;

    Serial.println(x/100);
  //  Serial.println(y);
  }
