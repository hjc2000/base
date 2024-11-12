#pragma once
#include <base/stream/Stream.h>
#include <stdexcept>

namespace base
{
    /// @brief 内存流
    class MemoryStream final :
        public base::Stream
    {
    private:
        int32_t _buffer_size;
        uint8_t *_buffer;

        /// @brief 指向当前要读或写的位置。Read 和 Write 会操作的第一个字节就是 _position 指向的字节。
        int32_t _position = 0;

        /// @brief 流的长度。
        /// @note 流的长度可以小于缓冲区长度。此标志用来表示流的长度，也是缓冲区中有效数据的长度。
        /// @note 缓冲区中，第 _length 字节是无效的数据。
        /// 	@li 当 _length = 0 时，_buffer[0] 是无效数据，流中没有数据。
        /// 	@li _length 不为 0 时，[0 , _length - 1] 闭区间上是有效数据。
        int32_t _length = 0;

    public:
        /// @brief
        /// @param max_size 内部缓冲区的最大尺寸。小于等于 0 会抛出异常。
        MemoryStream(int32_t max_size);
        ~MemoryStream();

        /// @brief 获取本流的缓冲区
        /// @return
        uint8_t *Buffer();

        /// @brief 获取内部缓冲区大小。这就是本流能够储存的最大的字节数。
        /// @return
        int32_t BufferSize() const;

        /// @brief 从当前 Position 到 Length，总共有多少个可读字节。
        /// @return
        int32_t AvaliableToRead() const;

        /// @brief 从当前的 Position 开始，缓冲区中剩余的可写入空间。
        /// @return
        int32_t AvaliableToWrite() const;

        bool CanRead() override;
        bool CanWrite() override;
        bool CanSeek() override;

        /// @brief 本流的长度。
        /// @note 写入多少字节，长度就是多少。长度不是指缓冲区的大小。
        /// @return
        int64_t Length() override;

        /// @brief 设置本流的长度。
        /// @note 一般是用来减小长度以丢弃末尾的数据。如果是增大长度，会导致流的末尾出现一些
        /// 垃圾数据。
        ///
        /// @param value 要设置成的长度。
        /// @exception value 大于 max_size 会抛出 std::invalid_argument。
        void SetLength(int64_t value) override;

        /// @brief
        /// @param buffer
        /// @param offset
        /// @param count
        /// @return
        /// @exception buffer 为空指针会抛出 std::invalid_argument 异常。
        int32_t Read(uint8_t *buffer, int32_t offset, int32_t count) override;

        /// @brief
        /// @param buffer
        /// @param offset
        /// @param count
        /// @exception std::invalid_argument
        void Write(uint8_t const *buffer, int32_t offset, int32_t count) override;

        void Flush() override;

        /// @brief 没有任何作用。
        void Close() override;

        /// @brief 清空流，将 长度和位置都恢复为 0.
        void Clear();

        int64_t Position() override;
        void SetPosition(int64_t value) override;
    };
} // namespace base
