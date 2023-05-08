
#define FIRE_SENSOR 2 // same as in abdo and hussein code

void Bluetooth_alarm(); // for sending the Warning msg to the phone using Bluetooth 
void Bluetooth_data();  // for sending the flame sensor state data to the phone using Bluetooth

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(FIRE_SENSOR,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
    

}

void Bluetooth_alarm(){ // this function should be called if the flame sensor detected any fire

      Serial.write("------------------------------------------------------------------------------\n");
      Serial.write("WARNING!!!! Fire Detected in The Garage\n");
      Serial.write("------------------------------------------------------------------------------");

}

void Bluetooth_data(){ // this function should be put in void loop to continuously send the flame sensor data state to the phone 

      int data = digitalRead(FIRE_SENSOR);
      Serial.println(data);
}
