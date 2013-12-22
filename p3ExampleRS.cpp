/*
    This file is part of the Zero Reserve Plugin for Retroshare.

    Zero Reserve is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Zero Reserve is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with Zero Reserve.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "p3ExampleRS.h"

#include "pqi/p3linkmgr.h"

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>



// after getting data from 3 peers, we believe we're complete
static const int INIT_THRESHOLD = 3;

p3ExampleRS::p3ExampleRS(RsPluginHandler *pgHandler, RsPeers* peers, msgQue *msgin ) :
        RsPQIService( RS_SERVICE_TYPE_EXAMPLE_PLUGIN, CONFIG_TYPE_EXAMPLE_PLUGIN, 0, pgHandler ),

        m_peers(peers)
{
    addSerialType(new RsExampleSerialiser());
    pgHandler->getLinkMgr()->addMonitor( this );
    mMsgque = msgin;
    //tjd = tjdin;
    //tjd->p3service = this;
}

void p3ExampleRS::msgPeer(std::string peerId, std::string msg){//, std::string message){
    RsExampleItem * item = new RsExampleItem();
    item->PeerId( peerId );
    item->setMessage(msg);
    //item->m_msg = "hoozah!!";
    sendItem( item );
}
void p3ExampleRS::msgPeerXY(std::string peerId, int x, int y){//, std::string message){
    /*RsMouseEvent * item = new RsMouseEvent();
    item->PeerId( peerId );
    item->x = x;
    item->y = y;
    sendItem( item );*/
    std::stringstream ss;
    ss << "DATA " << x << " " <<y;
    std::string msg = ss.str();
    std::cout << "\n\n Sending xy message x=" << x << " y=" << y << std::endl;
    RsExampleItem * item = new RsExampleItem();
    item->PeerId( peerId );
    item->setMessage(msg);
    //item->m_msg = "hoozah!!";
    sendItem( item );
}
void p3ExampleRS::msgPeerBrush(std::string peerId, int w, int r, int g, int b, int a){
    std::stringstream ss;
    ss << "BRSH " << w << " " << r << " " << g << " " << b << " " << a;
    std::string msg = ss.str();
    RsExampleItem * item = new RsExampleItem();
    item->PeerId( peerId );
    item->setMessage(msg);
    sendItem( item );
}
void p3ExampleRS::msgPeerXYT(std::string peerId, int x, int y, std::string msgtype){
    std::stringstream ss;
    ss << msgtype<< " " << x << " " <<y;
    std::string msg = ss.str();
    std::cout << "\n\n Sending xy message x=" << x << " y=" << y << std::endl;
    RsExampleItem * item = new RsExampleItem();
    item->PeerId( peerId );
    item->setMessage(msg);
    sendItem( item );
}

void p3ExampleRS::testit(){
    //std::cerr << "passing: " << info.data() << std::endl;
    //ui->loginfo->append(info.data());
    std::cout << "Would send data here" << std::endl;
}

void p3ExampleRS::statusChange(const std::list< pqipeer > &plist)
{
    std::cerr << "Example: Status changed:" << std::endl;

    for (std::list< pqipeer >::const_iterator peerIt = plist.begin(); peerIt != plist.end(); peerIt++ ){
        if( RS_PEER_CONNECTED & (*peerIt).actions ){
            RsExampleItem * item = new RsExampleItem();
            item->PeerId( (*peerIt).id );
            std::stringstream ss;
            ss << "INIT " << "please";
            //std::string msg = ss.str();
            item->setMessage(ss.str());
            sendItem( item );
            //tjd->addPeerItem((*peerIt).id);
            //tjd->addPeerItem()
        }
    }
}


int p3ExampleRS::tick()
{
    RsItem *item = NULL;
    while(NULL != (item = recvItem())){
        switch( item->PacketSubType() )
        {
        case RsExampleItem::EXAMPLE_ITEM:
            handleExampleItem( dynamic_cast<RsExampleItem*>( item ) );
            break;
        default:
            std::cerr << "Example: Received Item unknown" << std::endl;
        }
        delete item;
    }
    return 0;
}


void p3ExampleRS::handleExampleItem( RsExampleItem * item )
{
    std::string msg = item->getMessage();
    mMsgque->storeMsg(item);
    /*std::cerr << item->PeerId() << " said: " << msg << std::endl;
    //msgque
    std::cerr << msg.substr(0,4) << std::endl;
    if (msg.substr(0,4).compare("DATA")==0){
        //DATA mx=75 my=127
        // tokeniser from http://stackoverflow.com/questions/236129/how-to-split-a-string-in-c
        std::istringstream iss(msg);
        std::vector<std::string> tokens;
        copy(std::istream_iterator<std::string>(iss),
                 std::istream_iterator<std::string>(),
                 std::back_inserter<std::vector<std::string> >(tokens));
        std::string xstr = tokens.at(1);
        int x = atoi(xstr.c_str());
        std::string ystr = tokens.at(2);
        int y = atoi(ystr.c_str());
        std::cout << "CONVERTEDNUMS: " << x << y << std::endl;
        //tjd->paintWAt(x,y);
    }else{
        //tjd->addLogInfo(item->PeerId());
        //tjd->addLogInfo(item->getMessage());
    }
    //item->RS_PKT_SUBTYPE*/
}


