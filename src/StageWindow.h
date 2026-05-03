#pragma once
#include <QWidget>

class QStackedWidget;
class QKeyEvent;

class StageWindow : public QWidget {
    Q_OBJECT
public:
    enum class Content { Black, Logo };

    explicit StageWindow(QWidget* parent = nullptr);

    void activateOnScreen(int screenIndex);
    void deactivate();

    bool    isActive()          const { return isVisible(); }
    int     activeScreenIndex() const { return m_screenIndex; }
    Content currentContent()    const { return m_content; }

public slots:
    void showBlack();
    void showLogo();
    void softHide();
    void softShow();

signals:
    void activated(int screenIndex);
    void deactivated();
    void contentChanged(StageWindow::Content content);

protected:
    void keyPressEvent(QKeyEvent* event) override;

private:
    QStackedWidget* m_stack       = nullptr;
    Content         m_content     = Content::Black;
    int             m_screenIndex = -1;
};
