#include "component1impl.h"
#include <QDebug>

void CComponent1Impl::methodX1() {
    qDebug() << "methodX1 in CComponent1Impl called";
}

int CComponent1Impl::methodX2() {
    qDebug() << "methodX2 in CComponent1Impl called";
    return 0;
}

double CComponent1Impl::methodX3() {
    qDebug() << "methodX3 in CComponent1Impl called";
    return 0;
}

void CComponent1Impl::methodY1() {
    qDebug() << "methodY1 in CComponent1Impl called";
}

double CComponent1Impl::methodY2() {
    qDebug() << "methodY2 in CComponent1Impl called";
    return 0;
}

int CComponent1Impl::methodY3() {
    qDebug() << "methodY3 in CComponent1Impl called";
    return 0;
}
