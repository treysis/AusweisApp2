/*!
 * \copyright Copyright (c) 2014-2020 Governikus GmbH & Co. KG, Germany
 */

#include "AutoStart.h"

#include <QLoggingCategory>
#include <QScopeGuard>

#import <Cocoa/Cocoa.h>
#import <ServiceManagement/ServiceManagement.h>


using namespace governikus;

Q_DECLARE_LOGGING_CATEGORY(settings)

static NSString* autostartBundleIdentifier = @"com.governikus.AusweisApp2.AutostartHelper";


bool AutoStart::enabled()
{
	auto jobDictionaries = (NSArray*) SMCopyAllJobDictionaries(kSMDomainUserLaunchd);
	if (jobDictionaries == nullptr)
	{
		qCCritical(settings) << "Getting autostart entries failed";
		return false;
	}

	const auto dictFree = qScopeGuard([jobDictionaries] {
				CFRelease(jobDictionaries);
			});

	for (NSDictionary* job in jobDictionaries)
	{
		if ([autostartBundleIdentifier isEqualToString:job[@"Label"]] == YES)
		{
			qCDebug(settings) << "Autostart entry found";
			return true;
		}
	}

	qCDebug(settings) << "No autostart entry found";
	return false;
}


bool AutoStart::isSetByAdmin()
{
	return false;
}


void AutoStart::set(bool pEnabled)
{
	if (SMLoginItemSetEnabled((CFStringRef) autostartBundleIdentifier, pEnabled))
	{
		qCDebug(settings) << "Setting autostart to" << pEnabled << "succeeded";
	}
	else
	{
		qCCritical(settings) << "Setting autostart failed";
	}
}
