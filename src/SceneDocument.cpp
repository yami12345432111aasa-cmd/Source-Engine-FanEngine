#include "SceneDocument.h"
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

void SceneDocument::reset()
{
    objects.clear();
    objects.push_back({"Camera", "Camera", 0, 2, -5});
    objects.push_back({"Directional Light", "Light", 0, 4, 0});
}

bool SceneDocument::save(const QString &path, QString *error) const
{
    QJsonArray array;
    for (const auto &item : objects) {
        QJsonObject o;
        o["name"] = item.name;
        o["type"] = item.type;
        o["x"] = item.x; o["y"] = item.y; o["z"] = item.z;
        array.append(o);
    }
    QJsonObject root;
    root["format"] = "FanEngineScene";
    root["version"] = 1;
    root["objects"] = array;
    QFile file(path);
    if (!file.open(QIODevice::WriteOnly)) {
        if (error) *error = file.errorString();
        return false;
    }
    file.write(QJsonDocument(root).toJson(QJsonDocument::Indented));
    return true;
}

bool SceneDocument::load(const QString &path, QString *error)
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)) {
        if (error) *error = file.errorString();
        return false;
    }
    QJsonParseError parseError;
    const auto doc = QJsonDocument::fromJson(file.readAll(), &parseError);
    if (parseError.error != QJsonParseError::NoError || !doc.isObject()) {
        if (error) *error = parseError.errorString();
        return false;
    }
    QVector<SceneObject> loaded;
    for (const auto value : doc.object()["objects"].toArray()) {
        const auto o = value.toObject();
        SceneObject item;
        item.name = o["name"].toString("Object");
        item.type = o["type"].toString("Empty");
        item.x = float(o["x"].toDouble());
        item.y = float(o["y"].toDouble());
        item.z = float(o["z"].toDouble());
        loaded.push_back(item);
    }
    objects = loaded;
    return true;
}
