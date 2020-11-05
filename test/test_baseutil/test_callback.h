#pragma once


#ifndef _TestCallback_H_
#define _TestCallback_H_

#include "BaseCallback.h"

class CTestCallbackNotify;


// test IBaseCallback class
class CTestCallback
{
public:
	CTestCallback();
	virtual ~CTestCallback();

	void Test(CTestCallbackNotify* pTestCallbackNotify);

private:
	BASECALLBACK_SINK(CTestCallback, CallbackFunc1);
	void OnCallbackFunc1Callback(int nResult, const void *pData, int nDataLen, void *pExtendData);
	BASECALLBACK_SINK(CTestCallback, CallbackFunc2);
	void OnCallbackFunc2Callback(int nResult, const void *pData, int nDataLen, void *pExtendData);

private:
	CBaseCallbackMgr    m_spFuncCallbackMgr;   //
};


//
class CTestCallbackNotify
{
public:
	CTestCallbackNotify();
	virtual ~CTestCallbackNotify();

	void AppendNotify(std::shared_ptr<IBaseCallback> spCallback);
	void RemoveNotify(std::shared_ptr<IBaseCallback> spCallback);

	void Test();

private:
	CBaseCallbackMgr    m_spFuncCallbackMgr;   //
};

#endif // _TestCallback_H_