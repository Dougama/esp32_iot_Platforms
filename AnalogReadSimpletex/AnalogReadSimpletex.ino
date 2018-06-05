
int const numero_muestras=200;
int sensorPin = 36;    

int sensorValue = 0;  
int values[numero_muestras];
int maxx,minn;
long media=0;
void setup() {

  Serial.begin(9600);
}

void loop() {
  int t = millis();
  for(int i=0; i<numero_muestras;i++)
  {   float t = micros();
      values[i] = analogRead(sensorPin);
      float ts = micros()-t;
      Serial.print("\t");
      Serial.println(ts);      
  }
  // read the value from the sensor:-
  media=0;
  maxx=0;
  minn=0xfff; 
  for(int i=0; i<numero_muestras;i++)
  {
      media += values[i];
      if(values[i] > maxx) maxx=values[i];
      if(values[i] < minn) minn=values[i];
  }
  
  Serial.print(media/numero_muestras);
  Serial.print("\t");
  Serial.print(maxx);
  Serial.print("\t");
  Serial.print(minn);
  Serial.print("\t");
  Serial.print(maxx-minn);
  Serial.print("\t \t \t");
  
  Serial.print((media/numero_muestras)*3330/4096);
  Serial.print("\t");
  Serial.print(maxx*3330/4096);
  Serial.print("\t");
  Serial.print(minn*3330/4096);
  Serial.print("\t");
  Serial.println((maxx-minn) *3330/4096);
               
}
