#ifndef REQUESTQUEUE_H
#define REQUESTQUEUE_H

#include <vector>
using std::vector;
#include "base/thread/spinlock.h"

template<class T>
class QueueNode
{
 public:
    vector<T> data;
    QueueNode *next;
 public:
    QueueNode()
    {
        next=NULL;
    }

    void InsertData(vector<T>& _data)
    {
        if(_data.empty())
            return;
        data.insert(data.end(),_data.begin(),_data.end());
    }

    void InsertData(vector<T>* _data)
    {
        if(_data->empty())
            return;
        data.insert(data.end(),_data->begin(),_data->end());
    }
};

template<class T>
class RequestQueue
{ 
private:
    QueueNode<T> *queue_head;
    QueueNode<T> *queue_end;
    SSpinLock spin_lock;
public:
    RequestQueue()
    {
        queue_head=NULL;
        queue_end=NULL;
    }

    QueueNode<T>* PopNode()
    {
        spin_lock.lock();
        QueueNode<T> *tmp_node=queue_head;
        if(queue_head==NULL)
        {
            queue_end=NULL;
        }
        else
        {
            queue_head=tmp_node->next;
            tmp_node->next=NULL;
        }
        spin_lock.unlock();
        return tmp_node;
    }

    void InsertNode(QueueNode<T> *tmp_node)
    {
        spin_lock.lock();
        if(queue_head==NULL)
        {
            queue_head=queue_end=tmp_node;
        }
        else
        {
            queue_end->next=tmp_node;
            queue_end=tmp_node;
        }
        spin_lock.unlock();
     }
};

#endif // REQUESTQUEUE_H
