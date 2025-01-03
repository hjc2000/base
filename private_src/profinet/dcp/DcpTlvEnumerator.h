#pragma once
#include <base/bit/AutoBitConverter.h>
#include <base/container/iterator/IEnumerator.h>
#include <base/stream/ReadOnlySpan.h>

namespace base
{
	namespace profinet
	{
		/// @brief 迭代一段 base::ReadOnlySpan 中的 TLV.
		class DcpTlvEnumerator :
			public base::IEnumerator<base::ReadOnlySpan>
		{
		private:
			base::ReadOnlySpan _span;
			base::ReadOnlySpan _remain_span;
			base::ReadOnlySpan _current_value;
			base::AutoBitConverter _converter{std::endian::big};

		public:
			DcpTlvEnumerator(base::ReadOnlySpan const &span);

			/// @brief 获取当前值的引用
			/// @return
			virtual base::ReadOnlySpan &CurrentValue() override
			{
				return _current_value;
			}

			/// @brief 迭代器前进到下一个值
			/// @return
			virtual bool MoveNext() override
			{
				if (_remain_span.Size() < 4)
				{
					return false;
				}

				uint16_t length = _converter.ToUInt16(_remain_span.Slice(base::Range{2, 4}));
				_current_value = _remain_span.Slice(0, 4 + length);
				if (4 + length > _remain_span.Size())
				{
					// TLV 中的 L 指示的 V 的长度出错了，加上 TL 的 4 个字节，已经超出 _remain_span 的大小了。
					return false;
				}

				_remain_span = _remain_span.Slice(base::Range{4 + length, _remain_span.Size()});
				return true;
			}

			/// @brief 将迭代器重置到容器开始的位置。
			/// @note 开始位置是第一个元素前。也就是说重置后，要调用一次 MoveNext 才能获取到第一个值。
			virtual void Reset() override
			{
				_current_value = base::ReadOnlySpan{};
				_remain_span = _span;
			}
		};
	} // namespace profinet
} // namespace base
