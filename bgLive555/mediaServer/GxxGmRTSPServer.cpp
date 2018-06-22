#include "GxxGmRTSPServer.h"
#include <liveMedia.hh>
#include <string.h>


GxxGmRTSPServer* GxxGmRTSPServer::createNew(UsageEnvironment& env, Port ourPort, UserAuthenticationDatabase* authDatabase, unsigned reclamationTestSeconds)
{
	int ourSocket = setUpOurSocket(env, ourPort);
	if (ourSocket == -1) return NULL;

	return new GxxGmRTSPServer(env, ourSocket, ourPort, authDatabase, reclamationTestSeconds);
}

GxxGmRTSPServer::GxxGmRTSPServer(UsageEnvironment& env, int ourSocket, Port ourPort, UserAuthenticationDatabase* authDatabase, unsigned reclamationTestSeconds)
: DynamicRTSPServer(env, ourSocket, ourPort, authDatabase, reclamationTestSeconds)
{
}

GxxGmRTSPServer::~GxxGmRTSPServer() {
}

// «∞÷√∂®“Â
//static ServerMediaSession* createNewSMS(UsageEnvironment& env, char const* fileName, FILE* fid);


ServerMediaSession* GxxGmRTSPServer::lookupServerMediaSession(char const* streamName, Boolean isFirstLookupInSession)
{
	// First, check whether the specified "streamName" exists as a local file:
	FILE* fid = fopen(streamName, "rb");
	Boolean fileExists = fid != NULL;

	// Next, check whether we already have a "ServerMediaSession" for this file:
	ServerMediaSession* sms = RTSPServer::lookupServerMediaSession(streamName);
	Boolean smsExists = sms != NULL;

	// Handle the four possibilities for "fileExists" and "smsExists":
	if (!fileExists) {
		if (smsExists) {
			// "sms" was created for a file that no longer exists. Remove it:
			removeServerMediaSession(sms);
			sms = NULL;
		}

		return NULL;
	} else {
		if (smsExists && isFirstLookupInSession) { 
			// Remove the existing "ServerMediaSession" and create a new one, in case the underlying
			// file has changed in some way:
			removeServerMediaSession(sms); 
			sms = NULL;
		} 

		if (sms == NULL) {
			//sms = createNewSMS(envir(), streamName, fid); 
			addServerMediaSession(sms);
		}

		fclose(fid);
		return sms;
	}
}