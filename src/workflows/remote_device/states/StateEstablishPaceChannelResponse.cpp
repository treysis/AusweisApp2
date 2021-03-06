/*!
 * \copyright Copyright (c) 2017-2020 Governikus GmbH & Co. KG, Germany
 */

#include "StateEstablishPaceChannelResponse.h"

#include "ServerMessageHandler.h"

using namespace governikus;


StateEstablishPaceChannelResponse::StateEstablishPaceChannelResponse(const QSharedPointer<WorkflowContext>& pContext)
	: AbstractState(pContext, false)
	, GenericContextContainer(pContext)
{
}


void StateEstablishPaceChannelResponse::run()
{
	Q_ASSERT(getContext()->getRemoteServer());
	Q_ASSERT(getContext()->hasEstablishedPaceChannelRequest());

	const QSharedPointer<RemoteServiceContext>& context = getContext();
	const auto& establishPaceChannelOutput = context->getEstablishPaceChannelOutput();
	if (context->getRemoteServer() && context->getRemoteServer()->getMessageHandler())
	{
		context->getRemoteServer()->getMessageHandler()->sendEstablishPaceChannelResponse(
				context->getEstablishPaceChannelMessageSlotHandle(),
				establishPaceChannelOutput
				);
	}

	const bool isWrongPacePassword = CardReturnCodeUtil::equalsWrongPacePassword(establishPaceChannelOutput.getPaceReturnCode());
	context->setEstablishPaceChannelMessage(nullptr);

	if (isWrongPacePassword)
	{
		Q_EMIT fireWrongPacePassword();
		return;
	}

	Q_EMIT fireContinue();
}
