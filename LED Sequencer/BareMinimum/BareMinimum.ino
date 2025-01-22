// libraries
#include <Toggle.h>

// initialize variables

// LEDs
int led_pin_number[] = {9, 10, 11, 12, 13};
int number_of_leds = sizeof(led_pin_number) / sizeof(led_pin_number[0]);;

// buttons
int button_pin_number[] = {2};
int number_of_buttons = sizeof(button_pin_number) / sizeof(button_pin_number[0]);
Toggle button;

// flags
int flag = 0;

// time
int time = 125;

// list of states in the system
enum {REST, STATE_R, STATE_RY, STATE_RYG, STATE_RYGB, STATE_RYGBW} current_state;

// this function runs the finite state machine
void run_finite_state_machine() {
  // update the button's state
  button.poll();

  // this switch statement will help us determine which state
  // we are in in order to determine what actions we must do
  switch (current_state) {
    // if we are in the REST state, then when we press the
    // button we would move to STATE_R and turn on the red LED
    case REST:
      if (button.onPress()) {
        for (int i = 0; i < 1; i++) {
          // turn on the red LED only
          digitalWrite(led_pin_number[i], HIGH);
        }

        // set the current state to the next state STATE_R
        current_state = STATE_R;
      }
      break;

    // if we are in STATE_R, then when we press the button we
    // would move to STATE_RY and turn on the red and yellow LEDs
    case STATE_R:
      if (button.onPress()) {
        for (int i = 0; i < 2; i++) {
          // turn on the red and yellow LEDs
          digitalWrite(led_pin_number[i], HIGH);
        }

        // set the current state to the next state STATE_RY
        current_state = STATE_RY;
      }
      break;

    // if we are in STATE_RY, then when we press the button we would
    // move to STATE_RYG and turn on the red, yellow, and green LEDs
    case STATE_RY:
      if (button.onPress()) {
        for (int i = 0; i < 3; i++) {
          // turn on the red, yellow, and green LEDs
          digitalWrite(led_pin_number[i], HIGH);
        }

        // set the current state to the next state STATE_RYG
        current_state = STATE_RYG;
      }
      break;

    // if we are in STATE_RYG, then when we press the button we would move
    // to STATE_RYGB and turn on the red, yellow, green, and blue LEDs
    case STATE_RYG:
      if (button.onPress()) {
        for (int i = 0; i < 4; i++) {
          // turn on the red, yellow, green, and blue LEDs
          digitalWrite(led_pin_number[i], HIGH);
        }

        // set the current state to the next state STATE_RYGB
        current_state = STATE_RYGB;
      }
      break;

    // if we are in STATE_RYGB, then when we press the button we would move to
    // STATE_RYGBW and turn on the red, yellow, green, blue, and white LEDs
    case STATE_RYGB:
      if (button.onPress()) {
        for (int i = 0; i < number_of_leds; i++) {
          // turn on the red, yellow, green, blue, and white LEDs
          digitalWrite(led_pin_number[i], HIGH);
        }

        // set the current state to the next state STATE_RYGBW
        current_state = STATE_RYGBW;
      }
      break;

    // if we are in STATE_RYGBW, then when we press the button
    // we would move to the REST state and turn off all the LEDs
    case STATE_RYGBW:
      if (button.onPress()) {
        turn_off_LEDs();

        // set the current state to the next state REST
        current_state = REST;
      }
      break;
  }
}

// this function will turn off all LEDs
void turn_off_LEDs() {
  // since we are turning off an LED, it will be easier to code
  // this function in a way that turns off all LEDs at once
  for (int i = 0; i < number_of_leds; i++) {
    digitalWrite(led_pin_number[i], LOW);
  }
}

void setup() {
  // put your setup code here, to run once:

  // create serial monitor
  Serial.begin(9600);

  // set LED pins as output signals
  for (int i = 0; i < number_of_leds; i++) {
    pinMode(led_pin_number[i], OUTPUT);
  }

  // set button pin as an input signal
  button.begin(button_pin_number[0]);

  // initially have all LEDs off
  turn_off_LEDs();

  // set the initial state in finite state machine as REST
  current_state = REST;
}

void loop() {
  // put your main code here, to run repeatedly:

  /*
  for (int i = 0; i < number_of_leds; i++) {
    digitalWrite(led_pin_number[i], HIGH);
    delay(time);
    digitalWrite(led_pin_number[i], LOW);
  }
  */

  // run the finite state machine where it
  // gets updated based on possible events
  run_finite_state_machine();
}
