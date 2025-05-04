#include <iostream>
#include <csignal>
#include <atomic>
#include <thread>
#include <chrono>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics/Image.hpp>

#include "KrakenImage.hpp"

// Global atomic flag to track whether the program should keep running
std::atomic<bool> running(true);

// Signal handler for clean shutdown
void handleSignal(int signal) {
    if (signal == SIGTERM || signal == SIGINT) {
        std::cout << "Received signal " << signal << ", exiting...\n";
        running = false;
    }
}

int main() {
    // Register signal handlers
    std::signal(SIGTERM, handleSignal);
    std::signal(SIGINT, handleSignal);

    const bool sendToKraken = true;
    const int sleepTimeSeconds = 1;

    KrakenImage krakenImage;

    while (running && krakenImage.isRunning()) {
        krakenImage.getTemperature();
        krakenImage.generateImage();

        if (sendToKraken) {
            krakenImage.sendToDisplay();
        }

        std::this_thread::sleep_for(std::chrono::seconds(sleepTimeSeconds));
    }

    std::cout << "Program shut down cleanly.\n";
    return 0;
}