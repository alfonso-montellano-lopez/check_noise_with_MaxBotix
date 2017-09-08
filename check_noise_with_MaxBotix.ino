/*
  This script is designed to take several readings from the MaxBotix sonar and generate a mode/median.
  Author: Jason Lessels
  Date created: 2011/June/06
  License: GPL (=>2)
  This work has been compiled using many sources mainly posts/wiki posts from;
  Allen, Bruce (2009/July/23) and Gentles, Bill (2010/Nov/12)
*/
//MaxBotix
//Set the pin to receive the signal.
const int pwPinMaxBotix = 9;//6 is RIGHT, 11 is LEFT, 9 is TOP
//variables needed to store values
const int arraysize = 31;//31  //quantity of values to find the median (sample size). Needs to be an odd number

//declare an array to store the samples. not necessary to zero the array values here, it just makes the code clearer
int rangevalueMaxBotix[arraysize], rangevalueHCSR04[arraysize]; //= {  0, 0, 0, 0, 0, 0, 0, 0, 0};
long pulseMaxBotix, pulseMEAN_MaxBotix = 0.0, pulseMEAN_HCSR04 = 0.0;
int modEMaxBotix, averageMaxBotix, rawsamplesMaxBotix;

int modEHCSR04;

long duration, distance; // Duration used to calculate distance

float t0=0.0,tn=0.0;

void setup()
{
  //Open up a serial connection
  Serial.begin(9600);  
  pinMode(pwPinMaxBotix, INPUT);
  //Wait for the serial connection
//  Serial.print("t0=");
//  t0=millis();
//  Serial.println(t0);
//  delay(500);
}

//Main loop where the action takes place
void loop()
{
///////////////MAXBOTIX///////////////////////////////////////  
//
  rawsamplesMaxBotix = pulseIn(pwPinMaxBotix, HIGH) / 5.82;//mm
  //Serial.println(rawsamplesMaxBotix);

  
  for (int i = 0; i < arraysize; i++)
  {
    
    pulseMaxBotix = pulseIn(pwPinMaxBotix, HIGH);
    rangevalueMaxBotix[i] = pulseMaxBotix / 5.82;//mm
    
//    pulseMEAN_MaxBotix = pulseMEAN_MaxBotix + rangevalueMaxBotix[i];
    
  }
  
//  pulseMEAN_MaxBotix = pulseMEAN_MaxBotix / arraysize;

//  Serial.print(pulseMEAN_MaxBotix);

  isort(rangevalueMaxBotix, arraysize);

  modEMaxBotix = mode(rangevalueMaxBotix, arraysize);

  Serial.println(modEMaxBotix);
//
////  Serial.println(pulseMEAN_MaxBotix);
//
//  Serial.print("tn=");
//  tn=millis();
//  Serial.println(tn);
}


/*-----------Functions------------*/
//Function to print the arrays.
void printArray(int *a, int n)
{
  for (int i = 0; i < n; i++)
  {
    Serial.print(a[i], DEC);
    Serial.print(' ');
  }

  Serial.println();
}

//Sorting function
// sort function (Author: Bill Gentles, Nov. 12, 2010)
void isort(int *a, int n) {
  //  *a is an array pointer function

  for (int i = 1; i < n; ++i)
  {
    int j = a[i];
    int k;
    for (k = i - 1; (k >= 0) && (j < a[k]); k--)
    {
      a[k + 1] = a[k];
    }
    a[k + 1] = j;
  }
}

//Mode function, returning the mode or median.
int mode(int *x, int n) {
  int i = 0;
  int count = 0;
  int maxCount = 0;
  int mode = 0;
  int bimodal;
  int prevCount = 0;

  while (i < (n - 1)) {
    prevCount = count;
    count = 0;

    while (x[i] == x[i + 1]) {
      count++;
      i++;
    }

    if (count > prevCount & count > maxCount) {
      mode = x[i];
      maxCount = count;
      bimodal = 0;
    }
    if (count == 0) {
      i++;
    }
    if (count == maxCount) { //If the dataset has 2 or more modes.
      bimodal = 1;
    }
    if (mode == 0 || bimodal == 1) { //Return the median if there is no mode.
      mode = x[(n / 2)];
    }
    return mode;
  }
}
