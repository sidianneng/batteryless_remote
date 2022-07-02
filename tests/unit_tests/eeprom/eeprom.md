## 1 eeprom_read
```
  #include "eeprom.h"

  static int16_t ret = 0;
  static uint32_t test_read_data;

  ret = eeprom_read(EEPROM_START_ADDR, &test_read_data, 1);
  Log_Printf("ret1:%d data:%d\n", ret, test_read_data);
  ret = eeprom_read(0, &test_read_data, 1);
  Log_Printf("ret2:%d data:%d\n", ret, test_read_data);
  ret = eeprom_read(EEPROM_START_ADDR-1, &test_read_data, 1);
  Log_Printf("ret3:%d data:%d\n", ret, test_read_data);
  ret = eeprom_read(EEPROM_START_ADDR-4, &test_read_data, 1);
  Log_Printf("ret4:%d data:%d\n", ret, test_read_data);
  ret = eeprom_read(EEPROM_START_ADDR+2, &test_read_data, 1);
  Log_Printf("ret5:%d data:%d\n", ret, test_read_data);
  ret = eeprom_read(EEPROM_START_ADDR+10, &test_read_data, 1);
  Log_Printf("ret6:%d data:%d\n", ret, test_read_data);
  ret = eeprom_read(EEPROM_START_ADDR, 0, 1);
  Log_Printf("ret7:%d data:%d\n", ret, test_read_data);
  ret = eeprom_read(EEPROM_START_ADDR+10, &test_read_data, 0);
  Log_Printf("ret8:%d data:%d\n", ret, test_read_data);
```

## eeprom_write
```
  #include "eeprom.h"

  static int16_t ret = 0;
  static uint32_t test_read_data[5] = { 0 };
  static uint32_t test_write_data[5] = { 0X01, 0X02, 0X03, 0X04, 0X05 };

  ret = eeprom_write(EEPROM_START_ADDR, test_write_data, 5, 0);
  Log_Printf("1 write ret:%d\n", ret);
  ret = eeprom_read(EEPROM_START_ADDR, &test_read_data[0], 5);
  Log_Printf("1 read ret:%d %d %d %d %d %d\n", ret, test_read_data[0],
  test_read_data[1], test_read_data[2], test_read_data[3], test_read_data[4]);
  ret = eeprom_write(EEPROM_START_ADDR-1, test_write_data, 5, 0);
  Log_Printf("2 write ret:%d\n", ret);
  ret = eeprom_write(EEPROM_START_ADDR+10, test_write_data, 5, 0);
  Log_Printf("3 write ret:%d\n", ret);
  ret = eeprom_write(EEPROM_START_ADDR, 0, 5, 0);
  Log_Printf("4 write ret:%d\n", ret);
  ret = eeprom_write(EEPROM_START_ADDR, test_write_data, 0, 0);
  Log_Printf("5 write ret:%d\n", ret);
  ret = eeprom_write(EEPROM_START_ADDR, test_write_data, 3, 0);
  Log_Printf("6 write ret:%d\n", ret);
  memset(test_read_data, 0x00, 5);
  ret = eeprom_read(EEPROM_START_ADDR, &test_read_data[0], 3);
  Log_Printf("7 read ret:%d %d %d %d %d %d\n", ret, test_read_data[0],
  test_read_data[1], test_read_data[2], test_read_data[3], test_read_data[4]);
  ret = eeprom_write(EEPROM_START_ADDR, test_write_data, 5, -1);
  Log_Printf("7 write ret:%d\n", ret);
  ret = eeprom_read(EEPROM_START_ADDR, &test_read_data[0], 5);
  Log_Printf("7 read ret:%d %d %d %d %d %d\n", ret, test_read_data[0],
  test_read_data[1], test_read_data[2], test_read_data[3], test_read_data[4]);
  ret = eeprom_write(EEPROM_START_ADDR, test_write_data, 5, 10);
  Log_Printf("8 write ret:%d\n", ret);
  ret = eeprom_read(EEPROM_START_ADDR, &test_read_data[0], 5);
  Log_Printf("8 read ret:%d %d %d %d %d %d\n", ret, test_read_data[0],
  test_read_data[1], test_read_data[2], test_read_data[3], test_read_data[4]);
```