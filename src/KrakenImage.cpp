#include "KrakenImage.hpp"

KrakenImage::KrakenImage() {
    if (!font.openFromFile("fonts/BebasNeue-Regular.ttf")) {
        std::cerr << "sf::Font::openFromFile() error" << sf::err << '\n';
        running = false;
    }

    renderTex = sf::RenderTexture({320, 320});
}

void KrakenImage::getTemperature() {
    std::ifstream file("/sys/class/hwmon/hwmon3/temp1_input");
    int millidegrees = 0;
    file >> millidegrees;
    file.close();
    temperature = millidegrees / 1000.0f;
}

void KrakenImage::generateImage() {
    sf::Text tempText(font);

    std::ostringstream oss;
    oss.precision(1);
    oss << std::fixed << temperature;
    std::string text = oss.str() + u8"°";

    sf::String finalText = sf::String::fromUtf8(text.begin(), text.end());

    tempText.setString(finalText);
    tempText.setCharacterSize(160);
    tempText.setFillColor(sf::Color::White);
    tempText.setPosition({160 - (tempText.getLocalBounds().size.x / 2), 160 - (tempText.getCharacterSize() / 2) - 60});

    textStartX = tempText.getPosition().x;
    textEndX = tempText.getPosition().x + tempText.getGlobalBounds().size.x;
    textStartY = tempText.getPosition().y;
    textEndY = tempText.getPosition().y + tempText.getCharacterSize();
    
    renderTex.clear(sf::Color::Black);
    renderTex.draw(tempText);
    drawTemperatureBar();
    renderTex.display();

    renderImg = renderTex.getTexture().copyToImage();
    renderImg.saveToFile("images/kraken-temp.png");
}

void KrakenImage::drawTemperatureBar() {
    float normalized = std::clamp((temperature - 0.f) / 100.f, 0.f, 1.f);

    const float width = (textEndX - textStartX) * normalized;
    const float height = 40.f;
    const float x = textStartX;
    const float y = textEndY + 40;

    sf::Color orange(255, 165, 0);
    sf::Color red(255, 0, 0);

    // Rectangle made of 2 triangles = 6 vertices
    sf::VertexArray gradient(sf::PrimitiveType::Triangles, 6);

    // First triangle: top-left, top-right, bottom-right
    gradient[0].position = {x, y};
    gradient[0].color = orange;

    gradient[1].position = {x + width, y};
    gradient[1].color = red;

    gradient[2].position = {x + width, y + height};
    gradient[2].color = red;

    // Second triangle: bottom-right, bottom-left, top-left
    gradient[3].position = {x + width, y + height};
    gradient[3].color = red;

    gradient[4].position = {x, y + height};
    gradient[4].color = orange;

    gradient[5].position = {x, y};
    gradient[5].color = orange;

    renderTex.draw(gradient);

    // Draw temperature indicator
    float indicatorX = x + width;

    sf::RectangleShape indicator({8.f, height});
    indicator.setFillColor(sf::Color::White);
    indicator.setPosition({indicatorX - 2.f, y - 2.f});

    renderTex.draw(indicator);
}

void KrakenImage::sendToDisplay() {
    system("liquidctl set --match 2023 lcd screen static images/kraken-temp.png");
}

bool KrakenImage::isRunning() { return running; }
