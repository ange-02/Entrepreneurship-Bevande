#define SLAVE_ADD 4

unsigned long TIME_TO_POUR = 2100;

byte ratio1 = 0;
byte ratio2 = 1;
byte ratio3 = 0;

// bool isStarting = true;
// bool isFinished = false;
 
int leftBottle = 8;
int middleBottle = 9;
int rightBottle = 10;

const int buttonPin = 7;

bool active = false;

// variables will change:
int buttonState = 0;  // variable for reading the pushbutton status

unsigned long t1 = millis();


void setup() {
  // setup pumps
  pinMode(leftBottle, OUTPUT);
  pinMode(middleBottle, OUTPUT);
  pinMode(rightBottle, OUTPUT);
  // setting all relays to off
  //digitalWrite(leftBottle, HIGH);
  //digitalWrite(middleBottle, HIGH);
  //digitalWrite(rightBottle, HIGH);

  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);
 }

void loop() {
  
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);
  //Serial.println(buttonState);
  

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH && !active) {
    // start pourting
    active = true;
  }
    
    t1 = millis();
    int totalRatio = ratio1 + ratio2 + ratio3;
    // we do not pour for the same amount of time for every drink
    // this is because each drink might use 2 or more dispensers simultaneously
    // this means that there is a higher rate of flow when more dispensers are active
    // thus we need a shorter time if this is the case
    
    while ((millis() - t1 <= TIME_TO_POUR * (double) maximum(ratio1, ratio2, ratio3) / totalRatio) && active ) {
      // pouring from each bottle depending on the ratios:
      Serial.println(active);

      // pour from the left bottle
      if (millis() - t1 <= TIME_TO_POUR * ((double)ratio1 / totalRatio)) {
        digitalWrite(leftBottle, HIGH);
      } else {
        digitalWrite(leftBottle, LOW);
      }

        // pour from the middle bottle
        if (millis() - t1 <= TIME_TO_POUR * ((double)ratio2 / totalRatio)) {
          digitalWrite(middleBottle, HIGH);
        } else {
          digitalWrite(middleBottle, LOW);
        }

        // pour from the right bottle
        if (millis() - t1 <= TIME_TO_POUR * ((double)ratio3 / totalRatio)) {
          digitalWrite(rightBottle, HIGH);
        } else {
          digitalWrite(rightBottle, LOW);
        }
  }
  // stop pouring
  active = false;
}


/**
 * Returns the maximum value from 3 bytes
 */
int maximum(byte r1, byte r2, byte r3) {
  if (r1 > r2) {
    if (r1 >= r3) {
      return r1;
    } else {
      return r3;
    }
  } else {
    if (r2 > r3) {
      return r2;
    } else {
      return r3;
    }
  }
}
