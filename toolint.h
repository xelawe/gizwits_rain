// Declarations and Routines for Interrupt

volatile int gf_rain_cnt;
volatile boolean gf_no_int;
volatile unsigned long ContactTime;  // Timer to avoid conatct bounce in interrupt routine


void int_rain_cnt(void) {

  if ((millis() - ContactTime) > 15 ) {  // debounce of REED contact. With 15ms speed more than 150 km/h can be measured
    ContactTime = millis();

    if (gf_no_int) {
      return;
    } else {
      gf_rain_cnt++;
    }

  }
}

void Int_setup( ) {
  // Interrupt und Pin für Regensensor initialisieren
  pinMode(gc_pin_rain, INPUT_PULLUP);
  //digitalWrite(gc_pin_rain, HIGH);
  gf_no_int = true;
  attachInterrupt(gc_pin_rain, int_rain_cnt, FALLING);
  // LOW to trigger the interrupt whenever the pin is low,
  // CHANGE to trigger the interrupt whenever the pin changes value
  // RISING to trigger when the pin goes from low to high,
  // FALLING for when the pin goes from high to low.
  delay(1000);
  gf_no_int = false; // Spätestens jetzt sollte der INT sauber sein ...
}

