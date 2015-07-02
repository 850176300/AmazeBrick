Mopub

2.3  2014.08.05
------------------------------------------
[Changed] 去除了AdFalcon, Greystripe, InMobi这些第3方广告支持

需要添加的库如下：

CoreMedia.framework
CoreData.framework
QuartzCore.framework
AudioToolbox.framework
SystemConfiguration.framework
iAd.framework
MessageUI.framework
AVFoundation.framework
CoreMotion.framework
Security.framework
MediaPlayer.framework
CoreTelephony.framework
EventKit.framework
EventKitUI.framework
StoreKit.framework
PassKit.framework   optional
AdSupport.framework optional
libz.dylib
libsqlite3.0.dylib

另: 1.在"Build Settings下面的Other Linker Flags添加 -ObjC "，
    2.还需要通过外链的方式添加广告商自己的SDK，如果不需要支持某个广告，那么可以在AdNetworkSupport文件夹下删除对应的广告支持类文件引用,
    3.目前Mopub不支持显示Greystripe广告，所以请到AdNetworkSupport文件夹下面删掉Greystripe这个文件夹引用
    4.在应用程序启动的时候需要初始化InMobi。代码：[InMobi initialize:@"0cd2ee11744f4f6c8e2de7181687450d"] 这个是InMobi4.0.2新SDK要求的。
   