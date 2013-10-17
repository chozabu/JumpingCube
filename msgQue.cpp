#include "msgQue.h"

msgQue::msgQue()
{

    buffer = new std::vector<RsExampleItem>;
}


void msgQue::storeMsg(RsExampleItem * item){

    //should be doing a mutex lock here?
    buffer->push_back(*item);
}


//std::list<std::string>
std::vector<RsExampleItem> *msgQue::getMsgList(){
    //should also be doing a mutex lock here?
    std::vector<RsExampleItem> *oldbuffer = buffer;
    buffer = new std::vector<RsExampleItem>;
    return oldbuffer;

}
