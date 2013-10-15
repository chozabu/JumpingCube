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

// after getting data from 3 peers, we believe we're complete
static const int INIT_THRESHOLD = 3;

p3ExampleRS::p3ExampleRS(RsPluginHandler *pgHandler, RsPeers* peers, TopJCDialog *tjdin ) :
        RsPQIService( RS_SERVICE_TYPE_EXAMPLE_PLUGIN, CONFIG_TYPE_EXAMPLE_PLUGIN, 0, pgHandler ),

        m_peers(peers)
{
    addSerialType(new RsExampleSerialiser());
    pgHandler->getLinkMgr()->addMonitor( this );
    tjd = tjdin;
    tjd->p3service = this;
    //tjd->setp3();
    //connect(tjd->getOKButton(), SIGNAL(clicked()), this, SLOT(okClicked()));
}

void p3ExampleRS::msgPeer(std::string peerId, std::string msg){//, std::string message){
    RsExampleItem * item = new RsExampleItem();
    item->PeerId( peerId );
    item->setMessage(msg);
    //item->m_msg = "hoozah!!";
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
            //item->m_msg = "hoozah!!";
            sendItem( item );
            tjd->addPeerItem((*peerIt).id);
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
    //QString msg = new QString(item->getMessage();

    tjd->addLogInfo(item->PeerId());
    tjd->addLogInfo(item->getMessage());
    //item->RS_PKT_SUBTYPE
    std::cerr << item->PeerId() << " said: " << item->getMessage() << std::endl;
}


