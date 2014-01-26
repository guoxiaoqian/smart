#ifndef SIG_SLOT_H
#define SIG_SLOT_H

#include <iostream>
#include <vector>
using namespace std;


template<class T, class... tParam>
class SlotBase
{
public:
    SlotBase(T* pObj, void (T::*func)(tParam...) )
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
class Slot
{
public:
    virtual void Exec(tParam... param) = 0;
};

template<class T,class... tParam>
class SlotImpl:public Slot<tParam...>
{
public:
    SlotImpl(T* pObj, void (T::*func)(tParam...) )
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


template<typename... tParam>
class Signal
{
public:
    template<class T>
    void Bind(T* pObj, void (T::*func)(tParam...))
    {
        m_pSlotSet.push_back( new SlotImpl<T,tParam...>(pObj,func) );
    }

    ~Signal()
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
    vector< Slot<tParam...>* > m_pSlotSet;
};

#define SConnect( sender, signal, receiver, method) ( (sender)->signal.Bind(receiver,method) )
#define SSlot
#define SEmit

#endif // SIG_SLOT_H
