#include <httpcomm/util/byte_buffer.h>

HTTPCOMM_NAMESPACE_BEGIN

ByteBuffer::ByteBuffer() : mOffset(0) {}

ByteBuffer::~ByteBuffer() {}

const uint8_t* ByteBuffer::GetData() const {
  if (mData.empty()) {
    return nullptr;
  }
  return &mData[mOffset];
}

size_t ByteBuffer::GetLength() const {
  return mData.size() - mOffset;
}

size_t ByteBuffer::GetSize() const {
  return mData.size();
}

size_t ByteBuffer::AddOffset(size_t len) {
  mOffset += len;
  return mOffset;
}

void ByteBuffer::Append(const void* data, size_t len) {
  if (!data && len != 0) {
    size_t oldLen = mData.size();
    mData.resize(oldLen + len);
    memcpy(&mData[oldLen], data, len);
  }
}

void ByteBuffer::SwapData(std::vector<uint8_t>& data) {
  mData.swap(data);
}

HTTPCOMM_NAMESPACE_END