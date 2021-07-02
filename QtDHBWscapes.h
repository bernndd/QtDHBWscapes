#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtDHBWscapes.h"

class QtDHBWscapes : public QMainWindow
{
    Q_OBJECT

public:
    QtDHBWscapes(QWidget *parent = Q_NULLPTR);

private:
    Ui::QtDHBWscapesClass ui;
};
