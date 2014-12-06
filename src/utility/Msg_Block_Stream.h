/*
 * Msg_Block_Stream.h
 *
 *  Created on: Jun 28, 2014
 *      Author: "enjolras"
 */

#ifndef MSG_BLOCK_STREAM_H_
#define MSG_BLOCK_STREAM_H_

#include "Msg_Block.h"
#include <google/protobuf/io/zero_copy_stream.h>

class Msg_Block_OStream: public google::protobuf::io::ZeroCopyOutputStream {
public:
	Msg_Block_OStream(Msg_Block* buf) : buffer_(buf), originalSize_(buffer_->readable_bytes()) { }

	virtual bool Next(void** data, int* size) override;
	virtual void BackUp(int count) override;
	virtual int64_t ByteCount(void) const override;

private:
	Msg_Block* buffer_;
	size_t originalSize_;
};

bool Msg_Block_OStream::Next(void** data, int* size) {
	*data = buffer_->get_wptr();
	*size = static_cast<int>(buffer_->writable_bytes());
	buffer_->forward_wptr(*size);
	return true;
}

void Msg_Block_OStream::BackUp(int count) {
	buffer_->back_wptr(count);
}

int64_t Msg_Block_OStream::ByteCount(void) const {
	return buffer_->readable_bytes() - originalSize_;
}

#endif /* MSG_BLOCK_STREAM_H_ */
