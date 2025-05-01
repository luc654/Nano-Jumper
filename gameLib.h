#include <Adafruit_SH110X.h> 

class GameLib {
    public:
        GameLib(Adafruit_SH1106G* displayObject);
        void print(); 
        void begin(); 
        void updateScreen();
        void addText(int xPos, int yPos, const char* content);
        
    private:
        Adafruit_SH1106G* _display;
        void displayText(int xPos, int yPos, const char* content);
};