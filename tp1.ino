int serial {14};
int shifting {12};
int latch {13};
int cible1 {4};
int cible2 {0};
int cible3 {2};
int buzzer {15};
int boutonInput {5};
int redLED{1};
char target{0};
char stage {0};
char power {0};
char success {0};
char score {0};
char failure {0};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(serial, OUTPUT);
  pinMode(shifting, OUTPUT);
  pinMode(latch, OUTPUT);
  pinMode(cible1, OUTPUT);
  pinMode(cible2, OUTPUT);
  pinMode(cible3, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(boutonInput, INPUT);
  pinMode(redLED, OUTPUT);
  digitalWrite(latch, LOW);
  delay(500);
  start();
  newRound();
}

void loop() {
  // put your main code here, to run repeatedly:
  switch (stage) {
    case 0:
      if (digitalRead(boutonInput) == 1){
        power = 1;
        unsigned char base = 128;
        unsigned char i = 128 + score;
        shiftOut(serial, shifting, MSBFIRST, i);
        digitalWrite(latch, HIGH);
        digitalWrite(latch, LOW);
        tone(buzzer, 800);
        delay(1000);
        while (digitalRead(boutonInput) == 1 && power < 5) {
          power++;
          base = base/2;
          tone(buzzer, 800/power);
          i = i + base;
          shiftOut(serial, shifting, MSBFIRST, i);
          digitalWrite(latch, HIGH);
          digitalWrite(latch, LOW);
          delay(1000);
        }
        noTone(buzzer);
        stage++;
      } 
      break;
    case 1:
      if (target == power - 1){
        success++;
        char count = 1;
        score = 1;
        while (count < success){
          score = score + count*2;
          count++;
        }
        for (int i = 0; i < 3; i++) {
          shiftOut(serial, shifting, MSBFIRST, 0);
          digitalWrite(latch, HIGH);
          digitalWrite(latch, LOW);
          noTone(buzzer);
          delay(500);
          shiftOut(serial, shifting, MSBFIRST, score);
          digitalWrite(latch, HIGH);
          digitalWrite(latch, LOW);
          tone(buzzer, 1000);
          delay(500);
        }
        noTone(buzzer);
      }
      else {
        failure++;
        tone(buzzer, 10);
        for (char i = 0; i < 5; i++) {
          digitalWrite(redLED, HIGH);
          delay(500);
          digitalWrite(redLED, LOW);
          delay(500);
        }
        digitalWrite(redLED, HIGH);
        noTone(buzzer);
      }
      if (success == 3 || failure == 2) {
        end();
        start();
      }
      newRound();
      stage--;
      break;
  }

  
}
void newRound() {
  target = random(1, 4);
  power = 0;
  int cible = 0;
  if (target == 1) {
    cible = cible1;
  }
  else if ( target == 2) {
    cible = cible2;
  }
  else {
    cible = cible3;
  }
  digitalWrite(cible, HIGH);
  delay(1000);
  digitalWrite(cible, LOW);
}

void end() {
  if (success == 3) {
    digitalWrite(redLED, LOW);
    for(int i = 0; i < 5; i++) {
      shiftOut(serial, shifting, MSBFIRST, 5);
      digitalWrite(latch, HIGH);
      digitalWrite(latch, LOW);
      tone(buzzer,1500);
      delay(1000);
      shiftOut(serial, shifting, MSBFIRST, 2);
      digitalWrite(latch, HIGH);
      digitalWrite(latch, LOW);
      tone(buzzer,500);
      delay(1000);
    }
      shiftOut(serial, shifting, MSBFIRST, 0);
      digitalWrite(latch, HIGH);
      digitalWrite(latch, LOW);
      tone(buzzer,1500);
      delay(2000);
      shiftOut(serial, shifting, MSBFIRST, 0);
      digitalWrite(latch, HIGH);
      digitalWrite(latch, LOW);
      noTone(buzzer);
      delay(1000);
  }
  else {
    shiftOut(serial, shifting, MSBFIRST, 0);
      digitalWrite(latch, HIGH);
      digitalWrite(latch, LOW);
      tone(buzzer,400);
      digitalWrite(redLED, HIGH);
      delay(400);
      digitalWrite(redLED, LOW);
      delay(400);
      digitalWrite(redLED, HIGH);
      delay(400);
      tone(buzzer,200);
      digitalWrite(redLED, LOW);
      delay(400);
      digitalWrite(redLED, HIGH);
      delay(400);
      digitalWrite(redLED, LOW);
      delay(400);
      tone(buzzer,50);
      digitalWrite(redLED, HIGH);
      delay(400);
      digitalWrite(redLED, LOW);
      delay(400);
      digitalWrite(redLED, HIGH);
      delay(400);
      digitalWrite(redLED, LOW);
      noTone(buzzer);
  }
  delay(5000);
}

void start() {
  digitalWrite(cible1, HIGH);
  digitalWrite(cible2, HIGH);
  digitalWrite(cible3, HIGH);
  tone(buzzer, 600);
  delay(1000);
  digitalWrite(cible1, LOW);
  digitalWrite(cible2, LOW);
  digitalWrite(cible3, LOW);
  digitalWrite(redLED, HIGH);
  tone(buzzer, 900);
  delay(1000);
  digitalWrite(redLED, LOW);
  shiftOut(serial, shifting, MSBFIRST, 7);
  digitalWrite(latch, HIGH);
  digitalWrite(latch, LOW);
  tone(buzzer,1300);
  delay(1000);
  shiftOut(serial, shifting, MSBFIRST, 248);
  digitalWrite(latch, HIGH);
  digitalWrite(latch, LOW);
  tone(buzzer,1900);
  delay(1000);
  shiftOut(serial, shifting, MSBFIRST, 0);
  digitalWrite(latch, HIGH);
  digitalWrite(latch, LOW);
  noTone(buzzer);
  delay(4000);
  success = 0;
  failure = 0;
  score = 0;
}

