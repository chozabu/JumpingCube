#ifndef MSGQUE_H
#define MSGQUE_H

#include "RSExampleItems.h"
//class msgQue;
//extern msgQue *msgque;

class msgQue
{
public:
    msgQue();
    virtual void storeMsg(RsExampleItem *item);
    virtual std::vector<RsExampleItem> *getMsgList();

    std::vector<RsExampleItem> *buffer;
};

#endif // MSGQUE_H
