// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include <QDBusInterface>
#include <QObject>

namespace DDaemonInternal {
static const QString AudioServiceName("com.deepin.daemon.Audio");
static const QString AudioServiceInterface(AudioServiceName);
static const QString AudioPath("/com/deepin/daemon/Audio");

static const QString AudioServiceSinkInterface(AudioServiceInterface + ".Sink");
static const QString AudioServiceSinkInputInterface(AudioServiceSinkInterface + "Input");
static const QString AudioServiceSourceInterface(AudioServiceInterface + ".Source");
static const QString AudioServiceSourceOutputInterface(AudioServiceSourceInterface + ".Output");

static const QString SinkFlag("Sink");
static const QString SourceFlag("Source");
static const QString SinkInputFlag("SinkInput");
static const QString SourceOutputFlag("SourceOutput");
inline QDBusInterface audioInterface(const QString &path = AudioPath, const QString &interface = AudioServiceInterface)
{
    return QDBusInterface(AudioServiceName, path, interface);
}
inline QDBusInterface *newAudioInterface(const QString &path = AudioPath, const QString &interface = AudioServiceInterface)
{
    return new QDBusInterface(audioInterface(path, interface));
}
inline QString deviceName(const QString &path)
{
    auto subfix = path.mid(path.lastIndexOf("/") + 1);
    if (subfix.startsWith(SinkFlag))
        return subfix.mid(SinkFlag.size());
    if (subfix.startsWith(SourceFlag))
        return subfix.mid(SourceFlag.size());
    return subfix;
}
inline QString streamName(const QString &path)
{
    auto subfix = path.mid(path.lastIndexOf("/") + 1);
    if (subfix.startsWith(SinkInputFlag))
        return subfix.mid(SinkInputFlag.size());
    if (subfix.startsWith(SourceOutputFlag))
        return subfix.mid(SourceOutputFlag.size());
    return subfix;
}
}
