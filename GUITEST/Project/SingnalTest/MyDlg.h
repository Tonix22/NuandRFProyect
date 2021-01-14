#include <QDialog>
#include <QHBoxLayout>
#include <QPushButton>
#include <QDebug>

class MyDlg : public QDialog
{
    Q_OBJECT
    private:    
    QPushButton *pBttn;
    QHBoxLayout *pLayout;

    public:
        MyDlg();
    private slots:
        void onButtonClicked();
};