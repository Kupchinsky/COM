#include "localregistry.h"

#include <QDebug>

unique_ptr<CLocalRegistry> CLocalRegistry::instance;

QJsonObject CLocalRegistry::getRoot() {
    return this->document.object();
}

void CLocalRegistry::write() {
    QByteArray byteArray = this->document.toBinaryData();

    QFile file(JSON_PATH);
    file.write(byteArray);
    file.flush();

    qDebug() << "Local registry updated";
}

unique_ptr<CLocalRegistry>& CLocalRegistry::getInstance() {
    if (CLocalRegistry::instance != NULL) {
        return CLocalRegistry::instance;
    }

    QFile file(JSON_PATH);
    QByteArray byteArray = file.readAll();
    QJsonDocument jsonDocument =
            QJsonDocument::fromBinaryData(byteArray, QJsonDocument::DataValidation::BypassValidation);

    CLocalRegistry::instance = unique_ptr<CLocalRegistry>(new CLocalRegistry(jsonDocument));

    qDebug() << "Local registry loaded";
    return CLocalRegistry::instance;
}
