#ifndef _GxxGmRTSPServer_H_
#define _GxxGmRTSPServer_H_

#ifndef _RTSP_SERVER_SUPPORTING_HTTP_STREAMING_HH
#include "RTSPServerSupportingHTTPStreaming.hh"
#endif

#include "DynamicRTSPServer.hh"

class GxxGmRTSPServer : public DynamicRTSPServer
{
public:
	static GxxGmRTSPServer* createNew(UsageEnvironment& env, Port ourPort, UserAuthenticationDatabase* authDatabase, unsigned reclamationTestSeconds = 65);

protected:
	GxxGmRTSPServer(UsageEnvironment& env, int ourSocket, Port ourPort, UserAuthenticationDatabase* authDatabase, unsigned reclamationTestSeconds);
	virtual ~GxxGmRTSPServer();

protected: // redefined virtual functions
	virtual ServerMediaSession* lookupServerMediaSession(char const* streamName, Boolean isFirstLookupInSession);
};

#endif//_GxxGmRTSPServer_H_
