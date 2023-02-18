//
// Created by lhhlu on 2/9/2023.
//

#ifndef UNTITLED_BUTTON_H
#define UNTITLED_BUTTON_H


class Button {
public:
    explicit Button(unsigned char p);
    void setup() const;
    void setState(bool s);
    bool getPreviousState() const;
    bool readPin() const;

private:
    unsigned char pin;
    bool state = false;
};


#endif //UNTITLED_BUTTON_H
