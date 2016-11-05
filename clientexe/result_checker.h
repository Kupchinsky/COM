#ifndef RESULT_CHECKER_H
#define RESULT_CHECKER_H

#include <QDebug>
#include <QException>
#include "../unknown.h"

class InvalidResultException: public QException {
    _HRESULT result;
public:
    InvalidResultException(_HRESULT result) {
        this->result = result;
    }

    QString what() {
        return QString("Not successfull result: ") + QString::number(result);
    }
};

class ResultChecker {
public:
    static void check(_HRESULT result) {
        if (result != _S_OK) {
            throw InvalidResultException(result);
        }
    }
};
#endif // RESULT_CHECKER_H
