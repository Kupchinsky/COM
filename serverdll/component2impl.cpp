#include "component2impl.h"
#include <QDebug>

void CComponent2Impl::methodX1() {
    qDebug() << "methodX1 in CComponent2Impl called";
}

int CComponent2Impl::methodX2() {
    qDebug() << "methodX2 in CComponent2Impl called";
    return 0;
}

double CComponent2Impl::methodX3() {
    qDebug() << "methodX3 in CComponent2Impl called";
    return 0;
}

void CComponent2Impl::methodY1() {
    qDebug() << "methodY1 in CComponent2Impl called";
}

double CComponent2Impl::methodY2() {
    qDebug() << "methodY2 in CComponent2Impl called";
    return 0;
}

int CComponent2Impl::methodY3() {
    qDebug() << "methodY3 in CComponent2Impl called";
    return 0;
}
