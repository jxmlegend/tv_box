/*
********************************************************************************
*                                    eMOD
*                   the Easy Portable/Player Develop Kits
*                               mod_herb sub-system
*                          vdrv encode framework module
*
*          (c) Copyright 2009-2010, Allwinner Microelectronic Co., Ltd.
*                              All Rights Reserved
*
* File   : cvr_watermark.c
* Version: V1.0
* By     : xiechr
* Date   : 2011-07-12
********************************************************************************
*/

#include "cvr_watermark.h"

static __u32                    pic_cnt;
__lotus_overlay_pic_info_t*     pic_info_640;       // 时间水印资源
__lotus_overlay_pic_info_t*     pic_info_1280;       // 时间水印资源

static __u8*    over_pixel_640[OVERLAY_MAX_SRC_INGROUP];
static __u8*    over_pixel_1280[OVERLAY_MAX_SRC_INGROUP];

static __u32    mark_res_640[OVERLAY_MAX_SRC_INGROUP] = {ID_DV_VGA_WATER_MARK_0_BMP, ID_DV_VGA_WATER_MARK_1_BMP, ID_DV_VGA_WATER_MARK_2_BMP,
                ID_DV_VGA_WATER_MARK_3_BMP, ID_DV_VGA_WATER_MARK_4_BMP, ID_DV_VGA_WATER_MARK_5_BMP, ID_DV_VGA_WATER_MARK_6_BMP, 
                ID_DV_VGA_WATER_MARK_7_BMP, ID_DV_VGA_WATER_MARK_8_BMP, ID_DV_VGA_WATER_MARK_9_BMP, ID_DV_VGA_WATER_MARK_MAOHAO_BMP, 
                ID_DV_VGA_WATER_MARK_DEC_BMP, ID_DV_VGA_WATER_MARK_BLANK_BMP};
static __u32    mark_res_1280[OVERLAY_MAX_SRC_INGROUP] = {ID_DV_720_WATER_MARK_0_BMP, ID_DV_720_WATER_MARK_1_BMP, ID_DV_720_WATER_MARK_2_BMP,
                ID_DV_720_WATER_MARK_3_BMP, ID_DV_720_WATER_MARK_4_BMP, ID_DV_720_WATER_MARK_5_BMP, ID_DV_720_WATER_MARK_6_BMP, 
                ID_DV_720_WATER_MARK_7_BMP, ID_DV_720_WATER_MARK_8_BMP, ID_DV_720_WATER_MARK_9_BMP, ID_DV_720_WATER_MARK_MAOHAO_BMP, 
                ID_DV_720_WATER_MARK_DEC_BMP, ID_DV_720_WATER_MARK_BLANK_BMP};

static  void __cvr_res_get(__u32 res_id, void * buf, __u32 buf_len)
{
    char*       res_data;
    HTHEME       icon_hdle;

    icon_hdle   = dsk_theme_open(res_id);
    res_data    = dsk_theme_hdl2buf(icon_hdle);
    
    eLIBs_memcpy(buf, res_data + 56, buf_len);
    
    dsk_theme_close(icon_hdle);
}

void    cvr_water_mark_res_init(void)
{
    __u32   i, len;

    pic_cnt = 13;
    pic_info_640 = esMEMS_Balloc(pic_cnt * sizeof(__lotus_overlay_pic_info_t));
    pic_info_1280 = esMEMS_Balloc(pic_cnt * sizeof(__lotus_overlay_pic_info_t));
    for(i = 0; i < pic_cnt; i++)
    {
        pic_info_640[i].ID            = i;
        pic_info_640[i].size.width    = 12;
        pic_info_640[i].size.height   = 16;
        len = pic_info_640[i].size.width * pic_info_640[i].size.height * 4;
        pic_info_640[i].pOverlayPixel = esMEMS_Balloc(len);
        
        __cvr_res_get(mark_res_640[i], pic_info_640[i].pOverlayPixel, len);
        
        pic_info_1280[i].ID            = 20 + i;
        pic_info_1280[i].size.width    = 18;
        pic_info_1280[i].size.height   = 24;
        len = pic_info_1280[i].size.width * pic_info_1280[i].size.height * 4;
        pic_info_1280[i].pOverlayPixel = esMEMS_Balloc(len);
        
        __cvr_res_get(mark_res_1280[i], pic_info_1280[i].pOverlayPixel, len);
    }
}

void    cvr_water_mark_res_uninit(void)
{
    __u32       i;

    for(i = 0; i < pic_cnt; i++)
    {
        if(pic_info_640[i].pOverlayPixel)
        {
            esMEMS_Bfree(pic_info_640[i].pOverlayPixel, pic_info_640[i].size.width * pic_info_640[i].size.height * 4);
            pic_info_640[i].pOverlayPixel = NULL;
        }
        if(pic_info_1280[i].pOverlayPixel)
        {
            esMEMS_Bfree(pic_info_1280[i].pOverlayPixel, pic_info_1280[i].size.width * pic_info_1280[i].size.height * 4);
            pic_info_1280[i].pOverlayPixel = NULL;
        }
    }
    for(i = 0; i < pic_cnt; i++)
    {
        if(over_pixel_640[i])
        {
            esMEMS_Bfree(over_pixel_640[i], pic_info_640[i].size.width * pic_info_640[i].size.height);
            over_pixel_640[i] = NULL;
        }  
    }
    for(i = 0; i < pic_cnt; i++)
    {
        if(over_pixel_1280[i])
        {
            esMEMS_Bfree(over_pixel_1280[i], pic_info_1280[i].size.width * pic_info_1280[i].size.height);
            over_pixel_1280[i] = NULL;
        }  
    }
    if(pic_info_640)
    {
        esMEMS_Bfree(pic_info_640, pic_cnt * sizeof(__lotus_overlay_pic_info_t));
        pic_info_640 = NULL;
    }
    if(pic_info_1280)
    {
        esMEMS_Bfree(pic_info_1280, pic_cnt * sizeof(__lotus_overlay_pic_info_t));
        pic_info_1280 = NULL;
    }
}


/*******************************************************************************
* Function name: __RGBPalette2YUV
* Description:
*    把rgb调色板转换为yuv调色板
*
* Parameters:
*    @param pal_rgb:    ARGB调色板buffer
*    @param pal_num:    调色板大小(颜色数目)
* Outputs:
*    @param pal_yuv:    AYUV调色板buffer
*
* Return:
*    @return: on success return EPDK_OK otherwise return EPDK_FAIL.
* Time: 2011/7/7
*******************************************************************************/
static __s32 __RGBPalette2YUV(__u32 *pal_yuv, __u32 *pal_rgb, int pal_num)
{
    int i;
    __u8 y,cb,cr,r,g,b;
    if (pal_yuv == NULL || pal_rgb == NULL)
    {
        __wrn("input para err!\n");
        return EPDK_FAIL;
    }
    for(i = 0; i < pal_num; i++)
    {
        r = (pal_rgb[i]&0x00FF0000)>>16;
        g = (pal_rgb[i]&0x0000FF00)>>8;
        b = (pal_rgb[i]&0x000000FF);
        y = (__u8)((299*r+587*g+114*b)/1000);
        cb = 128+(__u8)(564*(b-y)/1000);
        cr = 128+(__u8)(713*(r-y)/1000);

        pal_yuv[i] = (y<<16)|(cb<<8)|(cr);
    }
    return EPDK_OK;
}

/*******************************************************************************
* Function name: cvr_water_mark_get_overlay_data
* Description:
*    获取时间水印的图标数据
*
* Parameters:
*    @param level:    获取的数据尺寸	(0:640x480、 1:1280x720)
* Outputs:
*    @param overlay_src_pic:   把ARGB数据转换成结构体形式
*
*
* Return:
*    @return: on success return EPDK_OK otherwise return EPDK_FAIL.
* Time: 2011/7/7
*******************************************************************************/
__s32   cvr_water_mark_get_overlay_data(__lotus_overlay_src_init_t*  overlay_src_pic, __u32 level)
{
    __u32   picIndex, pixelIndex, paletteIndex;
    __u32   palette[16];
    __u32   numPal;
    __u32   picSize;
    __u32*  psrcPixel;

    if(overlay_src_pic == NULL)
    {
        __wrn("input para err!\n");
        return EPDK_FAIL;
    }
    eLIBs_memset(palette, 0, sizeof(palette));
    overlay_src_pic->srcPicNum = pic_cnt;
    numPal = 0;
    if(level == 0)
    {
        for(picIndex = 0; picIndex < pic_cnt; picIndex++)
        {
            overlay_src_pic->srcPic[picIndex].ID = pic_info_640[picIndex].ID;
            overlay_src_pic->srcPic[picIndex].size = pic_info_640[picIndex].size;
            if(over_pixel_640[picIndex] == NULL)
            {
                over_pixel_640[picIndex] = (__u8*)esMEMS_Balloc(pic_info_640[picIndex].size.width * pic_info_640[picIndex].size.height);
            }
            psrcPixel = (__u32*)pic_info_640[picIndex].pOverlayPixel;
            picSize = pic_info_640[picIndex].size.width * pic_info_640[picIndex].size.height;

            overlay_src_pic->srcPic[picIndex].pOverlayPixel = over_pixel_640[picIndex];
            for (pixelIndex = 0; pixelIndex < picSize; pixelIndex++)
            {
                for (paletteIndex = 0; paletteIndex < numPal; paletteIndex++)
                {
                    if (palette[paletteIndex] == ((*psrcPixel)&0x00FFFFFF))
                    {
                        break;
                    }
                }
                if (paletteIndex == numPal)
                {
                    if (numPal >= 16)
                    {
                        //__wrn("err! palette is bigger than 16!\n");
                        paletteIndex = 0;
                        *psrcPixel = 0;
                    }
                    else
                    {
                        palette[paletteIndex] = ((*psrcPixel)&0x00FFFFFF);
                        numPal++;
                    }
                }
                overlay_src_pic->srcPic[picIndex].pOverlayPixel[pixelIndex] 
                        = (__u8)((((*psrcPixel)&0xf0000000)>>24)|paletteIndex);
                psrcPixel++;
            }
        }
    }
    else
    {
        for(picIndex = 0; picIndex < pic_cnt; picIndex++)
        {
            overlay_src_pic->srcPic[picIndex].ID = pic_info_1280[picIndex].ID;
            overlay_src_pic->srcPic[picIndex].size = pic_info_1280[picIndex].size;
            if(over_pixel_1280[picIndex] == NULL)
            {
                over_pixel_1280[picIndex] = (__u8*)esMEMS_Balloc(pic_info_1280[picIndex].size.width * pic_info_1280[picIndex].size.height);
            }
            psrcPixel = (__u32*)pic_info_1280[picIndex].pOverlayPixel;
            picSize = pic_info_1280[picIndex].size.width * pic_info_1280[picIndex].size.height;

            overlay_src_pic->srcPic[picIndex].pOverlayPixel = over_pixel_1280[picIndex];
            for (pixelIndex = 0; pixelIndex < picSize; pixelIndex++)
            {
                for (paletteIndex = 0; paletteIndex < numPal; paletteIndex++)
                {
                    if (palette[paletteIndex] == ((*psrcPixel)&0x00FFFFFF))
                    {
                        break;
                    }
                }
                if (paletteIndex == numPal)
                {
                    if (numPal >= 16)
                    {
                        //__wrn("err! palette is bigger than 16!\n");
                        paletteIndex = 0;
                        *psrcPixel = 0;
                    }
                    else
                    {
                        palette[paletteIndex] = ((*psrcPixel)&0x00FFFFFF);
                        numPal++;
                    }
                }
                overlay_src_pic->srcPic[picIndex].pOverlayPixel[pixelIndex] 
                        = (__u8)((((*psrcPixel)&0xf0000000)>>24)|paletteIndex);
                psrcPixel++;
            }
        }
    }
    overlay_src_pic->color_num = numPal;
    if(__RGBPalette2YUV(overlay_src_pic->ppalette_yuv, palette, numPal) != EPDK_OK)
    {
        return EPDK_FAIL;
    }
    return EPDK_OK;
}



