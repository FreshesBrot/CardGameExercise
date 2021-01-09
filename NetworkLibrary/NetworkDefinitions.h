#pragma once
//this header includes important definitions shared across the network library


#include <vector>
#include <memory>

#include <asio-1.18.0/include/asio.hpp>

#include "src/Queues/ObjectProvider.h"
#include "src/Queues/Subscriber.h"

#ifdef PROTOCOL_READY
typedef Protocol<Command> ProtocolType;
#else
typedef int ProtocolType;
#endif // PROTOCOL_READY

typedef std::shared_ptr <ObjectProvider<ProtocolType>> ProtocolQueue;

using TCP = asio::ip::tcp;
typedef std::shared_ptr<TCP::socket> SharedSocket;
typedef std::shared_ptr<asio::io_context> SharedContext;
typedef std::vector<char> Buffer;