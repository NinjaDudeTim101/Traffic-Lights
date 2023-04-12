// Define the pins that the buttons and lights are connected to:
#define pedestrianNorthWalkBlue 2
#define pedestrianNorthStopRed 3
#define pedestrianSouthWalkBlue 4
#define pedestrianSouthStopRed 5
#define westRedButton 6
#define eastGreenButton 7
#define westRed 8
#define westYellow 9
#define westGreen 10
#define eastRed 11
#define eastYellow 12
#define eastGreen 13
#define yellowBlinkTime 500  // 0.5 seconds for yellow light blink

boolean trafficWest = true;  // west = true, east = false
int flowTime = 10000;        // amount of time to let traffic flow
int changeDelay = 2000;      // amount of time between color changes

void setup() {
  // Set up the digital I/O pins
  pinMode(westRedButton, INPUT);
  pinMode(eastGreenButton, INPUT);
  pinMode(westRed, OUTPUT);
  pinMode(westYellow, OUTPUT);
  pinMode(westGreen, OUTPUT);
  pinMode(eastRed, OUTPUT);
  pinMode(eastYellow, OUTPUT);
  pinMode(eastGreen, OUTPUT);  // Set initial state for lights - west side is green first

  // Set up the pedestrian crossing signals
  pinMode(pedestrianNorthWalkBlue, OUTPUT);
  pinMode(pedestrianNorthStopRed, OUTPUT);
  pinMode(pedestrianSouthWalkBlue, OUTPUT);
  pinMode(pedestrianSouthStopRed, OUTPUT);
  digitalWrite(pedestrianNorthWalkBlue, LOW);
  digitalWrite(pedestrianNorthStopRed, HIGH);
  digitalWrite(pedestrianSouthWalkBlue, LOW);
  digitalWrite(pedestrianSouthStopRed, HIGH);

// Set up the traffic lights signals
  digitalWrite(westRed, LOW);
  digitalWrite(westYellow, LOW);
  digitalWrite(westGreen, HIGH);
  digitalWrite(eastRed, HIGH);
  digitalWrite(eastYellow, LOW);
  digitalWrite(eastGreen, LOW);
}

void loop() {
  // Check if the west button has been pressed
  if (digitalRead(westRedButton) == HIGH) {
    // Stop traffic from the east
    digitalWrite(eastGreen, LOW);
    digitalWrite(eastYellow, LOW);
    digitalWrite(eastRed, HIGH);

    // Turn on the pedestrian walk signal for the north side
    digitalWrite(pedestrianNorthWalkBlue, HIGH);
    digitalWrite(pedestrianNorthStopRed, LOW);

    // Wait for the pedestrian to cross
    delay(flowTime);

    // Turn off the pedestrian walk signal and turn on the pedestrian stop signal for the north side
    digitalWrite(pedestrianNorthWalkBlue, LOW);
    digitalWrite(pedestrianNorthStopRed, HIGH);

    // Turn on the yellow light for the west side and wait for it to turn red
    digitalWrite(westYellow, HIGH);
    delay(changeDelay);
    digitalWrite(westYellow, LOW);
    digitalWrite(westRed, HIGH);
    delay(changeDelay);

    // Blink the yellow light on the east side to warn drivers of the upcoming light change
    for (int i = 0; i < 5; i++) {
      digitalWrite(eastYellow, LOW);
      delay(yellowBlinkTime);
      digitalWrite(eastYellow, HIGH);
      delay(yellowBlinkTime);
    }
    digitalWrite(eastYellow, LOW);

    // Turn on the green light for the west side and allow traffic to flow in that direction
    digitalWrite(westRed, LOW);
    digitalWrite(westGreen, HIGH);
    trafficWest = true;
  }
  // Check if the east button has been pressed
  if (digitalRead(eastGreenButton) == HIGH) {
    // Stop traffic flow from both sides
    digitalWrite(westGreen, LOW);
    digitalWrite(westYellow, LOW);
    digitalWrite(westRed, HIGH);
    digitalWrite(eastGreen, LOW);
    digitalWrite(eastYellow, LOW);
    digitalWrite(eastRed, HIGH);
    // Turn on the walk signal for pedestrians on the south side
    digitalWrite(pedestrianSouthStopRed, LOW);
    digitalWrite(pedestrianSouthWalkBlue, HIGH);

    // Wait for pedestrians to cross
    delay(flowTime);

    // Turn off the walk signal and allow traffic to flow again
    digitalWrite(pedestrianSouthWalkBlue, LOW);
    digitalWrite(pedestrianSouthStopRed, HIGH);

    digitalWrite(westRed, LOW);
    digitalWrite(eastGreen, HIGH);
    delay(changeDelay);
  }
}
    