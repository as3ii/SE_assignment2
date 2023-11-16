#include <LiquidCrystal_I2C.h> 
#include "LcdScreen.h"

LcdScreen::LcdScreen(){
    this->lcd.init();
    this->lcd.backlight();
}

void LcdScreen::setCursor(int x, int y) {
    this->lcd.setCursor(x,y);
}

void LcdScreen::print(char* text) {
    this->lcd.print(text);
}
