#pragma once

#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QString>

namespace DefaultConfigUtils {

inline bool copyResourceDefaultTo(const QString& resourcePath, const QString& destPath) {
    QFile src(resourcePath);
    if (!src.open(QIODevice::ReadOnly))
        return false;

    QDir().mkpath(QFileInfo(destPath).dir().absolutePath());

    QFile dst(destPath);
    if (!dst.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;

    dst.write(src.readAll());
    return true;
}

}  // namespace DefaultConfigUtils
