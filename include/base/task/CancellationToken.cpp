#include "CancellationToken.h" // IWYU pragma: keep

std::shared_ptr<base::CancellationToken> base::CancellationToken::_none_cancellation_token{new base::CancellationToken{}};
