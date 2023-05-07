
void Bluetooth();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:


}

void Bluetooth(){

      Serial.write("------------------------------------------------------------------------------\n");
      Serial.write("WARNING!!!! Fire Detected in The Garage\n");
      Serial.write("------------------------------------------------------------------------------");

}
