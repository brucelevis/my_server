// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: login.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "login.pb.h"

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

const ::google::protobuf::Descriptor* login_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  login_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_login_2eproto() {
  protobuf_AddDesc_login_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "login.proto");
  GOOGLE_CHECK(file != NULL);
  login_descriptor_ = file->message_type(0);
  static const int login_offsets_[2] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(login, role_id_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(login, account_),
  };
  login_reflection_ =
    ::google::protobuf::internal::GeneratedMessageReflection::NewGeneratedMessageReflection(
      login_descriptor_,
      login::default_instance_,
      login_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(login, _has_bits_[0]),
      -1,
      -1,
      sizeof(login),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(login, _internal_metadata_),
      -1);
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_login_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
      login_descriptor_, &login::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_login_2eproto() {
  delete login::default_instance_;
  delete login_reflection_;
}

void protobuf_AddDesc_login_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\013login.proto\022\003MSG\")\n\005login\022\017\n\007role_id\030\001"
    " \002(\003\022\017\n\007account\030\002 \002(\t", 61);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "login.proto", &protobuf_RegisterTypes);
  login::default_instance_ = new login();
  login::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_login_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_login_2eproto {
  StaticDescriptorInitializer_login_2eproto() {
    protobuf_AddDesc_login_2eproto();
  }
} static_descriptor_initializer_login_2eproto_;

namespace {

static void MergeFromFail(int line) GOOGLE_ATTRIBUTE_COLD;
static void MergeFromFail(int line) {
  GOOGLE_CHECK(false) << __FILE__ << ":" << line;
}

}  // namespace


// ===================================================================

#ifndef _MSC_VER
const int login::kRoleIdFieldNumber;
const int login::kAccountFieldNumber;
#endif  // !_MSC_VER

login::login()
  : ::google::protobuf::Message() , _internal_metadata_(NULL)  {
  SharedCtor();
  // @@protoc_insertion_point(constructor:MSG.login)
}

void login::InitAsDefaultInstance() {
}

login::login(const login& from)
  : ::google::protobuf::Message(),
    _internal_metadata_(NULL) {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:MSG.login)
}

void login::SharedCtor() {
  ::google::protobuf::internal::GetEmptyString();
  _cached_size_ = 0;
  role_id_ = GOOGLE_LONGLONG(0);
  account_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

login::~login() {
  // @@protoc_insertion_point(destructor:MSG.login)
  SharedDtor();
}

void login::SharedDtor() {
  account_.DestroyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  if (this != default_instance_) {
  }
}

void login::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* login::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return login_descriptor_;
}

const login& login::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_login_2eproto();
  return *default_instance_;
}

login* login::default_instance_ = NULL;

login* login::New(::google::protobuf::Arena* arena) const {
  login* n = new login;
  if (arena != NULL) {
    arena->Own(n);
  }
  return n;
}

void login::Clear() {
  if (_has_bits_[0 / 32] & 3) {
    role_id_ = GOOGLE_LONGLONG(0);
    if (has_account()) {
      account_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    }
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  if (_internal_metadata_.have_unknown_fields()) {
    mutable_unknown_fields()->Clear();
  }
}

bool login::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:MSG.login)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required int64 role_id = 1;
      case 1: {
        if (tag == 8) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int64, ::google::protobuf::internal::WireFormatLite::TYPE_INT64>(
                 input, &role_id_)));
          set_has_role_id();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(18)) goto parse_account;
        break;
      }

      // required string account = 2;
      case 2: {
        if (tag == 18) {
         parse_account:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_account()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->account().data(), this->account().length(),
            ::google::protobuf::internal::WireFormat::PARSE,
            "MSG.login.account");
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
  // @@protoc_insertion_point(parse_success:MSG.login)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:MSG.login)
  return false;
#undef DO_
}

void login::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:MSG.login)
  // required int64 role_id = 1;
  if (has_role_id()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt64(1, this->role_id(), output);
  }

  // required string account = 2;
  if (has_account()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->account().data(), this->account().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "MSG.login.account");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      2, this->account(), output);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:MSG.login)
}

::google::protobuf::uint8* login::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:MSG.login)
  // required int64 role_id = 1;
  if (has_role_id()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt64ToArray(1, this->role_id(), target);
  }

  // required string account = 2;
  if (has_account()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->account().data(), this->account().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "MSG.login.account");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        2, this->account(), target);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:MSG.login)
  return target;
}

int login::RequiredFieldsByteSizeFallback() const {
  int total_size = 0;

  if (has_role_id()) {
    // required int64 role_id = 1;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int64Size(
        this->role_id());
  }

  if (has_account()) {
    // required string account = 2;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::StringSize(
        this->account());
  }

  return total_size;
}
int login::ByteSize() const {
  int total_size = 0;

  if (((_has_bits_[0] & 0x00000003) ^ 0x00000003) == 0) {  // All required fields are present.
    // required int64 role_id = 1;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int64Size(
        this->role_id());

    // required string account = 2;
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

void login::MergeFrom(const ::google::protobuf::Message& from) {
  if (GOOGLE_PREDICT_FALSE(&from == this)) MergeFromFail(__LINE__);
  const login* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const login*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void login::MergeFrom(const login& from) {
  if (GOOGLE_PREDICT_FALSE(&from == this)) MergeFromFail(__LINE__);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_role_id()) {
      set_role_id(from.role_id());
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

void login::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void login::CopyFrom(const login& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool login::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000003) != 0x00000003) return false;

  return true;
}

void login::Swap(login* other) {
  if (other == this) return;
  InternalSwap(other);
}
void login::InternalSwap(login* other) {
  std::swap(role_id_, other->role_id_);
  account_.Swap(&other->account_);
  std::swap(_has_bits_[0], other->_has_bits_[0]);
  _internal_metadata_.Swap(&other->_internal_metadata_);
  std::swap(_cached_size_, other->_cached_size_);
}

::google::protobuf::Metadata login::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = login_descriptor_;
  metadata.reflection = login_reflection_;
  return metadata;
}

#if PROTOBUF_INLINE_NOT_IN_HEADERS
// login

// required int64 role_id = 1;
 bool login::has_role_id() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
 void login::set_has_role_id() {
  _has_bits_[0] |= 0x00000001u;
}
 void login::clear_has_role_id() {
  _has_bits_[0] &= ~0x00000001u;
}
 void login::clear_role_id() {
  role_id_ = GOOGLE_LONGLONG(0);
  clear_has_role_id();
}
 ::google::protobuf::int64 login::role_id() const {
  // @@protoc_insertion_point(field_get:MSG.login.role_id)
  return role_id_;
}
 void login::set_role_id(::google::protobuf::int64 value) {
  set_has_role_id();
  role_id_ = value;
  // @@protoc_insertion_point(field_set:MSG.login.role_id)
}

// required string account = 2;
 bool login::has_account() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
 void login::set_has_account() {
  _has_bits_[0] |= 0x00000002u;
}
 void login::clear_has_account() {
  _has_bits_[0] &= ~0x00000002u;
}
 void login::clear_account() {
  account_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  clear_has_account();
}
 const ::std::string& login::account() const {
  // @@protoc_insertion_point(field_get:MSG.login.account)
  return account_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 void login::set_account(const ::std::string& value) {
  set_has_account();
  account_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:MSG.login.account)
}
 void login::set_account(const char* value) {
  set_has_account();
  account_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:MSG.login.account)
}
 void login::set_account(const char* value, size_t size) {
  set_has_account();
  account_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:MSG.login.account)
}
 ::std::string* login::mutable_account() {
  set_has_account();
  // @@protoc_insertion_point(field_mutable:MSG.login.account)
  return account_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 ::std::string* login::release_account() {
  clear_has_account();
  return account_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
 void login::set_allocated_account(::std::string* account) {
  if (account != NULL) {
    set_has_account();
  } else {
    clear_has_account();
  }
  account_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), account);
  // @@protoc_insertion_point(field_set_allocated:MSG.login.account)
}

#endif  // PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)

}  // namespace MSG

// @@protoc_insertion_point(global_scope)