#pragma once
#include <QList>
#include <QString>
#include <QStringList>

struct RundownItem {
    QString type;    // "app" or "media"
    QString ref;     // id of the referenced entry
};

class RundownConfig {
public:
    bool loadFromFile(const QString& path);
    bool saveToFile(const QString& path) const;

    // Adds new app/media ids not yet in the rundown (disabled), removes stale refs.
    void syncWithLibraries(const QStringList& appIds, const QStringList& mediaIds);

    const QList<RundownItem>& items() const { return m_items; }
    void setItems(const QList<RundownItem>& items) { m_items = items; }

    void moveUp(int index);
    void moveDown(int index);

private:
    QList<RundownItem> m_items;
};
