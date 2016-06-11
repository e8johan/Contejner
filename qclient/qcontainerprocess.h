/*
 * Contejner - a d-bus interface to cgroups and namespaces
 * Copyright (C) 2016 Johan Thelin
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#ifndef QCONTAINERPROCESS_H
#define QCONTAINERPROCESS_H

#include <QProcess>

class QContainerEnvironment
{
public:
    QContainerEnvironment();
    QContainerEnvironment(const QContainerEnvironment &);
    ~QContainerEnvironment();
};

class QContainerProcess : public QIODevice
{
    Q_OBJECT

public:
    QContainerProcess(QObject *parent = Q_NULLPTR);
    ~QContainerProcess();

    // Starting
    void start(const QString &program, const QStringList &arguments, OpenMode mode = ReadWrite);
    void start(const QString &command, OpenMode mode = ReadWrite);
    void start(OpenMode mode = ReadWrite);
    bool open(OpenMode mode = ReadWrite) Q_DECL_OVERRIDE;

    // Configuration
    QString program() const;
    void setProgram(const QString &);

    QStringList arguments() const;
    void setArguments(const QStringList &);

    QProcessEnvironment processEnvironment() const;
    void setProcessEnvironment(const QProcessEnvironment &);

    QString workingDirectory() const;
    void setWorkingDirectory(const QString &);

    QContainerEnvironment containerEnvironment() const;
    void setContainerEnvironment(const QContainerEnvironment &);

    // IO Setup
    QProcess::ProcessChannelMode readChannelMode() const;
    void setReadChannelMode(QProcess::ProcessChannelMode mode);
    QProcess::ProcessChannelMode processChannelMode() const;
    void setProcessChannelMode(QProcess::ProcessChannelMode mode);
    QProcess::InputChannelMode inputChannelMode() const;
    void setInputChannelModel(QProcess::InputChannelMode mode);

    QProcess::ProcessChannel readChannel() const;
    void setReadChannel(QProcess::ProcessChannel channel);

    void closeReadChannel(QProcess::ProcessChannel channel);
    void closeWriteChannel();

    void setStandardInputFile(const QString &fileName, OpenMode mode = Truncate);
    void setStandardOutputFile(const QString &fileName);
    void setStandardErrorFile(const QString &fileName, OpenMode mode = Truncate);

    // State and errors
    QProcess::ProcessState state();

    qint64 processId() const;

    QProcess::ProcessError error() const;

    int exitCode() const;
    QProcess::ExitStatus exitStatus() const;

    // Waiting
    bool waitForStarted(int msecs = 30000);
    bool waitForFinished(int msecs = 30000);

    // from QIODevice
    bool atEnd() const Q_DECL_OVERRIDE;
    qint64 bytesAvailable() const Q_DECL_OVERRIDE;
    qint64 bytesToWrite() const Q_DECL_OVERRIDE;
    bool isSequential() const Q_DECL_OVERRIDE;
    bool canReadLine() const Q_DECL_OVERRIDE;
    void close() Q_DECL_OVERRIDE;

    bool waitForReadyRead(int msecs = 30000) Q_DECL_OVERRIDE;
    bool waitforBytesWritten(int msecs = 30000) Q_DECL_OVERRIDE;

    // Static helpers
    bool startDetached(const QString &program, const QStringList &arguments, const QString &workingDirectory = QString(), quint64 *pid = Q_NULLPTR);
    bool startDetached(const QString &command);

public slots:
    void kill();
    void terminate();

signals:
    void errorOccurred(QProcess::ProcessError error);
    void finished(int exitCore, QProcess::ExitStatus exitStatus);
    void readyReadStandardError();
    void readyReadStandardOutput();
    void started();
    void stateChanged(QProcess::ProcessState newState);
};

#endif // QCONTAINERPROCESS_H
