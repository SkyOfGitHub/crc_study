#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "crc_study.h"

#define POLY_CRC8 0x07 /* CRC-8: x8+x2+x+1 */
#define POLY_CRC7 0x09 /* CRC-7/MMC: x7+x3+1 */
#define POLY_CRC16 0x1021 /* CRC16-XMODEM: x16+x12+x5+1 */

// unsigned char CRC_8(unsigned char *, unsigned int);
// unsigned char CRC_7(unsigned char *, unsigned int);
// unsigned int CRC_16(unsigned char *, unsigned int);
// unsigned int CRC_16_for_SD_CMD(unsigned char *array, unsigned int num);

static const unsigned char array[] = {0xfe, 0x34, 0x56, 0x78, 0x12, 0x34, 0x56, 0x78, 0x34, 0x56, 0x78, 0x12, 0x34, 0x56, 0x78, 0x12, 0x34, 0x56, 0x78, 0x12, 0x34, 0x56, 0x78, 0x34, 0x56, 0x78, 0x12, 0x34, 0x56, 0x78};
// static const unsigned char array[] = {0x40, 0x00, 0x00, 0x00, 0x00,};
static unsigned char watch;
static unsigned int watch16;
static unsigned long int watch32;
static unsigned char array1[512];

int main(void)
{
  unsigned int i;

  // for (i = 0; i < 256; ++i)
  // {
  //   printf("crc7 table test: 0x%02x\n", CRC7((unsigned char *)&i, 1, 0x09, 0x00, 0, 0, 0x00) << 1);
  // }

  watch = CRC4((unsigned char *)array, sizeof(array) / sizeof(unsigned char), 0x03, 0x00, 1, 1, 0x00); /* poly: CRC-4/ITU x4+x+1, init: 0x00, refin: true, refout: true, xorout: 0x00 */
  printf("CRC4 = 0x%02X\n", watch);
  watch = CRC4T((unsigned char *)array, sizeof(array) / sizeof(unsigned char), 0x03, 0x00, 1, 1, 0x00); /* poly: CRC-4/ITU x4+x+1, init: 0x00, refin: true, refout: true, xorout: 0x00 */
  printf("CRC4T = 0x%02X\n", watch);

  watch = CRC5((unsigned char *)array, sizeof(array) / sizeof(unsigned char), 0x09, 0x09, 0, 0, 0x00); /* poly: CRC-5/EPC x5+x3+1, init: 0x09, refin: false, refout: false, xorout: 0x00 */
  printf("CRC5 = 0x%02X\n", watch);
  watch = CRC5((unsigned char *)array, sizeof(array) / sizeof(unsigned char), 0x15, 0x00, 1, 1, 0x00); /* poly: CRC-5/ITU x5+x4+x2+1, init: 0x00, refin: true, refout: true, xorout: 0x00 */
  printf("CRC5 = 0x%02X\n", watch);
  watch = CRC5((unsigned char *)array, sizeof(array) / sizeof(unsigned char), 0x05, 0x1f, 1, 1, 0x1f); /* poly: CRC-5/USB x5+x2+1, init: 0x1f, refin: true, refout: true, xorout: 0x1f */
  printf("CRC5 = 0x%02X\n", watch);
  watch = CRC5T((unsigned char *)array, sizeof(array) / sizeof(unsigned char), 0x09, 0x09, 0, 0, 0x00); /* poly: CRC-5/EPC x5+x3+1, init: 0x09, refin: false, refout: false, xorout: 0x00 */
  printf("CRC5T = 0x%02X\n", watch);
  watch = CRC5T((unsigned char *)array, sizeof(array) / sizeof(unsigned char), 0x15, 0x00, 1, 1, 0x00); /* poly: CRC-5/ITU x5+x4+x2+1, init: 0x00, refin: true, refout: true, xorout: 0x00 */
  printf("CRC5T = 0x%02X\n", watch);
  watch = CRC5T((unsigned char *)array, sizeof(array) / sizeof(unsigned char), 0x05, 0x1f, 1, 1, 0x1f); /* poly: CRC-5/USB x5+x2+1, init: 0x1f, refin: true, refout: true, xorout: 0x1f */
  printf("CRC5T = 0x%02X\n", watch);

  watch = CRC6((unsigned char *)array, sizeof(array) / sizeof(unsigned char), 0x03, 0x00, 1, 1, 0x00); /* poly: CRC-6/ITU x6+x+1, init: 0x00, refin: true, refout: true, xorout: 0x00 */
  printf("CRC6 = 0x%02X\n", watch);
  watch = CRC6T((unsigned char *)array, sizeof(array) / sizeof(unsigned char), 0x03, 0x00, 1, 1, 0x00); /* poly: CRC-6/ITU x6+x+1, init: 0x00, refin: true, refout: true, xorout: 0x00 */
  printf("CRC6T = 0x%02X\n", watch);

  watch = CRC7((unsigned char *)array, sizeof(array) / sizeof(unsigned char), 0x09, 0x00, 0, 0, 0x00); /* poly: CRC-7/MMC x7+x3+1, init: 0x00, refin: false, refout: false, xorout: 0x00 */
  printf("CRC7 = 0x%02X\n", watch);

  watch = CRC7T((unsigned char *)array, sizeof(array) / sizeof(unsigned char), 0x09, 0x00, 0, 0, 0x00); /* poly: CRC-7/MMC x7+x3+1, init: 0x00, refin: false, refout: false, xorout: 0x00 */
  printf("CRC7T = 0x%02X\n", watch);
  // watch = CRC_7((unsigned char *)array, sizeof(array) / sizeof(unsigned char));
  // printf("CRC7 = 0x%02X\n", watch);

  watch = CRC8((unsigned char *)array, sizeof(array) / sizeof(unsigned char), 0x07, 0xff, 1, 1, 0x00); /* poly: CRC-8/ROHC x8+x2+x+1, init: 0xff, refin: true, refout: true, xorout: 0x00 */
  printf("CRC8 = 0x%02X\n", watch);
  watch = CRC8((unsigned char *)array, sizeof(array) / sizeof(unsigned char), 0x07, 0x00, 0, 0, 0x55); /* poly: CRC-8/ITU x8+x2+x+1, init: 0x00, refin: false, refout: false, xorout: 0x55 */
  printf("CRC8 = 0x%02X\n", watch);
  watch = CRC8((unsigned char *)array, sizeof(array) / sizeof(unsigned char), 0x31, 0x00, 1, 1, 0x00); /* poly: CRC-8/MAXIM x8+x5+x4+1, init: 0x00, refin: true, refout: true, xorout: 0x00 */
  printf("CRC8 = 0x%02X\n", watch);
  watch = CRC8T((unsigned char *)array, sizeof(array) / sizeof(unsigned char), 0x07, 0xff, 1, 1, 0x00); /* poly: CRC-8/ROHC x8+x2+x+1, init: 0xff, refin: true, refout: true, xorout: 0x00 */
  printf("CRC8T = 0x%02X\n", watch);
  watch = CRC8T((unsigned char *)array, sizeof(array) / sizeof(unsigned char), 0x07, 0x00, 0, 0, 0x55); /* poly: CRC-8/ITU x8+x2+x+1, init: 0x00, refin: false, refout: false, xorout: 0x55 */
  printf("CRC8T = 0x%02X\n", watch);
  watch = CRC8T((unsigned char *)array, sizeof(array) / sizeof(unsigned char), 0x31, 0x00, 1, 1, 0x00); /* poly: CRC-8/MAXIM x8+x5+x4+1, init: 0x00, refin: true, refout: true, xorout: 0x00 */
  printf("CRC8T = 0x%02X\n", watch);
  // watch = CRC_8((unsigned char *)array, sizeof(array) / sizeof(unsigned char));
  // printf("CRC8 = 0x%02X\n", watch);

  watch16 = CRC16((unsigned char *)array, sizeof(array) / sizeof(unsigned char), 0x8005, 0x0000, 1, 1, 0xffff); /* poly: CRC-16/MAXIM x16+x15+x2+1, init: 0x0000, refin: true, refout: true, xorout: 0xffff */
  printf("CRC16 = 0x%04X\n", watch16);
  watch16 = CRC16((unsigned char *)array, sizeof(array) / sizeof(unsigned char), 0x8005, 0xffff, 1, 1, 0xffff); /* poly: CRC-16/USB x16+x15+x2+1, init: 0xffff, refin: true, refout: true, xorout: 0xffff */
  printf("CRC16 = 0x%04X\n", watch16);
  for (i = 0; i < 512; ++i) array1[i] = 0xff;
  watch16 = CRC16((unsigned char *)array1, sizeof(array1) / sizeof(unsigned char), 0x1021, 0x0000, 0, 0, 0x0000); /* poly: CRC-16/SD CARD x16+x12+x5+1, init: 0x0000, refin: false, refout: false, xorout: 0x0000 */
  printf("CRC16 = 0x%04X\n", watch16);
  watch16 = CRC16T((unsigned char *)array, sizeof(array) / sizeof(unsigned char), 0x8005, 0x0000, 1, 1, 0xffff); /* poly: CRC-16/MAXIM x16+x15+x2+1, init: 0x0000, refin: true, refout: true, xorout: 0xffff */
  printf("CRC16T = 0x%04X\n", watch16);
  watch16 = CRC16T((unsigned char *)array, sizeof(array) / sizeof(unsigned char), 0x8005, 0xffff, 1, 1, 0xffff); /* poly: CRC-16/USB x16+x15+x2+1, init: 0xffff, refin: true, refout: true, xorout: 0xffff */
  printf("CRC16T = 0x%04X\n", watch16);
  watch16 = CRC16T((unsigned char *)array1, sizeof(array1) / sizeof(unsigned char), 0x1021, 0x0000, 0, 0, 0x0000); /* poly: CRC-16/SD CARD x16+x12+x5+1, init: 0x0000, refin: false, refout: false, xorout: 0x0000 */
  printf("CRC16T = 0x%04X\n", watch16);
  // watch16 = CRC_16((unsigned char *)array1, sizeof(array1) / sizeof(unsigned char));
  // printf("CRC16 = 0x%04X\n", watch16);
  // watch16 = CRC_16_for_SD_CMD((unsigned char *)array1, sizeof(array1) / sizeof(unsigned char));
  // printf("CRC_16_for_SD_CMD = 0x%04X\n", watch16);

  watch32 = CRC32((unsigned char *)array, sizeof(array) / sizeof(unsigned char), 0x04c11db7, 0xfffffffful, 1, 1, 0xfffffffful); /* poly: CRC-32 x32+x26+x23+x22+x16+x12+x11+x10+x8+x7+x5+x4+x2+x+1, init: 0xffffffff, refin: true, refout: true, xorout: 0xffffffff */
  printf("CRC32 = 0x%08lX\n", watch32);
  watch32 = CRC32((unsigned char *)array, sizeof(array) / sizeof(unsigned char), 0x04c11db7, 0xfffffffful, 0, 0, 0x00000000); /* poly: CRC-32/MPEG-2 x32+x26+x23+x22+x16+x12+x11+x10+x8+x7+x5+x4+x2+x+1, init: 0xffffffff, refin: false, refout: false, xorout: 0x00000000 */
  printf("CRC32 = 0x%08lX\n", watch32);
  watch32 = CRC32T((unsigned char *)array, sizeof(array) / sizeof(unsigned char), 0x04c11db7, 0xfffffffful, 1, 1, 0xfffffffful); /* poly: CRC-32 x32+x26+x23+x22+x16+x12+x11+x10+x8+x7+x5+x4+x2+x+1, init: 0xffffffff, refin: true, refout: true, xorout: 0xffffffff */
  printf("CRC32T = 0x%08lX\n", watch32);
  watch32 = CRC32T((unsigned char *)array, sizeof(array) / sizeof(unsigned char), 0x04c11db7, 0xfffffffful, 0, 0, 0x00000000); /* poly: CRC-32/MPEG-2 x32+x26+x23+x22+x16+x12+x11+x10+x8+x7+x5+x4+x2+x+1, init: 0xffffffff, refin: false, refout: false, xorout: 0x00000000 */
  printf("CRC32T = 0x%08lX\n", watch32);
  return 0;
}

static unsigned char byte_reverse(unsigned char byte)
{
  static unsigned char bit[] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, };
  static unsigned char tib[] = {0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01, };
  unsigned char result, i;

  result = 0;

  for (i = 0; i < 8; ++i)
  {
    if (0 != (byte & bit[i]))
    {
      result |= tib[i];
    }
  }

  return result;
}

unsigned char CRC4(const unsigned char * const array, const unsigned int num, const unsigned char poly, const unsigned char init, const unsigned char refin, const unsigned char refout, const unsigned char xorout)
{
  unsigned char reg;

  if (num < 1) return 0;

  unsigned int byte;
  unsigned char bit;
  unsigned char tmp;
  unsigned int max_byte;

  if (0 != refin)
  {
    reg  = byte_reverse(array[0]) >> 4;
  }
  else
  {
    reg  = array[0] >> 4;
  }

  reg ^= init;

  byte = 0; /* 下一个左移的数据字节，即第一个数据字节，因为还有4位没有左移 */

  if (0 != refin)
  {
    bit = 0x10; /* 下一个左移的位 */
  }
  else
  {
    bit = 0x08; /* 下一个左移的位 */
  }

  max_byte = num - 1; /* 计算出最后一个数据字节的位置 */

  while (byte <= max_byte)
  {
    tmp = array[byte];

    if (reg & 0x08)
    {
      reg = reg << 1 | (tmp & bit ? 0x01 : 0x00);
      reg ^= poly;
    }
    else
    {
      reg = reg << 1 | (tmp & bit ? 0x01 : 0x00);
    }


    if (0 != refin)
    {
      bit <<= 1;
    }
    else
    {
      bit >>= 1;
    }

    if (0 == bit)
    {
      ++byte;
  
      if (0 != refin)
      {
        bit = 0x01; /* 下一个左移的位 */
      }
      else
      {
        bit = 0x80; /* 下一个左移的位 */
      }
    }
  }

  /* 以下是填充位左移 */

  bit = 4; /* 剩下的填充位个数 */
  
  for ( ; ; )
  {
    if (reg & 0x08)
    {
      reg = reg << 1;
      reg ^= poly;
    }
    else
    {
      reg = reg << 1;
    }

    --bit;

    if (0 == bit)
    {
      break;
    }
  }

  if (0 != refout)
  {
    reg = byte_reverse(reg) >> 4;
  }

  reg ^= xorout;

  return reg & 0x0f;
}

unsigned char CRC5(const unsigned char * const array, const unsigned int num, const unsigned char poly, const unsigned char init, const unsigned char refin, const unsigned char refout, const unsigned char xorout)
{
  unsigned char reg;

  if (num < 1) return 0;

  unsigned int byte;
  unsigned char bit;
  unsigned char tmp;
  unsigned int max_byte;

  if (0 != refin)
  {
    reg  = byte_reverse(array[0]) >> 3;
  }
  else
  {
    reg  = array[0] >> 3;
  }

  reg ^= init;

  byte = 0; /* 下一个左移的数据字节，即第一个数据字节，因为还有3位没有左移 */

  if (0 != refin)
  {
    bit = 0x20; /* 下一个左移的位 */
  }
  else
  {
    bit = 0x04; /* 下一个左移的位 */
  }

  max_byte = num - 1; /* 计算出最后一个数据字节的位置 */

  while (byte <= max_byte)
  {
    tmp = array[byte];

    if (reg & 0x10)
    {
      reg = reg << 1 | (tmp & bit ? 0x01 : 0x00);
      reg ^= poly;
    }
    else
    {
      reg = reg << 1 | (tmp & bit ? 0x01 : 0x00);
    }


    if (0 != refin)
    {
      bit <<= 1;
    }
    else
    {
      bit >>= 1;
    }

    if (0 == bit)
    {
      ++byte;
  
      if (0 != refin)
      {
        bit = 0x01; /* 下一个左移的位 */
      }
      else
      {
        bit = 0x80; /* 下一个左移的位 */
      }
    }
  }

  /* 以下是填充位左移 */

  bit = 5; /* 剩下的填充位个数 */
  
  for ( ; ; )
  {
    if (reg & 0x10)
    {
      reg = reg << 1;
      reg ^= poly;
    }
    else
    {
      reg = reg << 1;
    }

    --bit;

    if (0 == bit)
    {
      break;
    }
  }

  if (0 != refout)
  {
    reg = byte_reverse(reg) >> 3;
  }

  reg ^= xorout;

  return reg & 0x1f;
}

unsigned char CRC6(const unsigned char * const array, const unsigned int num, const unsigned char poly, const unsigned char init, const unsigned char refin, const unsigned char refout, const unsigned char xorout)
{
  unsigned char reg;

  if (num < 1) return 0;
  
  unsigned int byte;
  unsigned char bit;
  unsigned char tmp;
  unsigned int max_byte;

  if (0 != refin)
  {
    reg  = byte_reverse(array[0]) >> 2;
  }
  else
  {
    reg  = array[0] >> 2;
  }

  reg ^= init;

  byte = 0; /* 下一个左移的数据字节，即第一个数据字节，因为还有2位没有左移 */

  if (0 != refin)
  {
    bit = 0x40; /* 下一个左移的位 */
  }
  else
  {
    bit = 0x02; /* 下一个左移的位 */
  }

  max_byte = num - 1; /* 计算出最后一个数据字节的位置 */

  while (byte <= max_byte)
  {
    tmp = array[byte];

    if (reg & 0x20)
    {
      reg = reg << 1 | (tmp & bit ? 0x01 : 0x00);
      reg ^= poly;
    }
    else
    {
      reg = reg << 1 | (tmp & bit ? 0x01 : 0x00);
    }


    if (0 != refin)
    {
      bit <<= 1;
    }
    else
    {
      bit >>= 1;
    }

    if (0 == bit)
    {
      ++byte;
  
      if (0 != refin)
      {
        bit = 0x01; /* 下一个左移的位 */
      }
      else
      {
        bit = 0x80; /* 下一个左移的位 */
      }
    }
  }

  /* 以下是填充位左移 */

  bit = 6; /* 剩下的填充位个数 */
  
  for ( ; ; )
  {
    if (reg & 0x20)
    {
      reg = reg << 1;
      reg ^= poly;
    }
    else
    {
      reg = reg << 1;
    }

    --bit;

    if (0 == bit)
    {
      break;
    }
  }

  if (0 != refout)
  {
    reg = byte_reverse(reg) >> 2;
  }

  reg ^= xorout;

  return reg & 0x3f;
}

unsigned char CRC7(const unsigned char * const array, const unsigned int num, const unsigned char poly, const unsigned char init, const unsigned char refin, const unsigned char refout, const unsigned char xorout)
{
  unsigned char reg;

  if (num < 1) return 0;

  unsigned int byte;
  unsigned char bit;
  unsigned char tmp;
  unsigned int max_byte;

  if (0 != refin)
  {
    reg  = byte_reverse(array[0]) >> 1;
  }
  else
  {
    reg  = array[0] >> 1;
  }

  reg ^= init;

  byte = 0; /* 下一个左移的数据字节，即第一个数据字节，因为还有一位没有左移 */

  if (0 != refin)
  {
    bit = 0x80; /* 下一个左移的位 */
  }
  else
  {
    bit = 0x01; /* 下一个左移的位 */
  }

  max_byte = num - 1; /* 计算出最后一个数据字节的位置 */

  while (byte <= max_byte)
  {
    tmp = array[byte];

    if (reg & 0x40)
    {
      reg = reg << 1 | (tmp & bit ? 0x01 : 0x00);
      reg ^= poly;
    }
    else
    {
      reg = reg << 1 | (tmp & bit ? 0x01 : 0x00);
    }


    if (0 != refin)
    {
      bit <<= 1;
    }
    else
    {
      bit >>= 1;
    }

    if (0 == bit)
    {
      ++byte;
  
      if (0 != refin)
      {
        bit = 0x01; /* 下一个左移的位 */
      }
      else
      {
        bit = 0x80; /* 下一个左移的位 */
      }
    }
  }

  /* 以下是填充位左移 */

  bit = 7; /* 剩下的填充位个数 */
  
  for ( ; ; )
  {
    if (reg & 0x40)
    {
      reg = reg << 1;
      reg ^= poly;
    }
    else
    {
      reg = reg << 1;
    }

    --bit;

    if (0 == bit)
    {
      break;
    }
  }

  if (0 != refout)
  {
    reg = byte_reverse(reg) >> 1;
  }

  reg ^= xorout;

  return reg & 0x7f;
}

unsigned char CRC8(const unsigned char * const array, const unsigned int num, const unsigned char poly, const unsigned char init, const unsigned char refin, const unsigned char refout, const unsigned char xorout)
{
  unsigned char reg;

  if (num < 1) return 0;
  
  unsigned int byte;
  unsigned char bit;
  unsigned char tmp;
  unsigned int max_byte;

  if (0 != refin)
  {
    reg  = byte_reverse(array[0]);
  }
  else
  {
    reg  = array[0];
  }

  reg ^= init;

  byte = 1; /* 下一个左移的数据字节（如果存在） */

  if (0 != refin)
  {
    bit = 0x01; /* 下一个左移的位 */
  }
  else
  {
    bit = 0x80; /* 下一个左移的位 */
  }

  max_byte = num - 1; /* 计算出最后一个数据字节的位置 */

  while (byte <= max_byte)
  {
    tmp = array[byte];

    if (reg & 0x80)
    {
      reg = reg << 1 | (tmp & bit ? 0x01 : 0x00);
      reg ^= poly;
    }
    else
    {
      reg = reg << 1 | (tmp & bit ? 0x01 : 0x00);
    }

    if (0 != refin)
    {
      bit <<= 1;
    }
    else
    {
      bit >>= 1;
    }

    if (0 == bit)
    {
      ++byte;
  
      if (0 != refin)
      {
        bit = 0x01; /* 下一个左移的位 */
      }
      else
      {
        bit = 0x80; /* 下一个左移的位 */
      }
    }
  }

  /* 以下是填充位左移 */

  bit = 8; /* 剩下的填充位个数 */
  
  for ( ; ; )
  {
    if (reg & 0x80)
    {
      reg <<= 1;
      reg ^= poly;
    }
    else
    {
      reg <<= 1;
    }

    --bit;

    if (0 == bit)
    {
      break;
    }
  }

  if (0 != refout)
  {
    reg = byte_reverse(reg);
  }

  reg ^= xorout;

  return reg;
}

// unsigned char CRC_8(unsigned char *array, unsigned int num)
// {
//   unsigned int bcnt, Bcnt;
//   unsigned char rslt;
//   unsigned char flag;
//   unsigned char *array_ptr;

//   if (!num) return 0;

//   bcnt = num * 8;
//   Bcnt = 0;
//   array_ptr = (unsigned char *)malloc(num);
//   memcpy(array_ptr, array, num);
//   rslt = array_ptr[Bcnt];
//   flag = 0;

//   while (bcnt) {
//     if (0x80 & rslt) flag = 1;
//     rslt <<= 1;
//     if (Bcnt + 1 < num) {
//       if (0 != (0x80 & array_ptr[Bcnt + 1])) rslt |= 0x01;
//       array_ptr[Bcnt + 1] <<= 1;
//     }
//     if (flag) {
//       rslt ^= POLY_CRC8;
//       flag = 0;
//     }
//     if (0 == (--bcnt & 0x7)) ++Bcnt;
//   }

//   free(array_ptr);
//   return rslt;
// }

// unsigned char CRC_7(unsigned char *array, unsigned int num)
// {
//   unsigned int bcnt, Bcnt;
//   unsigned char rslt;
//   unsigned char flag;
//   unsigned char *array_ptr;

//   if (!num) return 0;

//   bcnt = num * 8;
//   Bcnt = 0;
//   array_ptr = (unsigned char *)malloc(num);
//   memcpy(array_ptr, array, num);
//   rslt = array_ptr[Bcnt];
//   flag = 0;

//   while (bcnt) {
//     if (0x80 & rslt) flag = 1;
//     rslt <<= 1;
//     if (Bcnt + 1 < num) {
//       if (0 != (0x80 & array_ptr[Bcnt + 1])) rslt |= 0x01;
//       array_ptr[Bcnt + 1] <<= 1;
//     }
//     if (flag) {
//       rslt ^= (POLY_CRC7 << 1);
//       flag = 0;
//     }
//     if (0 == (--bcnt & 0x7)) ++Bcnt;
//   }

//   free(array_ptr);

//   rslt = (rslt >> 1) & 0x7F;//结果是前面的7bit

//   return rslt;
// }

// unsigned char CRC_7(unsigned char *array, unsigned int num)
// {
//   unsigned char result, flag, next_bit, bit_of_byte;
//   unsigned int next_byte_no, bit_cnt;

//   if (0 == num) return POLY_CRC7 & 0x7F;

//   bit_cnt = num * 8;

//   result = array[0];
//   next_byte_no = 1;

//   bit_of_byte = 0;

//   while (bit_cnt > 0) {
//     flag = (result & 0x80);

//     result <<= 1;
//     --bit_cnt;

//     next_bit = 0;
//     if (next_byte_no < num) /* get next bit */
//     {
//       next_bit = !!(array[next_byte_no] & 0x01 << (7 - bit_of_byte));
//       if (++bit_of_byte >= 8) 
//       {
//         bit_of_byte = 0;
//         ++next_byte_no;
//       }
//     }

//     result |= next_bit;

//     if (0 != flag)
//     {
//       result ^= (POLY_CRC7 << 1);
//     }
//   }

//   return (result >> 1) & 0x7F;
// }

unsigned int CRC16(const unsigned char * const array, const unsigned int num, const unsigned int poly, const unsigned int init, const unsigned char refin, const unsigned char refout, const unsigned int xorout)
{
  unsigned int reg;

  if (num < 1) return 0;

  unsigned int byte;
  unsigned char bit;
  unsigned char tmp;
  unsigned int max_byte;

  if (0 != refin)
  {
    if (num > 1)
    {
      reg  = byte_reverse(array[0]) << 8 | byte_reverse(array[1]);

      byte = 2; /* 下一个左移的数据字节（如果存在） */
    }
    else
    {
      reg  = byte_reverse(array[0]) << 8;

      byte = 1; /* 下一个左移的数据字节（如果存在） */
    }
  }
  else
  {
    if (num > 1)
    {
      reg  = array[0] << 8 | array[1];

      byte = 2; /* 下一个左移的数据字节（如果存在） */
    }
    else
    {
      reg  = array[0] << 8;

      byte = 1; /* 下一个左移的数据字节（如果存在） */
    }
  }

  max_byte = num - 1; /* 计算出最后一个数据字节的位置 */

  reg ^= init;

  if (0 != refin)
  {
    bit = 0x01; /* 下一个左移的位 */
  }
  else
  {
    bit = 0x80; /* 下一个左移的位 */
  }

  while (byte <= max_byte)
  {
    tmp = array[byte];

    if (reg & 0x8000)
    {
      reg = reg << 1 | (tmp & bit ? 0x0001 : 0x0000);
      reg ^= poly;
    }
    else
    {
      reg = reg << 1 | (tmp & bit ? 0x0001 : 0x0000);
    }

    if (0 != refin)
    {
      bit <<= 1;
    }
    else
    {
      bit >>= 1;
    }

    if (0 == bit)
    {
      ++byte;
  
      if (0 != refin)
      {
        bit = 0x01; /* 下一个左移的位 */
      }
      else
      {
        bit = 0x80; /* 下一个左移的位 */
      }
    }
  }

  /* 以下是填充位左移 */

  if (num >= 2) /* 计算剩下的填充字节数（值为零） */
  {
    byte = 2;
  }
  else
  {
    byte = num;
  }

  bit = byte << 3; /* 剩下的填充位个数 */
  
  for ( ; ; )
  {
    if (reg & 0x8000)
    {
      reg = reg << 1;
      reg ^= poly;
    }
    else
    {
      reg = reg << 1;
    }

    --bit;

    if (0 == bit)
    {
      break;
    }
  }

  if (0 != refout)
  {
    reg = byte_reverse(reg & 0x00ff) << 8 | byte_reverse(reg >> 8 & 0x00ff);
  }

  reg ^= xorout;

  return reg & 0xffffu;
}

// unsigned int CRC_16(unsigned char *array, unsigned int num)
// {
//   unsigned int bcnt, Bcnt;
//   unsigned int rslt;
//   unsigned char flag;
//   unsigned char *array_ptr;

//   if (!num) return 0;

//   array_ptr = (unsigned char *)malloc(num);
//   memcpy(array_ptr, array, num);
//   bcnt = num * 8;
//   if (num < 2) {
//     rslt = (unsigned int)(array_ptr[0] << 8);
//     Bcnt = 0;
//   }
//   else {
//     rslt = (unsigned int)((array_ptr[0] << 8) | (array_ptr[1]));
//     Bcnt = 1;
//   }
//   flag = 0;

//   while (bcnt) {
//     if (0x8000 & rslt) flag = 1;
//     rslt <<= 1;
//     if (Bcnt + 1 < num) {
//       if(0 != (0x80 & array_ptr[Bcnt + 1])) rslt |= 0x0001;
//       array_ptr[Bcnt + 1] <<= 1;
//     }
//     if (flag) {
//       rslt ^= POLY_CRC16;
//       flag = 0;
//     }
//     if (0 == (--bcnt & 0x7)) ++Bcnt;
//   }

//   free(array_ptr);

//   return (rslt & 0xFFFF);
// }

// unsigned int CRC_16(unsigned char *array, unsigned int num)
// {
//   unsigned int result, flag, next_bit;
//   unsigned int next_byte_no, bit_cnt;
//   unsigned char bit_of_byte;

//   bit_cnt = num * 8;

//   if (0 == num) return POLY_CRC16;

//   if (num < 2) {
//     result = (unsigned int)(array[0] << 8);
//     next_byte_no = 1;
//   }
//   else {
//     result = (unsigned int)((array[0] << 8) | (array[1]));
//     next_byte_no = 2;
//   }

//   bit_of_byte = 0;

//   while (bit_cnt > 0) {
//     flag = (result & 0x8000);

//     result <<= 1;
//     --bit_cnt;

//     next_bit = 0;
//     if (next_byte_no < num) /* get next bit */
//     {
//       next_bit = !!(array[next_byte_no] & 0x01 << (7 - bit_of_byte));
//       if (++bit_of_byte >= 8) 
//       {
//         bit_of_byte = 0;
//         ++next_byte_no;
//       }
//     }

//     result |= next_bit;

//     if (0 != flag)
//     {
//       result ^= POLY_CRC16;
//     }
//   }

//   return result & 0xFFFF;
// }

// unsigned int CRC_16_for_SD_CMD(unsigned char *array, unsigned int num)
// {
//   unsigned int bcnt, Bcnt;
//   unsigned int rslt;
//   unsigned char flag;
//   unsigned char *array_ptr;

//   if (!num) return 0;

//   array_ptr = (unsigned char *)malloc(num);
//   memcpy(array_ptr, array, num);
//   bcnt = num * 8;
//   if (num < 2) {
//     rslt = (unsigned int)(array_ptr[0] << 8);
//     Bcnt = 0;
//   }
//   else {
//     rslt = (unsigned int)((array_ptr[0] << 8) | (array_ptr[1]));
//     Bcnt = 1;
//   }
//   flag = 0;

//   while (bcnt) {
//     // if (0x8000 & rslt) flag = 1;
//     // rslt <<= 1;

//     if (!!(0x8000 & rslt) != !!(0x80 & array_ptr[Bcnt + 1])) {
//       flag = 1;
//       rslt <<= 1;
//       rslt |= 0x0001;
//     }
//     else {
//       rslt <<= 1;
//     }
//     if (Bcnt + 1 < num) {
//       array_ptr[Bcnt + 1] <<= 1;
//     }
//     // if (Bcnt + 1 < num) {
//     //   if(0 != (0x80 & array_ptr[Bcnt + 1])) rslt |= 0x0001;
//     //   array_ptr[Bcnt + 1] <<= 1;
//     // }
//     if (flag) {
//       rslt ^= (POLY_CRC16 & ~0x0001);
//       flag = 0;
//     }
//     if (0 == (--bcnt & 0x7)) ++Bcnt;
//   }

//   free(array_ptr);

//   return (rslt & 0xFFFF);
// }

unsigned long int CRC32(const unsigned char * const array, const unsigned int num, const unsigned long int poly, const unsigned long int init, const unsigned char refin, const unsigned char refout, const unsigned long int xorout)
{
  unsigned long int reg;

  if (num < 1) return 0;

  unsigned int byte;
  unsigned char bit;
  unsigned char tmp;
  unsigned int max_byte;

  if (0 != refin)
  {
    if (num > 3)
    {
      reg  = byte_reverse(array[0]) << 24 | byte_reverse(array[1]) << 16 | byte_reverse(array[2]) << 8 | byte_reverse(array[3]);

      byte = 4; /* 下一个左移的数据字节（如果存在） */
    }
    else if (num > 2)
    {
      reg  = byte_reverse(array[0]) << 24 | byte_reverse(array[1]) << 16 | byte_reverse(array[2]) << 8;

      byte = 3; /* 下一个左移的数据字节（如果存在） */
    }
    else if (num > 1)
    {
      reg  = byte_reverse(array[0]) << 24 | byte_reverse(array[1]) << 16;

      byte = 2; /* 下一个左移的数据字节（如果存在） */
    }
    else
    {
      reg  = byte_reverse(array[0]) << 24;

      byte = 1; /* 下一个左移的数据字节（如果存在） */
    }
  }
  else
  {
    if (num > 3)
    {
      reg  = array[0] << 24 | array[1] << 16 | array[2] << 8 | array[3];

      byte = 4; /* 下一个左移的数据字节（如果存在） */
    }
    else if (num > 2)
    {
      reg  = array[0] << 24 | array[1] << 16 | array[2] << 8;

      byte = 3; /* 下一个左移的数据字节（如果存在） */
    }
    else if (num > 1)
    {
      reg  = array[0] << 24 | array[1] << 16;

      byte = 2; /* 下一个左移的数据字节（如果存在） */
    }
    else
    {
      reg  = array[0] << 24;

      byte = 1; /* 下一个左移的数据字节（如果存在） */
    }
  }

  max_byte = num - 1; /* 计算出最后一个数据字节的位置 */

  reg ^= init;

  if (0 != refin)
  {
    bit = 0x01; /* 下一个左移的位 */
  }
  else
  {
    bit = 0x80; /* 下一个左移的位 */
  }

  while (byte <= max_byte)
  {
    tmp = array[byte];

    if (reg & 0x80000000)
    {
      reg = reg << 1 | (tmp & bit ? 0x00000001 : 0x00000000);
      reg ^= poly;
    }
    else
    {
      reg = reg << 1 | (tmp & bit ? 0x00000001 : 0x00000000);
    }

    if (0 != refin)
    {
      bit <<= 1;
    }
    else
    {
      bit >>= 1;
    }

    if (0 == bit)
    {
      ++byte;
  
      if (0 != refin)
      {
        bit = 0x01; /* 下一个左移的位 */
      }
      else
      {
        bit = 0x80; /* 下一个左移的位 */
      }
    }
  }

  /* 以下是填充位左移 */

  if (num >= 4) /* 计算剩下的填充字节数（值为零） */
  {
    byte = 4;
  }
  else
  {
    byte = num;
  }

  bit = byte << 3; /* 剩下的填充位个数 */
  
  for ( ; ; )
  {
    if (reg & 0x80000000)
    {
      reg = reg << 1;
      reg ^= poly;
    }
    else
    {
      reg = reg << 1;
    }

    --bit;

    if (0 == bit)
    {
      break;
    }
  }

  if (0 != refout)
  {
    reg = byte_reverse(reg & 0x00ff) << 24 | byte_reverse(reg >> 8 & 0x00ff) << 16 | byte_reverse(reg >> 16 & 0x00ff) << 8 | byte_reverse(reg >> 24);
  }

  reg ^= xorout;

  return reg & 0xfffffffful;
}

static unsigned char crc4_table[CRC_TABLE_SIZE];
static struct CRC_SETTING crc4_setting;

unsigned char CRC4T(const unsigned char * const array, const unsigned int num, const unsigned char poly, const unsigned char init, const unsigned char refin, const unsigned char refout, const unsigned char xorout)
{
  unsigned char reg;

  if (num < 1) return 0;

  if (poly != crc4_setting.poly || 
      refin != crc4_setting.refin) /* 判断是否需要更新查询表 */
  {
    crc4_setting.poly = poly;
    crc4_setting.refin = refin;
    
    unsigned int i;

    for (i = 0; i < CRC_TABLE_SIZE; ++i)
    {
      unsigned char tmp;

      tmp = i;
      
      if (0 != refin)
      {
#if 1
        tmp = CRC4((unsigned char *)&tmp, 1, poly, 0x00, 1, 1, 0x00);
#else
        tmp = byte_reverse(tmp);

        tmp = CRC4((unsigned char *)&tmp, 1, poly, 0x00, 0, 0, 0x00) << 4;

        tmp = byte_reverse(tmp);
#endif
      }
      else
      {
        tmp = CRC4((unsigned char *)&tmp, 1, poly, 0x00, 0, 0, 0x00) << 4;
      }

      crc4_table[i] = tmp;
    }
  }

  if (0 != refin)
  {
    reg = byte_reverse(init << 4);
  }
  else
  {
    reg = init << 4;
  }

  unsigned int i;

  for (i = 0; i < num; ++i)
  {
    reg = crc4_table[reg ^ array[i]];
  }

  if (0 != refin)
  {
    if (0 == refout)
    {
      reg = byte_reverse(reg) >> 4;
    }
  }
  else
  {
    if (0 != refout)
    {
      reg = byte_reverse(reg);
    }
    else
    {
      reg = reg >> 4;
    }
  }

  reg ^= xorout;

  return reg & 0x0f;
}

static unsigned char crc5_table[CRC_TABLE_SIZE];
static struct CRC_SETTING crc5_setting;

unsigned char CRC5T(const unsigned char * const array, const unsigned int num, const unsigned char poly, const unsigned char init, const unsigned char refin, const unsigned char refout, const unsigned char xorout)
{
  unsigned char reg;

  if (num < 1) return 0;

  if (poly != crc5_setting.poly || 
      refin != crc5_setting.refin) /* 判断是否需要更新查询表 */
  {
    crc5_setting.poly = poly;
    crc5_setting.refin = refin;
    
    unsigned int i;

    for (i = 0; i < CRC_TABLE_SIZE; ++i)
    {
      unsigned char tmp;

      tmp = i;
      
      if (0 != refin)
      {
#if 1
        tmp = CRC5((unsigned char *)&tmp, 1, poly, 0x00, 1, 1, 0x00);
#else
        tmp = byte_reverse(tmp);

        tmp = CRC5((unsigned char *)&tmp, 1, poly, 0x00, 0, 0, 0x00) << 3;

        tmp = byte_reverse(tmp);
#endif
      }
      else
      {
        tmp = CRC5((unsigned char *)&tmp, 1, poly, 0x00, 0, 0, 0x00) << 3;
      }

      crc5_table[i] = tmp;
    }
  }

  if (0 != refin)
  {
    reg = byte_reverse(init << 3);
  }
  else
  {
    reg = init << 3;
  }

  unsigned int i;

  for (i = 0; i < num; ++i)
  {
    reg = crc5_table[reg ^ array[i]];
  }

  if (0 != refin)
  {
    if (0 == refout)
    {
      reg = byte_reverse(reg) >> 3;
    }
  }
  else
  {
    if (0 != refout)
    {
      reg = byte_reverse(reg);
    }
    else
    {
      reg = reg >> 3;
    }
  }

  reg ^= xorout;

  return reg & 0x1f;
}

static unsigned char crc6_table[CRC_TABLE_SIZE];
static struct CRC_SETTING crc6_setting;

unsigned char CRC6T(const unsigned char * const array, const unsigned int num, const unsigned char poly, const unsigned char init, const unsigned char refin, const unsigned char refout, const unsigned char xorout)
{
  unsigned char reg;

  if (num < 1) return 0;

  if (poly != crc6_setting.poly || 
      refin != crc6_setting.refin) /* 判断是否需要更新查询表 */
  {
    crc6_setting.poly = poly;
    crc6_setting.refin = refin;
    
    unsigned int i;

    for (i = 0; i < CRC_TABLE_SIZE; ++i)
    {
      unsigned char tmp;

      tmp = i;
      
      if (0 != refin)
      {
#if 1
        tmp = CRC6((unsigned char *)&tmp, 1, poly, 0x00, 1, 1, 0x00);
#else
        tmp = byte_reverse(tmp);

        tmp = CRC6((unsigned char *)&tmp, 1, poly, 0x00, 0, 0, 0x00) << 2;

        tmp = byte_reverse(tmp);
#endif
      }
      else
      {
        tmp = CRC6((unsigned char *)&tmp, 1, poly, 0x00, 0, 0, 0x00) << 2;
      }

      crc6_table[i] = tmp;
    }
  }

  if (0 != refin)
  {
    reg = byte_reverse(init << 2);
  }
  else
  {
    reg = init << 2;
  }

  unsigned int i;

  for (i = 0; i < num; ++i)
  {
    reg = crc6_table[reg ^ array[i]];
  }

  if (0 != refin)
  {
    if (0 == refout)
    {
      reg = byte_reverse(reg) >> 2;
    }
  }
  else
  {
    if (0 != refout)
    {
      reg = byte_reverse(reg);
    }
    else
    {
      reg = reg >> 2;
    }
  }

  reg ^= xorout;

  return reg & 0x3f;
}

static unsigned char crc7_table[CRC_TABLE_SIZE];
static struct CRC_SETTING crc7_setting;

unsigned char CRC7T(const unsigned char * const array, const unsigned int num, const unsigned char poly, const unsigned char init, const unsigned char refin, const unsigned char refout, const unsigned char xorout)
{
  unsigned char reg;

  if (num < 1) return 0;

  if (poly != crc7_setting.poly || 
      refin != crc7_setting.refin) /* 判断是否需要更新查询表 */
  {
    crc7_setting.poly = poly;
    crc7_setting.refin = refin;
    
    unsigned int i;

    for (i = 0; i < CRC_TABLE_SIZE; ++i)
    {
      unsigned char tmp;

      tmp = i;
      
      if (0 != refin)
      {
#if 1
        tmp = CRC7((unsigned char *)&tmp, 1, poly, 0x00, 1, 1, 0x00);
#else
        tmp = byte_reverse(tmp);

        tmp = CRC7((unsigned char *)&tmp, 1, poly, 0x00, 0, 0, 0x00) << 1;

        tmp = byte_reverse(tmp);
#endif
      }
      else
      {
        tmp = CRC7((unsigned char *)&tmp, 1, poly, 0x00, 0, 0, 0x00) << 1;
      }

      crc7_table[i] = tmp;
    }
  }

  if (0 != refin)
  {
    reg = byte_reverse(init << 1);
  }
  else
  {
    reg = init << 1;
  }

  unsigned int i;

  for (i = 0; i < num; ++i)
  {
    reg = crc7_table[reg ^ array[i]];
  }

  if (0 != refin)
  {
    if (0 == refout)
    {
      reg = byte_reverse(reg) >> 1;
    }
  }
  else
  {
    if (0 != refout)
    {
      reg = byte_reverse(reg);
    }
    else
    {
      reg = reg >> 1;
    }
  }

  reg ^= xorout;

  return reg & 0x7f;
}

static unsigned char crc8_table[CRC_TABLE_SIZE];
static struct CRC_SETTING crc8_setting;

unsigned char CRC8T(const unsigned char * const array, const unsigned int num, const unsigned char poly, const unsigned char init, const unsigned char refin, const unsigned char refout, const unsigned char xorout)
{
  unsigned char reg;

  if (num < 1) return 0;

  if (poly != crc8_setting.poly || 
      refin != crc8_setting.refin) /* 判断是否需要更新查询表 */
  {
    crc8_setting.poly = poly;
    crc8_setting.refin = refin;
    
    unsigned int i;

    for (i = 0; i < CRC_TABLE_SIZE; ++i)
    {
      unsigned char tmp;

      tmp = i;
      
      if (0 != refin)
      {
#if 1
        tmp = CRC8((unsigned char *)&tmp, 1, poly, 0x00, 1, 1, 0x00);
#else
        tmp = byte_reverse(tmp);

        tmp = CRC8((unsigned char *)&tmp, 1, poly, 0x00, 0, 0, 0x00);

        tmp = byte_reverse(tmp);
#endif
      }
      else
      {
        tmp = CRC8((unsigned char *)&tmp, 1, poly, 0x00, 0, 0, 0x00);
      }

      crc8_table[i] = tmp;
    }
  }

  if (0 != refin)
  {
    reg = byte_reverse(init);
  }
  else
  {
    reg = init;
  }

  unsigned int i;

  for (i = 0; i < num; ++i)
  {
    reg = crc8_table[reg ^ array[i]];
  }

  if (0 != refin)
  {
    if (0 == refout)
    {
      reg = byte_reverse(reg);
    }
  }
  else
  {
    if (0 != refout)
    {
      reg = byte_reverse(reg);
    }
  }

  reg ^= xorout;

  return reg;
}

static unsigned int crc16_table[CRC_TABLE_SIZE];
static struct CRC_SETTING crc16_setting;

unsigned int CRC16T(const unsigned char * const array, const unsigned int num, const unsigned int poly, const unsigned int init, const unsigned char refin, const unsigned char refout, const unsigned int xorout)
{
  unsigned int reg;

  if (num < 1) return 0;

  if (poly != crc16_setting.poly || 
      refin != crc16_setting.refin) /* 判断是否需要更新查询表 */
  {
    crc16_setting.poly = poly;
    crc16_setting.refin = refin;
    
    unsigned int i;

    for (i = 0; i < CRC_TABLE_SIZE; ++i)
    {
      unsigned int tmp;

      tmp = i;
      
      if (0 != refin)
      {
#if 1
        tmp = CRC16((unsigned char *)&tmp, 1, poly, 0x00, 1, 1, 0x00);
#else
        tmp = byte_reverse(tmp);

        tmp = CRC16((unsigned char *)&tmp, 1, poly, 0x00, 0, 0, 0x00);

        tmp = byte_reverse(tmp & 0xff) << 8 | byte_reverse(tmp >> 8 & 0xff);
#endif
      }
      else
      {
        tmp = CRC16((unsigned char *)&tmp, 1, poly, 0x00, 0, 0, 0x00);
      }

      crc16_table[i] = tmp;
    }
  }

  if (0 != refin)
  {
    reg = byte_reverse(init & 0xff) << 8 | byte_reverse(init >> 8 & 0xff);
  }
  else
  {
    reg = init;
  }

  unsigned int i;

  if (0 != refin)
  {
    for (i = 0; i < num; ++i)
    {
      reg = (reg >> 8 & 0x00ff) ^ crc16_table[(reg & 0x00ff) ^ array[i]];
    }
  }
  else
  {
    for (i = 0; i < num; ++i)
    {
      reg = reg << 8 ^ crc16_table[(reg >> 8 & 0x00ff) ^ array[i]];
    }
  }

  if (0 != refin)
  {
    if (0 == refout)
    {
      reg = byte_reverse(reg & 0xff) << 8  | byte_reverse(reg >> 8 & 0xff);
    }
  }
  else
  {
    if (0 != refout)
    {
      reg = byte_reverse(reg & 0xff) << 8  | byte_reverse(reg >> 8 & 0xff);
    }
  }

  reg ^= xorout;

  return reg & 0xffffu;
}

static unsigned long int crc32_table[CRC_TABLE_SIZE];
static struct CRC_SETTING crc32_setting;

unsigned long int CRC32T(const unsigned char * const array, const unsigned int num, const unsigned long int poly, const unsigned long int init, const unsigned char refin, const unsigned char refout, const unsigned long int xorout)
{
  unsigned long int reg;

  if (num < 1) return 0;

  if (poly != crc32_setting.poly || 
      refin != crc32_setting.refin) /* 判断是否需要更新查询表 */
  {
    crc32_setting.poly = poly;
    crc32_setting.refin = refin;
    
    unsigned int i;

    for (i = 0; i < CRC_TABLE_SIZE; ++i)
    {
      unsigned long int tmp;

      tmp = i;
      
      if (0 != refin)
      {
#if 1
        tmp = CRC32((unsigned char *)&tmp, 1, poly, 0x00, 1, 1, 0x00);
#else
        tmp = byte_reverse(tmp);

        tmp = CRC32((unsigned char *)&tmp, 1, poly, 0x00, 0, 0, 0x00);

        tmp = byte_reverse(tmp & 0x00ff) << 24 | byte_reverse(tmp >> 8 & 0x00ff) << 16 | byte_reverse(tmp >> 16 & 0x00ff) << 8 | byte_reverse(tmp >> 24);
#endif
      }
      else
      {
        tmp = CRC32((unsigned char *)&tmp, 1, poly, 0x00, 0, 0, 0x00);
      }

      crc32_table[i] = tmp;
    }
  }

  if (0 != refin)
  {
    reg = byte_reverse(init & 0x00ff) << 24 | byte_reverse(init >> 8 & 0x00ff) << 16 | byte_reverse(init >> 16 & 0x00ff) << 8 | byte_reverse(init >> 24);
  }
  else
  {
    reg = init;
  }

  unsigned int i;

  if (0 != refin)
  {
    for (i = 0; i < num; ++i)
    {
      reg = (reg >> 8 & 0x00ffffff) ^ crc32_table[(reg & 0x00ff) ^ array[i]];
    }
  }
  else
  {
    for (i = 0; i < num; ++i)
    {
      reg = reg << 8 ^ crc32_table[(reg >> 24 & 0x00ff) ^ array[i]];
    }
  }

  if (0 != refin)
  {
    if (0 == refout)
    {
      reg = byte_reverse(reg & 0x00ff) << 24 | byte_reverse(reg >> 8 & 0x00ff) << 16 | byte_reverse(reg >> 16 & 0x00ff) << 8 | byte_reverse(reg >> 24);
    }
  }
  else
  {
    if (0 != refout)
    {
      reg = byte_reverse(reg & 0x00ff) << 24 | byte_reverse(reg >> 8 & 0x00ff) << 16 | byte_reverse(reg >> 16 & 0x00ff) << 8 | byte_reverse(reg >> 24);
    }
  }

  reg ^= xorout;

  return reg & 0xfffffffful;
}
