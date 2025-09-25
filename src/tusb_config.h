#ifndef _TUSB_CONFIG_H_
#define _TUSB_CONFIG_H_

#ifdef __cplusplus
 extern "C" {
#endif

#define CFG_TUSB_MCU             OPT_MCU_RP2040
#define BOARD_TUD_RHPORT         0

#define CFG_TUSB_RHPORT0_MODE    (OPT_MODE_DEVICE | OPT_MODE_FULL_SPEED)
#define CFG_TUSB_OS              OPT_OS_NONE

#define CFG_TUD_ENDPOINT0_SIZE   64

// Enable only the Mass Storage Class (MSC)
#define CFG_TUD_CDC              0
#define CFG_TUD_MSC              1
#define CFG_TUD_HID              0
#define CFG_TUD_MIDI             0
#define CFG_TUD_VENDOR           0

#ifdef __cplusplus
 }
#endif

#endif /* _TUSB_CONFIG_H_ */
