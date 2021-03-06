/*!
 * \copyright Copyright (c) 2017-2020 Governikus GmbH & Co. KG, Germany
 */

#pragma once

#include "RemoteMessage.h"


namespace governikus
{
class IfdDisconnect
	: public RemoteMessage
{
	private:
		QString mSlotHandle;

	public:
		explicit IfdDisconnect(const QString& pReaderName);
		explicit IfdDisconnect(const QJsonObject& pMessageObject);
		virtual ~IfdDisconnect() override = default;

		const QString& getSlotHandle() const;
		virtual QByteArray toByteArray(const QString& pContextHandle) const override;
};


} // namespace governikus
