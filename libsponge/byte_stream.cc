#include "byte_stream.hh"

#include "iostream"
// Dummy implementation of a flow-controlled in-memory byte stream.

// For Lab 0, please replace with a real implementation that passes the
// automated checks run by `make check_lab0`.

// You will need to add private members to the class declaration in `byte_stream.hh`

using namespace std;

ByteStream::ByteStream(const size_t capacity) : buffer({}), cap(capacity), total_read(0), total_write(0), _end(false) {}

size_t ByteStream::write(const string &data) {
    if (input_ended())
        return 0;
    auto result = data.substr(0, remaining_capacity());
    buffer += result;
    total_write += result.length();
    return result.length();
}

//! \param[in] len bytes will be copied from the output side of the buffer
string ByteStream::peek_output(const size_t len) const { return buffer.substr(0, len); }

//! \param[in] len bytes will be removed from the output side of the buffer
void ByteStream::pop_output(const size_t len) {
    total_read += len;
    buffer.erase(0, len);
}

//! Read (i.e., copy and then pop) the next "len" bytes of the stream
//! \param[in] len bytes will be popped and returned
//! \returns a string
std::string ByteStream::read(const size_t len) {
    // pop
    pop_output(len);
    // return
    return buffer.substr(0, len);
}

void ByteStream::end_input() { _end = true; }

bool ByteStream::input_ended() const { return _end; }

size_t ByteStream::buffer_size() const { return buffer.length(); }

bool ByteStream::buffer_empty() const { return buffer_size() == 0; }

bool ByteStream::eof() const { return buffer_empty() && input_ended(); }

size_t ByteStream::bytes_written() const { return total_write; }

size_t ByteStream::bytes_read() const { return total_read; }

size_t ByteStream::remaining_capacity() const { return cap - buffer.length(); }
