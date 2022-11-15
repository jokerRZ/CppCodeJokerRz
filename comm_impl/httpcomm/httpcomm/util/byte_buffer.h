#pragma once

#include <httpcomm/common.h>

HTTPCOMM_NAMESPACE_BEGIN

class ByteBuffer {
public:
  ByteBuffer();

  ~ByteBuffer();

  const uint8_t* GetData() const;

  size_t GetLength() const;

  size_t GetSize() const;

  size_t AddOffset(size_t len);

  void Append(const void* data, size_t len);

  void SwapData(std::vector<uint8_t>& data);

private:
  size_t mOffset;
  std::vector<uint8_t> mData;
};

typedef std::shared_ptr<ByteBuffer> ByteBufferPtr;

HTTPCOMM_NAMESPACE_END