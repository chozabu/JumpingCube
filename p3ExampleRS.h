

#ifndef P3ZERORESERVERRS_H
#define P3ZERORESERVERRS_H


#include "RSExampleItems.h"

#include "retroshare/rspeers.h"
#include "plugins/rspqiservice.h"
#include "pqi/pqimonitor.h"
//#include "topjcdialog.h"

#include "msgQue.h"


class TopJCDialog;
class RsPluginHandler;
class RsPeers;

class p3ExampleRS : public RsPQIService,   // the service interface calls tick()
                    public pqiMonitor      // the monitor tells us when friends changed their status
{
public:
    p3ExampleRS(RsPluginHandler *pgHandler, RsPeers* peers, msgQue *msgin);

    virtual int tick();
    virtual void statusChange(const std::list<pqipeer> &plist);
    virtual void testit();
    virtual void msgPeer(std::string peerId, std::string msg);//, std::string message){
    virtual void msgPeerXY(std::string peerId, int x, int y);
    virtual void msgPeerXYT(std::string peerId, int x, int y, std::string msgtype);
	virtual void msgPeerBrush(std::string peerId, int w, int r, int g, int b, int a);
    msgQue * mMsgque;

private:
    void handleMessage( RsExampleItem *item );
    void handleExampleItem( RsExampleItem * item );

private:

    RsPeers * m_peers;
    //TopJCDialog *tjd;
};

#endif // P3ZERORESERVERRS_H
