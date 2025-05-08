#ifndef MENU_H
#define MENU_H

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define MENU_ITEM_HEIGHT 10  // Height for each menu item

class Menu {
public:
    // Pass a pointer to an initialized SSD1306 display object
    Menu(Adafruit_SSD1306* display)
      : display(display)
    {}

    // Call this function periodically and pass the current encoder count.
    int updateMenu(long encoderCount) {
        // Calculate selected menu index (wrap around)
        int selectedIndex = (int)(encoderCount % menuItemCount);
        if (selectedIndex < 0) {
            selectedIndex += menuItemCount;
        }

        // Clear display buffer
        display->clearDisplay();
        display->setTextSize(1);
        display->setTextWrap(false);

        // Render each menu item
        int y = 0;
        for (int i = 0; i < menuItemCount; i++) {
            if (i == selectedIndex) {
                // Invert the current selected item:
                // First, fill a rectangle with white for inverted background.
                display->fillRect(0, y, SCREEN_WIDTH, MENU_ITEM_HEIGHT, SSD1306_WHITE);
                // Then, draw text in black.
                display->setTextColor(SSD1306_BLACK);
            } else {
                // Normal text: white on black background.
                display->setTextColor(SSD1306_WHITE);
            }
            display->setCursor(0, y + 2); // Slight y offset for better centering
            display->println(menuItems[i]);
            y += MENU_ITEM_HEIGHT;
        }
        display->display();
        return selectedIndex; // Return the index of the selected menu item
    }

private:
    Adafruit_SSD1306* display;
    // Define menu items
    static const int menuItemCount = 3;
    const char* menuItems[menuItemCount] = {
        " 1: Motor&Measure",
        " 2: Send Bluetooth",
        " 3: Calibrate(admin)"
    };
};

#endif  // MENU_H