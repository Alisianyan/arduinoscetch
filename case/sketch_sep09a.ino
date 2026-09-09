#define BTN_PIN 3

enum class States {
    On,
    Blink_1,
    Blink_2,
    Blink_3,
    Off,
    _len,
};

States state = States::On;

// функция возвращает true при нажатии кнопки
bool buttonClick() {
    static bool pState;
    bool state = !digitalRead(BTN_PIN);

    if (pState != state) {
        pState = state;
        delay(20);
        return state;
    }

    return false;
}

void setup() {
    pinMode(BTN_PIN, INPUT_PULLUP);
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(4, OUTPUT);
    pinMode(5, OUTPUT);
    pinMode(6, OUTPUT);
}

void loop() {
    if (buttonClick()) {
        // переключить с переполнением
        state = States((int)state + 1);
        if (state == States::_len) state = States(0);
    }

    // постоянный вызов согласно режиму
    switch (state) {
        case States::On:
              digitalWrite(4, HIGH);
              digitalWrite(5, HIGH);
              digitalWrite(6, HIGH);
            break;

        case States::Off:
              digitalWrite(4, LOW);
              digitalWrite(5, LOW);
              digitalWrite(6, LOW);
            break;

        case States::Blink_1:
              digitalWrite(4, HIGH);
              digitalWrite(5, LOW);
              digitalWrite(6, LOW);
            break;

        case States::Blink_2:
              digitalWrite(5, HIGH);
              digitalWrite(6, LOW);
              digitalWrite(4, LOW);
            break;
            
        case States::Blink_3:
              digitalWrite(6, HIGH);
              digitalWrite(5, LOW);
              digitalWrite(4, LOW);
            break;
        default: break;
    }
}
