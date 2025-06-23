#pragma once

namespace base
{
	namespace task
	{
		class ITask
		{
		public:
			virtual bool IsCompleted() const = 0;

			virtual void Wait() = 0;
		};

	} // namespace task
} // namespace base
