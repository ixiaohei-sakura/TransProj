//
// Created by lhhlu on 2/10/2023.
//

#ifndef UNTITLED_POWERSUPPLY_H
#define UNTITLED_POWERSUPPLY_H


class PowerSupply {
public:
    PowerSupply(unsigned char bat_5, unsigned char on_board_5, unsigned char bat_stat);
    void setup() const;
    double batVoltage() const;
    double obVoltage() const;
    double batPercentage() const;

private:
    unsigned char bat = -1, ob = -1, stat = -1;
};


#endif //UNTITLED_POWERSUPPLY_H
