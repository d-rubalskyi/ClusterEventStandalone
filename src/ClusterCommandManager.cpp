
#include "ClusterCommandManager.h"


UClusterCommandManager::UClusterCommandManager()
{
	JsnClusterPort = 41003;
	BinClusterPort = 41004;

	sockpp::initialize();
}

UClusterCommandManager::UClusterCommandManager(std::string const& Address)
	: UClusterCommandManager()
{
	Connect(Address);
}

UClusterCommandManager::~UClusterCommandManager()
{
	JsnConnector.close();
	BinConnector.close();
}

bool UClusterCommandManager::SetJsnPort(in_port_t Port, bool bNeedRestoreConnection)
{
	if (JsnConnector.is_connected())
	{
		JsnConnector.close();
	}

	JsnClusterPort = Port;

	if (bNeedRestoreConnection)
	{
		return ConnectJsn({ JsnClusterAddress, JsnClusterPort });
	}

	return true;
}

bool UClusterCommandManager::SetBinPort(in_port_t Port, bool bNeedRestoreConnection)
{
	if (BinConnector.is_connected())
	{
		BinConnector.close();
	}

	BinClusterPort = Port;

	if (bNeedRestoreConnection)
	{
		return ConnectBin({ BinClusterAddress, BinClusterPort });
	}

	return true;
}

bool UClusterCommandManager::ConnectJsn(std::string const& Address)
{
	if (JsnConnector.connect({ Address, JsnClusterPort }))
	{
		JsnClusterAddress = Address;
		LastErrorStrJsn = "";

		return true;
	}
	else
	{
		JsnClusterAddress = "";
		LastErrorStrJsn = JsnConnector.last_error_str();
	}

	return false;
}

bool UClusterCommandManager::ConnectBin(std::string const& Address)
{
	if (BinConnector.connect({ Address, BinClusterPort }))
	{
		BinClusterAddress = Address;
		LastErrorStrBin = "";

		return true;
	}
	else
	{
		BinClusterAddress = "";
		LastErrorStrBin = BinConnector.last_error_str();
	}
	
	return false;
}

bool UClusterCommandManager::Connect(std::string const& Address)
{
	return ConnectJsn(Address) && ConnectBin(Address);
}

void UClusterCommandManager::Disconnect()
{
	JsnConnector.close();
	BinConnector.close();
}

std::string UClusterCommandManager::SerializeJsnCommand(std::string const& CmdName, std::string const& CmdType, std::string const& CmdCategory)
{
	return "{\"Name\": \"" + CmdName + "\", \"Type\": \"" + CmdType + "\", \"Category\": \"" + CmdCategory + "\", \"Parameters\": {}}";
}

std::vector<uint8_t> UClusterCommandManager::SerializeBinCommand(uint32_t EventId, bool bSystemEvent, bool bShouldRepeat, uint8_t* Value, uint32_t Count)
{
	uint8_t SystemEvent = bSystemEvent ? 1 : 0;
	uint8_t ShouldRepeat = bShouldRepeat ? 1 : 0;

	uint32_t EventIdSize = sizeof(EventId);
	uint32_t AuxParameterSize = sizeof(uint8_t);
	uint32_t TotalDataSize = sizeof(uint8_t) * Count;

	uint32_t PacketSize = EventIdSize + AuxParameterSize * 2 + TotalDataSize;
	size_t HeaderSize = sizeof(PacketSize);

	std::vector<uint8_t> Buffer(HeaderSize + PacketSize);

	memcpy(Buffer.data(), &PacketSize, HeaderSize);
	memcpy(Buffer.data() + HeaderSize, &EventId, EventIdSize);
	memcpy(Buffer.data() + HeaderSize + EventIdSize, &SystemEvent, AuxParameterSize);
	memcpy(Buffer.data() + HeaderSize + EventIdSize + AuxParameterSize, &ShouldRepeat, AuxParameterSize);
	memcpy(Buffer.data() + HeaderSize + EventIdSize + AuxParameterSize * 2, Value, TotalDataSize);

	return Buffer;
}

bool UClusterCommandManager::SendClusterCommandJsn(std::string const& Cmd)
{
	uint32_t PacketSize = Cmd.length();
	size_t HeaderSize = sizeof(PacketSize);

	std::vector<uint8_t> Buffer(HeaderSize + PacketSize);

	memcpy(Buffer.data(), &PacketSize, HeaderSize);
	memcpy(Buffer.data() + HeaderSize, Cmd.data(), PacketSize);

	ssize_t BytesWritten = JsnConnector.write_n(Buffer.data(), Buffer.size());

	if (BytesWritten != Buffer.size())
	{
		LastErrorStrJsn = JsnConnector.last_error_str();
		return false;
	}

	LastErrorStrJsn = "";
	return true;
}

bool UClusterCommandManager::SendClusterCommandJsn(std::string const& CmdName, std::string const& CmdType, std::string const& CmdCategory)
{
	std::string Cmd = SerializeJsnCommand(CmdName, CmdType, CmdCategory);

	return SendClusterCommandJsn(Cmd);
}

bool UClusterCommandManager::SendClusterCommandBin(std::vector<uint8_t> const& Buffer)
{
	ssize_t BytesWritten = BinConnector.write_n(Buffer.data(), Buffer.size());

	if (BytesWritten != Buffer.size())
	{
		LastErrorStrBin = BinConnector.last_error_str();
		return false;
	}

	LastErrorStrBin = "";
	return true;
}

bool UClusterCommandManager::SendClusterCommandBin(uint32_t EventId, bool bSystemEvent, bool bShouldRepeat, uint8_t* Value, uint32_t Count)
{
	std::vector<uint8_t> Buffer = SerializeBinCommand(EventId, bSystemEvent, bShouldRepeat, Value, Count);
	
	return SendClusterCommandBin(Buffer);
}