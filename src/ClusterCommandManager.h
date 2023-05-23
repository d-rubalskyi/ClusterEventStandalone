#pragma once

#include "sockpp/tcp_connector.h"

class UClusterCommandManager
{	
public:

	UClusterCommandManager();
	UClusterCommandManager(std::string const& Address);
	~UClusterCommandManager();

	bool SetJsnPort(in_port_t Port, bool bNeedRestoreConnection = false);
	bool SetBinPort(in_port_t Port, bool bNeedRestoreConnection = false);

	bool Connect(std::string const& Address);
	void Disconnect();

	bool SendClusterCommandJsn(std::string const& Cmd);
	bool SendClusterCommandJsn(std::string const& CmdName, std::string const& CmdType, std::string const& CmdCategory);

	bool SendClusterCommandBin(std::vector<uint8_t> const& Buffer);
	bool SendClusterCommandBin(uint32_t EventId, bool bSystemEvent, bool bShoudRepeat, uint8_t* Value, uint32_t Count);

private:

	std::string JsnClusterAddress;
	std::string BinClusterAddress;

	in_port_t JsnClusterPort;
	in_port_t BinClusterPort;	

	sockpp::tcp_connector JsnConnector;
	sockpp::tcp_connector BinConnector;

	std::string LastErrorStrJsn;
	std::string LastErrorStrBin;

	bool ConnectJsn(std::string const& Address);
	bool ConnectBin(std::string const& Address);

	std::string SerializeJsnCommand(std::string const& CmdName, std::string const& CmdType, std::string const& CmdCategory);
	std::vector<uint8_t> SerializeBinCommand(uint32_t EventId, bool bSystemEvent, bool bShouldRepeat, uint8_t* Value, uint32_t Count);
};