/* Copyright 2007-2015 QReal Research Group
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License. */

#include <utils/tcpConnectionHandler.h>

#include <QtNetwork/QHostAddress>

#include <qrkernel/logging.h>

using namespace utils;

TcpConnectionHandler::TcpConnectionHandler(int port)
	: mPort(port)
{
	QObject::connect(&mSocket, SIGNAL(readyRead()), this, SLOT(onIncomingData()), Qt::DirectConnection);
}

bool TcpConnectionHandler::connect(const QHostAddress &serverAddress)
{
	if (mSocket.state() == QTcpSocket::ConnectedState || mSocket.state() == QTcpSocket::ConnectingState) {
		return true;
	}

	mSocket.connectToHost(serverAddress, static_cast<quint16>(mPort));
	const bool result = mSocket.waitForConnected(3000);
	if (!result) {
		QLOG_ERROR() << mSocket.errorString();
	}

	mBuffer.clear();
	mExpectedBytes = 0;

	return result;
}

bool TcpConnectionHandler::isConnected()
{
	return mSocket.state() == QTcpSocket::ConnectedState;
}

void TcpConnectionHandler::disconnect()
{
	if (mSocket.state() == QTcpSocket::ConnectedState) {
		mSocket.disconnectFromHost();
		mSocket.waitForDisconnected(3000);
	}
}

void TcpConnectionHandler::send(const QString &data)
{
	QByteArray dataByteArray = data.toUtf8();
	dataByteArray = QByteArray::number(dataByteArray.size()) + ':' + dataByteArray;
	mSocket.write(dataByteArray);
	if (!mSocket.waitForBytesWritten(3000)) {
		QLOG_ERROR() << "Unable to send data" << data << "to" << mSocket.peerAddress();
	}
}

void TcpConnectionHandler::onIncomingData()
{
	if (!mSocket.isValid()) {
		return;
	}

	const QByteArray &data = mSocket.readAll();
	mBuffer.append(data);

	while (!mBuffer.isEmpty()) {
		if (mExpectedBytes == 0) {
			// Determining the length of a message.
			const int delimiterIndex = mBuffer.indexOf(':');
			if (delimiterIndex == -1) {
				// We did not receive full message length yet.
				return;
			} else {
				const QByteArray length = mBuffer.left(delimiterIndex);
				mBuffer = mBuffer.mid(delimiterIndex + 1);
				bool ok = false;
				mExpectedBytes = length.toInt(&ok);
				if (!ok) {
					QLOG_ERROR() << "Malformed message, can not determine message length from this:" << length;
					mExpectedBytes = 0;
				}
			}
		} else {
			if (mBuffer.size() >= mExpectedBytes) {
				const QByteArray message = mBuffer.left(mExpectedBytes);
				mBuffer = mBuffer.mid(mExpectedBytes);

				emit messageReceived(message);

				mExpectedBytes = 0;
			} else {
				// We don't have all message yet.
				return;
			}
		}
	}
}
