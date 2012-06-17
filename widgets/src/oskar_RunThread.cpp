/*
 * Copyright (c) 2012, The University of Oxford
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of the University of Oxford nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include "widgets/oskar_RunThread.h"
#include "widgets/oskar_SettingsModel.h"
#include "widgets/oskar_SettingsItem.h"

#include <QtCore/QProcess>

oskar_RunThread::oskar_RunThread(oskar_SettingsModel* model, QObject* parent)
: QThread(parent)
{
    abort_ = false;
    process_ = NULL;
    model_ = model;
}

// Public methods.

void oskar_RunThread::start(QString binary_name, QString settings_file,
        QStringList outputs)
{
    abort_ = false;
    binaryName_ = binary_name;
    settingsFile_ = settings_file;
    outputFiles_ = outputs;
    QThread::start();
}

void oskar_RunThread::stop()
{
    mutex_.lock();
    abort_ = true;
    if (process_)
        process_->kill();
    mutex_.unlock();
}

// Protected methods.

void oskar_RunThread::run()
{
    // Run recursively.
    run(0, outputFiles_);
    if (!abort_)
        emit completed();
}

// Private methods.

void oskar_RunThread::executeProcess()
{
    // Set up and start the process.
    mutex_.lock();
    process_ = new QProcess;
    process_->setProcessChannelMode(QProcess::MergedChannels);
    process_->start(binaryName_, QStringList() << settingsFile_);
    process_->waitForStarted();
    mutex_.unlock();

    // Monitor the process while it is running.
    while (process_->state() == QProcess::Running)
    {
        process_->waitForReadyRead(500);
        QString output = process_->readAll();
        if (!output.isEmpty())
            emit outputData(output);
    }

    // Check status of the process.
    mutex_.lock();
    if (abort_)
    {
        // User aborted the run.
        emit aborted();
    }
    else if (process_->exitStatus() == QProcess::CrashExit)
    {
        abort_ = true;
        emit crashed();
    }
    else if (process_->exitCode() != 0)
    {
        abort_ = true;
        emit failed();
    }
    delete process_;
    process_ = NULL;
    mutex_.unlock();
}

void oskar_RunThread::run(int depth, QStringList outputFiles)
{
    QByteArray settings = settingsFile_.toAscii();
    QStringList iterationKeys = model_->data(QModelIndex(),
            oskar_SettingsModel::IterationKeysRole).toStringList();
    if (iterationKeys.size() == 0)
    {
        executeProcess();
    }
    else
    {
        QStringList outputKeys = model_->data(QModelIndex(),
                oskar_SettingsModel::OutputKeysRole).toStringList();
        QString key = iterationKeys[depth];
        const oskar_SettingsItem* item = model_->getItem(key);
        QVariant start = item->value();
        QVariant inc = item->iterationInc();

        // Modify all the output file names with the subkey name.
        for (int i = 0; i < outputFiles.size(); ++i)
        {
            if (!outputFiles[i].isEmpty())
            {
                QString separator = (depth == 0) ? "__" : "_";
                outputFiles[i].append(separator + item->subkey());
            }
        }
        QStringList outputFilesStart = outputFiles;

        for (int i = 0; i < item->iterationNum(); ++i)
        {
            // Set the settings file parameter.
            QVariant val;
            if (item->type() == oskar_SettingsItem::INT ||
                    item->type() == oskar_SettingsItem::INT_UNSIGNED ||
                    item->type() == oskar_SettingsItem::INT_POSITIVE)
                val = QVariant(start.toInt() + i * inc.toInt());
            else if (item->type() == oskar_SettingsItem::DOUBLE)
                val = QVariant(start.toDouble() + i * inc.toDouble());
            model_->setValue(key, val);

            // Modify all the output file names with the parameter value.
            for (int i = 0; i < outputFiles.size(); ++i)
            {
                if (!outputFiles[i].isEmpty())
                {
                    outputFiles[i].append("_" + val.toString());
                    model_->setValue(outputKeys[i], outputFiles[i]);
                }
            }

            // Check if thread should stop.
            bool abort;
            mutex_.lock();
            abort = abort_;
            mutex_.unlock();

            // Check if recursion depth has been reached.
            if (depth < iterationKeys.size() - 1 && !abort)
            {
                // If not, then call this function again.
                run(depth + 1, outputFiles);
            }
            else if (!abort)
            {
                executeProcess();
            }

            // Restore the list of output file names.
            outputFiles = outputFilesStart;
        }

        // Restore initial value.
        model_->setValue(key, start);
    }
}
