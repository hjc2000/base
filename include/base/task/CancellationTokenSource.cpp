#include "CancellationTokenSource.h"

using namespace std;
using namespace base;

bool CancellationTokenSource::IsCancellationRequested() const
{
    return _token->IsCancellationRequested();
}

std::shared_ptr<CancellationToken> CancellationTokenSource::Token() const
{
    return _token;
}

void CancellationTokenSource::Cancel()
{
    _token->Cancel();
}
