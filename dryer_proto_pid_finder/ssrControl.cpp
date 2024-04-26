#include "Arduino.h"
#ifndef _SSR_SOURCE_
#define _SSR_SOURCE_

int htpmp = 4, ptc = 5, fan = 6;

#include "ssrControl.h"

void ssr::init(int heatpump_, int ptc_, int fan_) {
  htpmp = heatpump_;
  ptc = ptc_;
  fan = fan_;
  pinMode(htpmp, OUTPUT);
  pinMode(ptc, OUTPUT);
  pinMode(fan, OUTPUT);
}

void ssr::ptc_control(int w) {//PID control
  /*
  
  transfer fn'
  
  */
  int x = map(w, 0, 100, 0, 255);
  analogWrite(ptc, x);
}

void ssr::heatpump_control(int w) {//ON/OFF control
  /*
  
  transfer fn'
  
  */
  int x = (w > 50) * 5;
  digitalWrite(htpmp, x);
}

void ssr::fan_control(int w) {
  /*
  
  transfer fn'
  
  */
  int x = map(w, 0, 100, 0, 255);
  analogWrite(fan, x);
}

void ssr::P_control(int w) {//P control - for tuning
  int x = map(w, 0, 100, 0, 255);
  if (x > 10) {
    analogWrite(ptc, x);
    digitalWrite(htpmp, HIGH);
    analogWrite(fan, x);
  }
  else {
    analogWrite(ptc, 0);
    digitalWrite(htpmp, LOW);
    analogWrite(fan, 0);
  }
}

#endif