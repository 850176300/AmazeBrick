//
//  AppConfigs.h
//  AdsPopupDemo
//
//  Created by tang.wei on 13-12-13.
//  Copyright (c) 2013年 tang.wei. All rights reserved.
//

/*************************** MoPub账号设置 **************************/

#define IPHONE_BANNER_ID         @"1db5b603cbf64f82a511db7952c48ea4"
#define IPHONE_FULLSCREEN_ID     @"9463d7b42d5d42d1bcbcbe2cc8690a7d"

#define IPAD_BANNER_ID           @"d7288f9977fb494ab9892d9434550313"
#define IPAD_FULLSCREEN_ID       @"3229f1120fef42519b6961daeea89a52"

#define IPHONE_FULLSCREEN_ID_CROSSPROMO   @"6d5e6d383ad4481ba8f804a1bc246ee9"
#define IPAD_FULLSCREEN_ID_CROSSPROMO     @"a45ee4ad192344a5b6af9dd8595354e3"
// 方块广告，如果不需要支持可以留空
#define IPHONE_MEDIUM_RECT_ID    @""
#define IPAD_MEDIUM_RECT_ID      @""

// Chartboost账号，如果不需要支持开启chartboost会话，可以留空
#define CHARTBOOST_APP_ID        @""
#define CHARTBOOST_APP_SIGNATURE @""

/*************************** Flurry账号 ****************************/
// 如果留空不设置，那么表示不支持Flurry
#define FLURRY_KEY               @"5BBV2PDGJWZXZYBVS2BG"

/*************************** Privacy Page设置 ****************************/
// 如果留空默认为http://www.xxx.com/privacy.html, 其中xxx为bundle id中间部分
#define PRIVACY_PAGE_URL         @""