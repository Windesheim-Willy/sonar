
// define pins
const int triggerLeft = 5;
const int echoLeft = 6;

const int triggerRight = 7;
const int echoRight = 8;

const int triggerCenter = 9;
const int echoCenter = 10;

// defines variables
long duration;
int distance;

void setup()
{
  pinMode(triggerLeft, OUTPUT);
  pinMode(echoLeft, INPUT);

  pinMode(triggerRight, OUTPUT);
  pinMode(echoRight, INPUT);

  pinMode(triggerCenter, OUTPUT);
  pinMode(echoCenter, INPUT);

  Serial.begin(9600);
}

void loop()
{
  int distances[3];
  distances[0] = GetDistance(triggerLeft, echoLeft);
  distances[1] = GetDistance(triggerCenter, echoCenter);
  distances[2] = GetDistance(triggerRight, echoRight);

  Serial.println(GetMinNumber(distances));
}

int GetDistance(int triggerPin, int echoPin)
{
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);

  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(triggerPin, LOW);
  duration = pulseIn(echoPin, HIGH);

  distance = duration * 0.034 / 2;

  return distance;
}

int GetMinNumber(int distances[])
{
  int result = distances[0];
  for (int i = 0; i < 3; i++)
  {
    if (distances[i] < result)
    {
      result = distances[i];
    }
  }
  return result;
}

