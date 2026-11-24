const int LED1 = 3;
const int LED2 = 5;
const int LED3 = 6;
const int LED4 = 9;
const int LED5 = 11;
const int buzzer = 12;

// Array of LED pins in the order they will turn off
const int ledPins[] = {LED5, LED4, LED3, LED2, LED1};

void setup() {
  Serial.begin(9600);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);
  pinMode(buzzer, OUTPUT);
  Serial.println("Enter your timer in seconds:");
}

void loop() {
  if (Serial.available() > 0) {
    int userTime = Serial.parseInt();
    
    // Ignore invalid or zero inputs to prevent division issues
    if (userTime <= 0) return;

    // Calculate time per segment in milliseconds
    float LedTime = (userTime / 5.0) * 1000.0;

    // Turn all LEDs on at the start
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, HIGH);
    digitalWrite(LED4, HIGH);
    digitalWrite(LED5, HIGH);
    
    // Wait for the initial full-duration block
    delay(LedTime);

    // Countdown loop: turn off LEDs one by one with a beep
    for (int i = 0; i < 5; i++) {
      digitalWrite(ledPins[i], LOW);
      tone(buzzer, 1250);      // Turn buzzer on
      delay(200);              // Keep beep on for 0.2 seconds
      noTone(buzzer);          // Turn buzzer off
      
      // Prevent underflow if LedTime is less than 200ms
      float remainingTime = LedTime - 200;
      if (remainingTime > 0) {
        delay(remainingTime);
      }
    }
    
    // Completion melody
    tone(buzzer, 1000); 
    delay(250);
    noTone(buzzer);
    tone(buzzer, 1500); 
    delay(250);
    noTone(buzzer);
    tone(buzzer, 1000); 
    delay(250);
    noTone(buzzer);
    
    Serial.println("Timer finished! Enter next timer:");
  }
}
