extern "C"{
#include <Com/SocketServer.h>
#include <Com/TcpComLink.h>
#include <CSlim/Slim.h>
#include <CSlim/SlimConnectionHandler.h>
}
#include <stdlib.h>
#include <string.h>
Slim * slim;
extern "C"{
int connection_handler(int socket)
{
	int result = 0;
	TcpComLink * comLink = TcpComLink_Create(socket);

  result = Slim_HandleConnection(slim, (void*)comLink, &TcpComLink_send, &TcpComLink_recv);

	TcpComLink_Destroy(comLink);

	return result;
}

int main(int ac, char** av)
{
  slim = Slim_Create();
	SocketServer* server = SocketServer_Create();
	SocketServer_register_handler(server, &connection_handler);
	int result = SocketServer_Run(server, av[1]);

	SocketServer_Destroy(server);
  Slim_Destroy(slim);
	return 0;
}
}
