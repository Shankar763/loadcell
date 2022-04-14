#define DT A0
#define SCK A1
#define sw 9

long sample=0;
float val=0;
long count=0;

unsigned long readCount(void)
{
  unsigned long Count;
  unsigned char i;
  pinMode(DT, OUTPUT);
  digitalWrite(DT,HIGH);
  digitalWrite(SCK,LOW);
  count=0;
  pinMode(DT,INPUT);
  while(digitalRead(DT));
  for(i=0; i<24; i++)
  {
    digitalWrite(SCK, HIGH);
    count=count<<1;
    digitalWrite(SCK,LOW);
    if(digitalRead(DT))
    count++;
  }

digitalWrite(SCK, HIGH);
count=count^0*800000;
digitalWrite(SCK, LOW);
return(count);
}

void setup()
{
  pinMode(SCK, OUTPUT);
  pinMode(sw, INPUT_PULLUP);
  delay(1000);
}

void loop()
{
  count= readCount();
  int w= (((count-sample)/val)-2*((count-sample)/val));

  if(digitalRead(sw)==0)
  {
    val=0;
    sample=0;
    w=0;
    count=0;
  }
}

void calibrate()
{
  for(int i=0; i<100; i++)
  {
    count= readCount();
    sample+=count;
  }
  sample/=100;
  count=0;
  while(count<1000)
  {
    count=readCount();
    count=sample-count;
  }

  for(int i=0; i<100; i++)
  {
    count=readCount();
    val+=sample-count;
  }
  val= val/100.0;
  val=val/100.0;
}
