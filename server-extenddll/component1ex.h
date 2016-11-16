#ifndef COMPONENT1EX_H
#define COMPONENT1EX_H

#include "../unknown.h"
#include "../serverdll/component1.h"

#define CLSID_ComponentEx1 3

#define IID_IComponentEx1face IID_IClassFactoryPseudo + 4
#define IID_IComponentEx1ClassFactory IID_IClassFactoryPseudo + 5

class IComponentEx1face: public virtual IUnknownPseudo {
public:
    // New methods
    virtual void methodX4() = 0;
};

class IComponentEx1ClassFactory: public IClassFactoryPseudo {
};
#endif // COMPONENT1EX_H
