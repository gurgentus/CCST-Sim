#ifndef DYNAMICCONTROL_H
#define DYNAMICCONTROL_H

#include "cst/transferfunction.h"
#include "cst/pfd.h"
#include "control.h"

class DynamicControl : public Control
{
public:
    DynamicControl();
    void stepResponse(double ss);
    void setTfControl(bool flag);
    void updateFromTF();
    void setFValue(int value);
private:
    double elapsedTime = 0;
    QTimer *timer;
    Pfd pfd;
    bool tfControl = false;
};

#endif // DYNAMICCONTROL_H
