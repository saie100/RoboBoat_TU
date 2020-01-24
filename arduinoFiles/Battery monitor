double convert = 5/1024; // converts raw data to voltage
  // values for scaling voltage
double constant[6]= { 
    1,
    2.196759259,
    2.697299858,
    4.099352052,
    4.737104825,
    6.690951821
  };
void setup() {
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  for (int i =0; i < 6; i++){
  double rawVoltage = analogRead(i);
  double cellVoltage = rawVoltage*convert*constant[i]; // calulates cell voltage
    Serial.print("cell voltage ");
    Serial.print(i+1);
    Serial.print(" is ");
    Serial.print(cellVoltage);
    Serial.println();
    
    batteryStatus(i, cellVoltage); // checks health of battery
    Serial.println();
    Serial.println();
    Serial.println();
    delay(3000);
    // end of prototype program
    
  }





}
  double batteryStatus(int i, double voltage){
    switch(i){
      case 0:
      if(voltage > 3.95){
        Serial.print("cell ");
        Serial.print(i+1);
        Serial.print(" is healthy");
      }
      else if(voltage> 3.55){
        Serial.print("cell ");
        Serial.print(i+1);
        Serial.print(" is moderate");
      }
      else {
        Serial.print("cell ");
        Serial.print(i+1);
        Serial.print(" needs to charge");
      }
      break;
      case 1:
      if(voltage > 7.9){
        Serial.print("cell ");
        Serial.print(i+1);
        Serial.print(" is healthy");
      }
      else if(voltage> 7.1){
        Serial.print("cell ");
        Serial.print(i+1);
        Serial.print(" is moderate");
      }
      else {
        Serial.print("cell ");
        Serial.print(i+1);
        Serial.print(" needs to charge");
      }
      break; 
          
      case 2:  
      if(voltage > 11.85){
        Serial.print("cell ");
        Serial.print(i+1);
        Serial.print(" is healthy");
      }
      else if(voltage> 10.65){
        Serial.print("cell ");
        Serial.print(i+1);
        Serial.print(" is moderate");
      }
      else {
        Serial.print("cell ");
        Serial.print(i+1);
        Serial.print(" needs to charge");
      }
      break;
      
      case 3:
      if(voltage > 15.8){
        Serial.print("cell ");
        Serial.print(i+1);
        Serial.print(" is healthy");
      }
      else if(voltage> 14.2){
        Serial.print("cell ");
        Serial.print(i+1);
        Serial.print(" is moderate");
      }
      else {
        Serial.print("cell ");
        Serial.print(i+1);
        Serial.print(" needs to charge");
      }
      break;
      
      case 4:
      if(voltage > 19.75){
        Serial.print("cell ");
        Serial.print(i+1);
        Serial.print(" is healthy");
      }
      else if(voltage> 17.75){
        Serial.print("cell ");
        Serial.print(i+1);
        Serial.print(" is moderate");
      }
      else {
        Serial.print("cell ");
        Serial.print(i+1);
        Serial.print(" needs to charge");
      }
      break;
    
      case 5:if(voltage > 23.7){
        Serial.print("cell ");
        Serial.print(i+1);
        Serial.print(" is healthy");
      }
      else if(voltage> 21.3){
        Serial.print("cell ");
        Serial.print(i+1);
        Serial.print(" is moderate");
      }
      else {
        Serial.print("cell ");
        Serial.print(i+1);
        Serial.print(" needs to charge");
      }
      break;
      
      default:
      Serial.println("failed");
    }
    
    
  }
  
