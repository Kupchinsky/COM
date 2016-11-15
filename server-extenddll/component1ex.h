#ifndef COMPONENT1EX_H
#define COMPONENT1EX_H

#include "../unknown.h"
#include "../serverdll/component1.h"

#define CLSID_ComponentEx1 1

#define IID_IComponentEx1face IID_IClassFactoryPseudo + 1
#define IID_IComponentEx1ClassFactory IID_IClassFactoryPseudo + 2

class IComponentEx1face: public virtual IUnknownPseudo,
        public virtual IComponent1faceX,
        public virtual IComponent1faceY {
public:
    // Methods from original IComponent1faceX
    virtual void methodX1() = 0;
    virtual int methodX2() = 0;
    virtual double methodX3() = 0;

    // Methods from original IComponent1faceY
    virtual void methodY1() = 0;
    virtual double methodY2() = 0;
    virtual int methodY3() = 0;

    // New methods
    virtual void methodX4() = 0;
};

class IComponentEx1ClassFactory: public IClassFactoryPseudo {
};
#endif // COMPONENT1EX_H
