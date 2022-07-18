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

#ifndef _SSV_SKB_H_
#define _SSV_SKB_H_

#include <linux/skbuff.h>
#include <ssv6xxx_common.h>

#ifdef CONFIG_THROUGHPUT_PROFILE
enum SSV_TP_PRO_TIME{
	E_SSV_TP_PRO_T_START,
	E_SSV_TP_PRO_T_AMPDU,
	E_SSV_TP_PRO_T_IF_SEND,
	E_SSV_TP_PRO_T_TX_STATUS,
	E_SSV_TP_PRO_T_RATE_RPT_RECV,
	E_SSV_TP_PRO_T_RATE_RPT,
	E_SSV_TP_PRO_T_BA_RECV,
	E_SSV_TP_PRO_T_BA,
	E_SSV_TP_PRO_T_RX_RECV,
	E_SSV_TP_PRO_T_RX_DONE,
	E_SSV_TP_PRO_T_FREE,
	E_SSV_TP_PRO_NUM,
};
#endif
/*
 * SSV private header for MPDU in SKB
 */
struct SKB_info_st
{
    struct ieee80211_sta       *sta;
    u16                         mpdu_retry_counter;
    unsigned long               aggr_timestamp;
    u16                         ampdu_tx_status;
    u16                         ampdu_tx_final_retry_count;
    u16                         lowest_rate;                 // Lowest retry rate.
    struct fw_rc_retry_params   rates[SSV62XX_TX_MAX_RATES]; // Retry rates of this AMPDU.
#ifdef CONFIG_THROUGHPUT_PROFILE
	ktime_t tp_ts[E_SSV_TP_PRO_NUM];
#endif
    bool                        directly_ack;
    bool                        no_update_rpt;
    bool                        mpdu_tx_frame;
    bool                        txtput_frame;
};

typedef struct SKB_info_st      SKB_info;
typedef struct SKB_info_st     *p_SKB_info;


/*
 * SSV private header for A-MPDU in SKB
 */
// Header to keep tracking status of early aggregated AMPDU.
struct ampdu_hdr_st
{
    u32                        first_sn;
    struct sk_buff_head        mpdu_q;   // Aggreated MPDU queue. To keep track them during aggregation before send to HCI Q.
    u32                        max_size; // Maximum aggregated size allowed in this AMPDU according to the rate of the first MPDU.
    u32                        size;     // Current aggregated size.
    struct AMPDU_TID_st       *ampdu_tid;
    struct ieee80211_sta      *sta;
    u16                        mpdu_num;
    u16                        ssn[MAX_AGGR_NUM];
    struct fw_rc_retry_params  rates[SSV62XX_TX_MAX_RATES]; // Retry rates of this AMPDU.
};


// SSV device application layer skb allocation/free functions.
struct sk_buff *ssv_skb_alloc(void *app_param, s32 len);
struct sk_buff *ssv_skb_alloc_ex(void *app_param, s32 len, gfp_t gfp_mask);
void ssv_skb_free(void *app_param, struct sk_buff *skb);

#endif // __SSV_SKB_H__
