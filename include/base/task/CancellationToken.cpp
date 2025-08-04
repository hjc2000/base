#include "CancellationToken.h"

std::shared_ptr<base::CancellationToken> base::CancellationToken::_none_cancellation_token{new base::CancellationToken{}};
