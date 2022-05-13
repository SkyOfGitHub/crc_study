#ifndef __CRC_STUDY_H__
#define __CRC_STUDY_H__

struct CRC_SETTING
{
  unsigned long int poly;
  unsigned long int init;
  unsigned char refin;
  unsigned char refout;
  unsigned long int xorout;
};

unsigned char CRC4(const unsigned char * const array, const unsigned int num, const struct CRC_SETTING * const crc_setting);
unsigned char CRC5(const unsigned char * const array, const unsigned int num, const struct CRC_SETTING * const crc_setting);
unsigned char CRC6(const unsigned char * const array, const unsigned int num, const struct CRC_SETTING * const crc_setting);
unsigned char CRC7(const unsigned char * const array, const unsigned int num, const struct CRC_SETTING * const crc_setting);
unsigned char CRC8(const unsigned char * const array, const unsigned int num, const struct CRC_SETTING * const crc_setting);
unsigned int CRC16(const unsigned char * const array, const unsigned int num, const struct CRC_SETTING * const crc_setting);
unsigned long int CRC32(const unsigned char * const array, const unsigned int num, const struct CRC_SETTING * const crc_setting);

unsigned char CRC7T(const unsigned char * const array, const unsigned int num, const struct CRC_SETTING * const crc_setting);
#endif
