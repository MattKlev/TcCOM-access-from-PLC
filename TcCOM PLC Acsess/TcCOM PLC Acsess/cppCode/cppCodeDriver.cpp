///////////////////////////////////////////////////////////////////////////////
// cppCodeDriver.cpp
#include "TcPch.h"
#pragma hdrstop

#include "cppCodeDriver.h"
#include "cppCodeClassFactory.h"

DECLARE_GENERIC_DEVICE(CPPCODEDRV)

IOSTATUS CcppCodeDriver::OnLoad( )
{
	TRACE(_T("CObjClassFactory::OnLoad()\n") );
	m_pObjClassFactory = new CcppCodeClassFactory();

	return IOSTATUS_SUCCESS;
}

VOID CcppCodeDriver::OnUnLoad( )
{
	delete m_pObjClassFactory;
}

unsigned long _cdecl CcppCodeDriver::CPPCODEDRV_GetVersion( )
{
	return( (CPPCODEDRV_Major << 8) | CPPCODEDRV_Minor );
}

