#include "console.h"

#include <logging/logger.h>
#include <lib/lib.h>

using namespace Sk::Logging;

namespace Sk {

uint32_t Console::term_color = 0xFFFFFF;
int Console::termx = 0;
int Console::termy = 0;
Framebuffer Console::framebuf = Framebuffer(0, 0, 0);

unsigned char font[] = {
    0x36, 0x04, 0x02, 0x10, 0x00, 0x00, 0x00, 0x3e, 0x63, 0x5d, 0x7d, 0x7b,
    0x77, 0x77, 0x7f, 0x77, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x7e, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x22, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x7f, 0x04, 0x08, 0x10, 0x7f, 0x20,
    0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x10, 0x20, 0x40,
    0x20, 0x10, 0x08, 0x00, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x10, 0x08, 0x04, 0x02, 0x04, 0x08, 0x10, 0x00, 0x3e, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x38, 0x7c,
    0xfe, 0x7c, 0x38, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x30,
    0x10, 0x11, 0x12, 0x04, 0x08, 0x12, 0x26, 0x4a, 0x0f, 0x02, 0x02, 0x00,
    0x00, 0x00, 0x10, 0x30, 0x10, 0x11, 0x12, 0x04, 0x08, 0x10, 0x26, 0x49,
    0x02, 0x04, 0x0f, 0x00, 0x00, 0x00, 0x70, 0x08, 0x30, 0x09, 0x72, 0x04,
    0x08, 0x12, 0x26, 0x4a, 0x0f, 0x02, 0x02, 0x00, 0x00, 0x00, 0x08, 0x08,
    0x08, 0x08, 0x08, 0x00, 0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00,
    0x00, 0x24, 0x24, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x30, 0x00, 0x00, 0x07, 0x08,
    0x08, 0x08, 0x3e, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x70, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x08, 0x08, 0x3e, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08,
    0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x3e, 0x08, 0x08,
    0x08, 0x08, 0x3e, 0x08, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x42,
    0xa4, 0xa4, 0x48, 0x10, 0x10, 0x2a, 0x55, 0x55, 0x8a, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0xf1, 0x5b, 0x55, 0x51, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x49, 0x49, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x08, 0x10, 0x20, 0x10, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x08, 0x04, 0x08, 0x10, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x24, 0x24, 0x24, 0x12, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x24, 0x24, 0x24,
    0x48, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x24,
    0x24, 0x24, 0x48, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x24, 0x24, 0x24, 0x12, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x10, 0x10, 0x08, 0x00,
    0x42, 0x3c, 0x00, 0x3c, 0x42, 0x42, 0x40, 0x40, 0x4e, 0x42, 0x42, 0x42,
    0x3c, 0x00, 0x00, 0x00, 0x00, 0x42, 0x3c, 0x00, 0x00, 0x3a, 0x46, 0x42,
    0x42, 0x42, 0x46, 0x3a, 0x02, 0x02, 0x42, 0x3c, 0x08, 0x08, 0x00, 0x3e,
    0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x3e, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08,
    0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x42, 0x42, 0x40, 0x30,
    0x0c, 0x02, 0x42, 0x42, 0x3c, 0x08, 0x08, 0x30, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x3c, 0x42, 0x40, 0x30, 0x0c, 0x02, 0x42, 0x3c, 0x08, 0x08, 0x30,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x08, 0x08, 0x08,
    0x08, 0x08, 0x00, 0x08, 0x08, 0x00, 0x00, 0x00, 0x00, 0x24, 0x24, 0x24,
    0x24, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x24, 0x24, 0x24, 0x7e, 0x24, 0x24, 0x7e, 0x24, 0x24,
    0x24, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x3e, 0x49, 0x48, 0x48,
    0x3e, 0x09, 0x09, 0x49, 0x3e, 0x08, 0x08, 0x00, 0x00, 0x00, 0x00, 0x31,
    0x4a, 0x4a, 0x34, 0x08, 0x08, 0x16, 0x29, 0x29, 0x46, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x18, 0x24, 0x24, 0x24, 0x18, 0x28, 0x45, 0x42, 0x46,
    0x39, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x08, 0x10, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x08,
    0x08, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x08, 0x08, 0x04, 0x00, 0x00,
    0x00, 0x00, 0x20, 0x10, 0x10, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x10,
    0x10, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x49, 0x2a,
    0x1c, 0x2a, 0x49, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x08, 0x08, 0x08, 0x7f, 0x08, 0x08, 0x08, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08,
    0x08, 0x08, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x7e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x02, 0x02, 0x04, 0x04, 0x08, 0x08, 0x10, 0x10, 0x20,
    0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x42, 0x42, 0x42, 0x4a,
    0x52, 0x42, 0x42, 0x42, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08,
    0x18, 0x28, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x3e, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x3c, 0x42, 0x42, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40,
    0x7e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x42, 0x42, 0x02, 0x1c,
    0x02, 0x02, 0x42, 0x42, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04,
    0x0c, 0x14, 0x24, 0x44, 0x44, 0x7e, 0x04, 0x04, 0x04, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x7e, 0x40, 0x40, 0x40, 0x7c, 0x02, 0x02, 0x02, 0x42,
    0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x20, 0x40, 0x40, 0x7c,
    0x42, 0x42, 0x42, 0x42, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7e,
    0x02, 0x02, 0x04, 0x04, 0x08, 0x08, 0x10, 0x10, 0x10, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x3c, 0x42, 0x42, 0x42, 0x3c, 0x42, 0x42, 0x42, 0x42,
    0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x42, 0x42, 0x42, 0x42,
    0x3e, 0x02, 0x02, 0x04, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x08, 0x08, 0x00, 0x00, 0x00, 0x08, 0x08, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x00, 0x00, 0x00, 0x08,
    0x08, 0x08, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x08, 0x10, 0x20,
    0x40, 0x20, 0x10, 0x08, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x7e, 0x00, 0x00, 0x00, 0x7e, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x20, 0x10, 0x08, 0x04, 0x02, 0x04, 0x08, 0x10,
    0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x42, 0x42, 0x02, 0x04,
    0x08, 0x08, 0x00, 0x08, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1c,
    0x22, 0x4a, 0x56, 0x52, 0x52, 0x52, 0x4e, 0x20, 0x1e, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x18, 0x24, 0x24, 0x42, 0x42, 0x7e, 0x42, 0x42, 0x42,
    0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x42, 0x42, 0x42, 0x7c,
    0x42, 0x42, 0x42, 0x42, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c,
    0x42, 0x42, 0x40, 0x40, 0x40, 0x40, 0x42, 0x42, 0x3c, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x78, 0x44, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x44,
    0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7e, 0x40, 0x40, 0x40, 0x7c,
    0x40, 0x40, 0x40, 0x40, 0x7e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7e,
    0x40, 0x40, 0x40, 0x7c, 0x40, 0x40, 0x40, 0x40, 0x40, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x3c, 0x42, 0x42, 0x40, 0x40, 0x4e, 0x42, 0x42, 0x42,
    0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x42, 0x42, 0x42, 0x42, 0x7e,
    0x42, 0x42, 0x42, 0x42, 0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3e,
    0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x3e, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x1f, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x44, 0x44,
    0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x42, 0x44, 0x48, 0x50, 0x60,
    0x60, 0x50, 0x48, 0x44, 0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40,
    0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x7e, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x41, 0x63, 0x63, 0x55, 0x55, 0x49, 0x49, 0x41, 0x41,
    0x41, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x42, 0x62, 0x62, 0x52, 0x52,
    0x4a, 0x4a, 0x46, 0x46, 0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c,
    0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x3c, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x7c, 0x42, 0x42, 0x42, 0x42, 0x7c, 0x40, 0x40, 0x40,
    0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x42, 0x42, 0x42, 0x42,
    0x42, 0x42, 0x5a, 0x66, 0x3c, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c,
    0x42, 0x42, 0x42, 0x7c, 0x48, 0x44, 0x44, 0x42, 0x42, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x3c, 0x42, 0x42, 0x40, 0x30, 0x0c, 0x02, 0x42, 0x42,
    0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0x08, 0x08, 0x08, 0x08,
    0x08, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x42,
    0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x3c, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x41, 0x41, 0x41, 0x22, 0x22, 0x22, 0x14, 0x14, 0x08,
    0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x41, 0x41, 0x41, 0x49, 0x49,
    0x55, 0x55, 0x63, 0x63, 0x41, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x42,
    0x42, 0x24, 0x24, 0x18, 0x18, 0x24, 0x24, 0x42, 0x42, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x41, 0x41, 0x22, 0x22, 0x14, 0x08, 0x08, 0x08, 0x08,
    0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7e, 0x02, 0x02, 0x04, 0x08,
    0x10, 0x20, 0x40, 0x40, 0x7e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x10,
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x1c, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x20, 0x20, 0x10, 0x10, 0x08, 0x08, 0x04, 0x04, 0x02,
    0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x08, 0x08, 0x08, 0x08, 0x08,
    0x08, 0x08, 0x08, 0x08, 0x08, 0x38, 0x00, 0x00, 0x00, 0x08, 0x14, 0x22,
    0x41, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x7f, 0x00, 0x00, 0x00, 0x10, 0x10, 0x10, 0x08, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x3c, 0x42, 0x02, 0x3e, 0x42, 0x42, 0x46, 0x3a, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x40, 0x40, 0x40, 0x5c, 0x62, 0x42, 0x42, 0x42, 0x42, 0x62,
    0x5c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x42, 0x40,
    0x40, 0x40, 0x40, 0x42, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x02,
    0x02, 0x3a, 0x46, 0x42, 0x42, 0x42, 0x42, 0x46, 0x3a, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x42, 0x42, 0x7e, 0x40, 0x40, 0x42,
    0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x10, 0x10, 0x10, 0x7c, 0x10,
    0x10, 0x10, 0x10, 0x10, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x3a, 0x46, 0x42, 0x42, 0x42, 0x46, 0x3a, 0x02, 0x02, 0x42, 0x3c,
    0x00, 0x00, 0x40, 0x40, 0x40, 0x5c, 0x62, 0x42, 0x42, 0x42, 0x42, 0x42,
    0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x00, 0x18, 0x08, 0x08,
    0x08, 0x08, 0x08, 0x08, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x04,
    0x00, 0x0c, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x44, 0x38,
    0x00, 0x00, 0x40, 0x40, 0x40, 0x44, 0x48, 0x50, 0x60, 0x50, 0x48, 0x44,
    0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x08, 0x08, 0x08, 0x08, 0x08,
    0x08, 0x08, 0x08, 0x08, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x76, 0x49, 0x49, 0x49, 0x49, 0x49, 0x49, 0x49, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x5c, 0x62, 0x42, 0x42, 0x42, 0x42, 0x42,
    0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x42, 0x42,
    0x42, 0x42, 0x42, 0x42, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x5c, 0x62, 0x42, 0x42, 0x42, 0x42, 0x62, 0x5c, 0x40, 0x40, 0x40,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x3a, 0x46, 0x42, 0x42, 0x42, 0x42, 0x46,
    0x3a, 0x02, 0x02, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x5c, 0x62, 0x40,
    0x40, 0x40, 0x40, 0x40, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x3c, 0x42, 0x40, 0x30, 0x0c, 0x02, 0x42, 0x3c, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x10, 0x10, 0x10, 0x10, 0x7c, 0x10, 0x10, 0x10, 0x10, 0x10,
    0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x42, 0x42, 0x42,
    0x42, 0x42, 0x42, 0x46, 0x3a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x41, 0x41, 0x41, 0x22, 0x22, 0x14, 0x14, 0x08, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x41, 0x41, 0x49, 0x49, 0x49, 0x49, 0x49,
    0x36, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x42, 0x42, 0x24,
    0x18, 0x18, 0x24, 0x42, 0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x42, 0x42, 0x42, 0x42, 0x42, 0x46, 0x3a, 0x02, 0x02, 0x42, 0x3c,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x7e, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40,
    0x7e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x08, 0x08, 0x08, 0x08, 0x30,
    0x08, 0x08, 0x08, 0x08, 0x08, 0x06, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08,
    0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00,
    0x00, 0x00, 0x30, 0x08, 0x08, 0x08, 0x08, 0x06, 0x08, 0x08, 0x08, 0x08,
    0x08, 0x30, 0x00, 0x00, 0x00, 0x31, 0x49, 0x46, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x18, 0x3c, 0x3c, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x30, 0x0c, 0x00, 0x18, 0x24, 0x24, 0x42, 0x42, 0x7e, 0x42, 0x42, 0x42,
    0x42, 0x00, 0x00, 0x00, 0x0c, 0x30, 0x00, 0x18, 0x24, 0x24, 0x42, 0x42,
    0x7e, 0x42, 0x42, 0x42, 0x42, 0x00, 0x00, 0x00, 0x18, 0x24, 0x00, 0x18,
    0x24, 0x24, 0x42, 0x42, 0x7e, 0x42, 0x42, 0x42, 0x42, 0x00, 0x00, 0x00,
    0x32, 0x4c, 0x00, 0x18, 0x24, 0x24, 0x42, 0x42, 0x7e, 0x42, 0x42, 0x42,
    0x42, 0x00, 0x00, 0x00, 0x24, 0x24, 0x00, 0x18, 0x24, 0x24, 0x42, 0x42,
    0x7e, 0x42, 0x42, 0x42, 0x42, 0x00, 0x00, 0x00, 0x18, 0x24, 0x24, 0x18,
    0x24, 0x24, 0x42, 0x42, 0x7e, 0x42, 0x42, 0x42, 0x42, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x1f, 0x28, 0x48, 0x48, 0x7e, 0x48, 0x48, 0x48, 0x48,
    0x4f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x42, 0x42, 0x40, 0x40,
    0x40, 0x40, 0x42, 0x42, 0x3c, 0x08, 0x08, 0x30, 0x30, 0x0c, 0x00, 0x7e,
    0x40, 0x40, 0x40, 0x7c, 0x40, 0x40, 0x40, 0x40, 0x7e, 0x00, 0x00, 0x00,
    0x0c, 0x30, 0x00, 0x7e, 0x40, 0x40, 0x40, 0x7c, 0x40, 0x40, 0x40, 0x40,
    0x7e, 0x00, 0x00, 0x00, 0x18, 0x24, 0x00, 0x7e, 0x40, 0x40, 0x40, 0x7c,
    0x40, 0x40, 0x40, 0x40, 0x7e, 0x00, 0x00, 0x00, 0x24, 0x24, 0x00, 0x7e,
    0x40, 0x40, 0x40, 0x7c, 0x40, 0x40, 0x40, 0x40, 0x7e, 0x00, 0x00, 0x00,
    0x30, 0x0c, 0x00, 0x3e, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08,
    0x3e, 0x00, 0x00, 0x00, 0x06, 0x18, 0x00, 0x3e, 0x08, 0x08, 0x08, 0x08,
    0x08, 0x08, 0x08, 0x08, 0x3e, 0x00, 0x00, 0x00, 0x18, 0x24, 0x00, 0x3e,
    0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x3e, 0x00, 0x00, 0x00,
    0x22, 0x22, 0x00, 0x3e, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08,
    0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x44, 0x42, 0x42, 0xf2,
    0x42, 0x42, 0x42, 0x44, 0x78, 0x00, 0x00, 0x00, 0x32, 0x4c, 0x00, 0x42,
    0x62, 0x62, 0x52, 0x52, 0x4a, 0x4a, 0x46, 0x46, 0x42, 0x00, 0x00, 0x00,
    0x30, 0x0c, 0x00, 0x3c, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42,
    0x3c, 0x00, 0x00, 0x00, 0x0c, 0x30, 0x00, 0x3c, 0x42, 0x42, 0x42, 0x42,
    0x42, 0x42, 0x42, 0x42, 0x3c, 0x00, 0x00, 0x00, 0x18, 0x24, 0x00, 0x3c,
    0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x3c, 0x00, 0x00, 0x00,
    0x32, 0x4c, 0x00, 0x3c, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42,
    0x3c, 0x00, 0x00, 0x00, 0x24, 0x24, 0x00, 0x3c, 0x42, 0x42, 0x42, 0x42,
    0x42, 0x42, 0x42, 0x42, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x22, 0x14, 0x08, 0x14, 0x22, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x02, 0x3a, 0x44, 0x46, 0x4a, 0x4a, 0x52, 0x52, 0x62, 0x22,
    0x5c, 0x40, 0x00, 0x00, 0x30, 0x0c, 0x00, 0x42, 0x42, 0x42, 0x42, 0x42,
    0x42, 0x42, 0x42, 0x42, 0x3c, 0x00, 0x00, 0x00, 0x0c, 0x30, 0x00, 0x42,
    0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x3c, 0x00, 0x00, 0x00,
    0x18, 0x24, 0x00, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42,
    0x3c, 0x00, 0x00, 0x00, 0x24, 0x24, 0x00, 0x42, 0x42, 0x42, 0x42, 0x42,
    0x42, 0x42, 0x42, 0x42, 0x3c, 0x00, 0x00, 0x00, 0x06, 0x18, 0x00, 0x41,
    0x41, 0x22, 0x22, 0x14, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x40, 0x40, 0x7c, 0x42, 0x42, 0x42, 0x42, 0x7c, 0x40,
    0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x44, 0x4c, 0x50, 0x50,
    0x4c, 0x42, 0x42, 0x52, 0x4c, 0x00, 0x00, 0x00, 0xaa, 0x55, 0xaa, 0x55,
    0xaa, 0x55, 0xaa, 0x55, 0xaa, 0x55, 0xaa, 0x55, 0xaa, 0x55, 0xaa, 0x55,
    0x00, 0x00, 0x00, 0x08, 0x08, 0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08,
    0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x3e, 0x49, 0x48,
    0x48, 0x48, 0x48, 0x49, 0x3e, 0x08, 0x08, 0x00, 0x00, 0x00, 0x00, 0x1c,
    0x20, 0x20, 0x20, 0x78, 0x20, 0x20, 0x20, 0x22, 0x7e, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x0e, 0x11, 0x20, 0x7e, 0x20, 0x7c, 0x20, 0x11,
    0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x41, 0x41, 0x22, 0x14, 0x08,
    0x3e, 0x08, 0x3e, 0x08, 0x08, 0x00, 0x00, 0x00, 0x24, 0x18, 0x00, 0x3c,
    0x42, 0x42, 0x40, 0x30, 0x0c, 0x02, 0x42, 0x42, 0x3c, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x1c, 0x22, 0x20, 0x18, 0x24, 0x22, 0x22, 0x12, 0x0c, 0x02,
    0x22, 0x1c, 0x00, 0x00, 0x00, 0x24, 0x18, 0x00, 0x00, 0x3c, 0x42, 0x40,
    0x30, 0x0c, 0x02, 0x42, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c,
    0x42, 0x99, 0xa5, 0xa1, 0xa1, 0xa5, 0x99, 0x42, 0x3c, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x38, 0x04, 0x3c, 0x44, 0x3c, 0x00, 0x7c, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x12, 0x24,
    0x48, 0x24, 0x12, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x7e, 0x02, 0x02, 0x02, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x22, 0x1c, 0x22, 0x22, 0x22, 0x1c, 0x22,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x42, 0xb9, 0xa5, 0xa5,
    0xb9, 0xa9, 0xa5, 0x42, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x18, 0x24, 0x24, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x08, 0x7f, 0x08,
    0x08, 0x08, 0x00, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x44,
    0x04, 0x18, 0x20, 0x40, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x38, 0x44, 0x04, 0x38, 0x04, 0x44, 0x38, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x24, 0x18, 0x00, 0x7e, 0x02, 0x02, 0x04, 0x08,
    0x10, 0x20, 0x40, 0x40, 0x7e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x66, 0x5a, 0x40, 0x40, 0x40,
    0x00, 0x00, 0x00, 0x3e, 0x7a, 0x7a, 0x7a, 0x7a, 0x3a, 0x0a, 0x0a, 0x0a,
    0x0a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08,
    0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x24, 0x18, 0x00,
    0x00, 0x7e, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x7e, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x10, 0x30, 0x50, 0x10, 0x10, 0x10, 0x7c, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x44, 0x44, 0x44, 0x38, 0x00,
    0x7c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x48, 0x24, 0x12, 0x24, 0x48, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x37, 0x48, 0x48, 0x48, 0x4e, 0x48, 0x48, 0x48, 0x48,
    0x37, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x36, 0x49, 0x49,
    0x4f, 0x48, 0x48, 0x49, 0x36, 0x00, 0x00, 0x00, 0x22, 0x22, 0x00, 0x41,
    0x41, 0x22, 0x22, 0x14, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x10, 0x10, 0x00, 0x10, 0x10, 0x20, 0x40, 0x42, 0x42,
    0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x08, 0x08,
    0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x08, 0x08, 0x08,
    0x08, 0x08, 0x08, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xf8, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08,
    0x08, 0x08, 0x08, 0x08, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0xf8, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08,
    0x0f, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08,
    0x08, 0x08, 0x08, 0x08, 0xf8, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x08, 0x08, 0x08,
    0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08,
    0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x08, 0x08,
    0x08, 0x08, 0x08, 0x08, 0xff, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08,
    0x88, 0x22, 0x88, 0x22, 0x88, 0x22, 0x88, 0x22, 0x88, 0x22, 0x88, 0x22,
    0x88, 0x22, 0x88, 0x22, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0xff, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14,
    0x14, 0x14, 0x14, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f,
    0x10, 0x17, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0xfc, 0x04, 0xf4, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14,
    0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x17, 0x10, 0x1f, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0xf4,
    0x04, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x14, 0x14, 0x14, 0x14,
    0x14, 0x14, 0x14, 0x17, 0x10, 0x17, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14,
    0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0xf4, 0x04, 0xf4, 0x14, 0x14,
    0x14, 0x14, 0x14, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff,
    0x00, 0xf7, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14,
    0x14, 0x14, 0x14, 0xf7, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0xf7, 0x00, 0xf7, 0x14, 0x14,
    0x14, 0x14, 0x14, 0x14, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x08, 0x1c, 0x2a, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x08, 0x08, 0x2a, 0x1c, 0x08,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x20,
    0x7f, 0x20, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x08, 0x04, 0xfe, 0x04, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x30, 0x0c, 0x00, 0x00, 0x3c, 0x42, 0x02, 0x3e, 0x42, 0x42, 0x46,
    0x3a, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x30, 0x00, 0x00, 0x3c, 0x42, 0x02,
    0x3e, 0x42, 0x42, 0x46, 0x3a, 0x00, 0x00, 0x00, 0x00, 0x18, 0x24, 0x00,
    0x00, 0x3c, 0x42, 0x02, 0x3e, 0x42, 0x42, 0x46, 0x3a, 0x00, 0x00, 0x00,
    0x00, 0x32, 0x4c, 0x00, 0x00, 0x3c, 0x42, 0x02, 0x3e, 0x42, 0x42, 0x46,
    0x3a, 0x00, 0x00, 0x00, 0x00, 0x24, 0x24, 0x00, 0x00, 0x3c, 0x42, 0x02,
    0x3e, 0x42, 0x42, 0x46, 0x3a, 0x00, 0x00, 0x00, 0x18, 0x24, 0x24, 0x18,
    0x00, 0x3c, 0x42, 0x02, 0x3e, 0x42, 0x42, 0x46, 0x3a, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x36, 0x49, 0x09, 0x3f, 0x48, 0x48, 0x49,
    0x36, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x42, 0x40,
    0x40, 0x40, 0x40, 0x42, 0x3c, 0x08, 0x08, 0x30, 0x00, 0x30, 0x0c, 0x00,
    0x00, 0x3c, 0x42, 0x42, 0x7e, 0x40, 0x40, 0x42, 0x3c, 0x00, 0x00, 0x00,
    0x00, 0x0c, 0x30, 0x00, 0x00, 0x3c, 0x42, 0x42, 0x7e, 0x40, 0x40, 0x42,
    0x3c, 0x00, 0x00, 0x00, 0x00, 0x18, 0x24, 0x00, 0x00, 0x3c, 0x42, 0x42,
    0x7e, 0x40, 0x40, 0x42, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x24, 0x24, 0x00,
    0x00, 0x3c, 0x42, 0x42, 0x7e, 0x40, 0x40, 0x42, 0x3c, 0x00, 0x00, 0x00,
    0x00, 0x30, 0x0c, 0x00, 0x00, 0x18, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08,
    0x3e, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x30, 0x00, 0x00, 0x18, 0x08, 0x08,
    0x08, 0x08, 0x08, 0x08, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x18, 0x24, 0x00,
    0x00, 0x18, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x3e, 0x00, 0x00, 0x00,
    0x00, 0x24, 0x24, 0x00, 0x00, 0x18, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08,
    0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x66, 0x18, 0x64, 0x02, 0x3a, 0x46,
    0x42, 0x42, 0x42, 0x42, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x32, 0x4c, 0x00,
    0x00, 0x5c, 0x62, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x00, 0x00, 0x00,
    0x00, 0x30, 0x0c, 0x00, 0x00, 0x3c, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42,
    0x3c, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x30, 0x00, 0x00, 0x3c, 0x42, 0x42,
    0x42, 0x42, 0x42, 0x42, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x18, 0x24, 0x00,
    0x00, 0x3c, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x3c, 0x00, 0x00, 0x00,
    0x00, 0x32, 0x4c, 0x00, 0x00, 0x3c, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42,
    0x3c, 0x00, 0x00, 0x00, 0x00, 0x24, 0x24, 0x00, 0x00, 0x3c, 0x42, 0x42,
    0x42, 0x42, 0x42, 0x42, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x10, 0x10, 0x00, 0x00, 0x7c, 0x00, 0x00, 0x10, 0x10, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x02, 0x3c, 0x46, 0x4a, 0x4a, 0x52, 0x52, 0x62,
    0x3c, 0x40, 0x00, 0x00, 0x00, 0x30, 0x0c, 0x00, 0x00, 0x42, 0x42, 0x42,
    0x42, 0x42, 0x42, 0x46, 0x3a, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x30, 0x00,
    0x00, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x46, 0x3a, 0x00, 0x00, 0x00,
    0x00, 0x18, 0x24, 0x00, 0x00, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x46,
    0x3a, 0x00, 0x00, 0x00, 0x00, 0x24, 0x24, 0x00, 0x00, 0x42, 0x42, 0x42,
    0x42, 0x42, 0x42, 0x46, 0x3a, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x30, 0x00,
    0x00, 0x42, 0x42, 0x42, 0x42, 0x42, 0x46, 0x3a, 0x02, 0x02, 0x42, 0x3c,
    0x00, 0x00, 0x40, 0x40, 0x40, 0x5c, 0x62, 0x42, 0x42, 0x42, 0x42, 0x62,
    0x5c, 0x40, 0x40, 0x40, 0x00, 0x24, 0x24, 0x00, 0x00, 0x42, 0x42, 0x42,
    0x42, 0x42, 0x46, 0x3a, 0x02, 0x02, 0x42, 0x3c, 0xfd, 0xff, 0xff, 0xff,
    0xc0, 0x03, 0xff, 0xff, 0x60, 0x22, 0xff, 0xff, 0x64, 0x22, 0xff, 0xff,
    0x65, 0x22, 0xff, 0xff, 0xa0, 0x25, 0xac, 0x25, 0xae, 0x25, 0xfc, 0x25,
    0xfe, 0x25, 0x1b, 0x2b, 0x0e, 0x22, 0xff, 0xff, 0xc6, 0x25, 0x66, 0x26,
    0x25, 0x2b, 0x27, 0x2b, 0xff, 0xff, 0xbc, 0x00, 0xff, 0xff, 0xbd, 0x00,
    0xff, 0xff, 0xbe, 0x00, 0xff, 0xff, 0xa6, 0x00, 0xff, 0xff, 0xa8, 0x00,
    0xff, 0xff, 0xb8, 0x00, 0xff, 0xff, 0x92, 0x01, 0xff, 0xff, 0x20, 0x20,
    0xff, 0xff, 0x21, 0x20, 0xff, 0xff, 0x30, 0x20, 0xff, 0xff, 0x22, 0x21,
    0xff, 0xff, 0x26, 0x20, 0xff, 0xff, 0x39, 0x20, 0xff, 0xff, 0x3a, 0x20,
    0xff, 0xff, 0x1c, 0x20, 0x1f, 0x20, 0x36, 0x20, 0xff, 0xff, 0x1d, 0x20,
    0xba, 0x02, 0xdd, 0x02, 0xee, 0x02, 0x33, 0x20, 0xff, 0xff, 0x1e, 0x20,
    0xff, 0xff, 0x42, 0x2e, 0xff, 0xff, 0x41, 0x2e, 0xce, 0x02, 0xff, 0xff,
    0x1e, 0x01, 0xff, 0xff, 0x1f, 0x01, 0xff, 0xff, 0x30, 0x01, 0xff, 0xff,
    0x31, 0x01, 0xff, 0xff, 0x5e, 0x01, 0xff, 0xff, 0x5f, 0x01, 0xff, 0xff,
    0x20, 0x00, 0xa0, 0x00, 0x00, 0x20, 0x01, 0x20, 0x02, 0x20, 0x03, 0x20,
    0x04, 0x20, 0x05, 0x20, 0x06, 0x20, 0x07, 0x20, 0x08, 0x20, 0x09, 0x20,
    0x0a, 0x20, 0x2f, 0x20, 0x5f, 0x20, 0xff, 0xff, 0x21, 0x00, 0xff, 0xff,
    0x22, 0x00, 0xff, 0xff, 0x23, 0x00, 0xff, 0xff, 0x24, 0x00, 0xff, 0xff,
    0x25, 0x00, 0xff, 0xff, 0x26, 0x00, 0xff, 0xff, 0x27, 0x00, 0xb4, 0x00,
    0xb9, 0x02, 0xbc, 0x02, 0xca, 0x02, 0x19, 0x20, 0x32, 0x20, 0xff, 0xff,
    0x28, 0x00, 0xff, 0xff, 0x29, 0x00, 0xff, 0xff, 0x2a, 0x00, 0x4e, 0x20,
    0x17, 0x22, 0xff, 0xff, 0x2b, 0x00, 0xff, 0xff, 0x2c, 0x00, 0xcf, 0x02,
    0x1a, 0x20, 0xff, 0xff, 0x2d, 0x00, 0xad, 0x00, 0x10, 0x20, 0x11, 0x20,
    0x12, 0x20, 0x13, 0x20, 0x43, 0x20, 0x12, 0x22, 0xff, 0xff, 0x2e, 0x00,
    0x24, 0x20, 0xff, 0xff, 0x2f, 0x00, 0x44, 0x20, 0x15, 0x22, 0xff, 0xff,
    0x30, 0x00, 0xff, 0xff, 0x31, 0x00, 0xff, 0xff, 0x32, 0x00, 0xff, 0xff,
    0x33, 0x00, 0xff, 0xff, 0x34, 0x00, 0xff, 0xff, 0x35, 0x00, 0xff, 0xff,
    0x36, 0x00, 0xff, 0xff, 0x37, 0x00, 0xff, 0xff, 0x38, 0x00, 0xff, 0xff,
    0x39, 0x00, 0xff, 0xff, 0x3a, 0x00, 0x36, 0x22, 0xff, 0xff, 0x3b, 0x00,
    0xff, 0xff, 0x3c, 0x00, 0xff, 0xff, 0x3d, 0x00, 0x40, 0x2e, 0xff, 0xff,
    0x3e, 0x00, 0xff, 0xff, 0x3f, 0x00, 0xff, 0xff, 0x40, 0x00, 0xff, 0xff,
    0x41, 0x00, 0xff, 0xff, 0x42, 0x00, 0xff, 0xff, 0x43, 0x00, 0xff, 0xff,
    0x44, 0x00, 0xff, 0xff, 0x45, 0x00, 0xff, 0xff, 0x46, 0x00, 0xff, 0xff,
    0x47, 0x00, 0xff, 0xff, 0x48, 0x00, 0xff, 0xff, 0x49, 0x00, 0xff, 0xff,
    0x4a, 0x00, 0xff, 0xff, 0x4b, 0x00, 0x2a, 0x21, 0xff, 0xff, 0x4c, 0x00,
    0xff, 0xff, 0x4d, 0x00, 0xff, 0xff, 0x4e, 0x00, 0xff, 0xff, 0x4f, 0x00,
    0xff, 0xff, 0x50, 0x00, 0xff, 0xff, 0x51, 0x00, 0xff, 0xff, 0x52, 0x00,
    0xff, 0xff, 0x53, 0x00, 0xff, 0xff, 0x54, 0x00, 0xff, 0xff, 0x55, 0x00,
    0xff, 0xff, 0x56, 0x00, 0xff, 0xff, 0x57, 0x00, 0xff, 0xff, 0x58, 0x00,
    0xff, 0xff, 0x59, 0x00, 0xff, 0xff, 0x5a, 0x00, 0xff, 0xff, 0x5b, 0x00,
    0xff, 0xff, 0x5c, 0x00, 0xf5, 0x29, 0xff, 0xff, 0x5d, 0x00, 0xff, 0xff,
    0x5e, 0x00, 0xc4, 0x02, 0xc6, 0x02, 0x03, 0x23, 0xff, 0xff, 0x5f, 0x00,
    0xff, 0xff, 0x60, 0x00, 0xbb, 0x02, 0xbd, 0x02, 0xcb, 0x02, 0x18, 0x20,
    0x1b, 0x20, 0x35, 0x20, 0xff, 0xff, 0x61, 0x00, 0xff, 0xff, 0x62, 0x00,
    0xff, 0xff, 0x63, 0x00, 0xff, 0xff, 0x64, 0x00, 0xff, 0xff, 0x65, 0x00,
    0xff, 0xff, 0x66, 0x00, 0xff, 0xff, 0x67, 0x00, 0xff, 0xff, 0x68, 0x00,
    0xff, 0xff, 0x69, 0x00, 0xff, 0xff, 0x6a, 0x00, 0xff, 0xff, 0x6b, 0x00,
    0xff, 0xff, 0x6c, 0x00, 0xff, 0xff, 0x6d, 0x00, 0xff, 0xff, 0x6e, 0x00,
    0xff, 0xff, 0x6f, 0x00, 0xff, 0xff, 0x70, 0x00, 0xff, 0xff, 0x71, 0x00,
    0xff, 0xff, 0x72, 0x00, 0xff, 0xff, 0x73, 0x00, 0xff, 0xff, 0x74, 0x00,
    0xff, 0xff, 0x75, 0x00, 0xff, 0xff, 0x76, 0x00, 0xff, 0xff, 0x77, 0x00,
    0xff, 0xff, 0x78, 0x00, 0xff, 0xff, 0x79, 0x00, 0xff, 0xff, 0x7a, 0x00,
    0xff, 0xff, 0x7b, 0x00, 0xff, 0xff, 0x7c, 0x00, 0x23, 0x22, 0xff, 0xff,
    0x7d, 0x00, 0xff, 0xff, 0x7e, 0x00, 0xdc, 0x02, 0xff, 0xff, 0x22, 0x20,
    0x19, 0x22, 0xcf, 0x25, 0xff, 0xff, 0xc0, 0x00, 0xff, 0xff, 0xc1, 0x00,
    0xff, 0xff, 0xc2, 0x00, 0xff, 0xff, 0xc3, 0x00, 0xff, 0xff, 0xc4, 0x00,
    0xff, 0xff, 0xc5, 0x00, 0x2b, 0x21, 0xff, 0xff, 0xc6, 0x00, 0xff, 0xff,
    0xc7, 0x00, 0xff, 0xff, 0xc8, 0x00, 0xff, 0xff, 0xc9, 0x00, 0xff, 0xff,
    0xca, 0x00, 0xff, 0xff, 0xcb, 0x00, 0xff, 0xff, 0xcc, 0x00, 0xff, 0xff,
    0xcd, 0x00, 0xff, 0xff, 0xce, 0x00, 0xff, 0xff, 0xcf, 0x00, 0xff, 0xff,
    0xd0, 0x00, 0x10, 0x01, 0xff, 0xff, 0xd1, 0x00, 0xff, 0xff, 0xd2, 0x00,
    0xff, 0xff, 0xd3, 0x00, 0xff, 0xff, 0xd4, 0x00, 0xff, 0xff, 0xd5, 0x00,
    0xff, 0xff, 0xd6, 0x00, 0xff, 0xff, 0xd7, 0x00, 0xff, 0xff, 0xd8, 0x00,
    0xff, 0xff, 0xd9, 0x00, 0xff, 0xff, 0xda, 0x00, 0xff, 0xff, 0xdb, 0x00,
    0xff, 0xff, 0xdc, 0x00, 0xff, 0xff, 0xdd, 0x00, 0xff, 0xff, 0xde, 0x00,
    0xff, 0xff, 0xdf, 0x00, 0xff, 0xff, 0x92, 0x25, 0xff, 0xff, 0xa1, 0x00,
    0xff, 0xff, 0xa2, 0x00, 0xff, 0xff, 0xa3, 0x00, 0xff, 0xff, 0xac, 0x20,
    0xff, 0xff, 0xa5, 0x00, 0xff, 0xff, 0x60, 0x01, 0xff, 0xff, 0xa7, 0x00,
    0xff, 0xff, 0x61, 0x01, 0xff, 0xff, 0xa9, 0x00, 0xff, 0xff, 0xaa, 0x00,
    0xff, 0xff, 0xab, 0x00, 0xff, 0xff, 0xac, 0x00, 0xff, 0xff, 0xa4, 0x00,
    0xff, 0xff, 0xae, 0x00, 0xff, 0xff, 0xaf, 0x00, 0xc9, 0x02, 0xff, 0xff,
    0xb0, 0x00, 0xda, 0x02, 0xff, 0xff, 0xb1, 0x00, 0xff, 0xff, 0xb2, 0x00,
    0xff, 0xff, 0xb3, 0x00, 0xff, 0xff, 0x7d, 0x01, 0xff, 0xff, 0xb5, 0x00,
    0xbc, 0x03, 0xff, 0xff, 0xb6, 0x00, 0xff, 0xff, 0xb7, 0x00, 0x27, 0x20,
    0xc5, 0x22, 0x31, 0x2e, 0xff, 0xff, 0x7e, 0x01, 0xff, 0xff, 0xb9, 0x00,
    0xff, 0xff, 0xba, 0x00, 0xff, 0xff, 0xbb, 0x00, 0xff, 0xff, 0x52, 0x01,
    0xff, 0xff, 0x53, 0x01, 0xff, 0xff, 0x78, 0x01, 0xff, 0xff, 0xbf, 0x00,
    0xff, 0xff, 0x00, 0x25, 0x14, 0x20, 0x15, 0x20, 0xaf, 0x23, 0xff, 0xff,
    0x02, 0x25, 0xff, 0xff, 0x0c, 0x25, 0x6d, 0x25, 0xff, 0xff, 0x10, 0x25,
    0x6e, 0x25, 0xff, 0xff, 0x14, 0x25, 0x70, 0x25, 0xff, 0xff, 0x18, 0x25,
    0x6f, 0x25, 0xff, 0xff, 0x1c, 0x25, 0xff, 0xff, 0x24, 0x25, 0xff, 0xff,
    0x2c, 0x25, 0xff, 0xff, 0x34, 0x25, 0xff, 0xff, 0x3c, 0x25, 0xff, 0xff,
    0x91, 0x25, 0xff, 0xff, 0xba, 0x23, 0x3e, 0x20, 0xff, 0xff, 0xbb, 0x23,
    0xff, 0xff, 0xbc, 0x23, 0xff, 0xff, 0xbd, 0x23, 0xff, 0xff, 0x50, 0x25,
    0x01, 0x25, 0xff, 0xff, 0x51, 0x25, 0x03, 0x25, 0xff, 0xff, 0x54, 0x25,
    0x0f, 0x25, 0xff, 0xff, 0x57, 0x25, 0x13, 0x25, 0xff, 0xff, 0x5a, 0x25,
    0x17, 0x25, 0xff, 0xff, 0x5d, 0x25, 0x1b, 0x25, 0xff, 0xff, 0x60, 0x25,
    0x23, 0x25, 0xff, 0xff, 0x63, 0x25, 0x2b, 0x25, 0xff, 0xff, 0x66, 0x25,
    0x33, 0x25, 0xff, 0xff, 0x69, 0x25, 0x3b, 0x25, 0xff, 0xff, 0x6c, 0x25,
    0x4b, 0x25, 0xff, 0xff, 0x88, 0x25, 0xff, 0xff, 0x91, 0x21, 0xff, 0xff,
    0x93, 0x21, 0xff, 0xff, 0x90, 0x21, 0xff, 0xff, 0x92, 0x21, 0xff, 0xff,
    0xe0, 0x00, 0xff, 0xff, 0xe1, 0x00, 0xff, 0xff, 0xe2, 0x00, 0xff, 0xff,
    0xe3, 0x00, 0xff, 0xff, 0xe4, 0x00, 0xff, 0xff, 0xe5, 0x00, 0xff, 0xff,
    0xe6, 0x00, 0xff, 0xff, 0xe7, 0x00, 0xff, 0xff, 0xe8, 0x00, 0xff, 0xff,
    0xe9, 0x00, 0xff, 0xff, 0xea, 0x00, 0xff, 0xff, 0xeb, 0x00, 0xff, 0xff,
    0xec, 0x00, 0xff, 0xff, 0xed, 0x00, 0xff, 0xff, 0xee, 0x00, 0xff, 0xff,
    0xef, 0x00, 0xff, 0xff, 0xf0, 0x00, 0xff, 0xff, 0xf1, 0x00, 0xff, 0xff,
    0xf2, 0x00, 0xff, 0xff, 0xf3, 0x00, 0xff, 0xff, 0xf4, 0x00, 0xff, 0xff,
    0xf5, 0x00, 0xff, 0xff, 0xf6, 0x00, 0xff, 0xff, 0xf7, 0x00, 0xff, 0xff,
    0xf8, 0x00, 0xff, 0xff, 0xf9, 0x00, 0xff, 0xff, 0xfa, 0x00, 0xff, 0xff,
    0xfb, 0x00, 0xff, 0xff, 0xfc, 0x00, 0xff, 0xff, 0xfd, 0x00, 0xff, 0xff,
    0xfe, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff};

void Console::ScrollUp()
{
    for (int y = 0; y < framebuf.Height - 16; y++)
    {
        for (int x = 0; x < framebuf.Width; x++)
        {
            uint32_t color = framebuf.GetPixel(x, y + 16);
            framebuf.SetPixel(x, y, color);
        }
    }

    for (int i = 0; i < 0 + framebuf.Width; i++)
    {
        for (int j = framebuf.Height - 15; j < framebuf.Height - 16 + 16; j++)
        {
            framebuf.SetPixel(i, j, 0x00000000);
        }
    }
}

void Console::Init(Framebuffer f)
{
    framebuf = f;
}

void Console::Reset()
{
    termx = 0;
    termy = 0;
    term_color = 0xFFFFFF;
}

void Console::PrintChar(char c)
{
    if (framebuf.UseDoubleBuffer)
    {
        return;
    }

    if (c == '\n')
    {
        termx = 0;
        termy += 16;
    }
    if (termx >= framebuf.Width)
    {
        termx = 0;
        termy += 16;
    }

    if (termy >= framebuf.Height)
    {
        ScrollUp();
        termy -= 16;
    }

    if (c != '\n')
    {
        //draw_char(c, term_x, term_y, term_color); 
        
        uint8_t *offset = font + sizeof(PsfFontHeader) + 16 * c;

        for (int i = 0; i < 16; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                if (offset[i] & (1 << j))
                {
                    framebuf.SetPixel(termx + 8 - j, termy + i, term_color);
                }
            }
        }
        termx += 8;
    }
}

void Console::Print(char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        PrintChar(str[i]);
    }
}

void Console::PrintFormatted(char *str, ...)
{
    if (framebuf.UseDoubleBuffer)
    {
        return;
    }
    va_list args;
    va_start(args, str);

    char buffer[256];

    for (const char *p = str; *p != '\0'; p++)
    {
        if (*p != '%')
        {
            PrintChar(*p);
            continue;
        }

        switch (*++p)
        {
        case 'c':
            PrintChar(va_arg(args, int));
            break;
        case 'd':
            Lib::IToString(va_arg(args, int), buffer, 10);
            for (char *p = buffer; *p != '\0'; p++)
                PrintChar(*p);
            break;
        case 'u':
            Lib::UToString(va_arg(args, unsigned int), buffer, 10);
            for (char *p = buffer; *p != '\0'; p++)
                PrintChar(*p);
            break;
        case 'x':
            Lib::UToString(va_arg(args, unsigned int), buffer, 16);
            for (char *p = buffer; *p != '\0'; p++)
                PrintChar(*p);
            break;
        case 's':
            for (char *p = va_arg(args, char *); *p != '\0'; p++)
                PrintChar(*p);
            break;
        case 'l':
            switch (*++p)
            {
            case 'l':
                switch (*++p)
                {
                case 'u':
                    Lib::UlliToString(va_arg(args, unsigned long long int), buffer, 10);
                    for (char *p = buffer; *p != '\0'; p++)
                        PrintChar(*p);
                    break;
                case 'x':
                    Lib::UlliToString(va_arg(args, unsigned long long int), buffer, 16);
                    for (char *p = buffer; *p != '\0'; p++)
                        PrintChar(*p);
                    break;
                }
                break;
            case 'd':
                Lib::IToString(va_arg(args, long int), buffer, 10);
                for (char *p = buffer; *p != '\0'; p++)
                    PrintChar(*p);
                break;
            case 'u':
                Lib::UToString(va_arg(args, unsigned long int), buffer, 10);
                for (char *p = buffer; *p != '\0'; p++)
                    PrintChar(*p);
                break;
            case 'x':
                Lib::UToString(va_arg(args, unsigned long int), buffer, 16);
                for (char *p = buffer; *p != '\0'; p++)
                    PrintChar(*p);
                break;
            }
            break;

        case 'p':
            Lib::UToString(va_arg(args, uintptr_t), buffer, 16);
            for (char *p = buffer; *p != '\0'; p++)
                PrintChar(*p);
            break;
        }
    }

    va_end(args);
}

}