#ifndef ERFASSEN_H
#define ERFASSEN_H

#include <QDialog>

namespace Ui {
class Erfassen;
}

/**
 * @brief The Erfassen class
 * Header-Datei für die Klasse "erfassen"
 */
class Erfassen : public QDialog
{
    Q_OBJECT

public:
    explicit Erfassen(QWidget *parent = 0);
    ~Erfassen();
    void loadTransaktion(int tid);
    int tID;

private slots:
    void on_btn_ErAbbrechen_clicked();

    void on_btn_ErErfassen_clicked();

private:
    Ui::Erfassen *ui;
    void updateComboBox();
};

#endif // ERFASSEN_H
