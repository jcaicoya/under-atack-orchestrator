#include "AlertBanner.h"
#include "BottomNavBar.h"
#include "CyberBackgroundWidget.h"
#include "CyberPanel.h"
#include "CyberTheme.h"
#include "MetricCard.h"

#include <QApplication>
#include <QHBoxLayout>
#include <QLabel>
#include <QPlainTextEdit>
#include <QVBoxLayout>
#include <QWidget>

// Minimal example for a runtime/operator screen.
// This file is intentionally standalone enough to be copied into a Qt Widgets app.

class RuntimeScreenExample : public CyberBackgroundWidget {
public:
    explicit RuntimeScreenExample(QWidget* parent = nullptr) : CyberBackgroundWidget(parent) {
        qApp->setStyleSheet(CyberTheme::globalStyleSheet());

        auto* root = new QVBoxLayout(this);
        root->setContentsMargins(32, 26, 32, 0);
        root->setSpacing(16);

        auto* title = new QLabel(QStringLiteral("Centro de control"), this);
        title->setObjectName("ScreenTitle");
        root->addWidget(title);

        auto* content = new QHBoxLayout();
        content->setSpacing(14);
        root->addLayout(content, 1);

        auto* leftColumn = new QVBoxLayout();
        leftColumn->setSpacing(14);
        content->addLayout(leftColumn, 2);

        auto* alert = new AlertBanner(this);
        alert->setSeverity(AlertBanner::Severity::Critical);
        alert->setMessage(QStringLiteral("CREDENCIAL INTERCEPTADA"));
        leftColumn->addWidget(alert);

        auto* logPanel = new CyberPanel(QStringLiteral("Eventos de tráfico"), this);
        auto* log = new QPlainTextEdit(this);
        log->setReadOnly(true);
        log->setPlainText(QStringLiteral(
            "[15:10:00] DemoPhone -> google.com [SEARCH]\n"
            "[15:10:01] DemoPhone -> whatsapp.net [WHATSAPP]\n"
            "[15:10:02] DemoPhone -> amazon.es [SHOPPING]\n"
            "[15:10:03] DemoPhone -> portal.local [CREDENTIAL]\n"));
        log->setStyleSheet(QStringLiteral(
            "QPlainTextEdit { font-family: 'Consolas', 'JetBrains Mono', monospace; color: #00FF55; font-size: 12px; }"));
        logPanel->bodyLayout()->addWidget(log);
        leftColumn->addWidget(logPanel, 1);

        auto* rightColumn = new QVBoxLayout();
        rightColumn->setSpacing(14);
        content->addLayout(rightColumn, 1);

        auto* statusPanel = new CyberPanel(QStringLiteral("Estado del sistema"), this);
        auto* status = new QLabel(QStringLiteral(
            "● Router: activo\n"
            "● Dispositivos: 3\n"
            "● Modo: LIVE\n"
            "● Portal: preparado"), this);
        status->setObjectName("StatusOk");
        statusPanel->bodyLayout()->addWidget(status);
        rightColumn->addWidget(statusPanel);

        auto* metric = new MetricCard(this);
        metric->setLabel(QStringLiteral("RIESGO"));
        metric->setValue(QStringLiteral("100"));
        metric->setSubtitle(QStringLiteral("CRÍTICO"));
        metric->setAccentColor(CyberTheme::color(CyberTheme::Error));
        rightColumn->addWidget(metric);
        rightColumn->addStretch(1);

        auto* nav = new BottomNavBar(this);
        nav->setItems(QStringList{
            QStringLiteral("Principal"),
            QStringLiteral("Dispositivos"),
            QStringLiteral("Mapa"),
            QStringLiteral("Riesgo"),
            QStringLiteral("Cifrado")
        });
        root->addWidget(nav);
    }
};

// Example usage:
// int main(int argc, char** argv) {
//     QApplication app(argc, argv);
//     RuntimeScreenExample window;
//     window.resize(1600, 900);
//     window.show();
//     return app.exec();
// }
