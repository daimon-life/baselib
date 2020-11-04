#pragma once


#ifndef _IBaseCallback_H_
#define _IBaseCallback_H_


#include <set>
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
}m_sp##CallbackName##Callback;
#endif // BASECALLBACK_SINK


class CBaseCallbackMgr
{
public:
    CBaseCallbackMgr()
    {
    }
    CBaseCallbackMgr(const CBaseCallbackMgr& Src)
    {
		std::lock_guard<std::mutex> lock(m_CallbackObjectSetMutex);
        m_CallbackObjectSet = Src.m_CallbackObjectSet;
    }
    ~CBaseCallbackMgr()
    {
        Clear();
    }

public:
    void Add(IBaseCallback *pCallback)
    {
        if (pCallback)
        {
			std::lock_guard<std::mutex> lock(m_CallbackObjectSetMutex);
            m_CallbackObjectSet.insert(pCallback);
        }
    }
	void Erase(IBaseCallback *pCallback)
	{
		if (pCallback)
		{
			std::lock_guard<std::mutex> lock(m_CallbackObjectSetMutex);
			m_CallbackObjectSet.erase(pCallback);
		}
	}
    void Clear()
    {
		std::lock_guard<std::mutex> lock(m_CallbackObjectSetMutex);
        m_CallbackObjectSet.clear();
    }
    bool IsActive()
    {
		std::lock_guard<std::mutex> lock(m_CallbackObjectSetMutex);
        bool bRet = !m_CallbackObjectSet.empty();
        return bRet;
    }
    void SafeCall_OnCallback(int nResult, const void *pData, int nDataLen, void *pExtendData)
    {
		std::lock_guard<std::mutex> lock(m_CallbackObjectSetMutex);
        std::set<IBaseCallback *>::iterator it;
        for (it = m_CallbackObjectSet.begin(); it != m_CallbackObjectSet.end(); it++)
        {
            (*it)->OnCallback(nResult, pData, nDataLen, pExtendData);
        }
    }
    CBaseCallbackMgr& operator=(const CBaseCallbackMgr &Src)
    {
		std::lock_guard<std::mutex> lock(m_CallbackObjectSetMutex);
        m_CallbackObjectSet = Src.m_CallbackObjectSet;
        return *this;
    }

private:
    std::set<IBaseCallback*>   m_CallbackObjectSet;
    std::mutex                                m_CallbackObjectSetMutex;
};


#endif // _IBaseCallback_H_