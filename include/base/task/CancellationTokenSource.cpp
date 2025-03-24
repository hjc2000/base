#include "CancellationTokenSource.h"

bool base::CancellationTokenSource::IsCancellationRequested() const
{
	return _token->IsCancellationRequested();
}

std::shared_ptr<base::CancellationToken> base::CancellationTokenSource::Token() const
{
	return _token;
}

void base::CancellationTokenSource::Cancel()
{
	_token->Cancel();
}
