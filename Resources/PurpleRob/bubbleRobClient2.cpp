// Make sure to have the server side running in V-REP!
// Start the server from a child script with following command:
// simExtRemoteApiStart(portNumber) -- starts a remote API server service on the specified port


#define NON_MATLAB_PARSING
#define MAX_EXT_API_CONNECTIONS 255
#define DO_NOT_USE_SHARED_MEMORY


#include <stdio.h>
#include <stdlib.h>

extern "C" {
#include "extApi.h"
}

extern "C" {
#include "extApiPlatform.h"
}



int main(int argc,char* argv[])
{
    int portNb=0;
    int objectHandle;

    if (argc>=5)
    {
        portNb=atoi(argv[1]);
        objectHandle=atoi(argv[2]);
    }
    else
    {
        printf("Indicate following arguments: 'portNumber objectHandle'!\n");
        extApi_sleepMs(5000);
        return 0;
    }

    int clientID=simxStart((simxChar*)"127.0.0.1",portNb,true,true,2000,5);
    if (clientID!=-1)
    {
        float position[3] ={0.0,0.0,0.0};

        while (simxGetConnectionId(clientID)!=-1)
        {
// Compute new position
            position[2]=position[2]+0.001;
// Set position        
            simxInt = simxSetObjectPosition(clientID,objectHandle,-1,position,simx_opmode_oneshot);
            extApi_sleepMs(5);
        }
        simxFinish(clientID);
    }
    return(0);
}

