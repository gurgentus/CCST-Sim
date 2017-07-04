#include "Output.hpp"

void Output::setValue(double value) {
    setText(QString::number(value*scale));
}
