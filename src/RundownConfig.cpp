#include "RundownConfig.h"
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <algorithm>

bool RundownConfig::loadFromFile(const QString& path) {
    QFile f(path);
    if (!f.exists()) return true;   // missing = empty rundown, not an error
    if (!f.open(QIODevice::ReadOnly)) return false;

    QJsonParseError err;
    auto doc = QJsonDocument::fromJson(f.readAll(), &err);
    if (err.error != QJsonParseError::NoError) return false;

    m_items.clear();
    for (const auto val : doc.array()) {
        const QJsonObject obj = val.toObject();
        RundownItem item;
        item.type    = obj["type"].toString();
        item.ref     = obj["ref"].toString();
        if (!item.type.isEmpty() && !item.ref.isEmpty())
            m_items.append(item);
    }
    return true;
}

bool RundownConfig::saveToFile(const QString& path) const {
    QJsonArray arr;
    for (const auto& item : m_items) {
        QJsonObject obj;
        obj["type"]    = item.type;
        obj["ref"]     = item.ref;
        arr.append(obj);
    }

    QDir().mkpath(QFileInfo(path).absolutePath());
    QFile f(path);
    if (!f.open(QIODevice::WriteOnly)) return false;
    f.write(QJsonDocument(arr).toJson());
    return true;
}

void RundownConfig::syncWithLibraries(const QStringList& appIds, const QStringList& mediaIds) {
    // Remove items whose ref no longer exists in any library
    m_items.erase(
        std::remove_if(m_items.begin(), m_items.end(), [&](const RundownItem& item) {
            if (item.type == "app")   return !appIds.contains(item.ref);
            if (item.type == "media") return !mediaIds.contains(item.ref);
            return true;
        }),
        m_items.end());

    for (const QString& id : appIds) {
        bool found = std::any_of(m_items.begin(), m_items.end(),
            [&](const RundownItem& i) { return i.type == "app" && i.ref == id; });
        if (!found)
            m_items.append({"app", id});
    }

    for (const QString& id : mediaIds) {
        bool found = std::any_of(m_items.begin(), m_items.end(),
            [&](const RundownItem& i) { return i.type == "media" && i.ref == id; });
        if (!found)
            m_items.append({"media", id});
    }
}

void RundownConfig::moveUp(int index) {
    if (index > 0 && index < m_items.size())
        m_items.swapItemsAt(index, index - 1);
}

void RundownConfig::moveDown(int index) {
    if (index >= 0 && index < m_items.size() - 1)
        m_items.swapItemsAt(index, index + 1);
}
