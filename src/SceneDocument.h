#pragma once
#include <QString>
#include <QVector>

struct SceneObject {
    QString name;
    QString type;
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
};

class SceneDocument
{
public:
    QVector<SceneObject> objects;
    void reset();
    bool load(const QString &path, QString *error = nullptr);
    bool save(const QString &path, QString *error = nullptr) const;
};
