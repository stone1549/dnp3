
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
// you under the GNU Affero General Public License Version 3.0
// (the "Additional License"). You may not use these modifications except in
// compliance with the additional license. You may obtain a copy of the Additional
// License at
//
// http://www.gnu.org/licenses/agpl.html
//
// Contact Automatak, LLC for a commercial license to these modifications
//
#ifndef __DEVICE_TEMPLATE_H_
#define __DEVICE_TEMPLATE_H_

#include <vector>
#include <sstream>

#include "DataInterfaces.h"
#include "DeviceTemplateTypes.h"

namespace opendnp3
{

/** Configuration structure that defines the default layout of the database	

	The indices of the points are implicit based on their
	position within the vectors below.
*/
struct DeviceTemplate {
	DeviceTemplate(size_t aNumBinary = 0,
	               size_t aNumAnalog = 0,
	               size_t aNumCounter = 0,
	               size_t aNumControlStatus = 0,
	               size_t aNumSetpointStatus = 0);

	//Measurements
	std::vector<EventPointRecord> mBinary;		// list of binary point properties
	std::vector<EventPointRecord> mCounter;		// list of counter point properties
	std::vector<DeadbandPointRecord> mAnalog;	// list of analog point properties
	std::vector<PointRecord> mControlStatus;	// list of control status point properties
	std::vector<PointRecord> mSetpointStatus;	// list of control status point properties

	bool mStartOnline;

	// Write the initial state of a database to an observer
	void Publish(IDataObserver*);

private:

	template <class T>
	static void InitObserver(IDataObserver* apObs, size_t aNum) {
		for(size_t i = 0; i < aNum; ++i) {
			T val;
			apObs->Update(val, i);
		}
	}

	// Helper function for setting up default names
	template <class T>
	void InitNames(const std::string& arName, std::vector<T>& arVec) {
		for(size_t i = 0; i < arVec.size(); ++i) {
			std::ostringstream oss;
			oss << arName << i;
			arVec[i].Name = oss.str();
		}
	}

};

}

#endif