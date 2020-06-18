#define uchar unsigned char
int clockpin=12;//寄存器时钟输入
int datapin=11;//寄存器数据输入
int leftpin=9;//左LED
int rightpin=10;//右LED
unsigned char smgduan[10]={0x90,0x00,0xf8,0x02,0x12,0x99,0xb0,0xa4,0xf9,0xc0};
void setup() {
  pinMode(clockpin,OUTPUT);
  pinMode(datapin,OUTPUT);
  pinMode(leftpin,OUTPUT);
  pinMode(rightpin,OUTPUT);
  pinMode(A0,INPUT);
  digitalWrite(leftpin,HIGH);
  digitalWrite(rightpin,HIGH);
  Serial.begin(9600);
  digitalWrite(A0,HIGH);
  // put your setup code here, to run once:

}
void shift(uchar a)
{
shiftOut(datapin,clockpin,MSBFIRST,a);
}
void startup()
{
  int i;
  for(i=0;i<20;i++){
 digitalWrite(leftpin,LOW);
    shift(0x06);
    delay(5);
digitalWrite(leftpin,HIGH);
digitalWrite(rightpin,LOW);
    shift(0x30);
    delay(5);
digitalWrite(rightpin,HIGH);
  }
  for(i=0;i<20;i++){
digitalWrite(leftpin,LOW);
    shift(0x00);
    delay(5);
digitalWrite(leftpin,HIGH);
digitalWrite(rightpin,LOW);
    shift(0x00);
    delay(5);
digitalWrite(rightpin,HIGH);
  }
  for(i=0;i<20;i++){ 
digitalWrite(leftpin,LOW);
    shift(0x70);
    delay(5);
digitalWrite(leftpin,HIGH);
digitalWrite(rightpin,LOW);
    shift(0x46);
    delay(5);
digitalWrite(rightpin,HIGH);
  }
  }
void count_l()
{
  int i;
  for(i=0;i<100;i++)
  {
digitalWrite(rightpin,LOW);  
shift(0x90);
delay(10);
digitalWrite(rightpin,HIGH);
digitalWrite(leftpin,LOW);
shift(smgduan[i/10]);
delay(10);
digitalWrite(leftpin,HIGH);
 }
 for(i=0;i<100;i++){
digitalWrite(rightpin,LOW); 
shift(0x00);
delay(10);
digitalWrite(rightpin,HIGH);
digitalWrite(leftpin,LOW);
shift(smgduan[i/10]);
delay(10);
digitalWrite(leftpin,HIGH);
 }
 for(i=0;i<100;i++){
digitalWrite(rightpin,LOW); 
shift(0xf8);
delay(10);
digitalWrite(rightpin,HIGH);
digitalWrite(leftpin,LOW);
shift(smgduan[i/10]);
delay(10);
digitalWrite(leftpin,HIGH);
 }
 for(i=0;i<100;i++){
digitalWrite(rightpin,LOW); 
shift(0x02);
delay(10);
digitalWrite(rightpin,HIGH);
digitalWrite(leftpin,LOW);
shift(smgduan[i/10]);
delay(10);
digitalWrite(leftpin,HIGH);
 }
 for(i=0;i<100;i++){
digitalWrite(rightpin,LOW); 
shift(0x12);
delay(10);
digitalWrite(rightpin,HIGH);
digitalWrite(leftpin,LOW);
shift(smgduan[i/10]);
delay(10);
digitalWrite(leftpin,HIGH);
 }
 for(i=0;i<100;i++){
digitalWrite(rightpin,LOW); 
shift(0x99);
delay(10);
digitalWrite(rightpin,HIGH);
digitalWrite(leftpin,LOW);
shift(smgduan[i/10]);
delay(10);
digitalWrite(leftpin,HIGH);
 }
 for(i=0;i<100;i++){
digitalWrite(rightpin,LOW); 
shift(0xb0);
delay(10);
digitalWrite(rightpin,HIGH);
digitalWrite(leftpin,LOW);
shift(smgduan[i/10]);
delay(10);
digitalWrite(leftpin,HIGH);
 }
 for(i=0;i<100;i++){
digitalWrite(rightpin,LOW); 
shift(0xa4);
delay(10);
digitalWrite(rightpin,HIGH);
digitalWrite(leftpin,LOW);
shift(smgduan[i/10]);
delay(10);
digitalWrite(leftpin,HIGH);
 }
 for(i=0;i<100;i++){
digitalWrite(rightpin,LOW); 
shift(0xf9);
delay(10);
digitalWrite(rightpin,HIGH);
digitalWrite(leftpin,LOW);
shift(smgduan[i/10]);
delay(10);
digitalWrite(leftpin,HIGH);
 }
 for(i=0;i<100;i++){
digitalWrite(rightpin,LOW); 
shift(0xc0);
delay(10);
digitalWrite(rightpin,HIGH);
digitalWrite(leftpin,LOW);
shift(smgduan[i/10]);
delay(10);
digitalWrite(leftpin,HIGH);
 }
}
void loop() {
  uchar a =0xff;
  shift(a);
  int sensorValue = analogRead(A0);
  if (sensorValue<20)
  {
   startup();
   startup();
   startup();
  count_l();
  }
  Serial.println(sensorValue);
  }
