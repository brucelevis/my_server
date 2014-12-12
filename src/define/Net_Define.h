/*
 * Net_Define.h
 *
 *  Created on: Jan 14, 2014
 *      Author: "enjolras@163.com"
 */

#ifndef NET_DEFINE_H_
#define NET_DEFINE_H_

const uint32_t MAX_LISTEN = 1024;

const uint32_t MAX_SEND = 2048;
const uint32_t MAX_RECV = 2048;

const int32_t ACCEPT_SOCK_TYPE =  SOCK_STREAM | SOCK_NONBLOCK | SOCK_CLOEXEC;
const int32_t STREAM_SOCK_TYPE = SOCK_NONBLOCK | SOCK_CLOEXEC;
const int32_t LISTEN_PORT = 7500;

#endif /* NET_DEFINE_H_ */
