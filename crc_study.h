#ifndef __CRC_STUDY_H__
#define __CRC_STUDY_H__

#define CRC_TABLE_SIZE (256)
#if CRC_TABLE_SIZE != 256
#error CRC_TABLE_SIZE must be 256!
#endif

struct CRC_SETTING
{
  unsigned long int poly;
  unsigned long int init;
  unsigned char refin;
  unsigned char refout;
  unsigned long int xorout;
};

unsigned char CRC4(const unsigned char * const array, const unsigned int num, const unsigned char poly, const unsigned char init, const unsigned char refin, const unsigned char refout, const unsigned char xorout);
unsigned char CRC5(const unsigned char * const array, const unsigned int num, const unsigned char poly, const unsigned char init, const unsigned char refin, const unsigned char refout, const unsigned char xorout);
unsigned char CRC6(const unsigned char * const array, const unsigned int num, const unsigned char poly, const unsigned char init, const unsigned char refin, const unsigned char refout, const unsigned char xorout);
unsigned char CRC7(const unsigned char * const array, const unsigned int num, const unsigned char poly, const unsigned char init, const unsigned char refin, const unsigned char refout, const unsigned char xorout);
unsigned char CRC8(const unsigned char * const array, const unsigned int num, const unsigned char poly, const unsigned char init, const unsigned char refin, const unsigned char refout, const unsigned char xorout);
unsigned int CRC16(const unsigned char * const array, const unsigned int num, const unsigned int poly, const unsigned int init, const unsigned char refin, const unsigned char refout, const unsigned int xorout);
unsigned long int CRC32(const unsigned char * const array, const unsigned int num, const unsigned long int poly, const unsigned long int init, const unsigned char refin, const unsigned char refout, const unsigned long int xorout);
unsigned char CRC4T(const unsigned char * const array, const unsigned int num, const unsigned char poly, const unsigned char init, const unsigned char refin, const unsigned char refout, const unsigned char xorout);
unsigned char CRC5T(const unsigned char * const array, const unsigned int num, const unsigned char poly, const unsigned char init, const unsigned char refin, const unsigned char refout, const unsigned char xorout);
unsigned char CRC6T(const unsigned char * const array, const unsigned int num, const unsigned char poly, const unsigned char init, const unsigned char refin, const unsigned char refout, const unsigned char xorout);
unsigned char CRC7T(const unsigned char * const array, const unsigned int num, const unsigned char poly, const unsigned char init, const unsigned char refin, const unsigned char refout, const unsigned char xorout);
unsigned char CRC8T(const unsigned char * const array, const unsigned int num, const unsigned char poly, const unsigned char init, const unsigned char refin, const unsigned char refout, const unsigned char xorout);
unsigned int CRC16T(const unsigned char * const array, const unsigned int num, const unsigned int poly, const unsigned int init, const unsigned char refin, const unsigned char refout, const unsigned int xorout);
unsigned long int CRC32T(const unsigned char * const array, const unsigned int num, const unsigned long int poly, const unsigned long int init, const unsigned char refin, const unsigned char refout, const unsigned long int xorout);

#endif
