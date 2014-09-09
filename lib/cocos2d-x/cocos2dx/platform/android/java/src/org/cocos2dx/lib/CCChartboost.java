package org.cocos2dx.lib;
import android.os.Handler;
import android.util.Log;

import com.chartboost.sdk.*;
import com.chartboost.sdk.Libraries.CBLogging.Level;
import com.chartboost.sdk.Model.CBError.CBClickError;
import com.chartboost.sdk.Model.CBError.CBImpressionError;

public class CCChartboost {
	private static final String TAG = CCChartboost.class.getSimpleName();
	private static final String cbLocation="nowhere";
	private Cocos2dxActivity m_activity;	
	private static CCChartboost s_instance=null;
	private ChartboostDelegate cbDelegate = new ChartboostDelegate() {
		public boolean shouldDisplayInterstitial(String location) {
	        return true;
	    }
		public boolean shouldRequestInterstitial(String location) {
	        return true;
	    }
		public void didCacheInterstitial(String location) {
	        Log.d(TAG, "cache chartboost interstitial at location: " + location + " success!");
		}
		public void didFailToLoadInterstitial(String location, CBImpressionError err) {
	        Log.d(TAG, "cache chartboost interstitial at location: " + location + " failed!" + err);
	    }
		public void didDismissInterstitial(String location) {
	        Chartboost.cacheInterstitial(location);
	        Log.d(TAG, "caching chartboost interstitial at location: " + location);
	    }
		public void didCloseInterstitial(String location) {
	    }
		public void didClickInterstitial(String location) {
	    }
		public void didDismissMoreApps(String location) {
			Chartboost.cacheMoreApps(location);
	    }
		public void didFailToRecordClick(String arg0, CBClickError arg1) {			
		}
	};
	protected CCChartboost(){
	}
	public static CCChartboost Instance(){
		if (s_instance == null){
			s_instance = new CCChartboost();
		}
		return s_instance;
	}
	
	public void init(Cocos2dxActivity activity, String cb_id, String cb_sign){
		m_activity = activity;
		Chartboost.startWithAppId(m_activity, cb_id, cb_sign);
		Chartboost.setLoggingLevel(Level.ALL);
		Chartboost.setDelegate(cbDelegate);
		Chartboost.onCreate(m_activity);
	}
	
	public static boolean showCBAds(){
		if ( Chartboost.hasInterstitial(cbLocation)) {
			Chartboost.showInterstitial(cbLocation);
			return true;
		}else{
			Chartboost.cacheInterstitial(cbLocation);
			return false;
		}
	}
	public static void showCBMoreApp(){
		Chartboost.showMoreApps(cbLocation);
	}
}
