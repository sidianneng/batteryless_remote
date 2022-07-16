## 1 flash_read/flash_write
```
  uint8_t test_write_data[256];
  uint8_t test_read_data[256];
  int16_t ret = IR_OK;
  uint16_t j;

  for(j = 0;j < 10; j++)
  {
    Log_Printf("j:%d\n", j);
    Log_Printf("start add: 0x%08x\n", IRDATA_START_ADDR + j * 0x100);
    for(uint16_t i = 0;i < 256; ++i)
      test_write_data[i] = i;
    ret = flash_write(IRDATA_START_ADDR + j * 0x100, test_write_data, 256, 0);
    Log_Printf("flash write ret:%d\n", ret);
    ret = flash_read(IRDATA_START_ADDR + j * 0x100, test_read_data, 256);
    Log_Printf("flash read ret:%d\n", ret);
    for(uint16_t i = 0;i < 256; ++i)
      Log_Printf("%02x ", test_read_data[i]);
    Log_Printf("\n");
    LL_mDelay(500000);
  }
  Log_Printf("test finish\n");
```