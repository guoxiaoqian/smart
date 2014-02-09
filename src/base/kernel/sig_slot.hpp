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
    virtual ~SSlot(){}
};

template<class T,class... tParam>
class SMemberSlot:public SSlot<tParam...>
{
public:
    SMemberSlot(T* pObj, void (T::*func)(tParam...) )
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
class SGlobalSlot:public SSlot<tParam...>
{
public:
    SGlobalSlot(void (*func)(tParam...))
    {
        m_func = func;
    }

    void Exec(tParam... param)
    {
        (*m_func)(param...);
    }
private:
    void (*m_func)(tParam...);
};

template<typename... tParam>
class SSignal
{
public:
    //绑定成员SLOT
    template<class T>
    void Bind(T* pObj, void (T::*func)(tParam...))
    {
        m_pSlotSet.push_back( new SMemberSlot<T,tParam...>(pObj,func) );
    }
    //绑定全局或静态SLOT
    void Bind(void (*func)(tParam...))
    {
        m_pSlotSet.push_back(new SGlobalSlot<tParam...>(func));
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


#define SConnectMM(sender, signal, receiver, method) ((sender)->signal.Bind(receiver,method))
#define SConnectMG(sender, signal, method) ((sender)->signal.Bind(method))
#define SConnectGM(signal, receiver, method) (signal.Bind(receiver,method))
#define SConnectGG(signal, method) (signal.Bind(method))
#define SSLOT
#define SEMIT

#endif // SIG_SLOT_H
