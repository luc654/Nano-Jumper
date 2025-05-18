#include "Arduino.h";
#include "GameLib.h";
#include <Adafruit_GFX.h>;

#define maxElem 10
#define screenHeight 64


int16_t id = 0;
enum ElementType { TEXT, 
    // BLOCK
 };

struct TextProperties{
    const char* content;
};
// struct BlockProperties{
//     bool collision;
//     int endX;
//     int endY;
// };
struct Object{
    int xPos;
    int yPos;
    int originalyPos;
    int weight;
    float velocity;
    bool affectGravity;
    bool canRespawn;
    int respawnTime;
    int respawnFrame;
    int id;
    ElementType type;
    union {
        TextProperties textProperties;
        BlockProperties blockProperties;
    } data;
};

Object screenElements[maxElem];


GameLib::GameLib(Adafruit_SH1106G* displayObject){
    _display = displayObject;
};


void GameLib::begin() {
    Serial.println("begin");
    _display->begin(0x3C, true);
    Serial.println("after display.begin()");
    _display->clearDisplay();
    _display->setTextSize(1);
    _display->setTextColor(SH110X_WHITE);
    _display->display();

  }


  void GameLib::addText(const TextOptions& options) {
    Serial.println("addText");
    if (id > maxElem) { return; }

    TextProperties txt = { options.getText() };

    screenElements[id].xPos = options.getX();
    screenElements[id].yPos = options.getY();
    screenElements[id].originalyPos = options.getY();
    screenElements[id].weight = options.weight;
    screenElements[id].velocity = 0;
    screenElements[id].affectGravity = options.affectGravity;
    screenElements[id].canRespawn = options.respawn;
    screenElements[id].respawnTime = options.respawnTime;
    screenElements[id].data.textProperties = txt;
    screenElements[id].id = id;
    screenElements[id].type = TEXT;

    id++;
}

// void GameLib::addBlock(const BlockOptions& options){
//     Serial.println("addBlock");
//     if (id > maxElem) { return; }
//     BlockProperties blk = { options.hasCollision(), options.getEndX(), options.getEndY() };
    
//     screenElements[id].xPos = options.getStartX();
//     screenElements[id].yPos = options.getStartY();
//     screenElements[id].originalyPos = options.getStartY();
//     screenElements[id].weight = options.weight;
//     screenElements[id].velocity = 0;
//     screenElements[id].affectGravity = options.affectGravity;
//     screenElements[id].canRespawn = options.respawn;
//     screenElements[id].respawnTime = options.respawnTime;
//     screenElements[id].id = id;
//     screenElements[id].type = BLOCK;


//     id++;
// }


void GameLib::updateScreen(){
    Serial.println("updateScreen");
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
    Serial.println("calcGravity");
    if(element.velocity == 0){
        element.velocity = 2;
    } else {
        // Gravity formula
        element.velocity = element.velocity * (100 + element.weight) / 100;
    }

    if (element.velocity > 20){
        element.velocity = 20;
    }
    
    if(element.yPos > (screenHeight + 10)){
        if(element.canRespawn){
            if(element.respawnFrame == element.respawnTime){
                element.yPos = element.originalyPos;
                screenElements[element.id].velocity = 0;
                screenElements[element.id].respawnFrame = 0;
                screenElements[element.id].yPos = element.yPos;
            } else {
                screenElements[element.id].respawnFrame = element.respawnFrame + 1;

            }
            } 
        } else {
            screenElements[element.id].velocity = element.velocity;
            screenElements[element.id].yPos = element.yPos + element.velocity;

        }

}

void GameLib::handleElem(Object element){
    Serial.println("handleElem");
    switch(element.type){
        case TEXT:
        displayText(element.xPos, element.yPos, element.data.textProperties.content);
        break;
        
        default:
        
        break;
    }
}

void GameLib::displayText(int xPos, int yPos, const char* content){
    Serial.println("displayText");
    _display->setCursor(xPos, yPos);
    _display->println(content);
}

