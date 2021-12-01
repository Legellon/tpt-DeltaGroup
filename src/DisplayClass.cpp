#include <LiquidCrystal_I2C.h>

class DisplayClass
{

public:
    DisplayClass(LiquidCrystal_I2C *lcd)
    {
        LCD = lcd;
        LCD->init();
        LCD->backlight();
    }

    int DisplayMessage(uint32_t messageID)
    {
        auto msg = Messages[messageID];
        size_t len = strlen(msg);
        return len;
    }

    ~DisplayClass()
    {
        delete[] LCD;
    }
private:
    enum MessageID : int
    {
        InputVelocity = 0,
        MovingVelocity = 1,
        EnumLenght = 2,
    };

    LiquidCrystal_I2C *LCD;

    const char* Messages[MessageID::EnumLenght] = {
        "Input a velocity of the platform:",
        "The platform is moving to the destination",
    };
};
