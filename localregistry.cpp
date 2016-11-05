#include "localregistry.h"

#include <QDebug>
#include <QIODevice>

unique_ptr<CLocalRegistry> CLocalRegistry::instance;

QJsonObject& CLocalRegistry::getRoot() {
    return this->root;
}

QJsonValueRef CLocalRegistry::getComponentsSection(QJsonObject &jsonObject) {
    QJsonValueRef valueRef = this->root[JSON_COMPONENTS_SECTION];

    if (!valueRef.isObject()) {
        valueRef = QJsonObject();
    }

    jsonObject = valueRef.toObject();
    return valueRef;
}

bool CLocalRegistry::queryComponentModule(_REFCLSID rclsid, QString &outPath) {
    QJsonObject componentsRoot;
    this->getComponentsSection(componentsRoot);

    QJsonValue componentValue = componentsRoot[QString::number(rclsid)];

    if (componentValue.isString()) {
        outPath = componentValue.toString();
        return true;
    } else {
        return false;
    }
}

void CLocalRegistry::insertComponentModule(_REFCLSID rclsid, QString path) {
    QJsonObject componentsRoot;
    QJsonValueRef componentsRef = this->getComponentsSection(componentsRoot);

    componentsRoot.insert(QString::number(rclsid), QJsonValue(path));
    componentsRef = componentsRoot;
}

void CLocalRegistry::removeComponent(_REFCLSID rclsid) {
    QJsonObject componentsRoot;
    QJsonValueRef componentsRef = this->getComponentsSection(componentsRoot);

    componentsRoot.remove(QString::number(rclsid));
    componentsRef = componentsRoot;
}

void CLocalRegistry::write() {
    QJsonDocument jsonDocument(this->root);
    QByteArray byteArray = jsonDocument.toJson();

    QFile file(JSON_PATH);
    file.open(QIODevice::WriteOnly);
    file.write(byteArray);
    file.close();

    qDebug() << "Local registry updated";
}

unique_ptr<CLocalRegistry>& CLocalRegistry::getInstance() {
    if (CLocalRegistry::instance != NULL) {
        return CLocalRegistry::instance;
    }

    QFile file(JSON_PATH);
    QJsonObject jsonObject;

    if (file.exists()) {
        file.open(QIODevice::ReadOnly);
        QByteArray byteArray = file.readAll();
        file.close();

        QJsonDocument jsonDocument = QJsonDocument::fromJson(byteArray);
        jsonObject = jsonDocument.object();
    }

    CLocalRegistry::instance = unique_ptr<CLocalRegistry>(new CLocalRegistry(jsonObject));

    qDebug() << "Local registry loaded";
    return CLocalRegistry::instance;
}
