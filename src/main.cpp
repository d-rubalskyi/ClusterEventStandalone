#include "sockpp/tcp_connector.h"

#include <string>
#include "ClusterCommandManager.h"

int main()
{
	UClusterCommandManager ClusterCommandManager("127.0.0.1");

	// Sending JSON command

	ClusterCommandManager.SendClusterCommandJsn("MyCommand", "MyType", "");

	// Sending BINARY command

	uint8_t Data[] = { 42, 146 };

	ClusterCommandManager.SendClusterCommandBin(1234, false, false, Data, 2);
 }
