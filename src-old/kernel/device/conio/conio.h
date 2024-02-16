#pragma once

#include <stddef.h>
#include <stdint.h>
#include <entry/entry.h>

void conio_write(char *buf, size_t charsize, size_t len);
void conio_chbg(uint32_t bg);
void conio_chfg(uint32_t fg);
void conio_rstcol();
void conio_clear();
void conio_initialize();