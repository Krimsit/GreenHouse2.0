int it = 0;
long _mode_sensors;
unsigned long long iter;
bool light = LOW;
bool temp = LOW;
bool pomp = LOW;

void setup() {
  Serial.begin(250000);
  pinMode(6, OUTPUT);
  pinMode(2, INPUT_PULLUP);
  digitalWrite(2, HIGH);
  iter = 0;
  _mode_sensors = 0;
}
int getIdr(){
  if(it > 5){
    it = -5;
  }
  it++;
  return 30 + it;
}
int getTemp(){
  if(it > 3){
    it = -1;
  }
  it++;
  return 24 + it;
}
int getHumAir(){
  if(it > 4){
    it = -1;
  }
  it++;
  return 60 + it;
}
void lightToggle(bool val){
  if(val){
    digitalWrite(6, HIGH);
  }
  else{
    digitalWrite(6, LOW);
  }
}

void tempToggle(bool val){
  if(val){
    digitalWrite(6, HIGH);
    delay(300);
    digitalWrite(6, LOW);
    delay(300);
    digitalWrite(6, HIGH);
  }
  else{
    digitalWrite(6, LOW);
  }
}
void pompToggle(bool val){
  if(val){
    digitalWrite(6, HIGH);
    delay(300);
    digitalWrite(6, LOW);
    delay(300);
    digitalWrite(6, HIGH);
    delay(300);
    digitalWrite(6, LOW);
    delay(300);
    digitalWrite(6, HIGH);
  }
  else{
    digitalWrite(6, LOW);
  }
}
void loop() {
  if (Serial.available() >= 1){
    // Отправляем полученную команду компьютера на программный UART
    long long num = Serial.parseInt();
    int arr[64];
    int i=0,r;
    while(num!=0){
      r = num%2;
      arr[i++] = r;
      num /= 2;
    }
    if(arr[i-1] == 1 && i == 7){
      _mode_sensors = 0;
    }
    else if(arr[i-1] == 1 && i == 6){
      _mode_sensors = 1;
    }
    else if(arr[i-1] == 1 && i == 5){
      _mode_sensors = 2;
    }
    else if(arr[i-1] == 1 && i == 4){
      _mode_sensors = 3;
    }
    //  Control  
    
    else if(arr[i-1] == 1 && i == 3){
      light = !light;
      lightToggle(light);
    }
    else if(arr[i-1] == 1 && i == 2){
      temp = !temp;
      tempToggle(temp);
    }
    else if(arr[i-1] == 1 && i == 1){
      pomp = !pomp;
      pompToggle(pomp);
    }


  }
//  Serial.println(_mode_sensors);
  
  if(light){
    lightToggle(HIGH);
  }
  if(iter % 1000 == 0){
    switch(_mode_sensors){
      case 0:
        Serial.println(getIdr());break;
      case 1:
        Serial.println(getTemp());break;
      case 2:
        Serial.println(getHumAir());break;
    }
    
  }
  if(iter > 2000000){
    iter = 0;
  }
  
  iter += 100;
  delay(100);
}
