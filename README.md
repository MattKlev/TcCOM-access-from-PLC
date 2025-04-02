# Examples of how to interface face with a TcCOM object instance from the PLC.

A function block wrapper is created that contains the interface pointers to the instance of the TcCOM object.

I_StateMachine - user created, application code interface. 

[ITComObject](https://infosys.beckhoff.com/content/1033/tc3_c/870173579.html?id=8481845685198705300) - Control the state of the TcCOM object, as well as read and write parameters.

ITCADI - Direct access to the Data areas of the TcCOM object. Please be sure to use caution.
- Efficient and flexible access to all DataAreas (also subareas of a DataArea)
- Access only via DataArea number and ByteOffset
- No type information (type cast is to be realized by the user)
- The pointer must be fetched and released every task cycle
- Not threadsafe

The function block gets its reference to the TcCOM object by using a TcInitSymbol of type OTCID.
![image](https://github.com/user-attachments/assets/11a85ed5-6f92-4e53-97e6-c109dad2c0d0)


The interface pointers to the TcCOM instance are initialized during FB_Init using [FW_ObjMgr_GetObjectInstance](https://infosys.beckhoff.com/content/1033/tcplclib_tc3_module/1900117643.html?id=4396498500852015490).

![image](https://github.com/user-attachments/assets/d17816c3-d853-401d-b9b9-2bccd9eb312f)




# ITComObject

Set object state using [TcSetObjState](https://infosys.beckhoff.com/content/1033/tcplclib_tc3_module/1901446027.html?id=7519022100055523476) :

- State : Variable of type TCOM_STATE set to for example: TCOM_STATE.TCOM_STATE_PREOP
- ipSrv : [TwinCAT_SystemInfoVarList._AppInfo.TComSrvPtr](https://infosys.beckhoff.com/content/1033/tc3_plc_intro/714818699.html?id=2967668981173165169)
- pInitData : Points to a list of parameters (optional).

Get object state using [TcGetObjState](https://infosys.beckhoff.com/content/1033/tcplclib_tc3_module/1901276683.html?id=173836337433110978) :

- State : Variable of type TCOM_STATE.

Parameter acsess:

<img width="798" alt="image" src="https://github.com/user-attachments/assets/6c50c010-33cb-4861-b7dc-1ed38d5815fe" />

Get parameter using [TcGetObjPara](https://infosys.beckhoff.com/content/1033/tcplclib_tc3_module/1901252491.html?id=2348496012395952160)


- pid : PTCID can be found by looking at the PTCID coulum in the the parameter tab of the TcCOM object 
![image](https://github.com/user-attachments/assets/5c6ab847-ce3e-4240-bff3-2ee6f2cdd929)

 - nData: the number of bytes to by read.
 - pData: Destination of where the data will be copid to.

Set parameter using [TcSetObjPara](https://infosys.beckhoff.com/content/1033/tcplclib_tc3_module/1901421835.html?id=7416363539111334143)


# ITCADI
Data area acsess: ![image](https://github.com/user-attachments/assets/cecdb4ab-23a9-435b-9c0a-e8ec35c0f466)

First a pointer to the data area is fetched, by using GetImagePtr.

```
  METHOD GetImagePtr : HRESULT
  VAR_INPUT
	  size     : UDINT;
	  offs     : UDINT;
	  adi_x    : UDINT;
	  ppData   : POINTER TO PVOID;
  END_VAR
```

- size : The number of bytes to be acsessed.
- adi_x : use the "Area No." colum from the Data area tab.
- offs : See Size colum from the Data area tab.
- ppData :  Returned pointer to the data, if the call is suscsesfull. 

Data in the memory array can be read or written to using [MEMCPY](https://infosys.beckhoff.com/content/1033/tcplclib_tc2_system/31041163.html?id=1342802077509225213).
Alaways release the Image pointer using ReleaseImagePtr!

Example of a read:
```
	IF GetIn1 THEN
		GetIn1 := FALSE;
		hr	   := StateMachine.ip_DataArea.GetImagePtr(size	  := SIZEOF(In1),
													   offs	  := 0,
													   adi_x  := 1,
													   ppData := ADR(PointerToInputs));

		IF hr = S_OK THEN
			MEMCPY(destAddr := ADR(In1), srcAddr := PointerToInputs, n := SIZEOF(In1));
			hr := StateMachine.ip_DataArea.ReleaseImagePtr(PointerToInputs);
		END_IF
	END_IF

```
Example of a write:
```
	IF SetIn1 THEN
		SetIn1 := FALSE;
		hr	   := StateMachine.ip_DataArea.GetImagePtr(size	  := SIZEOF(In1),
													   offs	  := 0,
													   adi_x  := 1,
													   ppData := ADR(PointerToInputs));

		IF hr = S_OK THEN
			MEMCPY(destAddr := PointerToInputs, srcAddr := ADR(In1), n := SIZEOF(In1));
			hr := StateMachine.ip_DataArea.ReleaseImagePtr(PointerToInputs);
		END_IF
	END_IF


```


# Further Information
Further Information on -- Module to Module communcation -- can be found at the [Beckhoff Infosys](https://infosys.beckhoff.com/content/1033/tc3_c/2491037963.html?id=6026373682280614824)

## Requirements

The following components must be installed to run the sample code:

- [Visual Studio 2022 and the C++ toolchain](https://infosys.beckhoff.com/content/1033/tc3_c/110675211.html?id=121428688628873596).
- TwinCAT XAE version 3.1.4026.0 or higher.



This sample is created by [Beckhoff Automation LLC.](https://www.beckhoff.com/en-us/), and is provided as-is under the Zero-Clause BSD license.
