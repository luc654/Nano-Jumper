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


void GameLib::begin() {
    _display->begin();
    _display->clearDisplay();
    _display->setTextSize(1);
    _display->setTextColor(SH110X_WHITE);
    _display->display();
  }


void GameLib::addText(int xPos, int yPos, const char* content){
    if (id > maxElem) { return;};
    
    TextProperties txt = {content};

    screenElements[id].xPos = xPos;
    screenElements[id].yPos = yPos;
    screenElements[id].data.textProperties = txt;
    screenElements[id].id = id;
    screenElements[id].type = TEXT;

    
    id++;
}


void GameLib::updateScreen(){
    for (int16_t index = 0; index < maxElem; index++ ){
        handleElem(screenElements[index]);
    }
    
    _display->display();
    
};


//  
// Private
// 


void GameLib::handleElem(Object element){
    switch(element.type){
        case TEXT:
        displayText(element.xPos, element.yPos, element.data.textProperties.content);
        break;
        
        default:
        
        break;
    }
}

void GameLib::displayText(int xPos, int yPos, const char* content){
    _display->setCursor(xPos, yPos);
    _display->println(content);
}

