# modbus 模块说明

# WritingRecordsRequestWriter

写记录的请求帧的作者。

写记录的功能码是 `0x10` 



例子

```c++
uint8_t buffer[1024]{};
base::Span span{buffer, sizeof(buffer)};
base::modbus::WritingRecordsRequestWriter writer{span};

// 按顺序写入各个信息
writer.WriteStationNumber(1);
writer.WriteFunctionCode();

// 要写入的数据的 modbus 地址
writer.WriteStartAddress(0x4050);

// 要写入的 modbus 数据由 2 个记录组成。
writer.WriteRecordCount(2);

// 要写入的 modbus 数据由 4 个字节组成。
writer.WriteDataByteCount(4);

// 要写入的 modbus 数据是 uint32_t 的 10000, 写入后会按照大端序放置到内存段 span 中。
writer.WriteData<uint32_t>(10000);

// 最后写入 CRC 然后就可以发送了。
writer.WriteCrc();

// 输出 modbus 帧
std::cout << writer.SpanForSendingString() << " ";
```



运行后输出

```tex
01 10 40 50 00 02 04 00 00 27 10 6c dd
```

