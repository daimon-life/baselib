#include "test_callback.h"

#include <future>
#include <iostream>
#include <chrono>

CTestCallback::CTestCallback()
{
	m_spFuncCallbackMgr.Add(m_spCallbackFunc1Callback);
	m_spFuncCallbackMgr.Add(m_spCallbackFunc2Callback);
}

CTestCallback::~CTestCallback()
{
	m_spFuncCallbackMgr.Erase(m_spCallbackFunc2Callback);
	m_spFuncCallbackMgr.Erase(m_spCallbackFunc1Callback);
}

void CTestCallback::Test(CTestCallbackNotify* pTestCallbackNotify)
{
	pTestCallbackNotify->AppendNotify(m_spCallbackFunc1Callback);
	pTestCallbackNotify->AppendNotify(m_spCallbackFunc2Callback);

	std::future<int> ifuture = std::async([&]()->int
	{
		for (int i : {0, 1})
		{
			std::this_thread::sleep_for(std::chrono::seconds(1));
			m_spFuncCallbackMgr.SafeCall_OnCallback(i, 0, 0, 0);
		}
		return 1;
	});
	ifuture.wait();
	std::cout << "CTestCallback::Test()" << ifuture.get() << std::endl;
}

void CTestCallback::OnCallbackFunc1Callback(int nResult, const void *pData, int nDataLen, void *pExtendData)
{
	std::cout << "OnCallbackFunc1Callback " << nResult << std::endl;
}

void CTestCallback::OnCallbackFunc2Callback(int nResult, const void *pData, int nDataLen, void *pExtendData)
{
	std::cout << "OnCallbackFunc2Callback " << nResult << std::endl;
}


CTestCallbackNotify::CTestCallbackNotify()
{

}

CTestCallbackNotify::~CTestCallbackNotify()
{

}

void CTestCallbackNotify::AppendNotify(std::shared_ptr<IBaseCallback> spCallback)
{
	m_spFuncCallbackMgr.Add(spCallback);
}

void CTestCallbackNotify::RemoveNotify(std::shared_ptr<IBaseCallback> spCallback)
{
	m_spFuncCallbackMgr.Erase(spCallback);
}

void CTestCallbackNotify::Test()
{
	std::future<int> ifuture = std::async([&]()->int
	{
		for (int i : {10, 11})
		{
			std::this_thread::sleep_for(std::chrono::seconds(1));
			m_spFuncCallbackMgr.SafeCall_OnCallback(i, 0, 0, 0);
		}
		return 1;
	});
	ifuture.wait();
	std::cout << "CTestCallbackNotify::Test()" << ifuture.get() << std::endl;
}