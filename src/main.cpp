#include "sockpp/tcp_connector.h"

#include <string>
#include "ClusterCommandManager.h"

/*
bool SendClusterCommand(sockpp::tcp_connector& Connector, std::string const& Cmd)
{
	uint32_t PacketSize = Cmd.length();
	size_t HeaderSize = sizeof(PacketSize);

	std::vector<uint8_t> Buffer(HeaderSize + PacketSize);
	
	memcpy(Buffer.data(), &PacketSize, HeaderSize);
	memcpy(Buffer.data() + HeaderSize, Cmd.data(), PacketSize);

	ssize_t BytesWritten = Connector.write_n(Buffer.data(), Buffer.size());

	if (BytesWritten != Buffer.size())
	{
		std::cerr << "Error writing to the TCP stream:"
			<< "\n\t" << Connector.last_error_str() << std::endl;

		return false;
	}

	return true;
}
*/

int main()
{
	/*
	sockpp::initialize();
	
	std::string Host = "127.0.0.1";
	in_port_t Port = 41003;

	sockpp::tcp_connector Connector({ Host, Port }, std::chrono::seconds{ 5 });

	if (!Connector) {
		std::cerr << "Error connecting to server at "
			<< sockpp::inet_address(Host, Port)
			<< "\n\t" << Connector.last_error_str() << std::endl;
		return 1;
	}

	std::cout << "Created a connection from " << Connector.address() << std::endl;

	// Set a timeout for the responses
	if (!Connector.read_timeout(std::chrono::seconds(5))) {
		std::cerr << "Error setting timeout on TCP stream: "
			<< Connector.last_error_str() << std::endl;
	}

	std::string Cmd = "{\"Name\": \"EventName\", \"Type\": \"EventType\", \"Category\": \"EventCategory\", \"Parameters\": {\"SomeField\":\"SomeField\"}}";

	SendClusterCommand(Connector, Cmd);
	*/

	UClusterCommandManager ClusterCommandManager("127.0.0.1");

	// Sending JSON command

	ClusterCommandManager.SendClusterCommandJsn("MyCommand", "MyType", "");

	// Sending BINARY command

	uint8_t Data[] = { 42, 146 };

	ClusterCommandManager.SendClusterCommandBin(1234, false, false, Data, 1);
}
