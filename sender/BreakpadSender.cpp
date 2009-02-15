/*
	Copyright (c) 2009, Aleksey Palazhchenko
	All rights reserved.

	Redistribution and use in source and binary forms, with or without
	modification, are permitted provided that the following conditions are
	met:

		* Redistributions of source code must retain the above copyright
	notice, this list of conditions and the following disclaimer.
		* Redistributions in binary form must reproduce the above
	copyright notice, this list of conditions and the following disclaimer
	in the documentation and/or other materials provided with the
	distribution.

	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
	"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
	LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
	A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
	OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
	SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
	LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
	DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
	THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
	(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
	OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "BreakpadSender.h"

#include <QDir>
#include <QByteArray>

#if defined(Q_OS_MAC)
#elif defined(Q_OS_LINUX)
#include "common/linux/http_upload.h"
#elif defined(Q_OS_WIN32)
#endif

namespace BreakpadQt
{

Sender::Sender(const QString& reportUrl)
	: m_reportUrl(reportUrl)
{
}

Sender::~Sender()
{
}

void Sender::addParameter(const QString& key, const QString& value)
{
	Q_ASSERT(!key.contains(QLatin1Char('"')));
	Q_ASSERT(key.toLatin1() == key.toUtf8());
	m_params[key.toStdString()] = value.toStdString();
}

void Sender::setFile(const QString& filename)
{
	Q_ASSERT(QDir::isAbsolutePath(filename));
	Q_ASSERT(QDir().exists(filename));
	m_filename = filename;
}

bool Sender::send(QString* result)
{
	std::string resString;
	const bool success = google_breakpad::HTTPUpload::SendRequest(m_reportUrl.toStdString(), m_params.toStdMap(),
																	m_filename.toStdString(), std::string("file"),
																	std::string(), std::string(),
																	&resString, &resString);
	if(result) {
		result->fromStdString(resString);
	}
	return success;
}

}	// namespace