/** ------------------------------------------------------------
 * SPDX-License-Identifier: GPL-3.0-or-later
 * -------------------------------------------------------------
 * File Authors  : Aoran Zeng <ccmywish@qq.com>
 * Contributors  :  Nil Null  <nil@null.org>
 * Created On    : <2024-08-08>
 * Last Modified : <2024-08-08>
 * ------------------------------------------------------------*/

/**
 * 2024-08-08 更新
 */
static SourceInfo
os_openwrt_sources[] = {
  {&Upstream,       NULL},
  {&MirrorZ,        "https://mirrors.cernet.edu.cn/openwrt"},
  {&Ali,            "https://mirrors.aliyun.com/openwrt"},
  {&Tencent,        "https://mirrors.cloud.tencent.com/openwrt"},
  {&Tuna,           "https://mirror.tuna.tsinghua.edu.cn/openwrt"},
  {&Sjtug_Zhiyuan,  "https://mirror.sjtu.edu.cn/openwrt"},
  {&Ustc,           "https://mirrors.ustc.edu.cn/openwrt"},
  {&Pku,            "https://mirrors.pku.edu.cn/openwrt"},
  {&Sustech,        "https://mirrors.sustech.edu.cn/openwrt"},
};

def_sources_n(os_openwrt);


#define OS_OpenWRT_SourceConfig "/etc/opkg/distfeeds.conf"

void
os_openwrt_getsrc (char *option)
{
  chsrc_view_file (OS_OpenWRT_SourceConfig);
}

/**
 * 参考: https://mirror.tuna.tsinghua.edu.cn/help/openwrt/
 */
void
os_openwrt_setsrc (char *option)
{
  chsrc_ensure_root ();

  SourceInfo source;
  chsrc_yield_source (os_openwrt);
  chsrc_confirm_source (&source);

  chsrc_backup (OS_OpenWRT_SourceConfig);

  char *cmd = xy_strjoin (3, "sed -E -i 's@https?://.*downloads.openwrt.org@", source.url, "@g' " OS_OpenWRT_SourceConfig);

  chsrc_run ("apt update", RunOpt_No_Last_New_Line);
  chsrc_say_lastly (&source, ChsrcTypeAuto);
}


def_target(os_openwrt);
