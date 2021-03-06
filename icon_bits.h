#ifndef __ICON_BITS_H__
#define __ICON_BITS_H__

/** Shown on boot */
#define happy_mac_width 32
#define happy_mac_height 32
const uint8_t happy_mac_bits[] = {
    0xE0, 0xFF, 0xFF, 0x03, 0x10, 0x00, 0x00, 0x04, 0x08, 0x00, 0x00, 0x08, 
    0x88, 0xFF, 0x7F, 0x08, 0x48, 0x00, 0x80, 0x08, 0x48, 0x00, 0x80, 0x08, 
    0x48, 0x00, 0x80, 0x08, 0x48, 0x88, 0x84, 0x08, 0x48, 0x88, 0x84, 0x08, 
    0x48, 0x80, 0x80, 0x08, 0x48, 0x80, 0x80, 0x08, 0x48, 0xC0, 0x80, 0x08, 
    0x48, 0x00, 0x80, 0x08, 0x48, 0x10, 0x82, 0x08, 0x48, 0xE0, 0x81, 0x08, 
    0x48, 0x00, 0x80, 0x08, 0x48, 0x00, 0x80, 0x08, 0x88, 0xFF, 0x7F, 0x08, 
    0x08, 0x00, 0x00, 0x08, 0x08, 0x00, 0x00, 0x08, 0x08, 0x00, 0x00, 0x08, 
    0x08, 0x00, 0x00, 0x08, 0x08, 0x00, 0xFC, 0x08, 0xC8, 0x00, 0x00, 0x08, 
    0x08, 0x00, 0x00, 0x08, 0x08, 0x00, 0x00, 0x08, 0x08, 0x00, 0x00, 0x08, 
    0xF0, 0xFF, 0xFF, 0x07, 0x10, 0x00, 0x00, 0x04, 0x10, 0x00, 0x00, 0x04, 
    0x10, 0x00, 0x00, 0x04, 0xF0, 0xFF, 0xFF, 0x07
};

/** Shown when whatever goes wrong (DHCP failed, MQTT connect failed, ...) */
#define sad_mac_width 32
#define sad_mac_height 32
const uint8_t sad_mac_bits[] = {
    0xE0, 0xFF, 0xFF, 0x03, 0x10, 0x00, 0x00, 0x04, 0x08, 0x00, 0x00, 0x08, 
    0x88, 0xFF, 0x7F, 0x08, 0x48, 0x00, 0x80, 0x08, 0x48, 0x00, 0x80, 0x08, 
    0x48, 0x0A, 0x94, 0x08, 0x48, 0x04, 0x88, 0x08, 0x48, 0x0A, 0x94, 0x08, 
    0x48, 0x00, 0x80, 0x08, 0x48, 0x20, 0x81, 0x08, 0x48, 0xC0, 0x80, 0x08, 
    0x48, 0x00, 0x80, 0x08, 0x48, 0xE0, 0x83, 0x08, 0x48, 0x10, 0x8C, 0x08, 
    0x48, 0x00, 0x90, 0x08, 0x48, 0x00, 0x80, 0x08, 0x88, 0xFF, 0x7F, 0x08, 
    0x08, 0x00, 0x00, 0x08, 0x08, 0x00, 0x00, 0x08, 0x08, 0x00, 0x00, 0x08, 
    0x08, 0x00, 0x00, 0x08, 0x08, 0x00, 0xFC, 0x08, 0xC8, 0x00, 0x00, 0x08, 
    0x08, 0x00, 0x00, 0x08, 0x08, 0x00, 0x00, 0x08, 0x08, 0x00, 0x00, 0x08, 
    0xF0, 0xFF, 0xFF, 0x07, 0x10, 0x00, 0x00, 0x04, 0x10, 0x00, 0x00, 0x04, 
    0x10, 0x00, 0x00, 0x04, 0xF0, 0xFF, 0xFF, 0x07
};

#if 0
/** This is just because I am a sucker for old C64 stuff... */
#define commodore_balloon_width 16
#define commodore_balloon_height 21
const t commodore_balloon_bits[] = {
  0xF0, 0x07, 0xFC, 0x1F, 0xFE, 0x3F, 0x3E, 0x3F, 0xDF, 0x7C, 0xDF, 0x7F, 
  0xDF, 0x7C, 0x3E, 0x3F, 0xFE, 0x3F, 0xFE, 0x3F, 0xFA, 0x2F, 0xF4, 0x17, 
  0xE4, 0x13, 0xC8, 0x09, 0xC8, 0x09, 0x90, 0x04, 0x90, 0x04, 0xE0, 0x03, 
  0xE0, 0x03, 0xE0, 0x03, 0xC0, 0x01
};
#endif

#endif // __ICON_BITS_H__
