#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <unistd.h>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <cmath>

class KrakenImage {
public:
    KrakenImage();
    void getTemperature();
    void generateImage();
    void sendToDisplay();
    void drawTemperatureBar();
    bool isRunning();

private:
    sf::Font font;
    sf::Image renderImg;
    sf::RenderTexture renderTex;
    sf::Clock updateClock;

    float temperature;
    float textStartX, textEndX;
    float textStartY, textEndY;
    bool running = true;
};