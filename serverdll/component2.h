#ifndef COMPONENT2_H
#define COMPONENT2_H

#include "unknown.h"

#define CLSID_Component2 2

#define IID_IComponent2faceX 1
#define IID_IComponent2faceY 2
#define IID_IComponent2ClassFactory 3

class IComponent2faceX: public IUnknownPseudo {
public:
    virtual void methodX1() = 0;
    virtual int methodX2() = 0;
    virtual double methodX3() = 0;
};

class IComponent2faceY: public IUnknownPseudo {
public:
    virtual void methodY1() = 0;
    virtual double methodY2() = 0;
    virtual int methodY3() = 0;
};

class IComponent2ClassFactory: public IClassFactoryPseudo {
};
#endif // COMPONENT2_H
