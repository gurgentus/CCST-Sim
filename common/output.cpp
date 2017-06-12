#include "output.h"

void Output::setValue(double value) {
    setText(QString::number(value*scale));
}
