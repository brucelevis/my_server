/*
 * Acceptor.h
 *
 *  Created on: Jan 8, 2014
 *      Author: "enjolras@163.com"
 */

#ifndef ACCEPTOR_H_
#define ACCEPTOR_H_

#include "Pre_Header.h"
#include "Event.h"

class Sock_Acceptor;
class Acceptor : public Event {
public:
	typedef std::function<void(int)> Accept_Callback;

	Acceptor(Reactor *reactor);
	virtual ~Acceptor(void);

	int init(Sock_Acceptor *sock_acceptor, const Accept_Callback &accept_cb);

	virtual void handle_input(void) override;
	virtual void handle_output(void) override;
	virtual void handle_close(void) override;
	virtual int get_fd(void) const override;
	virtual void set_fd(int fd) override;
private:
	boost::scoped_ptr<Sock_Acceptor> sock_acceptor_;
	Accept_Callback accept_cb_;
};

#endif /* ACCEPTOR_H_ */
