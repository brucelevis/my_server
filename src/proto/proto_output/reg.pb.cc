// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: reg.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "reg.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace MSG {

namespace {

const ::google::protobuf::Descriptor* reg_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  reg_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_reg_2eproto() {
  protobuf_AddDesc_reg_2eproto();
  const ::google::protobuf::FileDescriptor* file =
	::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
	  "reg.proto");
  GOOGLE_CHECK(file != NULL);
  reg_descriptor_ = file->message_type(0);
  static const int reg_offsets_[3] = {
	GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(reg, career_),
	GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(reg, sex_),
	GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(reg, account_),
  };
  reg_reflection_ =
	::google::protobuf::internal::GeneratedMessageReflection::NewGeneratedMessageReflection(
	  reg_descriptor_,
	  reg::default_instance_,
	  reg_offsets_,
	  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(reg, _has_bits_[0]),
	  -1,
	  -1,
	  sizeof(reg),
	  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(reg, _internal_metadata_),
	  -1);
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
				 &protobuf_AssignDesc_reg_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
	  reg_descriptor_, &reg::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_reg_2eproto() {
  delete reg::default_instance_;
  delete reg_reflection_;
}

void protobuf_AddDesc_reg_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
	"\n\treg.proto\022\003MSG\"3\n\003reg\022\016\n\006career\030\001 \002(\005\022"
	"\013\n\003sex\030\002 \002(\005\022\017\n\007account\030\003 \002(\t", 69);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
	"reg.proto", &protobuf_RegisterTypes);
  reg::default_instance_ = new reg();
  reg::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_reg_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_reg_2eproto {
  StaticDescriptorInitializer_reg_2eproto() {
	protobuf_AddDesc_reg_2eproto();
  }
} static_descriptor_initializer_reg_2eproto_;

namespace {

static void MergeFromFail(int line) GOOGLE_ATTRIBUTE_COLD;
static void MergeFromFail(int line) {
  GOOGLE_CHECK(false) << __FILE__ << ":" << line;
}

}  // namespace


// ===================================================================

#ifndef _MSC_VER
const int reg::kCareerFieldNumber;
const int reg::kSexFieldNumber;
const int reg::kAccountFieldNumber;
#endif  // !_MSC_VER

reg::reg()
  : ::google::protobuf::Message() , _internal_metadata_(NULL)  {
  SharedCtor();
  // @@protoc_insertion_point(constructor:MSG.reg)
}

void reg::InitAsDefaultInstance() {
}

reg::reg(const reg& from)
  : ::google::protobuf::Message(),
	_internal_metadata_(NULL) {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:MSG.reg)
}

void reg::SharedCtor() {
  ::google::protobuf::internal::GetEmptyString();
  _cached_size_ = 0;
  career_ = 0;
  sex_ = 0;
  account_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

reg::~reg() {
  // @@protoc_insertion_point(destructor:MSG.reg)
  SharedDtor();
}

void reg::SharedDtor() {
  account_.DestroyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  if (this != default_instance_) {
  }
}

void reg::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* reg::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return reg_descriptor_;
}

const reg& reg::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_reg_2eproto();
  return *default_instance_;
}

reg* reg::default_instance_ = NULL;

reg* reg::New(::google::protobuf::Arena* arena) const {
  reg* n = new reg;
  if (arena != NULL) {
	arena->Own(n);
  }
  return n;
}

void reg::Clear() {
#define ZR_HELPER_(f) reinterpret_cast<char*>(\
  &reinterpret_cast<reg*>(16)->f)

#define ZR_(first, last) do {\
  ::memset(&first, 0,\
		   ZR_HELPER_(last) - ZR_HELPER_(first) + sizeof(last));\
} while (0)

  if (_has_bits_[0 / 32] & 7) {
	ZR_(career_, sex_);
	if (has_account()) {
	  account_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
	}
  }

#undef ZR_HELPER_
#undef ZR_

  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  if (_internal_metadata_.have_unknown_fields()) {
	mutable_unknown_fields()->Clear();
  }
}

bool reg::MergePartialFromCodedStream(
	::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:MSG.reg)
  for (;;) {
	::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
	tag = p.first;
	if (!p.second) goto handle_unusual;
	switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
	  // required int32 career = 1;
	  case 1: {
		if (tag == 8) {
		  DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
				   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
				 input, &career_)));
		  set_has_career();
		} else {
		  goto handle_unusual;
		}
		if (input->ExpectTag(16)) goto parse_sex;
		break;
	  }

	  // required int32 sex = 2;
	  case 2: {
		if (tag == 16) {
		 parse_sex:
		  DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
				   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
				 input, &sex_)));
		  set_has_sex();
		} else {
		  goto handle_unusual;
		}
		if (input->ExpectTag(26)) goto parse_account;
		break;
	  }

	  // required string account = 3;
	  case 3: {
		if (tag == 26) {
		 parse_account:
		  DO_(::google::protobuf::internal::WireFormatLite::ReadString(
				input, this->mutable_account()));
		  ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
			this->account().data(), this->account().length(),
			::google::protobuf::internal::WireFormat::PARSE,
			"MSG.reg.account");
		} else {
		  goto handle_unusual;
		}
		if (input->ExpectAtEnd()) goto success;
		break;
	  }

	  default: {
	  handle_unusual:
		if (tag == 0 ||
			::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
			::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
		  goto success;
		}
		DO_(::google::protobuf::internal::WireFormat::SkipField(
			  input, tag, mutable_unknown_fields()));
		break;
	  }
	}
  }
success:
  // @@protoc_insertion_point(parse_success:MSG.reg)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:MSG.reg)
  return false;
#undef DO_
}

void reg::SerializeWithCachedSizes(
	::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:MSG.reg)
  // required int32 career = 1;
  if (has_career()) {
	::google::protobuf::internal::WireFormatLite::WriteInt32(1, this->career(), output);
  }

  // required int32 sex = 2;
  if (has_sex()) {
	::google::protobuf::internal::WireFormatLite::WriteInt32(2, this->sex(), output);
  }

  // required string account = 3;
  if (has_account()) {
	::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
	  this->account().data(), this->account().length(),
	  ::google::protobuf::internal::WireFormat::SERIALIZE,
	  "MSG.reg.account");
	::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
	  3, this->account(), output);
  }

  if (_internal_metadata_.have_unknown_fields()) {
	::google::protobuf::internal::WireFormat::SerializeUnknownFields(
		unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:MSG.reg)
}

::google::protobuf::uint8* reg::SerializeWithCachedSizesToArray(
	::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:MSG.reg)
  // required int32 career = 1;
  if (has_career()) {
	target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(1, this->career(), target);
  }

  // required int32 sex = 2;
  if (has_sex()) {
	target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(2, this->sex(), target);
  }

  // required string account = 3;
  if (has_account()) {
	::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
	  this->account().data(), this->account().length(),
	  ::google::protobuf::internal::WireFormat::SERIALIZE,
	  "MSG.reg.account");
	target =
	  ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
		3, this->account(), target);
  }

  if (_internal_metadata_.have_unknown_fields()) {
	target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
		unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:MSG.reg)
  return target;
}

int reg::RequiredFieldsByteSizeFallback() const {
  int total_size = 0;

  if (has_career()) {
	// required int32 career = 1;
	total_size += 1 +
	  ::google::protobuf::internal::WireFormatLite::Int32Size(
		this->career());
  }

  if (has_sex()) {
	// required int32 sex = 2;
	total_size += 1 +
	  ::google::protobuf::internal::WireFormatLite::Int32Size(
		this->sex());
  }

  if (has_account()) {
	// required string account = 3;
	total_size += 1 +
	  ::google::protobuf::internal::WireFormatLite::StringSize(
		this->account());
  }

  return total_size;
}
int reg::ByteSize() const {
  int total_size = 0;

  if (((_has_bits_[0] & 0x00000007) ^ 0x00000007) == 0) {  // All required fields are present.
	// required int32 career = 1;
	total_size += 1 +
	  ::google::protobuf::internal::WireFormatLite::Int32Size(
		this->career());

	// required int32 sex = 2;
	total_size += 1 +
	  ::google::protobuf::internal::WireFormatLite::Int32Size(
		this->sex());

	// required string account = 3;
	total_size += 1 +
	  ::google::protobuf::internal::WireFormatLite::StringSize(
		this->account());

  } else {
	total_size += RequiredFieldsByteSizeFallback();
  }
  if (_internal_metadata_.have_unknown_fields()) {
	total_size +=
	  ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
		unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void reg::MergeFrom(const ::google::protobuf::Message& from) {
  if (GOOGLE_PREDICT_FALSE(&from == this)) MergeFromFail(__LINE__);
  const reg* source =
	::google::protobuf::internal::dynamic_cast_if_available<const reg*>(
	  &from);
  if (source == NULL) {
	::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
	MergeFrom(*source);
  }
}

void reg::MergeFrom(const reg& from) {
  if (GOOGLE_PREDICT_FALSE(&from == this)) MergeFromFail(__LINE__);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
	if (from.has_career()) {
	  set_career(from.career());
	}
	if (from.has_sex()) {
	  set_sex(from.sex());
	}
	if (from.has_account()) {
	  set_has_account();
	  account_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.account_);
	}
  }
  if (from._internal_metadata_.have_unknown_fields()) {
	mutable_unknown_fields()->MergeFrom(from.unknown_fields());
  }
}

void reg::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void reg::CopyFrom(const reg& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool reg::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000007) != 0x00000007) return false;

  return true;
}

void reg::Swap(reg* other) {
  if (other == this) return;
  InternalSwap(other);
}
void reg::InternalSwap(reg* other) {
  std::swap(career_, other->career_);
  std::swap(sex_, other->sex_);
  account_.Swap(&other->account_);
  std::swap(_has_bits_[0], other->_has_bits_[0]);
  _internal_metadata_.Swap(&other->_internal_metadata_);
  std::swap(_cached_size_, other->_cached_size_);
}

::google::protobuf::Metadata reg::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = reg_descriptor_;
  metadata.reflection = reg_reflection_;
  return metadata;
}

#if PROTOBUF_INLINE_NOT_IN_HEADERS
// reg

// required int32 career = 1;
 bool reg::has_career() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
 void reg::set_has_career() {
  _has_bits_[0] |= 0x00000001u;
}
 void reg::clear_has_career() {
  _has_bits_[0] &= ~0x00000001u;
}
 void reg::clear_career() {
  career_ = 0;
  clear_has_career();
}
 ::google::protobuf::int32 reg::career() const {
  // @@protoc_insertion_point(field_get:MSG.reg.career)
  return career_;
}
 void reg::set_career(::google::protobuf::int32 value) {
  set_has_career();
  career_ = value;
  // @@protoc_insertion_point(field_set:MSG.reg.career)
}

// required int32 sex = 2;
 bool reg::has_sex() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
 void reg::set_has_sex() {
  _has_bits_[0] |= 0x00000002u;
}
 void reg::clear_has_sex() {
  _has_bits_[0] &= ~0x00000002u;
}
 void reg::clear_sex() {
  sex_ = 0;
  clear_has_sex();
}
 ::google::protobuf::int32 reg::sex() const {
  // @@protoc_insertion_point(field_get:MSG.reg.sex)
  return sex_;
}
 void reg::set_sex(::google::protobuf::int32 value) {
  set_has_sex();
  sex_ = value;
  // @@protoc_insertion_point(field_set:MSG.reg.sex)
}

// required string account = 3;
 bool reg::has_account() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
 void reg::set_has_account() {
  _has_bits_[0] |= 0x00000004u;
}
 void reg::clear_has_account() {
  _has_bits_[0] &= ~0x00000004u;
}
 void reg::clear_account() {
  account_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  clear_has_account();
}
 const ::std::string& reg::account() const {
  // @@protoc_insertion_point(field_get:MSG.reg.account)
  return account_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 void reg::set_account(const ::std::string& value) {
  set_has_account();
  account_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:MSG.reg.account)
}
 void reg::set_account(const char* value) {
  set_has_account();
  account_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:MSG.reg.account)
}
 void reg::set_account(const char* value, size_t size) {
  set_has_account();
  account_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
	  ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:MSG.reg.account)
}
 ::std::string* reg::mutable_account() {
  set_has_account();
  // @@protoc_insertion_point(field_mutable:MSG.reg.account)
  return account_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 ::std::string* reg::release_account() {
  clear_has_account();
  return account_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 void reg::set_allocated_account(::std::string* account) {
  if (account != NULL) {
	set_has_account();
  } else {
	clear_has_account();
  }
  account_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), account);
  // @@protoc_insertion_point(field_set_allocated:MSG.reg.account)
}

#endif  // PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)

}  // namespace MSG

// @@protoc_insertion_point(global_scope)
