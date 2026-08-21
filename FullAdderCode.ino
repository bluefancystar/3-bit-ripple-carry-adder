int switch_pin = 15;
int power_pin = 16;
int seven_seg_pwr = 17;

int seg_A = 4;
int seg_B = 13;
int seg_C = 14;
int seg_D = 18;
int seg_E = 19;
int seg_F = 21;
int seg_G = 22;

int first_bit = 26;
int second_bit = 25;
int third_bit = 27;
int fourth_bit = 32;

// 0 = LOW, 1 = HIGH
int rep_zero[7] = { 1, 1, 1, 1, 1, 1, 0 };
int rep_one[7] = { 0, 1, 1, 0, 0, 0, 0 };
int rep_two[7] = { 1, 1, 0, 1, 1, 0, 1 };
int rep_three[7] = { 1, 1, 1, 1, 0, 0, 1};
int rep_four[7] = { 0, 1, 1, 0, 0, 1, 1};
int rep_five[7] = { 1, 0, 1, 1, 0, 1, 1};
int rep_six[7] = { 1, 0, 1, 1, 1, 1, 1};
int rep_seven[7] = { 1, 1, 1, 0, 0, 0, 0};
int rep_eight[7] = { 1, 1, 1, 1, 1, 1, 1 };
int rep_nine[7] = { 1, 1, 1, 1, 0 , 1, 1};
int rep_ten[7] = { 1, 1, 1, 0, 1, 1, 1};
int rep_eleven[7] = { 0, 0, 1, 1, 1, 1, 1};
int rep_twelve[7] = { 1, 0, 0, 1, 1, 1, 0};
int rep_thirteen[7] = { 0, 1, 1, 1, 1, 0, 1};
int rep_fourteen[7] = { 1, 0, 0, 1, 1, 1, 1};
int rep_fifteen[7] = { 1, 0, 0, 0, 1, 1, 1} ;

// reads values coming from input switches and does binary conversion
int Read_Value()
{

  int bit_1;
  int bit_2;
  int bit_3;
  int bit_4;

  if (digitalRead(first_bit) == HIGH) { bit_1 = 1; }
  else { bit_1 = 0; }

  if (digitalRead(second_bit) == HIGH) { bit_2 = 1; }
  else { bit_2 = 0; }

  if (digitalRead(third_bit) == HIGH) { bit_3 = 1; }
  else { bit_3 = 0; }

  if (digitalRead(fourth_bit) == HIGH) { bit_4 = 1; }
  else { bit_4 = 0; }

  // truth table and decoder
  if      (bit_1 == 1 && bit_2 == 1 && bit_3 == 1 && bit_4 == 1) { return 15; }
  else if (bit_1 == 1 && bit_2 == 1 && bit_3 == 1 && bit_4 == 0) { return 14; }
  else if (bit_1 == 1 && bit_2 == 1 && bit_3 == 0 && bit_4 == 1) { return 13; }
  else if (bit_1 == 1 && bit_2 == 1 && bit_3 == 0 && bit_4 == 0) { return 12; }
  else if (bit_1 == 1 && bit_2 == 0 && bit_3 == 1 && bit_4 == 1) { return 11; }
  else if (bit_1 == 1 && bit_2 == 0 && bit_3 == 1 && bit_4 == 0) { return 10; }
  else if (bit_1 == 1 && bit_2 == 0 && bit_3 == 0 && bit_4 == 1) { return 9;  }
  else if (bit_1 == 1 && bit_2 == 0 && bit_3 == 0 && bit_4 == 0) { return 8;  }
  else if (bit_1 == 0 && bit_2 == 1 && bit_3 == 1 && bit_4 == 1) { return 7;  }
  else if (bit_1 == 0 && bit_2 == 1 && bit_3 == 1 && bit_4 == 0) { return 6;  }
  else if (bit_1 == 0 && bit_2 == 1 && bit_3 == 0 && bit_4 == 1) { return 5;  }
  else if (bit_1 == 0 && bit_2 == 1 && bit_3 == 0 && bit_4 == 0) { return 4;  }
  else if (bit_1 == 0 && bit_2 == 0 && bit_3 == 1 && bit_4 == 1) { return 3;  }
  else if (bit_1 == 0 && bit_2 == 0 && bit_3 == 1 && bit_4 == 0) { return 2;  }
  else if (bit_1 == 0 && bit_2 == 0 && bit_3 == 0 && bit_4 == 1) { return 1;  }
  else if (bit_1 == 0 && bit_2 == 0 && bit_3 == 0 && bit_4 == 0) { return 0;  }

}

// sets up the digital write function to display one-hot outputs on seven segment display
void Display_Value(int values[], int size)
{

  digitalWrite(seg_A, values[0]);
  digitalWrite(seg_B, values[1]);
  digitalWrite(seg_C, values[2]);
  digitalWrite(seg_D, values[3]);
  digitalWrite(seg_E, values[4]);
  digitalWrite(seg_F, values[5]);
  digitalWrite(seg_G, values[size - 1]);

}

void setup() 
{
  // configures each pin being used on the ESP32
  pinMode(switch_pin, INPUT_PULLUP);
  pinMode(power_pin, OUTPUT);
  pinMode(seven_seg_pwr, OUTPUT);
  
  pinMode(seg_A, OUTPUT);
  pinMode(seg_B, OUTPUT);
  pinMode(seg_C, OUTPUT);
  pinMode(seg_D, OUTPUT);
  pinMode(seg_E, OUTPUT);
  pinMode(seg_F, OUTPUT);
  pinMode(seg_G, OUTPUT);

  pinMode(first_bit, INPUT);
  pinMode(second_bit, INPUT);
  pinMode(third_bit, INPUT);
  pinMode(fourth_bit, INPUT);

  // begins Serial Monitor with 9600 baud rate
  Serial.begin(9600);

}

void loop() 
{
  // power switch for the circuit
  if (digitalRead(switch_pin) == LOW) { digitalWrite(power_pin, HIGH); digitalWrite(seven_seg_pwr, LOW); }
  else { digitalWrite(power_pin, LOW); digitalWrite(seven_seg_pwr, HIGH); }

  // seven-seg display statements
  if      (Read_Value() == 15) { Serial.println("Output: F"); Display_Value(rep_fifteen, 7); }
  else if (Read_Value() == 14) { Serial.println("Output: E"); Display_Value(rep_fourteen, 7); }
  else if (Read_Value() == 13) { Serial.println("Output: D"); Display_Value(rep_thirteen, 7); }
  else if (Read_Value() == 12) { Serial.println("Output: C"); Display_Value(rep_twelve, 7); }
  else if (Read_Value() == 11) { Serial.println("Output: B"); Display_Value(rep_eleven, 7); }
  else if (Read_Value() == 10) { Serial.println("Output: A"); Display_Value(rep_ten, 7); }
  else if (Read_Value() == 9)  { Serial.println("Output: 9"); Display_Value(rep_nine, 7); }
  else if (Read_Value() == 8)  { Serial.println("Output: 8"); Display_Value(rep_eight, 7); }
  else if (Read_Value() == 7)  { Serial.println("Output: 7"); Display_Value(rep_seven, 7); }
  else if (Read_Value() == 6)  { Serial.println("Output: 6"); Display_Value(rep_six, 7); }
  else if (Read_Value() == 5)  { Serial.println("Output: 5"); Display_Value(rep_five, 7); }
  else if (Read_Value() == 4)  { Serial.println("Output: 4"); Display_Value(rep_four, 7); }
  else if (Read_Value() == 3)  { Serial.println("Output: 3"); Display_Value(rep_three, 7); }
  else if (Read_Value() == 2)  { Serial.println("Output: 2"); Display_Value(rep_two, 7); }
  else if (Read_Value() == 1)  { Serial.println("Output: 1"); Display_Value(rep_one, 7); }
  else if (Read_Value() == 0)  { Serial.println("Output: 0"); Display_Value(rep_zero, 7); }

}
