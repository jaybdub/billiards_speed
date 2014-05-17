int back_pin = A0;
int front_pin = A1;
int back_threshold = 800;
int front_threshold = 800;
double dist_between_lasers = 0.5;

int back_reading = 0;
int front_reading = 0;
int last_back_reading = 0;
int last_front_reading = 0;

long start_time_ms = 0;
long end_time_ms = 0;

void setup() {
  Serial.begin(115200);
}
void loop() {
  //Update previous reading
  last_back_reading = back_reading;
  last_front_reading = front_reading;
  
  //Update current reading
  back_reading = analogRead(back_pin);
  front_reading = analogRead(front_pin);
  
  //Check for falling edge on back reading
  if( (back_reading < back_threshold) && 
      (last_back_reading > back_threshold) )
  {
    start_time_ms = millis();
    Serial.println("B");
  } 
  
  //Check for falling edge on front reading
  if( (front_reading < front_threshold) && 
      (last_front_reading > front_threshold) )
  {
    end_time_ms = millis();
    //Calculate and display velocity
    double dt = ((double)(end_time_ms - start_time_ms))*0.001;
    double velocity = dist_between_lasers / dt;
    Serial.println("F");
    Serial.print("Velocity (m/s): ");
    Serial.println(velocity);
  } 
  delay(1);
}
