#include "StreamWriter.h"

base::StreamWriter::StreamWriter(std::shared_ptr<base::Stream> const &stream)
	: _stream(stream)
{
}

void base::StreamWriter::Write(std::string const &str)
{
	base::ReadOnlySpan span{
		reinterpret_cast<uint8_t const *>(str.data()),
		static_cast<int32_t>(str.size()),
	};

	_stream->Write(span);
}

void base::StreamWriter::Write(base::String const &str)
{
	Write(str.StdString());
}

void base::StreamWriter::Write(char c)
{
	base::ReadOnlySpan span{
		reinterpret_cast<uint8_t const *>(&c),
		1,
	};

	_stream->Write(span);
}

void base::StreamWriter::Write(char const *str)
{
	int32_t end_index = 0;
	while (true)
	{
		if (str[end_index] == '\0')
		{
			break;
		}

		if (end_index == INT32_MAX)
		{
			break;
		}

		end_index++;
	}

	if (end_index <= 0)
	{
		return;
	}

	_stream->Write(reinterpret_cast<uint8_t const *>(str),
				   0,
				   end_index);
}

void base::StreamWriter::WriteLine(std::string const &str)
{
	Write(str);
	WriteLine();
}

void base::StreamWriter::WriteLine(base::String const &str)
{
	WriteLine(str.StdString());
}

void base::StreamWriter::WriteLine(char c)
{
	Write(c);
	WriteLine();
}

void base::StreamWriter::WriteLine(char const *str)
{
	Write(str);
	WriteLine();
}

void base::StreamWriter::WriteLine()
{
	Write('\n');
}

void base::StreamWriter::Write(base::ICanToString const &o)
{
	Write(o.ToString());
}

void base::StreamWriter::WriteLine(base::ICanToString const &o)
{
	WriteLine(o.ToString());
}

void base::StreamWriter::Write(base::ReadOnlySpan const &span)
{
	_stream->Write(span);
}

void base::StreamWriter::WriteLine(base::ReadOnlySpan const &span)
{
	_stream->Write(span);
	WriteLine();
}
