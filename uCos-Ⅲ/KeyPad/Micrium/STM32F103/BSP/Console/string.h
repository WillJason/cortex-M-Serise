#ifndef _STRING_H_
#define _STRING_H_
extern void putnstr(const char *str, size_t n);
extern void putstr(const char *str);
extern void u32todecimal(char *buf, unsigned long x);
extern void binarytohex(char *buf, long x, int nbytes);
extern void putstr_hex(const char *str, unsigned long value);
extern unsigned  stringtoul(const char *str, int *ret);
extern void hex_dump(unsigned char *data, size_t num);
#endif

