#pragma once

#include <QtWidgets/QWidget>
#include "ui_HyperSearch.h"

class HyperSearch : public QWidget
{
    Q_OBJECT

public:
    HyperSearch(QWidget *parent = Q_NULLPTR);

private:
    Ui::HyperSearchClass ui;
};
