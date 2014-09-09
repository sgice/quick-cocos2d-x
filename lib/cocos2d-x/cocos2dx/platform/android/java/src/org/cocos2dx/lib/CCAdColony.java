package org.cocos2dx.lib;
import com.jirbo.adcolony.*;

public class CCAdColony implements AdColonyAdListener, AdColonyV4VCListener, AdColonyAdAvailabilityListener{
	private static CCAdColony s_instance=null;
    private AdColonyV4VCAd v4vc_ad;
    
	protected CCAdColony(){
	}
	public static CCAdColony Instance(){
		if (s_instance == null){
			s_instance = new CCAdColony();
		}
		return s_instance;
	}
	public static void showAdcAds(String zoneid){
		Instance().showAds(zoneid);
	}
	public static int AdcRewardsAvailable(String zoneid){
		return Instance().rewardsAvailable(zoneid);
	}
	public static native void onReward(int amount, final String zone);
	public static native void onAdStart(final String zone);
	public static native void onAdFinish(boolean shown, final String zone);
	
	public void showAds(String zoneid){
		v4vc_ad = new AdColonyV4VCAd(zoneid).withListener(this);
		v4vc_ad.show();
	}
	public int rewardsAvailable(String zoneid){
		return 1; //fix me to get available rewards.
	}
	
	public void onAdColonyAdAvailabilityChange(boolean available, String zoneid) {		
	}
	public void onAdColonyV4VCReward(AdColonyV4VCReward reward) {	
		if (reward.success()){
			CCAdColony.onReward(reward.amount(), "no zone id in android");
		}
	}
	public void onAdColonyAdAttemptFinished(AdColonyAd ad) {	
		CCAdColony.onAdFinish(ad.shown(), "no zone id in android");
	}
	public void onAdColonyAdStarted(AdColonyAd ad) {	
		CCAdColony.onAdStart("no zone id in android");
	}
}
