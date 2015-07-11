#include <nan.h>

extern "C" {
#include "hwsl2.h"
}

using node::ObjectWrap;

using v8::Function;
using v8::FunctionTemplate;
using v8::Handle;
using v8::Local;
using v8::Number;
using v8::Object;
using v8::Persistent;
using v8::String;
using v8::Value;

static Persistent<FunctionTemplate> constructor;

class HashAppendWorker : public NanAsyncWorker {
  char *hash, *buf;
  size_t len;
  public:
  HashAppendWorker(NanCallback *callback, Local<Object> h, Local<Object> b)
    : NanAsyncWorker(callback) {
      SaveToPersistent("h", h);
      SaveToPersistent("b", b);
      int hashLen = node::Buffer::Length(h);
      assert(hashLen == 64);
      hash = node::Buffer::Data(h);
      len = node::Buffer::Length(b);
      buf = node::Buffer::Data(b);
    }
  void Execute() {
    hwsl2_append(hash, buf, len);
  }
};

class HashPrependWorker : public NanAsyncWorker {
  char *hash, *buf;
  size_t len;
  public:
  HashPrependWorker(NanCallback *callback, Local<Object> h, Local<Object> b)
    : NanAsyncWorker(callback) {
      SaveToPersistent("h", h);
      SaveToPersistent("b", b);
      int hashLen = node::Buffer::Length(h);
      assert(hashLen == 64);
      hash = node::Buffer::Data(h);
      len = node::Buffer::Length(b);
      buf = node::Buffer::Data(b);
    }
  void Execute() {
    hwsl2_prepend(hash, buf, len);
  }
};

NAN_METHOD(HashEmpty) {
  NanScope();
  void *mem = malloc(64);
  hwsl2_unit(mem);
  NanReturnValue(NanBufferUse((char *)mem, 64));
}

NAN_METHOD(HashAppend) {
  NanScope();
  Local<Object> hashObj = args[0]->ToObject();
  Local<Object> bufObj = args[1]->ToObject();
  NanCallback *callback = new NanCallback(args[2].As<Function>());
  NanAsyncQueueWorker(new HashAppendWorker(callback, hashObj, bufObj));
  NanReturnUndefined();
}

NAN_METHOD(HashPrepend) {
  NanScope();
  Local<Object> hashObj = args[0]->ToObject();
  Local<Object> bufObj = args[1]->ToObject();
  NanCallback *callback = new NanCallback(args[2].As<Function>());
  NanAsyncQueueWorker(new HashPrependWorker(callback, hashObj, bufObj));
  NanReturnUndefined();
}

NAN_METHOD(HashConcat) {
  NanScope();
  Local<Object> l = args[0]->ToObject();
  Local<Object> r = args[1]->ToObject();
  int leftLen = node::Buffer::Length(l);
  assert(leftLen == 64);
  char *left = node::Buffer::Data(l);
  int rightLen = node::Buffer::Length(r);
  assert(rightLen == 64);
  char *right = node::Buffer::Data(r);
  char *mem = (char *)malloc(64);
  hwsl2_concat(mem, left, right);
  NanReturnValue(NanBufferUse((char *)mem, 64));
}

NAN_METHOD(HashEquals) {
  NanScope();
  Local<Object> l = args[0]->ToObject();
  Local<Object> r = args[1]->ToObject();
  int leftLen = node::Buffer::Length(l);
  assert(leftLen == 64);
  char *left = node::Buffer::Data(l);
  int rightLen = node::Buffer::Length(r);
  assert(rightLen == 64);
  char *right = node::Buffer::Data(r);
  bool equals = hwsl2_equals(left, right);
  NanReturnValue(NanNew(equals));
}

NAN_METHOD(HashSerialize) {
  NanScope();
  Local<Object> h = args[0]->ToObject();
  int hashLen = node::Buffer::Length(h);
  assert(hashLen == 64);
  char *hash = node::Buffer::Data(h);
  char *buf = (char *)malloc(87);
  hwsl2_serialize(hash, buf);
  buf[86] = 0;
  NanReturnValue(NanNew(buf));
}

void Init(Handle<Object> exports, Handle<Object> module) {
  NODE_SET_METHOD(exports, "empty", HashEmpty);
  NODE_SET_METHOD(exports, "append", HashAppend);
  NODE_SET_METHOD(exports, "prepend", HashPrepend);
  NODE_SET_METHOD(exports, "concat", HashConcat);
  NODE_SET_METHOD(exports, "equals", HashEquals);
  NODE_SET_METHOD(exports, "serialize", HashSerialize);
}

NODE_MODULE(hwsl2, Init)
