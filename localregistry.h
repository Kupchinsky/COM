#ifndef LOCALREGISTRY_H
#define LOCALREGISTRY_H

#include "unknown.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <memory>

// Static path!
#define JSON_PATH "X:/COM/localregistry.json"
#define JSON_COMPONENTS_SECTION "components"

using namespace std;

class CLocalRegistry {
    QJsonObject root;
    static unique_ptr<CLocalRegistry> instance;

    CLocalRegistry(QJsonObject _root): root(_root) {
    }

    QJsonValueRef getComponentsSection(QJsonObject &jsonObject);
public:
    QJsonObject& getRoot();

    bool queryComponentModule(_REFCLSID rclsid, QString &outPath);
    void insertComponentModule(_REFCLSID rclsid, QString path);
    void removeComponent(_REFCLSID rclsid);

    void write();

    static unique_ptr<CLocalRegistry>& getInstance();
};
#endif // LOCALREGISTRY_H
