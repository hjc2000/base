#pragma once

namespace base::cortex
{
	enum class MemoryType
	{
		///
		/// @brief 设备。
		///
		/// @note 外设设备被映射到内存中，这种内存区域需要严格按照顺序读写，无缓存，无缓冲。
		///
		Device,

		///
		/// @brief 设备，但是有写缓冲。
		///
		/// @note 与 Device 类似，但是有写缓冲。
		///
		/// @note 适用于写入后不需要立刻读的设备。如果需要写入后立刻读，就不能用这个配置，
		/// 因为写入的数据可能还在缓冲区中，还没实际写入。
		///
		/// @note 这种缓冲区并不是像软件的标准输出的缓冲区那样的要满了或换行或手动冲洗才会
		/// 实际触发写入。这种硬件的缓冲区是只要有数据就会一直写入，和 CPU 是异步的，CPU 可以
		/// 把数据放到这后就离开，缓冲区控制器会立刻启动，一直不断写入，直到没有数据了。如果 CPU
		/// 需要阻塞，等待缓冲区清空，就需要内存屏障指令。
		///
		DeviceWithWritingBuffer,

		///
		/// @brief 普通内存。无缓存。
		///
		Normal,

		///
		/// @brief 普通内存。有缓存，写通。
		///
		/// @note 写通的意思是 CPU 写入数据同时写入到 cache 和主存中。
		///
		NormalWithCache_WriteThrough,

		///
		/// @brief 普通内存。有缓存，写回。
		///
		/// @note 写回的意思是 CPU 写入数据时写入到 cache 中并标记为脏，当触发硬件的
		/// 自动的 cache 写回机制，或者软件控制主动触发写回时，才会把脏数据写入主存。
		///
		NormalWithCache_WriteBack,
	};

} // namespace base::cortex
