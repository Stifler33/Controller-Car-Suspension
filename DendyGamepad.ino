/*
белый		    pin_data 			D10
синий		    pin_clock			D12
коричневый	pin_latch			D11
желтый +5В
красный GND
select =  223 32
start =   239 16
left =    253 2
right =   254 1
up =      247 8
down =    251 4
B =       191 64
A =       127 128

turbo B = 191 64
turbo A = 127 128
*/
//подключаемые пины
const int pin_data = 10;
const int pin_latch = 11;
const int pin_clock = 12;
const int pin_speacker = 13;
//пины для управления реле накачки и спуска
const int pin_relay_FR_up = 9;
const int pin_relay_FR_down = 8;
const int pin_relay_FL_up = 7;
const int pin_relay_FL_down = 6;
const int pin_relay_RR_up = 5;
const int pin_relay_RR_down = 4;
const int pin_relay_RL_up = 3;
const int pin_relay_RL_down = 2;
//значения при нажатии кнопок
const int select = 223;
const int start = 239;
const int left = 253;
const int right = 254;
const int up = 247;
const int down = 251;
const int B = 191;
const int A = 127;
const int A_B = 63;
const int up_A = 119;
const int up_B = 183;
const int down_B = 187;
const int down_A = 123;
const int select_start = 207;
const int left_A = 125;
const int left_B = 189;
const int right_A = 126;
const int right_B = 190;
const int zero = 255;
//false скачиваем, true накачиваем.
bool flag_pump = false;

bool hi = LOW;
bool low = HIGH;

int bufferNew = 0;
int bufferOld = 0;
const int TICK = 2;

void init_pin_relay()
{
  pinMode(pin_relay_FR_down, OUTPUT);
  pinMode(pin_relay_FL_down, OUTPUT);
  pinMode(pin_relay_RR_down, OUTPUT);
  pinMode(pin_relay_RL_down, OUTPUT);
  pinMode(pin_relay_FR_up, OUTPUT);
  pinMode(pin_relay_FL_up, OUTPUT);
  pinMode(pin_relay_RR_up, OUTPUT);
  pinMode(pin_relay_RL_up, OUTPUT);
}

void relay_all_off()
{
  digitalWrite(pin_relay_FR_down, low);
  digitalWrite(pin_relay_FL_down, low);
  digitalWrite(pin_relay_RR_down, low);
  digitalWrite(pin_relay_RL_down, low);
  digitalWrite(pin_relay_FR_up, low);
  digitalWrite(pin_relay_FL_up, low);
  digitalWrite(pin_relay_RR_up, low);
  digitalWrite(pin_relay_RL_up, low);
}
//поднять переднюю ось
void up_front_axis()
{
  digitalWrite(pin_relay_FR_up, hi);
  digitalWrite(pin_relay_FL_up, hi);
}
//поднять заднюю ось
void up_rear_axis()
{
  digitalWrite(pin_relay_RR_up, hi);
  digitalWrite(pin_relay_RL_up, hi);
}
//опустить переднюю ось
void down_front_axis()
{
  digitalWrite(pin_relay_FR_down, hi);
  digitalWrite(pin_relay_FL_down, hi);
}
//опустить заднюю ось
void down_rear_axis()
{
  digitalWrite(pin_relay_RR_down, hi);
  digitalWrite(pin_relay_RL_down, hi);
}
//поднять переднее правое колесо
void up_FR_wheel()
{
  digitalWrite(pin_relay_FR_up, hi);  
}
//поднять переднее левое колесо
void up_FL_wheel()
{
  digitalWrite(pin_relay_FL_up, hi);  
}
//поднять заднее правое колесо
void up_RR_wheel()
{
  digitalWrite(pin_relay_RR_up, hi);  
}
//подкнять заднее левое колесо
void up_RL_wheel()
{
  digitalWrite(pin_relay_RL_up, hi);  
}
//опустить переднее правое колесо
void down_FR_wheel()
{
  digitalWrite(pin_relay_FR_down, hi);
}
//опустить переднее левое колесо
void down_FL_wheel()
{
  digitalWrite(pin_relay_FL_down, hi);
}
//опустить заднее правое колесо
void down_RR_wheel()
{
  digitalWrite(pin_relay_RR_down, hi);
}
//опустить заднее левое колесо
void down_RL_wheel()
{
  digitalWrite(pin_relay_RL_down, hi);
}
//поднять весь авто
void up_all()
{
  digitalWrite(pin_relay_FR_up, hi);
  digitalWrite(pin_relay_FL_up, hi);
  digitalWrite(pin_relay_RR_up, hi);
  digitalWrite(pin_relay_RL_up, hi);
}
//опустить весь авто
void down_all()
{
  digitalWrite(pin_relay_FR_down, hi);
  digitalWrite(pin_relay_FL_down, hi);
  digitalWrite(pin_relay_RR_down, hi);
  digitalWrite(pin_relay_RL_down, hi);
}
//инициализация пинов джоистика
void init_joystick(int pin_data, int pin_latch, int pin_clock)
{
    pinMode(pin_data, INPUT);
    pinMode(pin_clock, OUTPUT);
    pinMode(pin_latch, OUTPUT);

    digitalWrite(pin_clock, HIGH);
}
//получение значений нажатых кнопок
int get_keys_state_joystick(int pin_data, int pin_latch, int pin_clock)
{
    digitalWrite(pin_latch, HIGH);
    delayMicroseconds(TICK);
    digitalWrite(pin_latch, LOW);

    int keys_state = 0;

    for (int i = 0; i < 8; ++i) {
        delayMicroseconds(TICK);
        digitalWrite(pin_clock, LOW);

        keys_state <<= 1;
        keys_state += digitalRead(pin_data);

        delayMicroseconds(TICK);
        digitalWrite(pin_clock, HIGH);
    }
    return keys_state;
}

void start_tone()
{
    tone(pin_speacker, 500);
    delay(500);
    tone(pin_speacker, 600);
    delay(100);
    tone(pin_speacker, 700);
    delay(100);
    tone(pin_speacker, 800, 100); 
}

void start_test_relay()
{
  delay(700);
  digitalWrite(pin_relay_FR_down, hi);
  delay(700);
  digitalWrite(pin_relay_FL_down, hi);
  delay(700);
  digitalWrite(pin_relay_RR_down, hi);
  delay(700);
  digitalWrite(pin_relay_RL_down, hi);
  delay(700);
  digitalWrite(pin_relay_FR_up, hi);
  delay(700);
  digitalWrite(pin_relay_FL_up, hi);
  delay(700);
  digitalWrite(pin_relay_RR_up, hi);
  delay(700);
  digitalWrite(pin_relay_RL_up, hi);
  delay(700);
}
void setup()
{        
    start_tone();
    init_joystick(pin_data, pin_latch, pin_clock);
    init_pin_relay();    
    //relay_all_off();
    //start_test_relay();
    relay_all_off();
    Serial.begin(9600);  
}

void loop()
{
    bufferNew = get_keys_state_joystick(pin_data, pin_latch, pin_clock);
    delay(10);
    if (bufferNew != bufferOld)
    {
      switch (bufferNew) {
        case select:
          Serial.println("select");
          flag_pump = false;
          tone(pin_speacker, 600, 100);
          break;
        case start:
          Serial.println("start");
          tone(pin_speacker, 800, 100);
          flag_pump = true;
          break;
        case left:
          Serial.println("left");          
          down_all();
          break;
        case right:
          Serial.println("right");        
          up_all();
          break;
        case up:
          Serial.println("up");          
          if(flag_pump){
            up_front_axis();
          }else down_front_axis();
          break;
        case down:
          Serial.println("down");          
          if(flag_pump){
            up_rear_axis();
          }else down_rear_axis();
          break;
        case B:
          Serial.println("B");
          relay_all_off();          
          break;
        case A:
          Serial.println("A");
          relay_all_off();          
          break;
        case A_B:
          Serial.println("A+B");  
          break;
        case up_A:
          if(flag_pump){
            up_FR_wheel();
          }else down_FR_wheel();
          Serial.println("up+A");  
          break;
        case up_B:
          if(flag_pump){
            up_FL_wheel();
          }else down_FL_wheel();
          Serial.println("up+B");  
          break;
        case down_B:
          if(flag_pump){
            up_RL_wheel();
          }else down_RL_wheel();
          Serial.println("down+B");  
          break;
        case down_A:
          if(flag_pump){
            up_RR_wheel();
          }else down_RR_wheel();
          Serial.println("down+A");  
          break;
        case select_start:
          Serial.println("select + start");          
          break;
        case left_A:
          Serial.println("left + A");
          break;
        case left_B:
          Serial.println("left + B");
          break;
        case right_B:
          Serial.println("right + B");
          break;
        case right_A:
          Serial.println("right + A");
          break;
        case zero:
          relay_all_off();
          //Serial.println("zero");
          break;
        default:        
          relay_all_off();
          break;
      }      
      bufferNew = bufferOld;      
    }
}