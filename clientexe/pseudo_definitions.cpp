#include "pseudo_definitions.h"
#include <QString>

InvalidResultException::InvalidResultException(_HRESULT result) {
    this->result = result;
}

QString InvalidResultException::what() {
    return QString("Not successfull result: ") + QString::number(result);
}

void checkResult(_HRESULT result) {
    if (result != _S_OK) {
        throw InvalidResultException(result);
    }
}
