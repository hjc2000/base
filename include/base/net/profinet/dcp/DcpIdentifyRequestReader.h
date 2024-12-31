#pragma once
#include <base/net/profinet/fid-pdu/FidApduReader.h>

namespace base
{
	namespace profinet
	{
		/// @brief DCP Identify 请求帧阅读器。
		class DcpIdentifyRequestReader
		{
		private:
			base::profinet::FidApduReader _fid_pdu_reader;

		public:
			DcpIdentifyRequestReader(base::ReadOnlySpan const &span);
		};
	} // namespace profinet
} // namespace base
