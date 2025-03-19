#pragma once
#include <base/string/ICanToString.h>
#include <base/string/String.h>

namespace base
{
	class Path :
		public base::ICanToString
	{
	private:
		base::String _path;

	public:
		Path() = default;

		Path(base::String const &path);

		///
		/// @brief 转化为字符串。
		///
		/// @return std::string
		///
		virtual std::string ToString() const override;

		///
		/// @brief 检查本路径是否是根路径。
		///
		/// @return true
		/// @return false
		///
		bool IsRootPath() const;

		bool AbsolutePath() const;

		bool IsWindowsDiskPath() const;
	};
} // namespace base
