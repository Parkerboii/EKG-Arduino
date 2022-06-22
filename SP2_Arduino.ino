#include <SPI.h>
#include <TimerOne.h>

//Specifikation af clock frekvensen og SPI mode.
SPISettings settings(8000000, MSBFIRST, SPI_MODE0);
const int adc = 10;
int val16 = 0;
const long tSampleInMicros = 2500; // Sample time in microseconds
//1/400*1000000
void setup() {
  Serial.begin(115200); //Mere end nødvendigt cuz good
  SPI.begin();
  SPI.beginTransaction(settings);
  pinMode(adc, OUTPUT);
  digitalWrite(adc, HIGH);
  Timer1.initialize(tSampleInMicros); // initialize timer1, and set the period
  Timer1.attachInterrupt(getEKGADC); // attaches callback() as a timer overflow interrupt
  while (!Serial) {
    ; // wait for serial port to connect. 
  }
}
  
void loop() {
 
}

void getEKGADC() {
   // take the SS pin low to select the chip:
  digitalWrite(adc, LOW);
  //  send in the address and value via SPI:
  val16 = SPI.transfer16(0x00);
  // take the SS pin high to de-select the chip:
  digitalWrite(adc, HIGH);
  //Serial.print("EKGdata: ");
  Serial.println(val16);          // debug value
}
