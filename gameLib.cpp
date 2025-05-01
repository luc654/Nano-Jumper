#include "Arduino.h";
#include "GameLib.h";
#include <Adafruit_GFX.h>;

#define maxElem 10

int16_t id = 0;
enum ElementType { TEXT };

struct TextProperties{
    const char* content;
};

struct Object{
    int xPos;
    int yPos;
    int id;
    ElementType type;
    union {
        TextProperties textProperties;
    } data;
};

Object screenElements[maxElem];


GameLib::GameLib(Adafruit_SH1106G* displayObject){
    _display = displayObject;
};

void GameLib::print(){
    Serial.println("testdd");
};

void GameLib::begin() {
    _display->begin(0x3c, true);
    _display->clearDisplay();
    _display->setTextSize(1);
    _display->setTextColor(SH110X_WHITE);
  }


void GameLib::addText(int xPos, int yPos, const char* content){
    if (id > maxElem) { return;};
    
    TextProperties txt = {content};

    screenElements[id].xPos = xPos;
    screenElements[id].yPos = yPos;
    screenElements[id].id = id;
    screenElements[id].type = TEXT;

    id++;
}

void GameLib::updateScreen(){

};


//  
// Private
// 



// void displayText(int xPos, int yPos, const char* content){
//     _display->setCursor(xPos, yPos);
//     _display->println(content);
// }