#pragma once


#ifndef _IBaseCallback_H_
#define _IBaseCallback_H_


#include <vector>
#include <mutex>
#include <memory>


class IBaseCallback
{
public:
    virtual void    OnCallback(int nResult, const void *pData, int nDataLen, void *pExtendData) = 0;
};


#ifndef BASECALLBACK_SINK
#define BASECALLBACK_SINK(ParentClassName, CallbackName) \
class C##CallbackName##CallbackPtr : public IBaseCallback \
{ \
public: \
    C##CallbackName##CallbackPtr() \
    { \
        m_pParent = ((ParentClassName*)((uint8_t *)this - offsetof(ParentClassName, m_sp##CallbackName##Callback))); \
    } \
    ~C##CallbackName##CallbackPtr() \
    { \
        m_pParent = NULL; \
    } \
\
public: \
    void OnCallback(int nResult, const void *pData, int nDataLen, void *pExtendData) \
    { \
        if (m_pParent) \
        { \
            m_pParent->On##CallbackName##Callback(nResult, pData, nDataLen, pExtendData); \
        } \
    } \
    operator IBaseCallback* () \
    { \
        return static_cast<IBaseCallback *>(this); \
    } \
\
private: \
    C##CallbackName##CallbackPtr& operator=(const C##CallbackName##CallbackPtr&); \
private: \
    ParentClassName *m_pParent; \
}; \
std::shared_ptr<C##CallbackName##CallbackPtr> m_sp##CallbackName##Callback = std::make_shared<C##CallbackName##CallbackPtr>();
#endif // BASECALLBACK_SINK


class CBaseCallbackMgr
{
public:
    CBaseCallbackMgr()
    {
    }
    CBaseCallbackMgr(const CBaseCallbackMgr& Src)
    {
		std::lock_guard<std::mutex> lock(m_CallbackObjectVecMutex);
        m_CallbackObjectVec = Src.m_CallbackObjectVec;
    }
    ~CBaseCallbackMgr()
    {
        Clear();
    }

public:
	void Add(std::shared_ptr<IBaseCallback> spCallback)
    {
		if (spCallback)
        {
			std::lock_guard<std::mutex> lock(m_CallbackObjectVecMutex);
			m_CallbackObjectVec.push_back(spCallback);
        }
    }
	void Erase(std::shared_ptr<IBaseCallback> spCallback)
	{
		if (spCallback)
		{
			std::lock_guard<std::mutex> lock(m_CallbackObjectVecMutex);
			std::vector<std::weak_ptr<IBaseCallback>>::iterator it;
			for (it = m_CallbackObjectVec.begin(); it != m_CallbackObjectVec.end(); it++)
			{
				if (!it->expired() && it->lock() == spCallback)
				{
					m_CallbackObjectVec.erase(it);
				}
			}
		}
	}
    void Clear()
    {
		std::lock_guard<std::mutex> lock(m_CallbackObjectVecMutex);
        m_CallbackObjectVec.clear();
    }
    bool IsActive()
    {
		std::lock_guard<std::mutex> lock(m_CallbackObjectVecMutex);
		return !m_CallbackObjectVec.empty();
    }
    void SafeCall_OnCallback(int nResult, const void *pData, int nDataLen, void *pExtendData)
    {
		std::lock_guard<std::mutex> lock(m_CallbackObjectVecMutex);
		std::vector<std::weak_ptr<IBaseCallback>>::iterator it;
        for (it = m_CallbackObjectVec.begin(); it != m_CallbackObjectVec.end(); it++)
        {
			if (!it->expired())
			{
				std::shared_ptr<IBaseCallback> spCallback = it->lock();
				spCallback->OnCallback(nResult, pData, nDataLen, pExtendData);
			}
        }
    }
    CBaseCallbackMgr& operator=(const CBaseCallbackMgr& Src)
    {
		std::lock_guard<std::mutex> lock(m_CallbackObjectVecMutex);
        m_CallbackObjectVec = Src.m_CallbackObjectVec;
        return *this;
    }

private:
    std::vector<std::weak_ptr<IBaseCallback>>   m_CallbackObjectVec;
    std::mutex                                  m_CallbackObjectVecMutex;
};


#endif // _IBaseCallback_H_