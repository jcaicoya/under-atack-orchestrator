#include "CyberBackgroundWidget.h"
#include "CyberTheme.h"

#include <QApplication>
#include <QFrame>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

// Minimal example of a setup screen using CyberBackgroundWidget.
// This file is only a reference. You can copy the layout ideas into each app.

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    app.setStyleSheet(CyberTheme::globalStyleSheet());

    CyberBackgroundWidget window;
    window.setWindowTitle("Cybershow Setup Example");
    window.resize(1280, 720);

    auto* root = new QVBoxLayout(&window);
    root->setContentsMargins(48, 48, 48, 48);
    root->setSpacing(14);
    root->addStretch(1);

    auto* title = new QLabel("MÓDULO DE EJEMPLO");
    title->setObjectName("ScreenTitle");
    title->setAlignment(Qt::AlignCenter);
    root->addWidget(title);

    auto* subtitle = new QLabel("Configuración técnica");
    subtitle->setObjectName("ScreenSubtitle");
    subtitle->setAlignment(Qt::AlignCenter);
    root->addWidget(subtitle);

    auto* panel = new QFrame;
    panel->setObjectName("CyberPanel");
    panel->setFixedWidth(460);

    auto* panelLayout = new QVBoxLayout(panel);
    panelLayout->setContentsMargins(24, 24, 24, 24);
    panelLayout->setSpacing(12);

    auto* modeLabel = new QLabel("Modo de ejecución");
    modeLabel->setObjectName("FieldLabel");
    panelLayout->addWidget(modeLabel);

    auto* modeField = new QLineEdit("Actuación real");
    panelLayout->addWidget(modeField);

    auto* statusLabel = new QLabel("ESTADO DEL SISTEMA");
    statusLabel->setObjectName("MutedLabel");
    panelLayout->addSpacing(8);
    panelLayout->addWidget(statusLabel);

    auto* statusText = new QLabel("● Conexión móvil: activa\n● Servidor local: preparado\n● Modo: actuación real");
    statusText->setStyleSheet("color: #00C78C; line-height: 140%;");
    panelLayout->addWidget(statusText);

    auto* secondary = new QPushButton("Probar conexión");
    secondary->setObjectName("SecondaryButton");
    panelLayout->addSpacing(8);
    panelLayout->addWidget(secondary);

    auto* start = new QPushButton("INICIAR SHOW");
    start->setObjectName("PrimaryButton");
    panelLayout->addWidget(start);

    auto* panelRow = new QHBoxLayout;
    panelRow->addStretch(1);
    panelRow->addWidget(panel);
    panelRow->addStretch(1);
    root->addLayout(panelRow);

    root->addStretch(2);

    window.show();
    return app.exec();
}
