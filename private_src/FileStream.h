#pragma once
#include "base/filesystem/IFileStream.h"
#include "base/filesystem/Path.h"

#if HAS_THREAD

namespace base
{
	class FileStream final :
		public base::IFileStream
	{
	private:
		FileStream(base::Path const &path);

		base::Path _path;
		std::shared_ptr<std::fstream> _fs;
		bool _can_read = false;
		bool _can_write = false;
		bool _can_seek = false;

	public:
		~FileStream();

		/* #region 工厂函数 */

		///
		/// @brief 先尝试打开文件。如果不存在会创建。
		///
		/// @param path
		///
		/// @return
		///
		static std::shared_ptr<base::FileStream> OpenOrCreate(base::Path const &path);

		///
		/// @brief 用创建模式打开文件流，无论如何都会创建一个新的空白文件。会覆盖旧的。
		/// @param path 文件路径
		///
		/// @return 创建文件成功则返回 FileStream 对象。创建失败会抛出异常，不会返回空指针。
		///
		static std::shared_ptr<base::FileStream> CreateNewAnyway(base::Path const &path);

		///
		/// @brief 用打开模式打开一个存在的文件。如果文件不存在，此函数不会创建文件。
		/// @param path 文件路径
		///
		/// @return 如果文件存在，且成功打开，则返回 FileStream 对象。失败会抛出异常，不会返回空指针。
		///
		static std::shared_ptr<base::FileStream> OpenExisting(base::Path const &path);

		///
		/// @brief 以只读方式打开文件。
		/// @param path 文件的路径。
		///
		/// @return 成功打开则返回 FileStream 对象。失败会抛出异常，不会返回空指针。
		///
		static std::shared_ptr<base::FileStream> OpenReadOnly(base::Path const &path);

		/* #endregion */

		/* #region 流属性 */

		///
		/// @brief 本流能否读取。
		///
		/// @return
		///
		virtual bool CanRead() const override
		{
			return _can_read;
		}

		///
		/// @brief 本流能否写入。
		///
		/// @return
		///
		virtual bool CanWrite() const override
		{
			return _can_write;
		}

		///
		/// @brief 本流能否定位。
		///
		/// @return
		///
		virtual bool CanSeek() const override
		{
			return _can_seek;
		}

		///
		/// @brief 流的长度
		///
		/// @return
		///
		virtual int64_t Length() const override
		{
			// 记录当前位置
			int64_t current_pos = _fs->tellg();

			// seek 到文件末尾
			_fs->seekg(0, _fs->end);

			// 记录文件末尾的位置（最后一个字节之后一个字节，所以 end_pos 等于文件长度）
			int64_t end_pos = _fs->tellg();

			// seek 回原来的位置
			_fs->seekg(current_pos);

			return end_pos;
		}

		///
		/// @brief 设置流的长度。
		///
		/// @param value
		///
		virtual void SetLength(int64_t value) override;

		///
		/// @brief 流当前的位置。
		///
		/// @return
		///
		virtual int64_t Position() const override;

		///
		/// @brief 设置流当前的位置。
		///
		/// @param value
		///
		virtual void SetPosition(int64_t value) override;
		/* #endregion */

		/* #region 读写冲关 */

		///
		/// @brief 将本流的数据读取到 span 中。
		///
		/// @param span
		///
		/// @return
		///
		virtual int32_t Read(base::Span const &span) override;

		///
		/// @brief 将 span 中的数据写入本流。
		///
		/// @param span
		///
		virtual void Write(base::ReadOnlySpan const &span) override;

		///
		/// @brief 冲洗流。
		///
		/// @note 对于写入的数据，作用是将其从内部缓冲区转移到底层。
		/// @note 对于内部的可以读取但尚未读取的数据，一般不会有什么作用。Flush 没见过对可读数据生效的。
		///
		virtual void Flush() override;

		///
		/// @brief 关闭流。
		///
		/// @note 关闭后对流的操作将会引发异常。
		///
		virtual void Close() override;
		/* #endregion */
	};

} // namespace base

#endif // HAS_THREAD
