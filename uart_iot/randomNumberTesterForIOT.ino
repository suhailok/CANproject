int randomNumber;
  char data[3];

void setup() {
  // Initialize UART with a baud rate of 115200
  Serial.begin(115200);

  // Seed the random number generator
  randomSeed(analogRead(0));
}

void loop() {
  // Generate a random number between 0 and 100
  randomNumber = random(60, 150);
  data[0]='H';
  data[1]= (char)randomNumber;
  Serial.println(data);
  delay(100); 
 
  // Send the random number via UART
  randomNumber = random(5, 50);
  data[0]='T';
  data[1]= (char)randomNumber;
  Serial.println(data);
 

  // Wait for 1 second before generating a new number
  delay(1000);
}
