
//
// Licensed to Green Energy Corp (www.greenenergycorp.com) under one or
// more contributor license agreements. See the NOTICE file distributed
// with this work for additional information regarding copyright ownership.
// Green Energy Corp licenses this file to you under the Apache License,
// Version 2.0 (the "License"); you may not use this file except in
// compliance with the License.  You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// This file was forked on 01/01/2013 by Automatak, LLC and modifications
// have been made to this file. Automatak, LLC licenses these modifications to
// you under the terms of the License.
//

#include "AsyncTaskNonPeriodic.h"
#include "AsyncTaskGroup.h"

#include <openpal/TimeDuration.h>

using namespace openpal;

namespace opendnp3
{


AsyncTaskNonPeriodic::AsyncTaskNonPeriodic(openpal::TimeDuration aRetryDelay, int aPriority, const TaskHandler& arCallback, AsyncTaskGroup* apGroup, const std::string& arName) :
	AsyncTaskBase(aPriority, arCallback, apGroup, MonotonicTimestamp::Min(), arName),
	mRetryDelay(aRetryDelay)
{

}

void AsyncTaskNonPeriodic::_OnComplete(bool aSuccess)
{	
	if(aSuccess) {
		mIsComplete = true;
		mNextRunTime = MonotonicTimestamp::Max();
	}
	else {
		mNextRunTime = mpGroup->GetCurrentTime().Add(mRetryDelay);
	}
}

} //end ns
