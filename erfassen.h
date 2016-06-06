#ifndef ERFASSEN_H
#define ERFASSEN_H

#include <QDialog>

namespace Ui {
class Erfassen;
}

class Erfassen : public QDialog
{
    Q_OBJECT

public:
    explicit Erfassen(QWidget *parent = 0);
    ~Erfassen();

private slots:
    void on_btn_ErAbbrechen_clicked();

    void on_btn_ErErfassen_clicked();

private:
    Ui::Erfassen *ui;
};

#endif // ERFASSEN_H
