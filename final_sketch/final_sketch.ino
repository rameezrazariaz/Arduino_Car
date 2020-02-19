void setup() {
pinMode(2,INPUT); //left ir
 pinMode(3,INPUT); //right ir
 pinMode(4,INPUT);  //left prox
 pinMode(7,INPUT);  //right prox
 pinMode(5,OUTPUT); //Left motor
 pinMode(6,OUTPUT); //left motor
 pinMode(9,OUTPUT); //right motor
 pinMode(10,OUTPUT); //right motor
 pinMode(13,OUTPUT); //led
 pinMode(11,OUTPUT);  //trig
 pinMode(12,INPUT);  //echo
 Serial.begin(9600);  //serial monitor 
}

void loop() {
int lir,rir,lpr,rpr;
 digitalWrite(11,HIGH);
 delay (50);
 digitalWrite(11,LOW);
 
 long duration=pulseIn(12,HIGH);  //time duration
long distance=(duration*0.0343)/2;
if(distance<5){
Serial.println("distance=");
  //Serial.println(distance);
  digitalWrite(13,HIGH);
  stp();
}
else
{
  Serial.println("distance");
  Serial.println(distance);
  digitalWrite(13,LOW);
}


 lir=digitalRead(2);  //l ir
 rir=digitalRead(3);  //r ir
 lpr=digitalRead(4);  //l prox
 rpr=digitalRead(7);  //r prox
 if(lpr==LOW && rpr==LOW)
 stp();
 else if(lir==LOW && rir==HIGH)
 lft();
 else if(lir==HIGH && rir==LOW)
 rgt();
 else if(lir==HIGH && rir==HIGH)
 fwd();
 if ((lpr==LOW || rpr==LOW) || (lpr==LOW && rpr==LOW))
 digitalWrite(13,HIGH);
 else
 digitalWrite(13,LOW);
}

void fwd()
{
  analogWrite(5,150); //left motor
  analogWrite(6,0);  //left motor
  analogWrite(9,150); //right motor
  analogWrite(10,0);  //right motor
}

void lft()
{
  analogWrite(5,0);  //left motor
  analogWrite(6,0);  //left motor
  analogWrite(9,150);  //right motor
  analogWrite(10,0);   //right motor
}

void rgt()
{
  analogWrite(5,150);  //left motor
  analogWrite(6,0);  //left motor
  analogWrite(9,0);  //right motor
  analogWrite(10,0);  //right motor
}

void stp()
{
  analogWrite(5,0);
  analogWrite(6,0);
  analogWrite(9,0);
  analogWrite(10,0);
}

void bck()
{
  analogWrite(5,0);  //left motor
  analogWrite(6,150);  //left motor
  analogWrite(9,0);  //right motor
  analogWrite(10,150);  //right motor
}
