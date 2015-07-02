/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2014 Chukong Technologies Inc.
 
http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
package org.cocos2dx.cpp;

import org.cocos2dx.lib.Cocos2dxActivity;

import com.common.android.PlatformCode;
import com.common.android.jni.MoreGamesActivityForJNI;
import com.common.android.jni.STMopubAds;
import com.common.android.jni.STMopubAds.STAmazonAdSize;
import com.common.android.utils.Utils;

import android.os.Bundle;
import android.view.Gravity;
import android.widget.FrameLayout.LayoutParams;

public class AppActivity extends Cocos2dxActivity {
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		
		//very important!!!!!!
		setPublicKey("");
		
		// 初始化JNI广告模块
		STMopubAds.setup(this, true);
		// 如果有Amazon广告，设置Amazon广告大小
		STMopubAds.getInstance().setAmazonSizeType(STAmazonAdSize.SIZE_728x90, STAmazonAdSize.SIZE_320x50);
		// 设置广告Banner大小和位置
		if (Utils.isTablet(this)) {
			STMopubAds.getInstance().setBannnerAdViewLayoutParams(
					LayoutParams.MATCH_PARENT, 90,
					Gravity.CENTER | Gravity.BOTTOM);
		} else {
			STMopubAds.getInstance().setBannnerAdViewLayoutParams(
					LayoutParams.MATCH_PARENT, 50,
					Gravity.CENTER | Gravity.BOTTOM);
		}
		
		//more game 
		MoreGamesActivityForJNI.ACTIVITY_LAYOUT_ID = R.layout.activity_more_games;
		MoreGamesActivityForJNI.WEBVIEW_ID = 0;
		MoreGamesActivityForJNI.TITLE_PROGRESS_ID = 0;
	}
	@Override
	public int getPlatformCode() {
		return PlatformCode.AMAZON;
	}

	@Override
	public boolean getDebugMode() {
		return true;
	}

	@Override
	public boolean enableEvent() {
		return !getDebugMode();
	}
}
