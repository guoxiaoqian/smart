#ifndef SINGLETON_H
#define SINGLETON_H

template<class T>
class Singleton
{
private:
    static T* p_object;
public:
    Singleton()
    {
        p_object = static_cast<T*>(this);
    }
    static T* getObject()
    {
        if(!p_object)
            p_object = new T();
        return p_object;
    }
};

template<class T>
T* Singleton<T>::p_object = 0;

#endif // SINGLETON_H
