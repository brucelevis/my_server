/*
 * Msg_Block.h
 *
 *  Created on: Jan 14, 2014
 *      Author: "enjolras@163.com"
 */

// +---------------+------------------+------------------+
// | reserve bytes |  readable bytes  |  writable bytes  |
// |               |     (CONTENT)    |                  |
// +---------------+------------------+------------------+
// |               |                  |                  |
// 0      <=   	rptr_      <=		wptr_      <=     	size

#ifndef MSG_BLOCK_H_
#define MSG_BLOCK_H_

#include "Pre_Header.h"
#include "Define.h"
#include "Log.h"

const uint32_t DEFAULT_RESERVE = 16;
const uint32_t DEFAULT_CONTENT = 1024;
class Tcp_Connection;
class Msg_Block : private copyable {
public:
	typedef std::function<int(void *, size_t, int)> SendRecv_Func;
	typedef uint16_t str_len_type;

	Msg_Block(void);
	Msg_Block(size_t reserve_size, size_t content_size);
	Msg_Block(const Msg_Block &msg_block) = default;
	Msg_Block(Msg_Block &&msg_block) = default;
	Msg_Block &operator=(const Msg_Block &msg_block) = default;
	Msg_Block &operator=(Msg_Block &&msg_block) = default;
	~Msg_Block(void) = default;

	void recv_msg(const SendRecv_Func &func, int flags);
	// success mean all msg has been send fail mean some byte left
	int send_msg(const SendRecv_Func &func, int flags);
	inline void reset(void);
	inline const char *get_rptr(void) const;
	inline size_t readable_bytes(void) const;
	inline size_t writable_bytes(void) const;
	inline size_t reserve_bytes(void) const;

	inline int read_bool(bool &v);
	inline int read_int8(int8_t &v);
	inline int read_int16(int16_t &v);
	inline int read_int32(int32_t &v);
	inline int read_int64(int64_t &v);
	inline int read_uint8(uint8_t &v);
	inline int read_uint16(uint16_t &v);
	inline int read_uint32(uint32_t &v);
	inline int read_uint64(uint64_t &v);
	inline int read_double(double &v);

	inline void write_bool(bool v);
	inline void write_int8(int8_t v);
	inline void write_int16(int16_t v);
	inline void write_int32(int32_t v);
	inline void write_int64(int64_t v);
	inline void write_uint8(uint8_t v);
	inline void write_uint16(uint16_t v);
	inline void write_uint32(uint32_t v);
	inline void write_uint64(uint64_t v);
	inline void write_double(double v);

	inline void write_uint32_tohead(uint32_t v);
	inline void write_bytes(const char *src, size_t len);

	inline int peek_bool(bool &v) const;
	inline int peek_int8(int8_t &v) const;
	inline int peek_int16(int16_t &v) const;
	inline int peek_int32(int32_t &v) const;
	inline int peek_int64(int64_t &v) const;
	inline int peek_uint8(uint8_t &v) const;
	inline int peek_uint16(uint16_t &v) const;
	inline int peek_uint32(uint32_t &v) const;
	inline int peek_uint64(uint64_t &v) const;
	inline int peek_double(double &v) const;

	inline int read_string(std::string &v);
	inline void write_string(const std::string &v);
	inline int peek_string(std::string &v) const;

	inline void forward_wptr(size_t len);
	inline void back_wptr(size_t len);
	inline void forward_rptr(size_t len);
	inline void back_rptr(size_t len);

	inline void log_contain(void) const;

	inline char *get_wptr(void);

	inline void swap(Msg_Block &msg);

private:
	inline bool is_readable(size_t len) const;
	inline void ensure_writeheadable(size_t len);
	inline void ensure_writeable(size_t len);
	inline void make_space(size_t len);
	inline char *get_whptr(size_t len);

	// avoid uncertain type by use private template member func
	template <typename T>
	inline int read(T &v);
	template <typename T>
	inline void write(T v);
	template <typename T>
	inline int peek(T &v) const;

private:
	std::vector<char> data_;
	size_t rptr_;
	size_t wptr_;
};

inline void Msg_Block::swap(Msg_Block &msg) {
	using std::swap;
	swap(data_, msg.data_);
	swap(rptr_, msg.rptr_);
	swap(wptr_, msg.wptr_);
}

namespace std {
	template<>
	inline void swap<Msg_Block>(Msg_Block &msg1, Msg_Block &msg2) {
		msg1.swap(msg2);
	}
}

inline size_t Msg_Block::readable_bytes(void) const {
	return wptr_ - rptr_;
}

inline size_t Msg_Block::writable_bytes(void) const {
	return data_.size() - wptr_;
}

inline size_t Msg_Block::reserve_bytes(void) const {
	return rptr_;
}

inline void Msg_Block::reset(void) {
	data_.resize(DEFAULT_RESERVE + DEFAULT_CONTENT);
	rptr_ =	DEFAULT_RESERVE;
	wptr_ = rptr_;
}

inline void Msg_Block::forward_wptr(size_t len) {
	assert(len <= writable_bytes());
	wptr_ += len;
}

inline void Msg_Block::back_wptr(size_t len) {
	assert(len <= readable_bytes());
	wptr_ -= len;
}

inline void Msg_Block::forward_rptr(size_t len) {
	assert(len <= readable_bytes());
	rptr_ += len;
}

inline void Msg_Block::back_rptr(size_t len) {
	assert(len <= reserve_bytes());
	rptr_ -= len;
}

inline const char *Msg_Block::get_rptr(void) const {
	return &data_[rptr_];
}

inline char *Msg_Block::get_wptr(void) {
	return &data_[wptr_];
}

inline char *Msg_Block::get_whptr(size_t len) {
	return &data_[rptr_ - len];
}

inline bool Msg_Block::is_readable(size_t len) const {
	return readable_bytes() >= len;
}

inline void Msg_Block::ensure_writeable(size_t len) {
	if (writable_bytes() < len) {
		make_space(len);
	}
}

inline void Msg_Block::ensure_writeheadable(size_t len) {
	if (reserve_bytes() < len) {
		std::vector<char> data;
		data.resize(data_.size() + len);
		memcpy(&data[rptr_ + len], &data_[rptr_], readable_bytes());
		rptr_ += len;
		wptr_ += len;
		using std::swap;
		swap(data_, data);
	}
}

inline void Msg_Block::make_space(size_t len) {
	if (writable_bytes() < len) {
		data_.resize(wptr_ + len);
	}
}

template <typename T>
inline int Msg_Block::read(T &v) {
	const size_t len = sizeof(v);
	if (is_readable(len)) {
		memcpy(&v, get_rptr(), len);
		rptr_ += len;
		return SUCCESS;
	} else {
		rec_log(Log::LVL_ERROR, "out of range");
		return FAIL;
	}
}

template <typename T>
inline void Msg_Block::write(T v) {
	const size_t len = sizeof(v);
	ensure_writeable(len);
	memcpy(get_wptr(), &v, len);
	wptr_ += len;
}

inline void Msg_Block::write_uint32_tohead(uint32_t v) {
	const size_t len = sizeof(v);
	ensure_writeheadable(len);
	memcpy(get_whptr(len), &v, len);
	rptr_ -= len;
}

inline void Msg_Block::write_bytes(const char *src, size_t len) {
	ensure_writeheadable(len);
	memcpy(get_wptr(), src, len);
	wptr_ += len;
}

template <typename T>
inline int Msg_Block::peek(T &v) const {
	const size_t len = sizeof(v);
	if (is_readable(len)) {
		memcpy(&v, get_rptr(), len);
		return SUCCESS;
	} else {
		rec_log(Log::LVL_ERROR, "out of range");
		return FAIL;
	}
}

inline int Msg_Block::read_bool(bool &v) {
	return read(v);
}

inline int Msg_Block::read_int8(int8_t &v) {
	return read(v);
}

inline int Msg_Block::read_int16(int16_t &v) {
	return read(v);
}

inline int Msg_Block::read_int32(int32_t &v) {
	return read(v);
}

inline int Msg_Block::read_int64(int64_t &v) {
	return read(v);
}

inline int Msg_Block::read_uint8(uint8_t &v) {
	return read(v);
}

inline int Msg_Block::read_uint16(uint16_t &v) {
	return read(v);
}

inline int Msg_Block::read_uint32(uint32_t &v) {
	return read(v);
}

inline int Msg_Block::read_uint64(uint64_t &v) {
	return read(v);
}

inline int Msg_Block::read_double(double &v) {
	return read(v);
}

inline int Msg_Block::read_string(std::string &v) {
	v.clear();
	str_len_type len = 0;
	int ret = read(len);
	if (SUCCESS == ret) {
		if (is_readable(len)) {
			v.resize(len);
			memcpy(static_cast<void*>(const_cast<char*>(v.c_str())), get_rptr(), len);
			rptr_ += len;
		} else {
			ret = FAIL;
		}
	}
	return ret;
}

inline void Msg_Block::write_bool(bool v) {
	write(v);
}

inline void Msg_Block::write_int8(int8_t v) {
	write(v);
}

inline void Msg_Block::write_int16(int16_t v) {
	write(v);
}

inline void Msg_Block::write_int32(int32_t v) {
	write(v);
}

inline void Msg_Block::write_int64(int64_t v) {
	write(v);
}

inline void Msg_Block::write_uint8(uint8_t v) {
	write(v);
}

inline void Msg_Block::write_uint16(uint16_t v) {
	write(v);
}

inline void Msg_Block::write_uint32(uint32_t v) {
	write(v);
}

inline void Msg_Block::write_uint64(uint64_t v) {
	write(v);
}

inline void Msg_Block::write_double(double v) {
	write(v);
}

inline void Msg_Block::write_string(const std::string &v) {
	str_len_type len = static_cast<str_len_type>(v.length());
	size_t total_len = sizeof(len) + len;
	ensure_writeable(total_len);
	write(len);
	memcpy(get_wptr(), v.c_str(), len);
	wptr_ += len;
}

inline int Msg_Block::peek_bool(bool &v) const {
	return peek(v);
}

inline int Msg_Block::peek_int8(int8_t &v) const {
	return peek(v);
}

inline int Msg_Block::peek_int16(int16_t &v) const {
	return peek(v);
}

inline int Msg_Block::peek_int32(int32_t &v) const {
	return peek(v);
}

inline int Msg_Block::peek_int64(int64_t &v) const {
	return peek(v);
}

inline int Msg_Block::peek_uint8(uint8_t &v) const {
	return peek(v);
}

inline int Msg_Block::peek_uint16(uint16_t &v) const {
	return peek(v);
}

inline int Msg_Block::peek_uint32(uint32_t &v) const {
	return peek(v);
}

inline int Msg_Block::peek_uint64(uint64_t &v) const {
	return peek(v);
}

inline int Msg_Block::peek_double(double &v) const {
	return peek(v);
}

inline int Msg_Block::peek_string(std::string &v) const {
	v.clear();
	str_len_type len = 0;
	int ret = peek(len);
	if (SUCCESS == ret) {
		if (is_readable(len)) {
			v.resize(len);
			memcpy(static_cast<void*>(const_cast<char*>(v.c_str())), get_rptr() + sizeof(len), len);
		} else {
			ret = FAIL;
		}
	}
	return ret;
}

inline void Msg_Block::log_contain(void) const {
	rec_log(Log::LVL_INFO, "read ptr : %d | write ptr : %d", rptr_, wptr_);
	const size_t buff_size = 2048;
	char contain[buff_size + 1] = {0};
	size_t size = std::min(buff_size / 2, readable_bytes());
	for (size_t i = 0; i < size; ++i) {
		size_t offset = 2 * i;
		snprintf(contain + offset, buff_size - offset, "%02x", static_cast<unsigned char>(data_[i + rptr_]));
	}
	rec_log(Log::LVL_INFO, "contain : %s", contain);
}

#endif /* MSG_BLOCK_H_ */
