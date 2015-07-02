##Ads Pop-up


####更新日志
* 2015.06.16
	
	1. 修复了全屏广告可能会弹出两次的bug
	
* 2015.06.11

	1. 修改了全屏广告的回调,在回调中增加了一个参数,可以判断全屏广告的类型
	
	
		参数值与对应类型
		<table border="1px">
			<tr><td>InterstitialAdTypeDefault</td><td>普通全屏广告</td></tr>
			<tr><td>InterstitialAdTypeCrossPromo</td><td>交叉广告</td></tr>
		</table>
	
	2. 在显示全屏广告函数中增加了一个判断是否成功的返回值
	
		返回true为显示成功,否则为false
	
* 2013.11.08

	1.0.0 - 2013.11.08
	
	集成MoPub和NewsBlast显示，MoPub Chartboost全屏广告与NewsBlast互斥显示。
	
	同时支持MoPub横幅广告显示
