#ifndef RESULT_CHECKER_H
#define RESULT_CHECKER_H

#include <QDebug>
#include <windows.h>

class InvalidResultException: public std::exception {
    HRESULT result;
public:
    InvalidResultException(HRESULT result) {
        this->result = result;
    }

    virtual const char* what() const throw() {
        return (QString("Not successfull result: ") + QString::number(result)).toStdString().c_str();
    }
};

class ResultChecker {
public:
    static void check(HRESULT result) {
        if (result != S_OK) {
            throw InvalidResultException(result);
        }
    }
};
#endif // RESULT_CHECKER_H
