/*
 * Reactor.cpp
 *
 *  Created on: Jan 7, 2014
 *      Author: "enjolras@163.com"
 */

#include "Reactor.h"
#include "Log.h"
#include "Event.h"
#include "Define.h"

Reactor::Reactor(void) : epfd_(nullfd), max_event_(4096), wait_ms_(-1) {

}

int Reactor::init(int max_event) {
	if ((epfd_ = ::epoll_create(100)) == nullfd) {
		rec_log(Log::LVL_ERROR, "epoll_create");
		return FAIL;
	}
	if (max_event_ < 0 || max_event > MAX_MAX_EVENT) {
		rec_log(Log::LVL_ERROR, "event to large");
		return FAIL;
	}
	max_event_ = max_event;
	events_.resize(max_event_);
	handlers_.resize(max_event_);
	return 0;
}

int Reactor::fini(void) {
	return 0;
}

int Reactor::register_handler(const SEvent &evh, int event_type) {
	struct epoll_event ev;
	memset(&ev, 0, sizeof(ev));
	int fd = evh->get_fd();
	if (fd < 0 || fd >= max_event_) {
		rec_log(Log::LVL_ERROR, "fd size : %d", fd);
		return FAIL;
	}

	switch (event_type) {
	case Event::READ_MASK:
		ev.events |= EPOLLIN | EPOLLRDHUP | EPOLLET;
		break;
	case Event::WRITE_MASK:
		ev.events |= EPOLLOUT | EPOLLET;
		break;
	case Event::EXCEPT_MASK:
		ev.events |= EPOLLPRI;
		break;
	case Event::ACCEPT_MASK:
		ev.events |= EPOLLIN;
		break;
	case Event::CONNECT_MASK:
		break;
	case Event::TIMER_MASK:
		break;
	case Event::READ_WRITE_MASK:
		ev.events |= EPOLLIN | EPOLLRDHUP | EPOLLOUT | EPOLLET;
		break;
	default:
		rec_log(Log::LVL_ERROR, "event_type : %d", event_type);
		return FAIL;
	}

	ev.data.fd = fd;
	if (::epoll_ctl(epfd_, EPOLL_CTL_ADD, fd, &ev) == nullfd) {
		rec_errno_log();
		return FAIL;
	}
	handlers_[fd] = evh;
	rec_log(Log::LVL_DEBUG, "register fd : %d", fd);

	return 0;
}

int Reactor::remove_handler(const SEvent &evh) {
	if (!evh) {
		rec_log(Log::LVL_ERROR, "null evh");
		return FAIL;
	}

	int ret = 0;
	int fd = evh->get_fd();
	if (fd < 0 || fd >= max_event_) {
		rec_log(Log::LVL_ERROR, "fd size : %d", fd);
		return FAIL;
	}

	if ((ret = ::epoll_ctl(epfd_, EPOLL_CTL_DEL, fd, NULL)) == FAIL) {
		rec_errno_log();
	}
	handlers_[fd].reset();

	return 0;
}

void Reactor::handle_event(void) {
	int nfds = ::epoll_wait(epfd_, &events_[0], max_event_, wait_ms_);
	if (nfds == nullfd) {
		if (errno != EINTR) {
			rec_errno_log();
		}
		return;
	}

	for (int i = 0; i < nfds; ++i) {
		int fd = events_[i].data.fd;
		const SEvent &evh = handlers_[fd];
		bool close = false;
		if (!evh) {
			rec_log(Log::LVL_ERROR, "null evh %d", events_[i].data.fd);
			continue;
		}
		if (events_[i].events & EPOLLIN) {	// 可读
			evh->handle_input();
		}
		if (events_[i].events & EPOLLOUT) {	// 可写
			evh->handle_output();
		}
		if (events_[i].events & EPOLLRDHUP) {	// 对端关闭
			rec_log(Log::LVL_DEBUG, "EPOLLRDHUP %d", evh->get_fd());
			close = true;
		}
		if (events_[i].events & EPOLLPRI) {	// 带外数据
			// ignore it
		}
		if (events_[i].events & EPOLLERR) {	// 对应的文件描述符发生错误
			rec_log(Log::LVL_DEBUG, "EPOLLERR %d", evh->get_fd());
			close = true;
		}
		if (events_[i].events & EPOLLHUP) {	// 对应的文件描述符被挂断
			rec_log(Log::LVL_DEBUG, "EPOLLHUP %d", evh->get_fd());
			close = true;
		}
		if (close) {
			evh->handle_close();
			remove_handler(evh);
		}
	}
}
