[使用方法]

将项目作为外链添加到Classes目录下，在项目中添加引用即可。

[使用注意]

1.本库包含了广告相关的Jni, 所以请将原项目中proj.android/jni下的相关文件删除；

2.把代码拖进xcode里面，需要删除AdJni文件夹的引用，注意是删除引用不是连文件一起删了；

 
广告加Loading的代码示例:

在appDelegate::applicationWillEnterForeground中:

    if (!STAds::isInterstitialShowing)
    {
        auto call = []()
        {
            if(!AdLoadingLayerBase::s_currentInstance)
            {
                auto adLoadingLayer = AdsLoadingLayer::create();
                Director::getInstance()->getRunningScene()->addChild(adLoadingLayer);
            }
            else
                AdLoadingLayerBase::s_currentInstance->loadAd();
        };
        //防止android黑屏
        Director::getInstance()->getRunningScene()->runAction(Sequence::create(CallFunc::create(call), NULL));
    }
	
	
在其他地方：

    if(!AdLoadingLayerBase::s_currentInstance)	
    {		
        auto adLoadingLayer = AdsLoadingLayer::create();
		
        Director::getInstance()->getRunningScene()->addChild(adLoadingLayer);		
    }	
    else	
        AdLoadingLayerBase::s_currentInstance->loadAd();
