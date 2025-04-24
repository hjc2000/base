#pragma once
#include "base/peripheral/heap/IHeap.h"
#include "base/stream/Span.h"
#include <cstddef>
#include <memory>

namespace base
{
	namespace heap
	{
		///
		/// @brief 获取主堆。
		///
		/// @warning 返回的对象必须是函数内部的 static 变量，并且使用 PREINIT 先
		/// 调用一次，保证在 main 函数之前已经初始化过了。
		///
		/// @warning 禁止在全局中定义 base::heap::IHeap 变量然后返回这个变量，
		/// 因为全局变量的构造顺序是不确定的。其他全局对象很有可能依赖动态内存分配。
		///
		/// @return
		///
		/// 下面是例子：
		/*

			namespace
			{
				uint8_t _buffer[configTOTAL_HEAP_SIZE];

				freertos::Heap4 &Heap4()
				{
					static freertos::Heap4 heap4{_buffer, sizeof(_buffer)};
					return heap4;
				}

			} // namespace

			PREINIT(Heap4)

			/// @brief 获取主堆。
			/// @return
			base::heap::IHeap &bsp::di::heap::Heap()
			{
				return Heap4();
			}

		 */
		///
		/// 这个例子中，在 Heap4() 函数内部定义 static 的 freertos::Heap4 对象，然后通过 PREINIT
		/// 来确保 Heap4() 函数在 main 函数前面至少被调用过一次了。然后实现本函数，直接转发 Heap4()
		/// 函数
		///
		base::heap::IHeap &Heap();

		std::shared_ptr<base::heap::IHeap> CreateHeap(uint8_t *buffer, size_t size);

		/* #region AddHeap */

		/// @brief 添加一个堆到堆列表。一旦添加，堆就会投入使用，被用于动态内存分配。
		/// @param heap
		void AddHeap(std::shared_ptr<base::heap::IHeap> const &heap);

		/// @brief 添加一个堆到堆列表。一旦添加，堆就会投入使用，被用于动态内存分配。
		/// @param buffer
		/// @param size
		void AddHeap(uint8_t *buffer, size_t size);

		/// @brief 添加一个堆到堆列表。一旦添加，堆就会投入使用，被用于动态内存分配。
		/// @param span
		void AddHeap(base::Span const &span);

		/* #endregion */

		void *Malloc(size_t size) noexcept;

		void Free(void *ptr) noexcept;

	} // namespace heap
} // namespace base
