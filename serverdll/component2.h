#ifndef COMPONENT2_H
#define COMPONENT2_H

#include "../unknown.h"

#define CLSID_Component2 2

#define IID_IComponent2faceX IID_IClassFactoryPseudo + 1
#define IID_IComponent2faceY IID_IClassFactoryPseudo + 2
#define IID_IComponent2ClassFactory IID_IClassFactoryPseudo + 3

class IComponent2faceX: public virtual IUnknownPseudo {
public:
    virtual void methodX1() = 0;
    virtual int methodX2() = 0;
    virtual double methodX3() = 0;
};

class IComponent2faceY: public virtual IUnknownPseudo {
public:
    virtual void methodY1() = 0;
    virtual double methodY2() = 0;
    virtual int methodY3() = 0;
};

class IComponent2ClassFactory: public IClassFactoryPseudo {
};
#endif // COMPONENT2_H
