#ifndef SIG_SLOT_H
#define SIG_SLOT_H

#include <iostream>
#include <vector>
using namespace std;


template<class T, class... tParam>
class SSlotBase
{
public:
    SSlotBase(T* pObj, void (T::*func)(tParam...) )
    {
        m_pObj = pObj;
        m_Func = func;
    }

    void Exec( tParam... param)
    {
        (m_pObj->*m_Func)(param...);
    }

private:
    T* m_pObj;
    void (T::*m_Func)(tParam...);
};


template<class... tParam>
class SSlot
{
public:
    virtual void Exec(tParam... param) = 0;
    virtual ~SSlot();
};

template<class T,class... tParam>
class SSlotImpl:public SSlot<tParam...>
{
public:
    SSlotImpl(T* pObj, void (T::*func)(tParam...) )
    {
        m_pObj = pObj;
        m_Func = func;
    }

    void Exec( tParam... param)
    {
        (m_pObj->*m_Func)(param...);
    }

    ~SSlotImpl()
    {

    }

private:
    T* m_pObj;
    void (T::*m_Func)(tParam...);
};


template<typename... tParam>
class SSignal
{
public:
    template<class T>
    void Bind(T* pObj, void (T::*func)(tParam...))
    {
        m_pSlotSet.push_back( new SSlotImpl<T,tParam...>(pObj,func) );
    }

    ~SSignal()
    {
        for(int i=0;i<(int)m_pSlotSet.size();i++)
        {
            delete m_pSlotSet[i];
        }
    }

    void operator()(tParam... param)
    {
        for(int i=0;i<(int)m_pSlotSet.size();i++)
        {
            m_pSlotSet[i]->Exec(param...);
        }
    }

private:
    vector< SSlot<tParam...>* > m_pSlotSet;
};

#define SConnect( sender, signal, receiver, method) ( (sender)->signal.Bind(receiver,method) )
#define SSLOT
#define SEMIT

#endif // SIG_SLOT_H
