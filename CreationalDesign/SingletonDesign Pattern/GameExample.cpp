// Singleton Design Pattern
//  Define a class that has only one instance and provides a global point of access to it.

#include <iostream>
#include <string>

class GameSetting
{
private:
    static GameSetting *_instance;
    int _brightness;
    int _width;
    int _height;
    GameSetting() : _width(786), _height(1300), _brightness(75) {}
    GameSetting(const GameSetting &) = delete;
    GameSetting &operator=(const GameSetting &) = delete;

public:
    static GameSetting *getInstance()
    {
        if (_instance == NULL)
        {
            _instance = new GameSetting();
        }
        return _instance;
    }
    void setWidth(int width)
    {
        _width = width;
    }
    void setHeight(int height)
    {
        _height = height;
    }
    void setBrightness(int brightness)
    {
        _brightness = brightness;
    }
    int getWidth()
    {
        return _width;
    }
    int getHeight()
    {
        return _height;
    }
    int getBrightness()
    {
        return _brightness;
    }
    void displaySetting()
    {
        std::cout << "brightness: " << _brightness << std::endl;
        std::cout << "width: " << _width << std::endl;
        std::cout << "height: " << _height << std::endl;
    }

    // destructors
    ~GameSetting()
    {
        delete _instance;
    }
};

GameSetting *GameSetting::_instance = nullptr;

int main()
{
    GameSetting *setting = GameSetting::getInstance();
    setting->displaySetting();
    setting->setBrightness(100);
    setting->setHeight(500);
    setting->setWidth(1000);
    setting->displaySetting();
    return 0;
}
