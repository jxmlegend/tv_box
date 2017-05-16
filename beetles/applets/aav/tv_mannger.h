/*
*********************************************************************************************************
*											        ePDK
*						            the Easy Portable/Player Develop Kits
*									           LARK sample
*
*						        (c) Copyright 2006-2007, terry, China
*											All	Rights Reserved
*
* File    : dsk_radio_p.h
* By      : terry.zeng
* Version : V1.00
*********************************************************************************************************
*/

#ifndef __DSK_TV_MANNGER_H__
#define __DSK_TV_MANNGER_H__

#include "apps.h"


typedef signed char			  s8;
typedef signed char			  __s8;
typedef signed char		      int8;
                              
typedef unsigned char		  u8;
typedef unsigned char		  __u8;
typedef unsigned char		  uint8;
                              
                              
typedef short int			  s16;
typedef short int			  __s16;
typedef short int			  int16;
                              
typedef unsigned short		  u16;
typedef unsigned short		  __u16;
typedef unsigned short		  uint16;
                              
typedef int					  s32;
typedef int					  __s32;
typedef int					  int32;
                              
typedef unsigned int		  u32;
typedef unsigned int		  __u32;
typedef unsigned int		  uint32;

typedef enum
{	
	TV_IMAGE_MODE_CUSTOM,
	TV_IMAGE_MODE_BRIGHT,
	TV_IMAGE_MODE_STANDARD,
	TV_IMAGE_MODE_MILD,
}tv_image_mode_t;

typedef struct {
	__u32				bright;
	__u32				contrast;
	__u32				color;
}tv_image_mode_data_t;
	
/*                            
typedef unsigned long long	  u64;
typedef unsigned long long	  __u64;
typedef unsigned long long	  uint64;
                              
typedef signed long long	  s64;
typedef signed long long	  __s64;
typedef signed long long	  int64;
*/

typedef int32                 __Bool;

extern __pCBK_t volatile  cb_search_success;
extern void   * volatile  cb_ctx_search_success;

extern __pCBK_t volatile  cb_search_fail;
extern void   * volatile  cb_ctx_search_fail;

extern __pCBK_t volatile  cb_search_over;
extern void * volatile  cb_ctx_search_over;

#define FREQ_LOW_BAND_VALUE			  44250000
#define FREQ_TOP_BAND_VALUE 			878250000			//878250000
#define FREQ_MIN_OFFSET_VALUE			250000

__u32 dsk_tv_rcv_open(void);
void TVSearchNextChannel(void);
void TVSearchPreChannel(void);
void TvSearchChannel(__u32 tvsys);

__s32 dsk_tv_rcv_save_search_result(void);
__s32 dsk_tv_rcv_pre_freq_play(void);
__s32 dsk_tv_rcv_next_freq_play(void);
__s32 dsk_tv_rcv_save_search_result(void);
__s32 dsk_tv_rcv_save_image_mode(void);
__s32 dsk_tv_rcv_get_sd_data(void);
__s32 dsk_tv_rcv_curchafornum_play(__u32 num);
__s32 dsk_tv_rcv_cur_channelnum(void);
__s32 SetDatato2137(__u32 frep);
void dsk_tv_set_cur_bright(void);
void dsk_tv_set_sourceInput(__u32 flag);
__s32 SetSoundDatato2137(void);
__s32 SetColorDatato2137(void);
void dsk_tv_SetTvSys(void);
void dsk_tv_SetC500VideoSys(void);

void dsk_tv_set_cur_contrast(void);
void dsk_tv_set_cur_color(void);
void dsk_tv_set_image_mode(tv_image_mode_t mode);
void dsk_tv_finerFreq(__u32 flag);
void Get2137PllData(void);
#endif