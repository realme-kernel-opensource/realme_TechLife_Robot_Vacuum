/*
 * Copyright (c) 2015 iComm-semi Ltd.
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#ifndef _INIT_H_
#define _INIT_H_

int ssv6xxx_init_mac(struct ssv_hw *sh);

void ssv6xxx_deinit_mac(struct ssv_softc *sc);
void ssv6xxx_restart_hw(struct work_struct *work);

void ssv6xxx_umac_hci_start(char *driver_name, char *device_name);
void ssv6xxx_umac_test(char *driver_name, char *device_name, struct sk_buff *skb, int size);
void ssv6xxx_umac_reg_read(char *driver_name, char *device_name, u32 addr, u32 *regval);
void ssv6xxx_umac_reg_write(char *driver_name, char *device_name, u32 addr, u32 value);
void ssv6xxx_umac_tx_frame(char *driver_name, char *device_name, struct sk_buff *skb);
int ssv6xxx_umac_attach(char *driver_name, char *device_name, struct ssv6xxx_umac_ops *umac_ops);
int ssv6xxx_umac_deattach(char *driver_name, char *device_name);

#if defined(CONFIG_SMARTLINK) || defined(CONFIG_SSV_SUPPORT_ANDROID)
struct ssv_softc *ssv6xxx_driver_attach(char *driver_name);
#endif

#define SSV_NEED_SW_CIPHER(_sh)                 HAL_NEED_SW_CIPHER(_sh)
#define SSV_SET_RF_ENABLE(_sc)                  HAL_SET_RF_ENABLE(_sc, true)
#define SSV_SET_RF_DISABLE(_sc)                 HAL_SET_RF_ENABLE(_sc, false)
#define SSV_SET_ON3_ENABLE(_sh, _val)           HAL_SET_ON3_ENABLE(_sh, _val)
#define SSV_GET_FW_NAME(_sh, _name)             HAL_GET_FW_NAME(_sh, _name)
#define SSV_FLASH_READ_ALL_MAP(_sh)             HAL_FLASH_READ_ALL_MAP(_sh)

#if (defined(CONFIG_SSV_SUPPORT_ANDROID)||defined(CONFIG_SSV_BUILD_AS_ONE_KO))
int ssv6xxx_init(void);
void ssv6xxx_exit(void);
#endif
#endif
