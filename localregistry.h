#ifndef LOCALREGISTRY_H
#define LOCALREGISTRY_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <memory>

// Static path!
#define JSON_PATH "X:\\COM\\localregistry.json"

using namespace std;

class CLocalRegistry {
    QJsonDocument document;
    static unique_ptr<CLocalRegistry> instance;

    CLocalRegistry(QJsonDocument& _document): document(_document) {
    }
public:
    QJsonObject getRoot();
    void write();

    static unique_ptr<CLocalRegistry>& getInstance();
};
#endif // LOCALREGISTRY_H
