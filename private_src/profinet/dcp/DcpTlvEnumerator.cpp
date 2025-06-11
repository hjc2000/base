#include "DcpTlvEnumerator.h"
#include "base/bit/AutoBitConverter.h"

base::profinet::DcpTlvEnumerator::DcpTlvEnumerator(base::ReadOnlySpan const &span)
{
	_span = span;
}

base::ReadOnlySpan &base::profinet::DcpTlvEnumerator::CurrentValue()
{
	return _current_value;
}

void base::profinet::DcpTlvEnumerator::Add()
{
	if (_is_end)
	{
		return;
	}

	if (_remain_span.Size() < 4)
	{
		/**
		 * 每个块至少有 1 字节的 option，1 字节的 suboption，2 字节的长度。
		 * 总共 4 字节。如果 4 字节都不到，就是非法的块。
		 */
		_is_end = true;
		return;
	}

	uint16_t length = base::big_endian_remote_converter.FromBytes<uint16_t>(_remain_span.Slice(base::Range{2, 4}));

	uint16_t padding_size = 0;
	if (length % 2 != 0)
	{
		// TLV 里面的 L 指定的是有效长度。但是每个块都要 2 字节对齐，不对齐需要填充 1 字节。
		padding_size = 1;
	}

	uint16_t block_size = 4 + length + padding_size;
	if (block_size > _remain_span.Size())
	{
		_is_end = true;
		return;
	}

	_current_value = _remain_span.Slice(base::Range{0, block_size});
	_remain_span = _remain_span.Slice(base::Range{block_size, _remain_span.Size()});
}
