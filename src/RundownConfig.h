#pragma once
#include <QList>
#include <QString>
#include <QStringList>

struct RundownItem {
    QString type;    // "app", "android", or "media"
    QString ref;     // id of the referenced entry
};

class RundownConfig {
public:
    bool loadFromFile(const QString& path);
    bool saveToFile(const QString& path) const;
    static bool copyDefaultTo(const QString& path);

    // Adds new Qt/Android/media ids not yet in the rundown, removes stale refs.
    void syncWithLibraries(const QStringList& appIds,
                           const QStringList& androidIds,
                           const QStringList& mediaIds);

    const QList<RundownItem>& items() const { return m_items; }
    void setItems(const QList<RundownItem>& items) { m_items = items; }

    void moveUp(int index);
    void moveDown(int index);

private:
    QList<RundownItem> m_items;
};
