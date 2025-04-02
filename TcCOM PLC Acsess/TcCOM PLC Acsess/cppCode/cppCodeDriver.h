///////////////////////////////////////////////////////////////////////////////
// cppCodeDriver.h

#ifndef __CPPCODEDRIVER_H__
#define __CPPCODEDRIVER_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TcBase.h"

#define CPPCODEDRV_NAME        "CPPCODE"
#define CPPCODEDRV_Major       1
#define CPPCODEDRV_Minor       0

#define DEVICE_CLASS CcppCodeDriver

#include "ObjDriver.h"

class CcppCodeDriver : public CObjDriver
{
public:
	virtual IOSTATUS	OnLoad();
	virtual VOID		OnUnLoad();

	//////////////////////////////////////////////////////
	// VxD-Services exported by this driver
	static unsigned long	_cdecl CPPCODEDRV_GetVersion();
	//////////////////////////////////////////////////////
	
};

Begin_VxD_Service_Table(CPPCODEDRV)
	VxD_Service( CPPCODEDRV_GetVersion )
End_VxD_Service_Table


#endif // ifndef __CPPCODEDRIVER_H__