#ifndef TCPSOCKET_H
#define TCPSOCKET_H

namespace icinga
{

class I2_BASE_API TCPSocket : public Socket
{
private:
	void MakeSocket(int family);

public:
	typedef shared_ptr<TCPSocket> Ptr;
	typedef weak_ptr<TCPSocket> WeakPtr;

	void Bind(string service, int family);
	void Bind(string node, string service, int family);
};

}

#endif /* TCPSOCKET_H */
