#include "preferencesdialog.h"
#include "ui_preferencesdialog.h"

#include <QSettings>

PreferencesDialog::PreferencesDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PreferencesDialog)
{
    ui->setupUi(this);

    ui->lineEditTokenID->setText(QSettings().value("tokenID").toString());
}

PreferencesDialog::~PreferencesDialog()
{
    delete ui;
}

void PreferencesDialog::on_lineEditTokenID_editingFinished()
{
    QSettings().setValue("tokenID", ui->lineEditTokenID->text());
}
