/**********************************************************************
* Copyright (c) 2015 Mark Charlebois
* 
* All rights reserved.
* 
* Redistribution and use in source and binary forms, with or without
* modification, are permitted (subject to the limitations in the
* disclaimer below) provided that the following conditions are met:
* 
*  * Redistributions of source code must retain the above copyright
*    notice, this list of conditions and the following disclaimer.
* 
*  * Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the
*    documentation and/or other materials provided with the
*    distribution.
* 
*  * Neither the name of Dronecode Project nor the names of its
*    contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
* 
* NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE
* GRANTED BY THIS LICENSE.  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT
* HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED
* WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
* MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
* LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
* CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
* SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
* BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
* WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
* OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
* IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*************************************************************************/
#include <stdint.h>
#include <time.h>
#include <memory>

#pragma once

namespace DriverFramework {

// Forward class declarations
class DriverMgr;
class DriverObj;

class DriverHandle
{
public:
	DriverHandle() :
		m_handle(nullptr),
		m_errno(0)
	{
	}

	~DriverHandle();

	bool isValid()
	{
		return m_handle != nullptr;
	}
	int getError()
	{
		return m_errno;
	}
private:
	friend DriverMgr;

	void *m_handle;
	int m_errno;
};

// DriverMgr Is initalized by DriverFramework::initialize()
class DriverMgr
{    
public:

	static int registerDriver(DriverObj *obj);
	static void unregisterDriver(DriverObj *obj);

	static DriverObj *getDriverObjByName(const std::string &name, unsigned int instance);
	static DriverObj *getDriverObjByID(union DeviceId id);
	static DriverObj *getDriverObjByHandle(DriverHandle &handle);

	static DriverHandle getHandle(const char *dev_path);
	static void releaseHandle(DriverHandle &handle);

	static void setDriverHandleError(DriverHandle &h, int error);
private:
	friend Framework;

	DriverMgr();
	~DriverMgr();

	static int initialize(void);
	static void finalize(void);
};

};
