#ifndef COMPONENT1_H
#define COMPONENT1_H

#include "unknown.h"

#define CLSID_Component1 1

#define IID_IComponent1faceX IID_IClassFactory + 1
#define IID_IComponent1faceY IID_IClassFactory + 2
#define IID_IComponent1ClassFactory IID_IClassFactory + 3

class IComponent1faceX: public IUnknownPseudo {
public:
    virtual void methodX1() = 0;
    virtual int methodX2() = 0;
    virtual double methodX3() = 0;
};

class IComponent1faceY: public IUnknownPseudo {
public:
    virtual void methodY1() = 0;
    virtual double methodY2() = 0;
    virtual int methodY3() = 0;
};

class IComponent1ClassFactory: public IClassFactoryPseudo {
};
#endif // COMPONENT1_H
