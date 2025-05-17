#include <Adafruit_SH110X.h> 


class BlockOptions {
private:
    int startX = 0;
    int startY = 0;
    int endX = 0;
    int endY = 0;
    bool collision = false;

    int respawnTime = 40;
    int weight = 0;
    bool affectGravity = false;
    bool respawn = false;
    

public:
    BlockOptions& setPosition(int startX, int startY, int endX, int endY) {
        this->startX = startX;
        this->startY = startY;
        this->endX = endX;
        this->endY = endY;
        return *this;
    }

    BlockOptions& setCollision(bool collision) {
        this->collision = collision;
        return *this;
    }

    int getStartX() const {
        return this->startX;
    }

    int getStartY() const {
        return this->startY;
    }

    int getEndX() const {
        return this->endX;
    }

    int getEndY() const {
        return this->endY;
    }

    bool hasCollision() const {
        return this->collision;
    }


        BlockOptions& setWeight(int weight) {
            this->weight = weight;
            return *this;
        }

        BlockOptions& setAffectGravity(bool affect) {
            this->affectGravity = affect;
            return *this;
        }

        BlockOptions& setCanRespawn(bool respawn){
            this->respawn = respawn;
            return *this;
        }

        BlockOptions& setRespawnTime(int respawnTime){
            this->respawnTime = respawnTime;
            return *this;
        }


        int getWeight() const {
            return this->weight;
        }
    
        bool affectsGravity() const {
            return this->affectGravity;
        }
    
        bool canRespawn() const {
            return this->respawn;
        }

        int getRespawnTime() const {
            return this-> respawnTime;
        }


    friend class GameLib;
};



class TextOptions {
    private:
        int x = 0;
        int y = 0;
        const char* text = "";
        int respawnTime = 40;
        int weight = 0;
        bool affectGravity = false;
        bool respawn = false;
    
    public:
        TextOptions& setPosition(int x, int y) {
            this->x = x;
            this->y = y;
            return *this;
        }
    
        TextOptions& setContent(const char* t) {
            this->text = t;
            return *this;
        }
    
    
        TextOptions& setWeight(int weight) {
            this->weight = weight;
            return *this;
        }

        TextOptions& setAffectGravity(bool affect) {
            this->affectGravity = affect;
            return *this;
        }

        TextOptions& setCanRespawn(bool respawn){
            this->respawn = respawn;
            return *this;
        }

        TextOptions& setRespawnTime(int respawnTime){
            this->respawnTime = respawnTime;
            return *this;
        }

        int getX() const {
            return this->x;
        }
    
        int getY() const {
            return this->y;
        }

        int getWeight() const {
            return this->weight;
        }
    
        const char* getText() const {
            return this->text;
        }
    
        bool affectsGravity() const {
            return this->affectGravity;
        }
    
        bool canRespawn() const {
            return this->respawn;
        }

        int getRespawnTime() const {
            return this-> respawnTime;
        }
        friend class GameLib;
    };
    




    class GameLib {
        public:
            GameLib(Adafruit_SH1106G* displayObject);
            void print(); 
            void begin(); 
            void updateScreen();
            void addText(const TextOptions& opts);
            void addBlock(const BlockOptions& opts);
            
            private:
            Adafruit_SH1106G* _display;
            void displayText(int xPos, int yPos, const char* content);
            void handleElem(struct Object);
            void calcGravity(struct Object);
    };
    