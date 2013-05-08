/***************************************************************************
 *   Copyright (C) 2013 by Daniel Nicoletti <dantti12@gmail.com>           *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; see the file COPYING. If not, write to       *
 *   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,  *
 *   Boston, MA 02110-1301, USA.                                           *
 ***************************************************************************/

#include "Description.h"
#include "ui_Description.h"

#include "TabDeviceInfo.h"
#include "TabDeviceAdvanced.h"

#include <QStringBuilder>
#include <QtDBus/QDBusInterface>
#include <QtDBus/QDBusReply>

#include <KGlobal>
#include <KLocale>
#include <KDateTime>
#include <KToolInvocation>
#include <KDebug>
#include <KMessageWidget>
#include <KMessageBox>

#include <NetworkManagerQt/Manager>

Description::Description(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Description)
{
    ui->setupUi(this);
}

Description::~Description()
{
    delete ui;
}

int Description::innerHeight() const
{
    int height;
    if (ui->tabWidget->currentWidget()) {
        height = ui->tabWidget->currentWidget()->height();
    } else {
        int tab = ui->tabWidget->addTab(new QWidget, "TabDeviceAdvanced.h");
        height = ui->tabWidget->currentWidget()->height();
        ui->tabWidget->removeTab(tab);
    }
    return height;
}

void Description::setDevice(const QString &uni)
{
    int i = 0;
    while (i < ui->tabWidget->count()) {
        ui->tabWidget->removeTab(i);
    }

    NetworkManager::Device::Ptr device = NetworkManager::findNetworkInterface(uni);
    if (device) {
        TabDeviceInfo *tabDeviceInfo = new TabDeviceInfo(this);
        tabDeviceInfo->setDevice(device);
        ui->tabWidget->addTab(tabDeviceInfo, i18n("Information"));

        TabDeviceAdvanced *tabDeviceAdvanced = new TabDeviceAdvanced(this);
        tabDeviceAdvanced->setDevice(device);
        ui->tabWidget->addTab(tabDeviceAdvanced, i18n("Advanced"));
    }
}

#include "Description.moc"
