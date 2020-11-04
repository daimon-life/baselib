#pragma once



#ifndef _IBaseCallback_H_
#define _IBaseCallback_H_


#include <set>
#include "BaseLock.h"


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
} m_sp##CallbackName##Callback;
#endif // BASECALLBACK_SINK


class CBaseCallbackMgr
{
public:
    CBaseCallbackMgr()
    {
    }
    CBaseCallbackMgr(const CBaseCallbackMgr& Src)
    {
        CBaseAutoLock AutoLock(&m_CallbackObjectSetLock);
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
            CBaseAutoLock AutoLock(&m_CallbackObjectSetLock);
            m_CallbackObjectSet.insert(pCallback);
        }
    }
    void Clear()
    {
        CBaseAutoLock AutoLock(&m_CallbackObjectSetLock);
        m_CallbackObjectSet.clear();
    }
    bool IsActive()
    {
        bool bRet = false;
        CBaseAutoLock AutoLock(&m_CallbackObjectSetLock);
        bRet = !m_CallbackObjectSet.empty();
        return bRet;
    }
    void Erase(IBaseCallback *pCallback)
    {
        if (pCallback)
        {
            CBaseAutoLock AutoLock(&m_CallbackObjectSetLock);
            m_CallbackObjectSet.erase(pCallback);
        }
    }
    void SafeCall_OnCallback(int nResult, const void *pData, int nDataLen, void *pExtendData)
    {
        std::set<IBaseCallback *>::iterator it;
        CBaseAutoLock AutoLock(&m_CallbackObjectSetLock);
        for (it = m_CallbackObjectSet.begin(); it != m_CallbackObjectSet.end(); it++)
        {
            (*it)->OnCallback(nResult, pData, nDataLen, pExtendData);
        }
    }
    CBaseCallbackMgr& operator=(const CBaseCallbackMgr &Src)
    {
        CBaseAutoLock AutoLock(&m_CallbackObjectSetLock);
        m_CallbackObjectSet = Src.m_CallbackObjectSet;
        return *this;
    }

private:
    std::set<IBaseCallback *>   m_CallbackObjectSet;
    CBaseLock                   m_CallbackObjectSetLock;
};


#endif // _IBaseCallback_H_
