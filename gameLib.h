#include <Adafruit_SH110X.h> 

class GameLib {
    public:
        GameLib(Adafruit_SH1106G* displayObject);
        void print(); 
        void begin(); 
        void updateScreen();
        void addText(int xPos, int yPos, const char* content, int weight, float velocity, bool affectGravity);
        
        private:
        Adafruit_SH1106G* _display;
        void displayText(int xPos, int yPos, const char* content);
        void handleElem(struct Object);
        void calcGravity(struct Object);
};