#pragma once

#include <cassert>
#include <cstdint>
#include <cstring>
#include <algorithm>

//
class CLoopBuffer {
 public:
  CLoopBuffer(uint32_t sz) {
    assert(sz > 0);
    _data = new uint8_t[sz];
    _size = _idle = sz;
    _fill = 0;
    _head = _read = _write = 0;
  }
  virtual ~CLoopBuffer() {
    delete[] _data;
  }

  uint32_t readbuffer(uint8_t* ptr, uint32_t sz) {
    if (_read)
      return 0;
    _read = std::min<uint32_t>(_fill, sz);
    if (_head + _read > _size) {
      std::memcpy(ptr, _data + _head, _size - _head);
      std::memcpy(ptr + (_size - _head), _data, _head + _read - _size);
    } else {
      std::memcpy(ptr, _data + _head, _read);
    }
    return _read;
  }
  uint32_t writebuffer(uint8_t* ptr, uint32_t sz) {
    if (_write)
      return 0;
    uint32_t uFileHead = (_head + _fill) % _size;
    _write = std::min<uint32_t>(_idle, sz);
    if (uFileHead + _write > _size) {
      std::memcpy(_data + uFileHead, ptr, _size - uFileHead);
      std::memcpy(_data, ptr + (_size - uFileHead), uFileHead + _write - _size);
    } else {
      std::memcpy(_data + uFileHead, ptr, _write);
    }
    return _write;
  }
  uint32_t size() {
    return _size;
  }
  uint32_t idle() {
    return _idle;
  }
  uint32_t fill() {
    return _fill;
  }
  void clear() {
    _idle = _size;
    _fill = 0;
    _head = _read = _write = 0;
  }

 protected:
  uint32_t readvalid() {
    uint32_t _read_tmp = _read;
    _head = (_head + _read) % _size;
    _fill -= _read;
    _idle += _read;
    _read = 0;
    return _read_tmp;
  }
  uint32_t writevalid() {
    uint32_t _write_tmp = _write;
    _fill += _write;
    _idle -= _write;
    _write = 0;
    return _write_tmp;
  }

 private:
  uint8_t* _data;
  uint32_t _size, _idle, _fill;
  uint32_t _head, _read, _write;
};
