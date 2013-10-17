#include "msgQue.h"

msgQue::msgQue()
{

    buffer = new std::vector<RsExampleItem>;
}


void msgQue::storeMsg(RsExampleItem * item){
    buffer->push_back(*item);
}


//std::list<std::string>
std::vector<RsExampleItem> *msgQue::getMsgList(){
    std::vector<RsExampleItem> *oldbuffer = buffer;
    buffer = new std::vector<RsExampleItem>;
    return oldbuffer;

}
