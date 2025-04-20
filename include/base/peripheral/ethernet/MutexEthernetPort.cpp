#include "MutexEthernetPort.h"

base::ethernet::MutexEthernetPort::MutexEthernetPort(base::ethernet::IEthernetPort *port)
{
	_port = port;
}

void base::ethernet::MutexEthernetPort::Open(base::Mac const &mac)
{
	base::LockGuard l{*_lock};
	_port->Open(mac);
}

void base::ethernet::MutexEthernetPort::Send(std::vector<base::ReadOnlySpan> const &spans)
{
	base::LockGuard l{*_sending_lock};
	_port->Send(spans);
}

void base::ethernet::MutexEthernetPort::Send(base::ReadOnlySpan const &span)
{
	base::LockGuard l{*_sending_lock};
	_port->Send(span);
}

base::IEvent<base::ReadOnlySpan> &base::ethernet::MutexEthernetPort::ReceivingEhternetFrameEvent()
{
	base::LockGuard l{*_sending_lock};
	return _port->ReceivingEhternetFrameEvent();
}

base::IEvent<> &base::ethernet::MutexEthernetPort::ConnectedEvent()
{
	base::LockGuard l{*_sending_lock};
	return _port->ConnectedEvent();
}

base::IEvent<> &base::ethernet::MutexEthernetPort::DisconnectedEvent()
{
	base::LockGuard l{*_sending_lock};
	return _port->DisconnectedEvent();
}
