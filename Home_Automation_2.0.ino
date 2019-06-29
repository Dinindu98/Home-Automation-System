int rcv[2];
int x=0;
int y=0;
int z;
int light[5];
int a=0;
int datax;
int qe=0; // light sensor
int data;
int waterlevel = 0;

void setup() {
  int a;
  for(a=0;a<5;a++){
    light[a]=5;
    
    
  }
  
  Serial.begin(9600);
  
  
  pinMode(32,OUTPUT); // light pin
  pinMode(33,OUTPUT);
  pinMode(34,OUTPUT);
  pinMode(35,OUTPUT);
  pinMode(36,OUTPUT);
  pinMode(37,OUTPUT);
  pinMode(38,OUTPUT);
  pinMode(39,OUTPUT);
  pinMode(40,OUTPUT);
  
  pinMode(22,INPUT); // tuch switch pin
  pinMode(23,INPUT);
  pinMode(24,INPUT);
  pinMode(25,INPUT);
  pinMode(26,INPUT);
  pinMode(27,INPUT);
  pinMode(28,INPUT);
  pinMode(29,INPUT);
  pinMode(30,INPUT);

  pinMode(A2,INPUT);
}

void loop() {
  if (Serial.available()>0){
    convert();
    datax=data%1000;
    if (data == 999){
     start();
    }
    rcv[0]=datax%10;
    rcv[1]=datax/10;
    light[(rcv[1]-11)]=rcv[0];
    if (rcv[0]==6){
      digitalWrite(rcv[1]+21,HIGH);
      Serial.println(data);
    }else{
      digitalWrite(rcv[1]+21,LOW);
      Serial.println(data);
   }
  }
  if(((digitalRead(22)==1)||(digitalRead(23)==1)||(digitalRead(24)==1)||(digitalRead(25)==1)||(digitalRead(26)==1))&&(a==0)){
    touchswitchRead(); 
    a=1;
    
  }else if(((digitalRead(22)==0)&&(digitalRead(23)==0)&&(digitalRead(24)==0)&&(digitalRead(25)==0)&&(digitalRead(26)==0))&&(a==1)){
    
    a=0;
  }
  if (((digitalRead(2))==1)&&qe==0){
    Serial.println("21306");
    qe=1;
  }else if(((digitalRead(2))==0)&&qe==1){
    Serial.println("21305");
    qe=0;
  }

  if(((analogRead(A2)-waterlevel)>10)||((analogRead(A2)-waterlevel)< -10)){
    int waterlevelx;
    waterlevel = analogRead(A2);
    waterlevelx = waterlevel + 20000;
    Serial.println(waterlevelx);
    
  }
}

void touchswitchRead(){
  int k;
  int count=0;
  int countx;
  while(count<5){
    countx= 22 + count;
    if (digitalRead(countx)==1){
      if (light[count]==6){
        light[count]=5;
        digitalWrite(count+32,LOW);
        k=(count*1+11)*10+22005;
        Serial.println(k);
    }
    else {
        light[count]=6;
        digitalWrite(count+32,HIGH);
        k=(count*1+11)*10+22006;
        Serial.println(k);
      }
    }
    count=count+1;
  }
}

void start(){
  int i=0;
  int k;
  while(i<5){
    k=(i*1+11)*10+22000+ light[i];
    Serial.println(k);
    delay(10);
    i=i+1;
  }
  
}
void convert(){
  String k;
  int l[5];
  int j=0;
  while(j<5){
      k=Serial.read();
      int i = k.toInt();
      i=i-48;
      l[j]=i;
      j=j+1;
      delay(10);
    }
    data=l[0]*10000+l[1]*1000+l[2]*100+l[3]*10+l[4];
}


