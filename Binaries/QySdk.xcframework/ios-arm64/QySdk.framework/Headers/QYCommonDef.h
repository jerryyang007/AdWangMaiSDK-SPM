//
//  QYCommonDef.h
//  Cupid
//
//  Created by Peiran Zhang on 2020/3/19.
//  Copyright © 2020 iqiyi. All rights reserved.
//

#ifndef QYCommonDef_h
#define QYCommonDef_h

/*********************** 定义mixer response返回json字段名称 ***********************/
#define MIXER_RESP_KEY_URLCONFIG                    @"urlConfig"
#define MIXER_RESP_KEY_CALLBACK                     @"ck"
#define MIXER_RESP_KEY_I71RACKING                   [QYUtils reverseString:@"gnikcarTiyiqi"]
#define MIXER_RESP_KEY_ADXTRACKING                  @"adxTracking"
#define MIXER_RESP_KEY_CUPIDTRACKING                @"cupidTracking"
#define MIXER_RESP_KEY_QILINTRACKING                @"qilinTracking"
#define MIXER_RESP_KEY_PINGBACKURLS                 @"pingback"
#define MIXER_RESP_KEY_MIXERURLS                    @"mixer"
#define MIXER_RESP_KEY_TRACKING_URL                 @"url"
#define MIXER_RESP_KEY_TRACKING_PARAM               @"params"
#define MIXER_RESP_KEY_TRACKING_EXTS                @"exts"
#define MIXER_RESP_KEY_TRACKING_EVENT               @"events"
#define MIXER_RESP_KEY_PINGBACK_CONFIG              @"pc"
#define MIXER_RESP_KEY_PINGBACK_CUPID_EXT           @"cupidExtras"
#define MIXER_RESP_KEY_GLOBAL_CONFIG                @"globalConfig"
#define MIXER_RESP_KEY_ADMTOAPP                     @"admToApp"

/************* response中与三方tracking对应的key，同时作为本地存储的key *************/
#define THIRD_TRACKING_KEY_EVENT_EVENT          @"event"
#define THIRD_TRACKING_KEY_EVENT_TRACKING       @"tracking"
#define THIRD_TRACKING_KEY_THIRDTRACKING        @"thirdPartyTracking"
#define THIRD_TRACKING_KEY_IMPRESSION           @"impressionTracking"
#define THIRD_TRACKING_KEY_CLICK                @"clickTracking"
#define THIRD_TRACKING_KEY_EVENT                @"eventTracking"
#define THRID_TRACKING_KEY_EVENT_START          @"start"
#define THRID_TRACKING_KEY_EVENT_1Q             @"firstQuartile"
#define THRID_TRACKING_KEY_EVENT_MID            @"midpoint"
#define THRID_TRACKING_KEY_EVENT_3Q             @"thirdQuartile"
#define THRID_TRACKING_KEY_EVENT_COMPLETE       @"complete"
#define THRID_TRACKING_KEY_EVENT_CONVERSION     @"conversion"
#define THRID_TRACKING_KEY_EVENT_TUREVIEW       @"trueview"
#define THRID_TRACKING_KEY_EVENT_SKIP           @"skip"
#define THRID_TRACKING_KEY_EVENT_DLOAD_START    @"downloadStart"
#define THRID_TRACKING_KEY_EVENT_DLOAD_FINISH   @"downloaded"
#define THRID_TRACKING_KEY_EVENT_NEGATIVE       @"close"
#define THRID_TRACKING_KEY_EVENT_INSTALLED      @"installed"
#define THRID_TRACKING_KEY_EVENT_DISPLAY        @"viewableImpression"
#define THRID_TRACKING_KEY_EVENT_REIMPRESSION   @"repeatedImpression"
#define THRID_TRACKING_KEY_EVENT_SLIMPRESSION   @"slidingImpression"
#define THRID_TRACKING_KEY_EVENT_INCENTIVETASK  @"incentiveTask"
#define THRID_TRACKING_KEY_EVENT_GOLD_COIN      @"goldCoin"

/************* 广告属性中的key *************/
#define PROP_K_CLICK_AREA           @"cla" //点击区域
#define PROP_K_PLAY_DURATION        @"playDuration"
#define PROP_K_TRUEVIEW_TYPE        @"trueview"
#define PROP_K_NEG_FB_ID            @"feedbackId"
#define PROP_K_NEG_FB_DETAIL        @"feedbackDetails"
#define PROP_K_SHOW_TYPE            @"showtype"
#define PROP_K_DISP_PROP            @"displayProportion"
#define PROP_K_CLICK_COR            @"clickCoordinate" //点击坐标
#define PROP_K_DISP_COR             @"displayCoordinate" //展示坐标
#define PROP_K_INSTALL_STATUS       @"appInstallStatus" //展示坐标

#define PROP_K_SECOND_HOLDER        @"secondPageHolder"

/************* 广告属性中的value *************/
#define PROP_V_BUTTON             @"button"
#define PROP_V_PLAYER             @"player"
#define PROP_V_GRAPHIC            @"graphic"
#define PROP_V_REWARD_RIGHT_TEXT  @"reward_right_text"
#define PROP_V_REWARD_BACKGROUND  @"reward_background"
#define PROP_V_REWARD_EXIT        @"exit_dialog"
#define PROP_V_REWARD_GIFT        @"reward_gift"
#define PROP_V_REWARD_DIALOG_HAND @"dialog_hand"
#define PROP_V_REWARD_ACTION_DIALOG @"action_dialog"
#define PROP_V_REWARD_ACTION_DIALOG_BUTTON @"action_dialog_button"
#define PROP_V_SHARK              @"shark"
#define PROP_V_TWIST              @"twist"
#define PROP_V_SLIDE              @"slide"
#define PROP_V_LAYER_BUTTON       @"layer_button"
#define PROP_V_LAYER_GRAPHIC      @"layer_graphic"
#define PROP_V_HALF_WEBVIEW       @"half_webview"
#define PROP_V_EPISODE_PLAYER_GRAPHIC       @"episode_player_graphic"   // 暂停Max，点击右下角区域
#define PROP_V_BACKGRPUND_IMG       @"background_Img"   // 新暂停Max，背景图
#define PROP_V_REWARD_NOTIFICATION  @"inner_push" // 激励广告通知

/************* 创意模板 *************/
#define CUPID_TEMPLATE_COMMON_PAUSE          @"common_pause"
#define CUPID_TEMPLATE_FLOW_NEW              @"mobile_flow_new"
#define CUPID_TEMPLATE_COMMON_ROLL           @"roll"
#define CUPID_TEMPLATE_IPHONE_SPLASH         @"iphone_interstitials"
#define CUPID_TEMPLATE_FOCUS                 @"mobile_focus"
#define CUPID_TEMPLATE_BANNER_PIC            @"banner_pic"

/************* trueview type *************/
#define TRUEVIEW_TYPE_INVALID               @""
#define TRUEVIEW_TYPE_TIME                  @"1"
#define TRUEVIEW_TYPE_CLICK_PLAY            @"2"
#define TRUEVIEW_TYPE_CLICK_PAUSEAD         @"7"    //暂停广告点击
#define TRUEVIEW_TYPE_CLICK_PLAYER          @"9"
#define TRUEVIEW_TYPE_CLICK_AUTOOPEN        @"10"   // 自动打开落地页

/************* 激励广告状态 *************/
#define REWARD_STAT_INVALID             @"REWARD_START_INVALID"
#define REWARD_STAT_READY               @"REWARD_START_READY"
#define REWARD_STAT_ERROR               @"REWARD_START_ERROR"
#define REWARD_STAT_FINISH              @"REWARD_START_FINISH"

#define VIDEOERROR_TIMEOUT              @"VIDEOERROR_TIMEOUT"

/************* DEEPLINK拉起类型KEY *************/
#define PROP_K_DPTYPE                   @"PROP_KEY_DPTYPE"
#define PROP_V_DPTYPE_ONLINEMOVIE       @"DPTYPE_ONLINEMOVIE"

/************* 内部传递信息KEY *************/
#define INFO_K_CLICK_POINT                @"INFO_KEY_CLK_POINT"
#define INFO_K_ITEM_IMPAREA               @"INFO_KEY_IMPAREA"

/************* 固定文案 *************/
#define REWARD_NO_AD_TOAST                @"现在点击的人太多啦，稍后再试吧" //激励广告请求无广告时的toast文案

typedef NS_ENUM(NSInteger, QY_CUPID_CLICK_THROUGH_TYPE) {
    QY_CUPID_CLICK_THROUGH_TYPE_UNKNOWN = -1,          // 未知方式，表示错误或不支持，不处理
    QY_CUPID_CLICK_THROUGH_TYPE_DEFAULT = 0,           // 默认方式，PC上是打开浏览器，移动端是打开webview
    QY_CUPID_CLICK_THROUGH_TYPE_WEBVIEW = 1,           // 打开内嵌webview的方式
    QY_CUPID_CLICK_THROUGH_TYPE_BROWSER = 2,           // 打开浏览器
    QY_CUPID_CLICK_THROUGH_TYPE_VIP = 3,               // 打开vip支付页面
    QY_CUPID_CLICK_THROUGH_TYPE_DOWNLOAD = 4,          // 下载
    QY_CUPID_CLICK_THROUGH_TYPE_VIDEO = 5,             // 播放视频
    QY_CUPID_CLICK_THROUGH_TYPE_PREDOWNLOAD = 6,       // App预下载
    QY_CUPID_CLICK_THROUGH_TYPE_APP_CENTER = 7,        // app center页面跳转
    QY_CUPID_CLICK_THROUGH_TYPE_MOVIE_TICKET = 8,      // movie ticket页面跳转
    QY_CUPID_CLICK_THROUGH_TYPE_QIXIU = 9,             // 秀场跳转
    QY_CUPID_CLICK_THROUGH_TYPE_INNER_START = 10,      // app内部调起
    QY_CUPID_CLICK_THROUGH_TYPE_DIRECT_DOWNLOAD = 11,  // app直接下载
    QY_CUPID_CLICK_THROUGH_TYPE_IMAGE = 12,            // 图片跳转
    QY_CUPID_CLICK_THROUGH_TYPE_CAROUSEL_STATION = 13, // 轮播台跳转
    QY_CUPID_CLICK_THROUGH_TYPE_DEEPLINK = 14,         // 原生唤醒
    QY_CUPID_CLICK_THROUGH_TYPE_UNILINK = 15,          // universal link
    QY_CUPID_CLICK_THROUGH_TYPE_REGISTRATION = 67      // app跳转注册制
};

typedef NS_ENUM(NSInteger, QY_CUPID_INTERACTIVE) {
    QY_CUPID_INTERACTIVE_SCREEN = 0,
    QY_CUPID_INTERACTIVE_BUTTON = 1,
    QY_CUPID_INTERACTIVE_CREATIVE = 2
};

typedef NS_ENUM(NSInteger, QY_CUPID_SLOT_TYPE) {
    QY_CUPID_SLOT_TYPE_UNKNOWN = -1,                   // 未知广告位类型，表示错误或不支持，不处理
    QY_CUPID_SLOT_TYPE_PAGE = 0,                       // 普通页面广告
    QY_CUPID_SLOT_TYPE_PRE_ROLL = 1,                   // 前贴广告
    QY_CUPID_SLOT_TYPE_MID_ROLL = 2,                   // 中贴广告
    QY_CUPID_SLOT_TYPE_POST_ROLL = 3,                  //后贴广告
    QY_CUPID_SLOT_TYPE_CORNER = 4,                     // 角标广告
    QY_CUPID_SLOT_TYPE_MARK = 5,                       //（还未启用）
    QY_CUPID_SLOT_TYPE_PAUSE = 6,                      // 暂停广告
    QY_CUPID_SLOT_TYPE_TOOLBAR = 7,                    // 工具栏广告（还未启用）
    QY_CUPID_SLOT_TYPE_VIEWPOINT = 8,                  // 视点广告
    QY_CUPID_SLOT_TYPE_OVERLAY = 9,                    // 覆盖类广告
    QY_CUPID_SLOT_TYPE_COMMON_OVERLAY = 10,            // 通用浮层广告
    QY_CUPID_SLOT_TYPE_COMMON_OVERLAY_INNER = 11,      // 通用浮层内广
    QY_CUPID_SLOT_TYPE_CACHE_BANNER = 12,              // 缓存banner广告
    QY_CUPID_SLOT_TYPE_WHOLE_CORNER = 13,              // 全程角标
    QY_CUPID_SLOT_TYPE_BARRAGE = 14,                   // 弹幕广告
    QY_CUPID_SLOT_TYPE_BRIEF_ROLL = 15                 // 前情提要 & 大头贴
};

typedef NS_ENUM(NSInteger, QY_CUPID_DELIVER_TYPE) {
    QY_CUPID_DELIVER_TYPE_UNSUPPORTED = 0,
    QY_CUPID_DELIVER_TYPE_PMP = 1,
    QY_CUPID_DELIVER_TYPE_TRUEVIEW = 2, //普通trueview
    QY_CUPID_DELIVER_TYPE_VIP_AD = 3, // 会员贴片
    QY_CUPID_DELIVER_TYPE_ORIGINAL_ROLL = 4, // 原创贴
    QY_CUPID_DELIVER_TYPE_SKIPPABLE_POST_ROLL = 5, // 可跳过后贴
    QY_CUPID_DELIVER_TYPE_SKIPPABLE_PRE_ROLL = 6, // 可跳过trueview贴片
    QY_CUPID_DELIVER_TYPE_SPORTS_VIP_AD = 7, //体育会员贴片
    QY_CUPID_DELIVER_TYPE_STICKER_ROLL = 8, //大头贴
    QY_CUPID_DELIVER_TYPE_BRIEF_ROLL = 9, //前情提要
    QY_CUPID_DELIVER_TYPE_COMMON_INTERACTIVE = 10, // 普通互动贴片
    QY_CUPID_DELIVER_TYPE_ORIGIN_INTERACTIVE = 11, // 原创帖互动贴片
    QY_CUPID_DELIVER_TYPE_BRIEF_ROLL_OVERLAY = 12,    // 前情提要带浮层图片
    QY_CUPID_DELIVER_TYPE_STANDARD_ROLL_TOAST = 13,   // 标版带toast提示
    QY_CUPID_DELIVER_TYPE_MAXVIEW = 14, // MAXVIEW
    QY_CUPID_DELIVER_TYPE_FLOW_INNOVATE_SCROLL = 15, // 信息流创新样式卷轴
    QY_CUPID_DELIVER_TYPE_EASTER_EGG_PAUSE = 16 //暂停彩蛋
};

typedef NS_ENUM(NSInteger, QY_I71_TRACKING_PARTY) {
    QY_I71_TRACKING_PARTY_THIRD = 0,            //第三方监测，旧版包含奇麟
    QY_I71_TRACKING_PARTY_CUPID = 1,            //奇胜，track2
    QY_I71_TRACKING_PARTY_ADX = 2,              //ADX，etx
    QY_I71_TRACKING_PARTY_QILIN = 3,            //奇麟，dsp_track2
    QY_I71_TRACKING_PARTY_TASKPAGE = 4,         //焕金-任务页完成任务
};

//VISIT行为类型
typedef NS_ENUM(NSInteger, QY_VISTI_ACT_TYPE) {
    QY_ACT_VISIT = 1
};

//广告行为类型
typedef NS_ENUM(NSInteger, QY_ACT_TYPE) {
    QY_ACT_TYPE_UNKNOWN          = 0,
    QY_ACT_TYPE_IMPRESSION       = 100,
    QY_ACT_TYPE_START,
    QY_ACT_TYPE_1ST_QUARTILE,
    QY_ACT_TYPE_MID_POINT,
    QY_ACT_TYPE_3RD_QUARTILE,
    QY_ACT_TYPE_COMPLETE,
    QY_ACT_TYPE_SKIP,
    QY_ACT_TYPE_PUSH,
    QY_ACT_TYPE_DOWNLOADSTART,
    QY_ACT_TYPE_DOWNLOADED,
    QY_ACT_TYPE_CONVERSION,
    QY_ACT_TYPE_TRUEVIEW,
    QY_ACT_TYPE_CLICK,
    QY_ACT_TYPE_LIKE,
    QY_ACT_TYPE_UNLIKE,
    QY_ACT_TYPE_SKIPBTN_CLICK,
    QY_ACT_TYPE_PAY_SHOW,
    QY_ACT_TYPE_PAY_CLICK,
    QY_ACT_TYPE_PAY_CLOSE,
    QY_ACT_TYPE_ERROR,
    QY_ACT_TYPE_STOP,
    QY_ACT_TYPE_LONG_VIEW_REWARD_SKIP,
    QY_ACT_TYPE_NEGATIVE,
    QY_ACT_TYPE_INSTALLED,
    QY_ACT_TYPE_DISPLAY,
    QY_ACT_TYPE_SKIPROLL_DETAIL_SHOW,
    QY_ACT_TYPE_APP_DOWNLOAD,
    QY_ACT_TYPE_AUDIO_PLAY_START,
    QY_ACT_TYPE_AUDIO_PLAY_COMPLETE,
    QY_ACT_TYPE_CLOSE,
    QY_ACT_TYPE_INTERACTIVE_OVERLAY_IMP,
    QY_ACT_TYPE_SKIPROLL_DETAIL_CLOSE,
    QY_ACT_TYPE_AUTO_PAGE_OPEN,
    QY_ACT_TYPE_AUTO_PAGE_CLOSE,
    QY_ACT_TYPE_MAXVIEW_DISPLAY,
    QY_ACT_TYPE_INCENTIVETASK,
    QY_ACT_TYPE_GOLD_COIN,
    QY_ACT_TYPE_TASKPAGE
};

//tracking 结果类型
typedef NS_ENUM(NSInteger, QY_TRACKING_ACT_TYPE) {
    QY_TRACKING_ACT_TYPE_SUCCESS                = 201,
    QY_TRACKING_ACT_TYPE_HTTP_ERR               = 202,
    QY_TRACKING_ACT_TYPE_TIMEOUT                = 203,
    QY_TRACKING_ACT_TYPE_PARAM_ERR              = 204,
    QY_TRACKING_ACT_TYPE_URL_LENGTH_LIMIT       = 205
};

typedef NS_ENUM (NSInteger, QY_ADX_TRACK_ACT_TYPE) {
    QY_ADX_TRACK_ACT_TYPE_SUCCESS               = 301,
    QY_ADX_TRACK_ACT_TYPE_HTTP_ERROR            = 302,
    QY_ADX_TRACK_ACT_TYPE_TIMEOUT               = 303,
    QY_ADX_TRACK_ACT_TYPE_PARAM_ERROR           = 304,
    QY_ADX_TRACK_ACT_TYPE_URL_LENGTH_LIMIT      = 305
};

typedef NS_ENUM (NSInteger, QY_THIRD_TRACK_ACT_TYPE) {
    QY_THIRD_TRACK_ACT_TYPE_SUCCESS             = 1301,
    QY_THIRD_TRACK_ACT_TYPE_HTTP_ERROR          = 1302,
    QY_THIRD_TRACK_ACT_TYPE_TIMEOUT             = 1303,
    QY_THIRD_TRACK_ACT_TYPE_PARAM_ERROR         = 1304,
    QY_THIRD_TRACK_ACT_TYPE_URL_LENGTH_LIMIT    = 1305
};

typedef NS_ENUM (NSInteger, QY_MIXER_ACT_TYPE) {
    QY_MIXER_ACT_TYPE_SUCCESS       = 601,
    QY_MIXER_ACT_TYPE_PARSE_ERROR   = 602,
    QY_MIXER_ACT_TYPE_PARAM_ERROR   = 603,
    QY_MIXER_ACT_TYPE_HTTP_ERROR    = 604,
    QY_MIXER_ACT_TYPE_TIMEOUT       = 605
};

typedef NS_ENUM (NSInteger, QY_CREATIVE_ACT_TYPE) {
    QY_CREATIVE_ACT_TYPE_LOAD               = 701,
    QY_CREATIVE_ACT_TYPE_CDN_HTTP_ERROR     = 702,
    QY_CREATIVE_ACT_TYPE_CDN_TIMEOUT        = 703,
    QY_CREATIVE_ACT_TYPE_CDN_PARSE_ERROR    = 704,
    QY_CREATIVE_ACT_TYPE_HTTP_ERROR         = 705,
    QY_CREATIVE_ACT_TYPE_TIMEOUT            = 706,
    QY_CREATIVE_ACT_TYPE_HANG               = 707,
    QY_CREATIVE_ACT_TYPE_ERROR              = 708,
    QY_CREATIVE_ACT_TYPE_AD_START_INTERVAL  = 709,
    QY_CREATIVE_ACT_TYPE_SUCCESS            = 710,
    QY_CREATIVE_ACT_TYPE_FAILURE_OVER_SIZE  = 711,
    QY_CREATIVE_ACT_TYPE_DATA_ERROR         = 712,
    QY_CREATIVE_ACT_TYPE_MAKEVER_ERROR      = 713,
    QY_CREATIVE_ACT_TYPE_LOAD_INCOMPLETE    = 714
};

typedef NS_ENUM (NSInteger, QY_STATISTIC_ACT_TYPE) {
    QY_STATISTIC_ACT_TYPE_3RD_SERVER_LOAD             = 800,
    QY_STATISTIC_ACT_TYPE_3RD_SERVER_SUCCESS          = 801,
    QY_STATISTIC_ACT_TYPE_3RD_SERVER_HTTP_ERROR       = 802,
    QY_STATISTIC_ACT_TYPE_3RD_SERVER_TIMEOUT          = 803,
    QY_STATISTIC_ACT_TYPE_3RD_SERVER_PARSE_ERROR      = 804,
    QY_STATISTIC_ACT_TYPE_3RD_SERVER_NO_AD            = 805,
    QY_STATISTIC_ACT_TYPE_UNSUPPORTED_TEMPLATE        = 806,
    QY_STATISTIC_ACT_TYPE_AD_LOADED                   = 807,
    QY_STATISTIC_ACT_TYPE_AD_WEBVIEW_HTTP_ERROR       = 808,
    QY_STATISTIC_ACT_TYPE_AD_WEBVIEW_TIMEOUT          = 809,
    QY_STATISTIC_ACT_TYPE_VIP_CHECK_CONFLICT          = 810,
    QY_STATISTIC_ACT_TYPE_AD_LOAD_BLOCK               = 811,
    QY_STATISTIC_ACT_TYPE_AD_PLAY_DURATION            = 812,
    QY_STATISTIC_ACT_TYPE_AD_AREA_CLICK               = 813,
    QY_STATISTIC_ACT_TYPE_AD_SEEK                     = 814,
    QY_STATISTIC_ACT_TYPE_AD_SKIPROLL_CARD_SHOW       = 815,
    QY_STATISTIC_ACT_TYPE_AD_SKIPROLL_CARD_CLOSE      = 816,
    QY_STATISTIC_ACT_TYPE_AD_WEBVIEW_SUCCESS          = 817,
    QY_STATISTIC_ACT_TYPE_AD_SKIPROLL_SHOW_DETAIL     = 818,
    QY_STATISTIC_ACT_TYPE_AD_DOWNLOAD_APP             = 819,
    QY_STATISTIC_ACT_TYPE_AD_PLAY_AUDIO               = 820,
    QY_STATISTIC_ACT_TYPE_AD_AREA_CLOSE               = 821,
    QY_STATISTIC_ACT_TYPE_AD_INTEROVERLAY_IMP         = 822,
    QY_STATISTIC_ACT_TYPE_AD_SKIPROLL_CLOSE_DETAIL    = 823,
    QY_STATISTIC_ACT_TYPE_AD_OPEN_AUTO_PAGE           = 824,
    QY_STATISTIC_ACT_TYPE_AD_CLOSE_AUTO_PAGE          = 825,
    QY_STATISTIC_ACT_TYPE_AD_DISPLAY_MAXVIEW          = 826,
    QY_STATISTIC_ACT_TYPE_AD_LINK                     = 827,
    QY_STATISTIC_ACT_TYPE_COLD_START                  = 1000,
    QY_STATISTIC_ACT_TYPE_AD_ADN_REQDURATION          = 1001,
    QY_STATISTIC_ACT_TYPE_AD_REWARD_GIFT_SHOW         = 1002,
    QY_STATISTIC_ACT_TYPE_AD_REWARD_GIFT_CLOSE        = 1003,
    QY_STATISTIC_ACT_TYPE_AD_NATIVE_ADN_IMP           = 1004
};

typedef NS_ENUM (NSInteger, QY_INVENTORY_ACT_TYPE) {
    QY_ACT_INVENTORY               = 1200
};

typedef NS_ENUM (NSInteger, QY_RISK_ACT_TYPE) {
    QY_RISK_ACT_TYPE_SUCCESS            = 1401,
    QY_RISK_ACT_TYPE_TIMEOUT            = 1402,
    QY_RISK_ACT_TYPE_HTTP_ERROR         = 1403,
    QY_RISK_ACT_TYPE_PARSE_ERROR        = 1404,
    QY_RISK_ACT_TYPE_RESCODE_ERROR      = 1405
};

typedef NS_ENUM(NSInteger, QY_SPLASH_TYPE) {
    QY_SPLASH_TYPE_NOTFULLSCR       = 0, // 非全面屏
    QY_SPLASH_TYPE_FULLSCREEN       = 1  // 全面屏
};

/*
 0  - 品牌logo和蒙层可点击
 1  - 品牌logo和全屏可点击
 2  - 沉浸式开屏&全屏可点击
 11 - 带按钮的非沉浸式样式
 12 - 带按钮的沉浸式样式
 针对11和12样式，creative Object中新增clickArea字段，0-仅按钮可点 1-全屏可点，不下发时默认仅按钮可点。
 **/
typedef NS_ENUM(NSInteger, QY_SPLASH_INTERSTYLE) {
    QY_SPLASH_INTERSTYLE_LOGOMASK       = 0,
    QY_SPLASH_INTERSTYLE_LOGOSCR        = 1,
    QY_SPLASH_INTERSTYLE_FULLSCR        = 2,
    QY_SPLASH_INTERSTYLE_BTNANDLOGO     = 11,
    QY_SPLASH_INTERSTYLE_BTNFULLSCR     = 12
};

typedef NS_ENUM(NSInteger, QY_RENDER_TYPE) {
    QY_RENDER_TYPE_STATIC           = 0,        // 静态素材，图片
    QY_RENDER_TYPE_DYNAMIC          = 1,        // 动态素材，视频
    QY_RENDER_TYPE_HTML             = 2,        // html素材
    QY_RENDER_TYPE_CONTAINER        = 100       // 背景图
};

typedef NS_ENUM(NSInteger, QY_CONVERSION_ID) {
    QY_CONVERSION_ID_DOWNLOAD_START             = 10201,
    QY_CONVERSION_ID_DOWNLOADED                 = 10202,
    QY_CONVERSION_ID_INSTALLED                  = 10203,
    QY_CONVERSION_ID_ACTIVATED                  = 10204,
    QY_CONVERSION_ID_ACTIVATED_AND_REGISTERD    = 10205,
    QY_CONVERSION_ID_ACTIVATED_AND_PAID         = 10206,
    QY_CONVERSION_ID_CREDITED                   = 10207,
    QY_CONVERSION_ID_RETAINED_NEXT_DAY          = 10208,
    QY_CONVERSION_ID_FORM_SUBMIT                = 19901,
    QY_CONVERSION_ID_CALL                       = 10101,
    QY_CONVERSION_ID_DETAIL                     = 10104,
    QY_CONVERSION_ID_DOWNLOAD                   = 10105,
    QY_CONVERSION_ID_ADVICE_ONLINE              = 10106,
    QY_CONVERSION_ID_FOCUS_ON_WECHAT            = 10107,
    QY_CONVERSION_ID_GAME_RESERVATION           = 10108,
    QY_CONVERSION_ID_START_APP                  = 10213,
    QY_CONVERSION_ID_LOGIN                      = 10215,
    QY_CONVERSION_ID_LOGOUT                     = 10216,
    QY_CONVERSION_ID_DURATION                   = 10214,
    QY_CONVERSION_ID_CONSULT                    = 10217,
    QY_CONVERSION_ID_SHARE                      = 10218,
    QY_CONVERSION_ID_SEARCH                     = 10219,
    QY_CONVERSION_ID_COLLECT                    = 10220,
    QY_CONVERSION_ID_SCORE                      = 10221,
    QY_CONVERSION_ID_CREATE_ROLE                = 10209,
    QY_CONVERSION_ID_UPGRADE                    = 10210,
    QY_CONVERSION_ID_SHOPPING_CARD              = 10211,
    QY_CONVERSION_ID_PLACE_ORDER                = 10212,
    QY_CONVERSION_ID_APPLY                      = 10222,
    QY_CONVERSION_ID_VISIT                      = 10223,
    QY_CONVERSION_ID_STAY_DESKTOP               = 10224,
    QY_CONVERSION_ID_USERDEFINE                 = 10299,
    QY_CONVERSION_ID_DEEPLINK                   = 20001,
    QY_CONVERSION_ID_DEEPLINK_SUCCESS           = 20002,
    QY_CONVERSION_ID_CONVERSION_EFFECTIVE_PLAY  = 10226,
    QY_CONVERSION_ID_FIRST_DAY_PAID             = 10227,
    QY_CONVERSION_ID_FIRST_TIME_PAID            = 10228,
    QY_CONVERSION_ID_JOIN_WECHAT_GROUP          = 10225,
    QY_CONVERSION_ID_FIRST_DAY_ROI              = 10230,
    QY_CONVERSION_ID_EACH_PAYMENT               = 10231
};

//一级行业ID
typedef NS_ENUM(NSInteger, QY_PRI_INDUSTRY_ID) {
    QY_PRI_INDUSTRY_ID_ONLINE_MOVIE = 3014
};

//横竖屏状态
typedef NS_ENUM(NSInteger, QY_SPP_PLT) {
    QY_SPP_PLT_LANDSCAPE = 0,           // 横屏
    QY_SPP_PLT_PORTRAIT = 1,            // 竖屏
};

//广告类型
typedef NS_ENUM(NSInteger, QY_ORDER_ITEM_TYPE) {
    QY_ORDER_ITEM_TYPE_QISHENG = 1,             // 奇胜
    QY_ORDER_ITEM_TYPE_QILIN = 2,               // 奇麟
    QY_ORDER_ITEM_TYPE_ADX = 3,                 // ADX
    QY_ORDER_ITEM_TYPE_CSJ = 4,                 // 穿山甲
    QY_ORDER_ITEM_TYPE_BQT = 5,                 // 百青藤
    QY_ORDER_ITEM_TYPE_KS = 7,                  // 快手
    QY_ORDER_ITEM_TYPE_GDT = 8,                 // 优量汇
    QY_ORDER_ITEM_TYPE_QM = 9,                  // 趣盟
};

typedef NS_ENUM(NSInteger, QY_SSP_ADN_AD_TYPE) {
    QY_SSP_ADN_AD_TYPE_UNKNOW = 0,
    QY_SSP_ADN_AD_TYPE_ROLL = 1,
    QY_SSP_ADN_AD_TYPE_FEED = 2,
    QY_SSP_ADN_AD_TYPE_DRAW = 3,
    QY_SSP_ADN_AD_TYPE_REWARD = 4,
    QY_SSP_ADN_AD_TYPE_SPLASH = 5,
};

//横竖屏状态
typedef NS_ENUM(NSInteger, QY_SSP_PAUSE_AD_TYPE) {
    QY_SSP_PAUSE_AD_TYPE_NORMAL = 0,                // 普通暂停
    QY_SSP_PAUSE_AD_TYPE_MAX_OLD = 5,               // 暂停Max
    QY_SSP_PAUSE_AD_TYPE_MAX_NEW = 6,               // 新版暂停Max
};

//横竖屏状态
typedef NS_ENUM(NSInteger, QY_SPP_ACTION_TYPE) {
    ACTION_TYPE_NORMAL = 0,             // 默认
    ACTION_TYPE_TWIST = 3,              // 扭转
    ACTION_TYPE_SHAKE = 4,              // 摇一摇
    ACTION_TYPE_SLIDE = 7,              // 滑动
};

#endif /* QYCommonDef_h */
