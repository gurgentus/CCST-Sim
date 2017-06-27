#ifndef CONTROLLABLE_H
#define CONTROLLABLE_H


class Controllable
{
public:
    Controllable();
    virtual void UpdateControls() = 0;
};

#endif // CONTROLLABLE_H
