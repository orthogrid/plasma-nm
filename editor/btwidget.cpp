/*
    Copyright 2013 Lukas Tinkl <ltinkl@redhat.com>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) version 3, or any
    later version accepted by the membership of KDE e.V. (or its
    successor approved by the membership of KDE e.V.), which shall
    act as a proxy defined in Section 6 of version 3 of the license.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <KLocalizedString>

#include "btwidget.h"
#include "ui_bt.h"
#include "uiutils.h"


BtWidget::BtWidget(const NetworkManager::Settings::Setting::Ptr &setting, QWidget* parent, Qt::WindowFlags f):
    SettingWidget(setting, parent, f),
    m_ui(new Ui::BtWidget),
    m_btSetting(setting.staticCast<NetworkManager::Settings::BluetoothSetting>())
{
    m_ui->setupUi(this);

    m_ui->type->addItem(i18n("DUN (dial up networking)"), NetworkManager::Settings::BluetoothSetting::Dun);
    m_ui->type->addItem(i18n("PAN (personal area network)"), NetworkManager::Settings::BluetoothSetting::Panu);

    m_ui->type->setEnabled(false);

    if (setting)
        loadConfig(setting);
}

BtWidget::~BtWidget()
{
}

void BtWidget::loadConfig(const NetworkManager::Settings::Setting::Ptr &setting)
{
    Q_UNUSED(setting);

    m_ui->bdaddr->setText(UiUtils::macAddressAsString(m_btSetting->bluetoothAddress()));
    m_ui->type->setCurrentIndex(m_ui->type->findData(m_btSetting->profileType()));
}

QVariantMap BtWidget::setting() const
{
    if (!m_ui->bdaddr->text().isEmpty())
        m_btSetting->setBluetoothAddress(UiUtils::macAddressFromString(m_ui->bdaddr->text()));
    m_btSetting->setProfileType(static_cast<NetworkManager::Settings::BluetoothSetting::ProfileType>(m_ui->type->itemData(m_ui->type->currentIndex()).toInt()));

    return m_btSetting->toMap();
}
