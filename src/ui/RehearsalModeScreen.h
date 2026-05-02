#pragma once
#include <QWidget>
#include <QTableWidget>
#include <QTextEdit>
#include <QPushButton>
#include "AppConfig.h"
#include "AppManager.h"
#include "MediaConfig.h"
#include "MediaManager.h"
#include "RundownConfig.h"

class RehearsalModeScreen : public QWidget {
    Q_OBJECT
public:
    explicit RehearsalModeScreen(const QString& packageRoot, QWidget* parent = nullptr);
    ~RehearsalModeScreen() override = default;

signals:
    void returnToSelector();

protected:
    void keyPressEvent(QKeyEvent* event) override;
    void showEvent(QShowEvent* event) override;

private slots:
    void onStateChanged(const QString& id, AppState state);
    void onMediaStateChanged(const QString& id, MediaState state);
    void onLogMessage(const QString& formatted);

private:
    void buildUI();
    void syncAndRefresh();
    void populateTable();
    void updateRow(int row);
    int  rowForRef(const QString& type, const QString& id) const;

    const AppEntry*   appEntryForId(const QString& id) const;
    const MediaEntry* mediaEntryForId(const QString& id) const;

    QString        m_packageRoot;
    QString        m_rundownPath;

    AppConfig      m_appConfig;
    MediaConfig    m_mediaConfig;
    RundownConfig  m_rundownConfig;

    AppManager*    m_appManager   = nullptr;
    MediaManager*  m_mediaManager = nullptr;

    QTableWidget*  m_table        = nullptr;
    QPushButton*   m_stopAllBtn   = nullptr;
    QTextEdit*     m_logPanel     = nullptr;
};
