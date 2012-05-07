#ifndef DISCOVERYCOMPONENT_H
#define DISCOVERYCOMPONENT_H

namespace icinga
{

class ComponentDiscoveryInfo : public Object
{
public:
	typedef shared_ptr<ComponentDiscoveryInfo> Ptr;
	typedef weak_ptr<ComponentDiscoveryInfo> WeakPtr;

	string Node;
	string Service;

	set<string> SubscribedMethods;
	set<string> PublishedMethods;
};

class DiscoveryComponent : public IcingaComponent
{
private:
	VirtualEndpoint::Ptr m_DiscoveryEndpoint;
	map<string, ComponentDiscoveryInfo::Ptr> m_Components;
	bool m_Broker;
	Timer::Ptr m_DiscoveryConnectTimer;

	int NewEndpointHandler(const NewEndpointEventArgs& neea);
	int NewIdentityHandler(const EventArgs& ea);

	int NewComponentMessageHandler(const NewRequestEventArgs& nrea);
	int RegisterComponentMessageHandler(const NewRequestEventArgs& nrea);

	void SendDiscoveryMessage(string method, string identity, Endpoint::Ptr recipient);
	void ProcessDiscoveryMessage(string identity, DiscoveryMessage message);

	bool GetComponentDiscoveryInfo(string component, ComponentDiscoveryInfo::Ptr *info) const;

	int CheckExistingEndpoint(Endpoint::Ptr endpoint, const NewEndpointEventArgs& neea);
	int DiscoveryEndpointHandler(const NewEndpointEventArgs& neea, ComponentDiscoveryInfo::Ptr info) const;
	int DiscoverySinkHandler(const NewMethodEventArgs& nmea, ComponentDiscoveryInfo::Ptr info) const;
	int DiscoverySourceHandler(const NewMethodEventArgs& nmea, ComponentDiscoveryInfo::Ptr info) const;

	int ReconnectTimerHandler(const TimerEventArgs& tea);

	bool IsBroker(void) const;

public:
	virtual string GetName(void) const;
	virtual void Start(void);
	virtual void Stop(void);
};

}

#endif /* DISCOVERYCOMPONENT_H */
