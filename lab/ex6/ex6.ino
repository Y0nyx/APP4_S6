const int outputPin = 4; // the pin where the signal is generated
const int inputPin = 5;  // the pin where the signal is measured

void setup() {
  pinMode(outputPin, OUTPUT);
  pinMode(inputPin, INPUT);
  Serial.begin(115200);
}

void loop() {
  int pulseWidth = 1000;  // pulse width in microseconds
  int period = 2000;  // period in microseconds

  // Generate a pulse of width pulseWidth
  digitalWrite(outputPin, HIGH);
  delayMicroseconds(pulseWidth);
  digitalWrite(outputPin, LOW);
  delayMicroseconds(period - pulseWidth);

  // Measure the pulse width
  long duration = pulseIn(inputPin, HIGH);
  Serial.print("Measured pulse width: ");
  Serial.println(duration);
  delay(1000);  // delay before next loop iteration
}
