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
    int weight;
    float velocity;
    bool affectGravity;
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


  void GameLib::addText(const TextOptions& options) {
    if (id > maxElem) { return; }

    TextProperties txt = { options.getText() };

    screenElements[id].xPos = options.getX();
    screenElements[id].yPos = options.getY();
    screenElements[id].weight = options.weight;
    screenElements[id].velocity = 0;
    screenElements[id].affectGravity = options.affectGravity;
    screenElements[id].data.textProperties = txt;
    screenElements[id].id = id;
    screenElements[id].type = TEXT;

    id++;
}



void GameLib::updateScreen(){
    _display->clearDisplay();
    for (int16_t index = 0; index < maxElem; index++ ){
        if(screenElements[index].affectGravity){
            calcGravity(screenElements[index]);
        }
        handleElem(screenElements[index]);
    }
    
    _display->display();
    
};


//  
// Private
// 

void GameLib::calcGravity(Object element){
    if(element.velocity == 0){
        element.velocity = 2;
    } else {
        // Gravity formula
        element.velocity = element.velocity * (100 + element.weight) / 100;
    }

    if (element.velocity > 20){
        element.velocity = 20;
    }
    
    screenElements[element.id].velocity = element.velocity;
    screenElements[element.id].yPos = element.yPos + element.velocity;
}

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

