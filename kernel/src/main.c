#include <arch/arch.h>
#include <boot/limine.h>
#include <dev/fb/fb.h>
#include <lib/log.h>
#include <lib/psf.h>
#include <lib/stdio.h>
#include <lib/stdlib.h>
#include <lib/stdtype.h>
#include <lib/terminal.h>
#include <memory/memory.h>
#include <stddef.h>

ui8 zap_light16[] = {
  0x36, 0x04, 0x02, 0x10, 0x00, 0x00, 0x00, 0x3e, 0x63, 0x5d, 0x7d, 0x7b, 0x77, 0x77, 0x7f, 0x77, 
  0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7e, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 
  0x22, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x7f, 0x04, 0x08, 0x10, 0x7f, 0x20, 
  0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x10, 0x20, 0x40, 0x20, 0x10, 0x08, 0x00, 
  0x7c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x08, 0x04, 0x02, 0x04, 0x08, 0x10, 0x00, 
  0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x38, 0x7c, 0xfe, 0x7c, 0x38, 0x10, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x30, 0x10, 0x11, 0x12, 0x04, 0x08, 0x12, 0x26, 0x4a, 
  0x0f, 0x02, 0x02, 0x00, 0x00, 0x00, 0x10, 0x30, 0x10, 0x11, 0x12, 0x04, 0x08, 0x10, 0x26, 0x49, 
  0x02, 0x04, 0x0f, 0x00, 0x00, 0x00, 0x70, 0x08, 0x30, 0x09, 0x72, 0x04, 0x08, 0x12, 0x26, 0x4a, 
  0x0f, 0x02, 0x02, 0x00, 0x00, 0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00, 0x08, 0x08, 0x08, 
  0x08, 0x08, 0x00, 0x00, 0x00, 0x24, 0x24, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x08, 0x08, 0x30, 0x00, 0x00, 0x07, 0x08, 0x08, 0x08, 0x3e, 0x08, 0x08, 0x08, 0x08, 0x08, 
  0x08, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x3e, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 
  0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x3e, 0x08, 0x08, 0x08, 0x08, 0x3e, 0x08, 
  0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x42, 0xa4, 0xa4, 0x48, 0x10, 0x10, 0x2a, 0x55, 0x55, 
  0x8a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf1, 0x5b, 0x55, 0x51, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x49, 
  0x49, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x10, 0x20, 0x10, 0x08, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x08, 0x04, 0x08, 0x10, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x24, 0x24, 0x24, 0x12, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x24, 0x24, 0x24, 0x48, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x24, 
  0x24, 0x24, 0x48, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x24, 
  0x24, 0x24, 0x12, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 
  0x10, 0x10, 0x08, 0x00, 0x42, 0x3c, 0x00, 0x3c, 0x42, 0x42, 0x40, 0x40, 0x4e, 0x42, 0x42, 0x42, 
  0x3c, 0x00, 0x00, 0x00, 0x00, 0x42, 0x3c, 0x00, 0x00, 0x3a, 0x46, 0x42, 0x42, 0x42, 0x46, 0x3a, 
  0x02, 0x02, 0x42, 0x3c, 0x08, 0x08, 0x00, 0x3e, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 
  0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 
  0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x42, 0x42, 0x40, 0x30, 0x0c, 0x02, 0x42, 0x42, 
  0x3c, 0x08, 0x08, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x42, 0x40, 0x30, 0x0c, 0x02, 0x42, 
  0x3c, 0x08, 0x08, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00, 0x08, 
  0x08, 0x00, 0x00, 0x00, 0x00, 0x24, 0x24, 0x24, 0x24, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x24, 0x24, 0x24, 0x7e, 0x24, 0x24, 0x7e, 0x24, 0x24, 
  0x24, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x3e, 0x49, 0x48, 0x48, 0x3e, 0x09, 0x09, 0x49, 
  0x3e, 0x08, 0x08, 0x00, 0x00, 0x00, 0x00, 0x31, 0x4a, 0x4a, 0x34, 0x08, 0x08, 0x16, 0x29, 0x29, 
  0x46, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x24, 0x24, 0x24, 0x18, 0x28, 0x45, 0x42, 0x46, 
  0x39, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x08, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x08, 0x08, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x08, 
  0x08, 0x04, 0x00, 0x00, 0x00, 0x00, 0x20, 0x10, 0x10, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x10, 
  0x10, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x49, 0x2a, 0x1c, 0x2a, 0x49, 0x08, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x08, 0x7f, 0x08, 0x08, 0x08, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 
  0x08, 0x08, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7e, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 
  0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x02, 0x04, 0x04, 0x08, 0x08, 0x10, 0x10, 0x20, 
  0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x42, 0x42, 0x42, 0x4a, 0x52, 0x42, 0x42, 0x42, 
  0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x18, 0x28, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 
  0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x42, 0x42, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 
  0x7e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x42, 0x42, 0x02, 0x1c, 0x02, 0x02, 0x42, 0x42, 
  0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x0c, 0x14, 0x24, 0x44, 0x44, 0x7e, 0x04, 0x04, 
  0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7e, 0x40, 0x40, 0x40, 0x7c, 0x02, 0x02, 0x02, 0x42, 
  0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x20, 0x40, 0x40, 0x7c, 0x42, 0x42, 0x42, 0x42, 
  0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7e, 0x02, 0x02, 0x04, 0x04, 0x08, 0x08, 0x10, 0x10, 
  0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x42, 0x42, 0x42, 0x3c, 0x42, 0x42, 0x42, 0x42, 
  0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x42, 0x42, 0x42, 0x42, 0x3e, 0x02, 0x02, 0x04, 
  0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x00, 0x00, 0x00, 0x08, 
  0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x00, 0x00, 0x00, 0x08, 
  0x08, 0x08, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x08, 0x10, 0x20, 0x40, 0x20, 0x10, 0x08, 
  0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7e, 0x00, 0x00, 0x00, 0x7e, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x10, 0x08, 0x04, 0x02, 0x04, 0x08, 0x10, 
  0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x42, 0x42, 0x02, 0x04, 0x08, 0x08, 0x00, 0x08, 
  0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x22, 0x4a, 0x56, 0x52, 0x52, 0x52, 0x4e, 0x20, 
  0x1e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x24, 0x24, 0x42, 0x42, 0x7e, 0x42, 0x42, 0x42, 
  0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x42, 0x42, 0x42, 0x7c, 0x42, 0x42, 0x42, 0x42, 
  0x7c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x42, 0x42, 0x40, 0x40, 0x40, 0x40, 0x42, 0x42, 
  0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x44, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x44, 
  0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7e, 0x40, 0x40, 0x40, 0x7c, 0x40, 0x40, 0x40, 0x40, 
  0x7e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7e, 0x40, 0x40, 0x40, 0x7c, 0x40, 0x40, 0x40, 0x40, 
  0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x42, 0x42, 0x40, 0x40, 0x4e, 0x42, 0x42, 0x42, 
  0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x42, 0x42, 0x42, 0x42, 0x7e, 0x42, 0x42, 0x42, 0x42, 
  0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3e, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 
  0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x44, 0x44, 
  0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x42, 0x44, 0x48, 0x50, 0x60, 0x60, 0x50, 0x48, 0x44, 
  0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 
  0x7e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x41, 0x63, 0x63, 0x55, 0x55, 0x49, 0x49, 0x41, 0x41, 
  0x41, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x42, 0x62, 0x62, 0x52, 0x52, 0x4a, 0x4a, 0x46, 0x46, 
  0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 
  0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x42, 0x42, 0x42, 0x42, 0x7c, 0x40, 0x40, 0x40, 
  0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x5a, 0x66, 
  0x3c, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x42, 0x42, 0x42, 0x7c, 0x48, 0x44, 0x44, 0x42, 
  0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x42, 0x42, 0x40, 0x30, 0x0c, 0x02, 0x42, 0x42, 
  0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 
  0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 
  0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x41, 0x41, 0x41, 0x22, 0x22, 0x22, 0x14, 0x14, 0x08, 
  0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x41, 0x41, 0x41, 0x49, 0x49, 0x55, 0x55, 0x63, 0x63, 
  0x41, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x42, 0x42, 0x24, 0x24, 0x18, 0x18, 0x24, 0x24, 0x42, 
  0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x41, 0x41, 0x22, 0x22, 0x14, 0x08, 0x08, 0x08, 0x08, 
  0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7e, 0x02, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x40, 
  0x7e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 
  0x10, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x20, 0x10, 0x10, 0x08, 0x08, 0x04, 0x04, 0x02, 
  0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 
  0x08, 0x38, 0x00, 0x00, 0x00, 0x08, 0x14, 0x22, 0x41, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x7f, 0x00, 0x00, 0x00, 0x10, 0x10, 0x10, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x42, 0x02, 0x3e, 0x42, 0x42, 0x46, 
  0x3a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x40, 0x40, 0x5c, 0x62, 0x42, 0x42, 0x42, 0x42, 0x62, 
  0x5c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x42, 0x40, 0x40, 0x40, 0x40, 0x42, 
  0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x02, 0x02, 0x3a, 0x46, 0x42, 0x42, 0x42, 0x42, 0x46, 
  0x3a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x42, 0x42, 0x7e, 0x40, 0x40, 0x42, 
  0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x10, 0x10, 0x10, 0x7c, 0x10, 0x10, 0x10, 0x10, 0x10, 
  0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3a, 0x46, 0x42, 0x42, 0x42, 0x46, 0x3a, 
  0x02, 0x02, 0x42, 0x3c, 0x00, 0x00, 0x40, 0x40, 0x40, 0x5c, 0x62, 0x42, 0x42, 0x42, 0x42, 0x42, 
  0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x00, 0x18, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 
  0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x04, 0x00, 0x0c, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 
  0x04, 0x04, 0x44, 0x38, 0x00, 0x00, 0x40, 0x40, 0x40, 0x44, 0x48, 0x50, 0x60, 0x50, 0x48, 0x44, 
  0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 
  0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x76, 0x49, 0x49, 0x49, 0x49, 0x49, 0x49, 
  0x49, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x5c, 0x62, 0x42, 0x42, 0x42, 0x42, 0x42, 
  0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 
  0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x5c, 0x62, 0x42, 0x42, 0x42, 0x42, 0x62, 
  0x5c, 0x40, 0x40, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3a, 0x46, 0x42, 0x42, 0x42, 0x42, 0x46, 
  0x3a, 0x02, 0x02, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x5c, 0x62, 0x40, 0x40, 0x40, 0x40, 0x40, 
  0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x42, 0x40, 0x30, 0x0c, 0x02, 0x42, 
  0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x10, 0x10, 0x10, 0x7c, 0x10, 0x10, 0x10, 0x10, 0x10, 
  0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x46, 
  0x3a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x41, 0x41, 0x41, 0x22, 0x22, 0x14, 0x14, 
  0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x41, 0x41, 0x49, 0x49, 0x49, 0x49, 0x49, 
  0x36, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x42, 0x42, 0x24, 0x18, 0x18, 0x24, 0x42, 
  0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x42, 0x42, 0x42, 0x42, 0x42, 0x46, 0x3a, 
  0x02, 0x02, 0x42, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7e, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 
  0x7e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x08, 0x08, 0x08, 0x08, 0x30, 0x08, 0x08, 0x08, 0x08, 
  0x08, 0x06, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 
  0x08, 0x08, 0x00, 0x00, 0x00, 0x00, 0x30, 0x08, 0x08, 0x08, 0x08, 0x06, 0x08, 0x08, 0x08, 0x08, 
  0x08, 0x30, 0x00, 0x00, 0x00, 0x31, 0x49, 0x46, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x3c, 0x3c, 0x18, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x30, 0x0c, 0x00, 0x18, 0x24, 0x24, 0x42, 0x42, 0x7e, 0x42, 0x42, 0x42, 
  0x42, 0x00, 0x00, 0x00, 0x0c, 0x30, 0x00, 0x18, 0x24, 0x24, 0x42, 0x42, 0x7e, 0x42, 0x42, 0x42, 
  0x42, 0x00, 0x00, 0x00, 0x18, 0x24, 0x00, 0x18, 0x24, 0x24, 0x42, 0x42, 0x7e, 0x42, 0x42, 0x42, 
  0x42, 0x00, 0x00, 0x00, 0x32, 0x4c, 0x00, 0x18, 0x24, 0x24, 0x42, 0x42, 0x7e, 0x42, 0x42, 0x42, 
  0x42, 0x00, 0x00, 0x00, 0x24, 0x24, 0x00, 0x18, 0x24, 0x24, 0x42, 0x42, 0x7e, 0x42, 0x42, 0x42, 
  0x42, 0x00, 0x00, 0x00, 0x18, 0x24, 0x24, 0x18, 0x24, 0x24, 0x42, 0x42, 0x7e, 0x42, 0x42, 0x42, 
  0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x28, 0x48, 0x48, 0x7e, 0x48, 0x48, 0x48, 0x48, 
  0x4f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x42, 0x42, 0x40, 0x40, 0x40, 0x40, 0x42, 0x42, 
  0x3c, 0x08, 0x08, 0x30, 0x30, 0x0c, 0x00, 0x7e, 0x40, 0x40, 0x40, 0x7c, 0x40, 0x40, 0x40, 0x40, 
  0x7e, 0x00, 0x00, 0x00, 0x0c, 0x30, 0x00, 0x7e, 0x40, 0x40, 0x40, 0x7c, 0x40, 0x40, 0x40, 0x40, 
  0x7e, 0x00, 0x00, 0x00, 0x18, 0x24, 0x00, 0x7e, 0x40, 0x40, 0x40, 0x7c, 0x40, 0x40, 0x40, 0x40, 
  0x7e, 0x00, 0x00, 0x00, 0x24, 0x24, 0x00, 0x7e, 0x40, 0x40, 0x40, 0x7c, 0x40, 0x40, 0x40, 0x40, 
  0x7e, 0x00, 0x00, 0x00, 0x30, 0x0c, 0x00, 0x3e, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 
  0x3e, 0x00, 0x00, 0x00, 0x06, 0x18, 0x00, 0x3e, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 
  0x3e, 0x00, 0x00, 0x00, 0x18, 0x24, 0x00, 0x3e, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 
  0x3e, 0x00, 0x00, 0x00, 0x22, 0x22, 0x00, 0x3e, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 
  0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x44, 0x42, 0x42, 0xf2, 0x42, 0x42, 0x42, 0x44, 
  0x78, 0x00, 0x00, 0x00, 0x32, 0x4c, 0x00, 0x42, 0x62, 0x62, 0x52, 0x52, 0x4a, 0x4a, 0x46, 0x46, 
  0x42, 0x00, 0x00, 0x00, 0x30, 0x0c, 0x00, 0x3c, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 
  0x3c, 0x00, 0x00, 0x00, 0x0c, 0x30, 0x00, 0x3c, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 
  0x3c, 0x00, 0x00, 0x00, 0x18, 0x24, 0x00, 0x3c, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 
  0x3c, 0x00, 0x00, 0x00, 0x32, 0x4c, 0x00, 0x3c, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 
  0x3c, 0x00, 0x00, 0x00, 0x24, 0x24, 0x00, 0x3c, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 
  0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x22, 0x14, 0x08, 0x14, 0x22, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x3a, 0x44, 0x46, 0x4a, 0x4a, 0x52, 0x52, 0x62, 0x22, 
  0x5c, 0x40, 0x00, 0x00, 0x30, 0x0c, 0x00, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 
  0x3c, 0x00, 0x00, 0x00, 0x0c, 0x30, 0x00, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 
  0x3c, 0x00, 0x00, 0x00, 0x18, 0x24, 0x00, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 
  0x3c, 0x00, 0x00, 0x00, 0x24, 0x24, 0x00, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 
  0x3c, 0x00, 0x00, 0x00, 0x06, 0x18, 0x00, 0x41, 0x41, 0x22, 0x22, 0x14, 0x08, 0x08, 0x08, 0x08, 
  0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x40, 0x7c, 0x42, 0x42, 0x42, 0x42, 0x7c, 0x40, 
  0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x44, 0x4c, 0x50, 0x50, 0x4c, 0x42, 0x42, 0x52, 
  0x4c, 0x00, 0x00, 0x00, 0xaa, 0x55, 0xaa, 0x55, 0xaa, 0x55, 0xaa, 0x55, 0xaa, 0x55, 0xaa, 0x55, 
  0xaa, 0x55, 0xaa, 0x55, 0x00, 0x00, 0x00, 0x08, 0x08, 0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 
  0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x3e, 0x49, 0x48, 0x48, 0x48, 0x48, 0x49, 
  0x3e, 0x08, 0x08, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x20, 0x20, 0x20, 0x78, 0x20, 0x20, 0x20, 0x22, 
  0x7e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x11, 0x20, 0x7e, 0x20, 0x7c, 0x20, 0x11, 
  0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x41, 0x41, 0x22, 0x14, 0x08, 0x3e, 0x08, 0x3e, 0x08, 
  0x08, 0x00, 0x00, 0x00, 0x24, 0x18, 0x00, 0x3c, 0x42, 0x42, 0x40, 0x30, 0x0c, 0x02, 0x42, 0x42, 
  0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x22, 0x20, 0x18, 0x24, 0x22, 0x22, 0x12, 0x0c, 0x02, 
  0x22, 0x1c, 0x00, 0x00, 0x00, 0x24, 0x18, 0x00, 0x00, 0x3c, 0x42, 0x40, 0x30, 0x0c, 0x02, 0x42, 
  0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x42, 0x99, 0xa5, 0xa1, 0xa1, 0xa5, 0x99, 0x42, 
  0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x04, 0x3c, 0x44, 0x3c, 0x00, 0x7c, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x12, 0x24, 0x48, 0x24, 0x12, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7e, 0x02, 0x02, 0x02, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x22, 0x1c, 0x22, 0x22, 0x22, 0x1c, 0x22, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x42, 0xb9, 0xa5, 0xa5, 0xb9, 0xa9, 0xa5, 0x42, 
  0x3c, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x24, 0x24, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x08, 0x7f, 0x08, 0x08, 0x08, 0x00, 0x7f, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x44, 0x04, 0x18, 0x20, 0x40, 0x7c, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x44, 0x04, 0x38, 0x04, 0x44, 0x38, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x24, 0x18, 0x00, 0x7e, 0x02, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x40, 
  0x7e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x66, 
  0x5a, 0x40, 0x40, 0x40, 0x00, 0x00, 0x00, 0x3e, 0x7a, 0x7a, 0x7a, 0x7a, 0x3a, 0x0a, 0x0a, 0x0a, 
  0x0a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x24, 0x18, 0x00, 0x00, 0x7e, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 
  0x7e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x30, 0x50, 0x10, 0x10, 0x10, 0x7c, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x44, 0x44, 0x44, 0x38, 0x00, 0x7c, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x48, 0x24, 0x12, 0x24, 0x48, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x37, 0x48, 0x48, 0x48, 0x4e, 0x48, 0x48, 0x48, 0x48, 
  0x37, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x36, 0x49, 0x49, 0x4f, 0x48, 0x48, 0x49, 
  0x36, 0x00, 0x00, 0x00, 0x22, 0x22, 0x00, 0x41, 0x41, 0x22, 0x22, 0x14, 0x08, 0x08, 0x08, 0x08, 
  0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x10, 0x00, 0x10, 0x10, 0x20, 0x40, 0x42, 0x42, 
  0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 
  0x08, 0x08, 0x08, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x08, 0x08, 0x08, 
  0x08, 0x08, 0x08, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x08, 0x08, 0x08, 
  0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x0f, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0xf8, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x0f, 0x08, 0x08, 0x08, 
  0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0xf8, 0x08, 0x08, 0x08, 
  0x08, 0x08, 0x08, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x08, 0x08, 0x08, 
  0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0xff, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0xff, 0x08, 0x08, 0x08, 
  0x08, 0x08, 0x08, 0x08, 0x88, 0x22, 0x88, 0x22, 0x88, 0x22, 0x88, 0x22, 0x88, 0x22, 0x88, 0x22, 
  0x88, 0x22, 0x88, 0x22, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0xff, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 
  0x14, 0x14, 0x14, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x10, 0x17, 0x14, 0x14, 
  0x14, 0x14, 0x14, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x04, 0xf4, 0x14, 0x14, 
  0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x17, 0x10, 0x1f, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0xf4, 0x04, 0xfc, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x17, 0x10, 0x17, 0x14, 0x14, 
  0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0xf4, 0x04, 0xf4, 0x14, 0x14, 
  0x14, 0x14, 0x14, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0xf7, 0x14, 0x14, 
  0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0xf7, 0x00, 0xff, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0xf7, 0x00, 0xf7, 0x14, 0x14, 
  0x14, 0x14, 0x14, 0x14, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x1c, 0x2a, 0x08, 0x08, 0x08, 0x08, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x08, 0x08, 0x2a, 0x1c, 0x08, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x20, 0x7f, 0x20, 0x10, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x04, 0xfe, 0x04, 0x08, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x0c, 0x00, 0x00, 0x3c, 0x42, 0x02, 0x3e, 0x42, 0x42, 0x46, 
  0x3a, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x30, 0x00, 0x00, 0x3c, 0x42, 0x02, 0x3e, 0x42, 0x42, 0x46, 
  0x3a, 0x00, 0x00, 0x00, 0x00, 0x18, 0x24, 0x00, 0x00, 0x3c, 0x42, 0x02, 0x3e, 0x42, 0x42, 0x46, 
  0x3a, 0x00, 0x00, 0x00, 0x00, 0x32, 0x4c, 0x00, 0x00, 0x3c, 0x42, 0x02, 0x3e, 0x42, 0x42, 0x46, 
  0x3a, 0x00, 0x00, 0x00, 0x00, 0x24, 0x24, 0x00, 0x00, 0x3c, 0x42, 0x02, 0x3e, 0x42, 0x42, 0x46, 
  0x3a, 0x00, 0x00, 0x00, 0x18, 0x24, 0x24, 0x18, 0x00, 0x3c, 0x42, 0x02, 0x3e, 0x42, 0x42, 0x46, 
  0x3a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x36, 0x49, 0x09, 0x3f, 0x48, 0x48, 0x49, 
  0x36, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x42, 0x40, 0x40, 0x40, 0x40, 0x42, 
  0x3c, 0x08, 0x08, 0x30, 0x00, 0x30, 0x0c, 0x00, 0x00, 0x3c, 0x42, 0x42, 0x7e, 0x40, 0x40, 0x42, 
  0x3c, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x30, 0x00, 0x00, 0x3c, 0x42, 0x42, 0x7e, 0x40, 0x40, 0x42, 
  0x3c, 0x00, 0x00, 0x00, 0x00, 0x18, 0x24, 0x00, 0x00, 0x3c, 0x42, 0x42, 0x7e, 0x40, 0x40, 0x42, 
  0x3c, 0x00, 0x00, 0x00, 0x00, 0x24, 0x24, 0x00, 0x00, 0x3c, 0x42, 0x42, 0x7e, 0x40, 0x40, 0x42, 
  0x3c, 0x00, 0x00, 0x00, 0x00, 0x30, 0x0c, 0x00, 0x00, 0x18, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 
  0x3e, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x30, 0x00, 0x00, 0x18, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 
  0x3e, 0x00, 0x00, 0x00, 0x00, 0x18, 0x24, 0x00, 0x00, 0x18, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 
  0x3e, 0x00, 0x00, 0x00, 0x00, 0x24, 0x24, 0x00, 0x00, 0x18, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 
  0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x66, 0x18, 0x64, 0x02, 0x3a, 0x46, 0x42, 0x42, 0x42, 0x42, 
  0x3c, 0x00, 0x00, 0x00, 0x00, 0x32, 0x4c, 0x00, 0x00, 0x5c, 0x62, 0x42, 0x42, 0x42, 0x42, 0x42, 
  0x42, 0x00, 0x00, 0x00, 0x00, 0x30, 0x0c, 0x00, 0x00, 0x3c, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 
  0x3c, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x30, 0x00, 0x00, 0x3c, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 
  0x3c, 0x00, 0x00, 0x00, 0x00, 0x18, 0x24, 0x00, 0x00, 0x3c, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 
  0x3c, 0x00, 0x00, 0x00, 0x00, 0x32, 0x4c, 0x00, 0x00, 0x3c, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 
  0x3c, 0x00, 0x00, 0x00, 0x00, 0x24, 0x24, 0x00, 0x00, 0x3c, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 
  0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x10, 0x00, 0x00, 0x7c, 0x00, 0x00, 0x10, 
  0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x3c, 0x46, 0x4a, 0x4a, 0x52, 0x52, 0x62, 
  0x3c, 0x40, 0x00, 0x00, 0x00, 0x30, 0x0c, 0x00, 0x00, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x46, 
  0x3a, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x30, 0x00, 0x00, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x46, 
  0x3a, 0x00, 0x00, 0x00, 0x00, 0x18, 0x24, 0x00, 0x00, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x46, 
  0x3a, 0x00, 0x00, 0x00, 0x00, 0x24, 0x24, 0x00, 0x00, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x46, 
  0x3a, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x30, 0x00, 0x00, 0x42, 0x42, 0x42, 0x42, 0x42, 0x46, 0x3a, 
  0x02, 0x02, 0x42, 0x3c, 0x00, 0x00, 0x40, 0x40, 0x40, 0x5c, 0x62, 0x42, 0x42, 0x42, 0x42, 0x62, 
  0x5c, 0x40, 0x40, 0x40, 0x00, 0x24, 0x24, 0x00, 0x00, 0x42, 0x42, 0x42, 0x42, 0x42, 0x46, 0x3a, 
  0x02, 0x02, 0x42, 0x3c, 0xfd, 0xff, 0xff, 0xff, 0xc0, 0x03, 0xff, 0xff, 0x60, 0x22, 0xff, 0xff, 
  0x64, 0x22, 0xff, 0xff, 0x65, 0x22, 0xff, 0xff, 0xa0, 0x25, 0xac, 0x25, 0xae, 0x25, 0xfc, 0x25, 
  0xfe, 0x25, 0x1b, 0x2b, 0x0e, 0x22, 0xff, 0xff, 0xc6, 0x25, 0x66, 0x26, 0x25, 0x2b, 0x27, 0x2b, 
  0xff, 0xff, 0xbc, 0x00, 0xff, 0xff, 0xbd, 0x00, 0xff, 0xff, 0xbe, 0x00, 0xff, 0xff, 0xa6, 0x00, 
  0xff, 0xff, 0xa8, 0x00, 0xff, 0xff, 0xb8, 0x00, 0xff, 0xff, 0x92, 0x01, 0xff, 0xff, 0x20, 0x20, 
  0xff, 0xff, 0x21, 0x20, 0xff, 0xff, 0x30, 0x20, 0xff, 0xff, 0x22, 0x21, 0xff, 0xff, 0x26, 0x20, 
  0xff, 0xff, 0x39, 0x20, 0xff, 0xff, 0x3a, 0x20, 0xff, 0xff, 0x1c, 0x20, 0x1f, 0x20, 0x36, 0x20, 
  0xff, 0xff, 0x1d, 0x20, 0xba, 0x02, 0xdd, 0x02, 0xee, 0x02, 0x33, 0x20, 0xff, 0xff, 0x1e, 0x20, 
  0xff, 0xff, 0x42, 0x2e, 0xff, 0xff, 0x41, 0x2e, 0xce, 0x02, 0xff, 0xff, 0x1e, 0x01, 0xff, 0xff, 
  0x1f, 0x01, 0xff, 0xff, 0x30, 0x01, 0xff, 0xff, 0x31, 0x01, 0xff, 0xff, 0x5e, 0x01, 0xff, 0xff, 
  0x5f, 0x01, 0xff, 0xff, 0x20, 0x00, 0xa0, 0x00, 0x00, 0x20, 0x01, 0x20, 0x02, 0x20, 0x03, 0x20, 
  0x04, 0x20, 0x05, 0x20, 0x06, 0x20, 0x07, 0x20, 0x08, 0x20, 0x09, 0x20, 0x0a, 0x20, 0x2f, 0x20, 
  0x5f, 0x20, 0xff, 0xff, 0x21, 0x00, 0xff, 0xff, 0x22, 0x00, 0xff, 0xff, 0x23, 0x00, 0xff, 0xff, 
  0x24, 0x00, 0xff, 0xff, 0x25, 0x00, 0xff, 0xff, 0x26, 0x00, 0xff, 0xff, 0x27, 0x00, 0xb4, 0x00, 
  0xb9, 0x02, 0xbc, 0x02, 0xca, 0x02, 0x19, 0x20, 0x32, 0x20, 0xff, 0xff, 0x28, 0x00, 0xff, 0xff, 
  0x29, 0x00, 0xff, 0xff, 0x2a, 0x00, 0x4e, 0x20, 0x17, 0x22, 0xff, 0xff, 0x2b, 0x00, 0xff, 0xff, 
  0x2c, 0x00, 0xcf, 0x02, 0x1a, 0x20, 0xff, 0xff, 0x2d, 0x00, 0xad, 0x00, 0x10, 0x20, 0x11, 0x20, 
  0x12, 0x20, 0x13, 0x20, 0x43, 0x20, 0x12, 0x22, 0xff, 0xff, 0x2e, 0x00, 0x24, 0x20, 0xff, 0xff, 
  0x2f, 0x00, 0x44, 0x20, 0x15, 0x22, 0xff, 0xff, 0x30, 0x00, 0xff, 0xff, 0x31, 0x00, 0xff, 0xff, 
  0x32, 0x00, 0xff, 0xff, 0x33, 0x00, 0xff, 0xff, 0x34, 0x00, 0xff, 0xff, 0x35, 0x00, 0xff, 0xff, 
  0x36, 0x00, 0xff, 0xff, 0x37, 0x00, 0xff, 0xff, 0x38, 0x00, 0xff, 0xff, 0x39, 0x00, 0xff, 0xff, 
  0x3a, 0x00, 0x36, 0x22, 0xff, 0xff, 0x3b, 0x00, 0xff, 0xff, 0x3c, 0x00, 0xff, 0xff, 0x3d, 0x00, 
  0x40, 0x2e, 0xff, 0xff, 0x3e, 0x00, 0xff, 0xff, 0x3f, 0x00, 0xff, 0xff, 0x40, 0x00, 0xff, 0xff, 
  0x41, 0x00, 0xff, 0xff, 0x42, 0x00, 0xff, 0xff, 0x43, 0x00, 0xff, 0xff, 0x44, 0x00, 0xff, 0xff, 
  0x45, 0x00, 0xff, 0xff, 0x46, 0x00, 0xff, 0xff, 0x47, 0x00, 0xff, 0xff, 0x48, 0x00, 0xff, 0xff, 
  0x49, 0x00, 0xff, 0xff, 0x4a, 0x00, 0xff, 0xff, 0x4b, 0x00, 0x2a, 0x21, 0xff, 0xff, 0x4c, 0x00, 
  0xff, 0xff, 0x4d, 0x00, 0xff, 0xff, 0x4e, 0x00, 0xff, 0xff, 0x4f, 0x00, 0xff, 0xff, 0x50, 0x00, 
  0xff, 0xff, 0x51, 0x00, 0xff, 0xff, 0x52, 0x00, 0xff, 0xff, 0x53, 0x00, 0xff, 0xff, 0x54, 0x00, 
  0xff, 0xff, 0x55, 0x00, 0xff, 0xff, 0x56, 0x00, 0xff, 0xff, 0x57, 0x00, 0xff, 0xff, 0x58, 0x00, 
  0xff, 0xff, 0x59, 0x00, 0xff, 0xff, 0x5a, 0x00, 0xff, 0xff, 0x5b, 0x00, 0xff, 0xff, 0x5c, 0x00, 
  0xf5, 0x29, 0xff, 0xff, 0x5d, 0x00, 0xff, 0xff, 0x5e, 0x00, 0xc4, 0x02, 0xc6, 0x02, 0x03, 0x23, 
  0xff, 0xff, 0x5f, 0x00, 0xff, 0xff, 0x60, 0x00, 0xbb, 0x02, 0xbd, 0x02, 0xcb, 0x02, 0x18, 0x20, 
  0x1b, 0x20, 0x35, 0x20, 0xff, 0xff, 0x61, 0x00, 0xff, 0xff, 0x62, 0x00, 0xff, 0xff, 0x63, 0x00, 
  0xff, 0xff, 0x64, 0x00, 0xff, 0xff, 0x65, 0x00, 0xff, 0xff, 0x66, 0x00, 0xff, 0xff, 0x67, 0x00, 
  0xff, 0xff, 0x68, 0x00, 0xff, 0xff, 0x69, 0x00, 0xff, 0xff, 0x6a, 0x00, 0xff, 0xff, 0x6b, 0x00, 
  0xff, 0xff, 0x6c, 0x00, 0xff, 0xff, 0x6d, 0x00, 0xff, 0xff, 0x6e, 0x00, 0xff, 0xff, 0x6f, 0x00, 
  0xff, 0xff, 0x70, 0x00, 0xff, 0xff, 0x71, 0x00, 0xff, 0xff, 0x72, 0x00, 0xff, 0xff, 0x73, 0x00, 
  0xff, 0xff, 0x74, 0x00, 0xff, 0xff, 0x75, 0x00, 0xff, 0xff, 0x76, 0x00, 0xff, 0xff, 0x77, 0x00, 
  0xff, 0xff, 0x78, 0x00, 0xff, 0xff, 0x79, 0x00, 0xff, 0xff, 0x7a, 0x00, 0xff, 0xff, 0x7b, 0x00, 
  0xff, 0xff, 0x7c, 0x00, 0x23, 0x22, 0xff, 0xff, 0x7d, 0x00, 0xff, 0xff, 0x7e, 0x00, 0xdc, 0x02, 
  0xff, 0xff, 0x22, 0x20, 0x19, 0x22, 0xcf, 0x25, 0xff, 0xff, 0xc0, 0x00, 0xff, 0xff, 0xc1, 0x00, 
  0xff, 0xff, 0xc2, 0x00, 0xff, 0xff, 0xc3, 0x00, 0xff, 0xff, 0xc4, 0x00, 0xff, 0xff, 0xc5, 0x00, 
  0x2b, 0x21, 0xff, 0xff, 0xc6, 0x00, 0xff, 0xff, 0xc7, 0x00, 0xff, 0xff, 0xc8, 0x00, 0xff, 0xff, 
  0xc9, 0x00, 0xff, 0xff, 0xca, 0x00, 0xff, 0xff, 0xcb, 0x00, 0xff, 0xff, 0xcc, 0x00, 0xff, 0xff, 
  0xcd, 0x00, 0xff, 0xff, 0xce, 0x00, 0xff, 0xff, 0xcf, 0x00, 0xff, 0xff, 0xd0, 0x00, 0x10, 0x01, 
  0xff, 0xff, 0xd1, 0x00, 0xff, 0xff, 0xd2, 0x00, 0xff, 0xff, 0xd3, 0x00, 0xff, 0xff, 0xd4, 0x00, 
  0xff, 0xff, 0xd5, 0x00, 0xff, 0xff, 0xd6, 0x00, 0xff, 0xff, 0xd7, 0x00, 0xff, 0xff, 0xd8, 0x00, 
  0xff, 0xff, 0xd9, 0x00, 0xff, 0xff, 0xda, 0x00, 0xff, 0xff, 0xdb, 0x00, 0xff, 0xff, 0xdc, 0x00, 
  0xff, 0xff, 0xdd, 0x00, 0xff, 0xff, 0xde, 0x00, 0xff, 0xff, 0xdf, 0x00, 0xff, 0xff, 0x92, 0x25, 
  0xff, 0xff, 0xa1, 0x00, 0xff, 0xff, 0xa2, 0x00, 0xff, 0xff, 0xa3, 0x00, 0xff, 0xff, 0xac, 0x20, 
  0xff, 0xff, 0xa5, 0x00, 0xff, 0xff, 0x60, 0x01, 0xff, 0xff, 0xa7, 0x00, 0xff, 0xff, 0x61, 0x01, 
  0xff, 0xff, 0xa9, 0x00, 0xff, 0xff, 0xaa, 0x00, 0xff, 0xff, 0xab, 0x00, 0xff, 0xff, 0xac, 0x00, 
  0xff, 0xff, 0xa4, 0x00, 0xff, 0xff, 0xae, 0x00, 0xff, 0xff, 0xaf, 0x00, 0xc9, 0x02, 0xff, 0xff, 
  0xb0, 0x00, 0xda, 0x02, 0xff, 0xff, 0xb1, 0x00, 0xff, 0xff, 0xb2, 0x00, 0xff, 0xff, 0xb3, 0x00, 
  0xff, 0xff, 0x7d, 0x01, 0xff, 0xff, 0xb5, 0x00, 0xbc, 0x03, 0xff, 0xff, 0xb6, 0x00, 0xff, 0xff, 
  0xb7, 0x00, 0x27, 0x20, 0xc5, 0x22, 0x31, 0x2e, 0xff, 0xff, 0x7e, 0x01, 0xff, 0xff, 0xb9, 0x00, 
  0xff, 0xff, 0xba, 0x00, 0xff, 0xff, 0xbb, 0x00, 0xff, 0xff, 0x52, 0x01, 0xff, 0xff, 0x53, 0x01, 
  0xff, 0xff, 0x78, 0x01, 0xff, 0xff, 0xbf, 0x00, 0xff, 0xff, 0x00, 0x25, 0x14, 0x20, 0x15, 0x20, 
  0xaf, 0x23, 0xff, 0xff, 0x02, 0x25, 0xff, 0xff, 0x0c, 0x25, 0x6d, 0x25, 0xff, 0xff, 0x10, 0x25, 
  0x6e, 0x25, 0xff, 0xff, 0x14, 0x25, 0x70, 0x25, 0xff, 0xff, 0x18, 0x25, 0x6f, 0x25, 0xff, 0xff, 
  0x1c, 0x25, 0xff, 0xff, 0x24, 0x25, 0xff, 0xff, 0x2c, 0x25, 0xff, 0xff, 0x34, 0x25, 0xff, 0xff, 
  0x3c, 0x25, 0xff, 0xff, 0x91, 0x25, 0xff, 0xff, 0xba, 0x23, 0x3e, 0x20, 0xff, 0xff, 0xbb, 0x23, 
  0xff, 0xff, 0xbc, 0x23, 0xff, 0xff, 0xbd, 0x23, 0xff, 0xff, 0x50, 0x25, 0x01, 0x25, 0xff, 0xff, 
  0x51, 0x25, 0x03, 0x25, 0xff, 0xff, 0x54, 0x25, 0x0f, 0x25, 0xff, 0xff, 0x57, 0x25, 0x13, 0x25, 
  0xff, 0xff, 0x5a, 0x25, 0x17, 0x25, 0xff, 0xff, 0x5d, 0x25, 0x1b, 0x25, 0xff, 0xff, 0x60, 0x25, 
  0x23, 0x25, 0xff, 0xff, 0x63, 0x25, 0x2b, 0x25, 0xff, 0xff, 0x66, 0x25, 0x33, 0x25, 0xff, 0xff, 
  0x69, 0x25, 0x3b, 0x25, 0xff, 0xff, 0x6c, 0x25, 0x4b, 0x25, 0xff, 0xff, 0x88, 0x25, 0xff, 0xff, 
  0x91, 0x21, 0xff, 0xff, 0x93, 0x21, 0xff, 0xff, 0x90, 0x21, 0xff, 0xff, 0x92, 0x21, 0xff, 0xff, 
  0xe0, 0x00, 0xff, 0xff, 0xe1, 0x00, 0xff, 0xff, 0xe2, 0x00, 0xff, 0xff, 0xe3, 0x00, 0xff, 0xff, 
  0xe4, 0x00, 0xff, 0xff, 0xe5, 0x00, 0xff, 0xff, 0xe6, 0x00, 0xff, 0xff, 0xe7, 0x00, 0xff, 0xff, 
  0xe8, 0x00, 0xff, 0xff, 0xe9, 0x00, 0xff, 0xff, 0xea, 0x00, 0xff, 0xff, 0xeb, 0x00, 0xff, 0xff, 
  0xec, 0x00, 0xff, 0xff, 0xed, 0x00, 0xff, 0xff, 0xee, 0x00, 0xff, 0xff, 0xef, 0x00, 0xff, 0xff, 
  0xf0, 0x00, 0xff, 0xff, 0xf1, 0x00, 0xff, 0xff, 0xf2, 0x00, 0xff, 0xff, 0xf3, 0x00, 0xff, 0xff, 
  0xf4, 0x00, 0xff, 0xff, 0xf5, 0x00, 0xff, 0xff, 0xf6, 0x00, 0xff, 0xff, 0xf7, 0x00, 0xff, 0xff, 
  0xf8, 0x00, 0xff, 0xff, 0xf9, 0x00, 0xff, 0xff, 0xfa, 0x00, 0xff, 0xff, 0xfb, 0x00, 0xff, 0xff, 
  0xfc, 0x00, 0xff, 0xff, 0xfd, 0x00, 0xff, 0xff, 0xfe, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff
};

static volatile struct limine_framebuffer_request fb_request = {
    .id = LIMINE_FRAMEBUFFER_REQUEST, 
    .revision = 0
};

void main()
{
    pmm_init();

    framebuffer *f;
    Terminal *t = malloc(sizeof(Terminal));

    f = fb_fromlimine(fb_request.response->framebuffers[0]);

    init_terminal(t, &zap_light16, f);

    log(LOGTYPE_INFO, "Welcome to SipaaKernel! Framebuf: a: %p w: %llu h: %llu p: %llu\n", f->address, f ->width, f->height, f->pitch);

    arch_init_stage1();

    // Try the POSIX subsystem
    int serial_fd = fopen("/dev/tty0", "w");
    log(LOGTYPE_INFO, "fopen returned %d\n", serial_fd);

    int r = fprintf(serial_fd, "Welcome to SipaaKernel! Framebuf: a: %p w: %llu h: %llu p: %llu\n", f->address, f ->width, f->height, f->pitch);
    log(LOGTYPE_INFO, "fprintf returned %d\n", r);

    r = fwrite("Hello, World!\n\0", sizeof(char), 13, serial_fd);
    log(LOGTYPE_INFO, "fwrite returned %d\n", r);

    char *buf;
    r = fread(buf, sizeof(char), 14, serial_fd);
    if (!buf)
        log(LOGTYPE_INFO, "fread returned NULL\n");

    r = fclose(serial_fd);
    log(LOGTYPE_INFO, "fclose returned %d\n", r);

    // Halt
    arch_idle();
}