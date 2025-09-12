#include "base/Console.h"

#if !HAS_THREAD

extern "C"
{
	#include <errno.h>
	#include <stdlib.h>
	#include <sys/stat.h>
	#include <sys/time.h>
	#include <sys/times.h>
	#include <unistd.h>

	__base_weak void *__dso_handle = (void *)&__dso_handle;

	/* #region 进程 */

	char *getenv(char const *name)
	{
		return nullptr;
	}

	int _getpid(void)
	{
		return 1;
	}

	int _kill(int pid, int sig)
	{
		errno = EINVAL;
		return -1;
	}

	int _wait(int *status)
	{
		errno = ECHILD;
		return -1;
	}

	void _exit(int status)
	{
		_kill(status, -1);
		while (1)
		{
			/* Make sure we hang here */
		}
	}

	__base_weak void _init()
	{
	}

	__base_weak void _fini()
	{
	}

	/* #endregion */

	/* #region 线程 */

	int _fork(void)
	{
		errno = EAGAIN;
		return -1;
	}

	int _execve(char *name, char **argv, char **env)
	{
		errno = ENOMEM;
		return -1;
	}

	/* #endregion */

	/* #region 文件操作 */

	int _read(int file, char *ptr, int len)
	{
		return EIO;
	}

	/// @brief stdio 底层会调用本函数。
	///
	/// @param file 文件描述符
	/// @note 对于标准输出，file = 1，对于错误输出，file = 2。
	///
	/// @param ptr
	/// @param len
	/// @return
	int _write(int file, char *ptr, int len)
	{
		try
		{
			base::console().Write(ptr, len);
			return len;
		}
		catch (...)
		{
			return EIO;
		}
	}

	int _close(int file)
	{
		return -1;
	}

	int _fstat(int file, struct stat *st)
	{
		st->st_mode = S_IFCHR;
		return 0;
	}

	int _isatty(int file)
	{
		return 0;
	}

	int _lseek(int file, int ptr, int dir)
	{
		return 0;
	}

	int _open(char *path, int flags, ...)
	{
		/* Pretend like we always fail */
		return -1;
	}

	int _stat(char *file, struct stat *st)
	{
		st->st_mode = S_IFCHR;
		return 0;
	}

	int _link(char *old, char *new_value)
	{
		errno = EMLINK;
		return -1;
	}

	int _unlink(char *name)
	{
		errno = ENOENT;
		return -1;
	}

	int fputc(int ch, FILE *f)
	{
		return ch;
	}

	int fputs(char const *str, FILE *f)
	{
		// 成功返回0，可以根据实际需求调整
		return 0;
	}

	/* #endregion */

	int _times(struct tms *buf)
	{
		return -1;
	}

	/* #region _sbrk */

	///
	/// @brief 使用自定义堆管理之后，禁止使用本函数。
	///
	/// @param incr
	/// @return
	///
	void *_sbrk(ptrdiff_t incr)
	{
		errno = ENOMEM;
		return (void *)-1;
	}

	///
	/// @brief 使用自定义堆管理之后，禁止使用本函数。
	///
	/// @param r
	/// @param incr
	/// @return void*
	///
	void *_sbrk_r(struct _reent *r, ptrdiff_t incr)
	{
		errno = ENOMEM;
		return (void *)-1;
	}

	/* #endregion */

} // extern "C"

#endif // !HAS_THREAD
