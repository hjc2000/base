#include "IdToken.h"

base::IdToken::IdToken(uint64_t id)
	: _id(id)
{
}

uint64_t base::IdToken::ID() const
{
	return _id;
}

bool base::IdToken::Used() const
{
	return _used;
}

void base::IdToken::SetAsUsed()
{
	_used = true;
}
