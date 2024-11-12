#pragma once
#include <base/stream/Span.h>

namespace base
{
    /// @brief DCP 头部
    class DcpHeader
    {
    public:
        DcpHeader(base::Span span);

        uint8_t _service_id = 0;
        uint8_t _service_type = 0;
        uint32_t _xid = 0;
        uint16_t _response_delay_factor = 0;
        uint16_t _data_length = 0;

        void Serialize(base::Span &out_span);
    };
} // namespace base
