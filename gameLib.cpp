#include "Arduino.h";
#include "GameLib.h";
#include <Adafruit_GFX.h>;




GameLib::GameLib(Adafruit_SH1106G* displayObject){
    _display = displayObject;
}

void GameLib::print(){
    Serial.println("testdd");
}

void GameLib::begin() {
    _display->begin(0x3c    , true);
    _display->clearDisplay();
    _display->setTextSize(1);
    _display->setTextColor(SH110X_WHITE);
  }

void GameLib::addText(int xPos, int yPos, const char* content){
    _display->setCursor(xPos, yPos);
    _display->println(content);
    _display->display();
    Serial.println("okay called");

};
