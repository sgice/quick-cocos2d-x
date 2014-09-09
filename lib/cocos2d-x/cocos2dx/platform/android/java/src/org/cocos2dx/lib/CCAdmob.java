package org.cocos2dx.lib;

import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;

import android.annotation.TargetApi;
import android.graphics.Point;
import android.os.Build;
import android.os.Handler;
import android.util.Log;
import android.view.Display;
import android.widget.LinearLayout;

import com.google.android.gms.ads.*;

public class CCAdmob {
	public static final int TOP=0;
	public static final int BOTTOM=1;
	private static CCAdmob s_instance=null;
	private AdView m_adview;
	private InterstitialAd mInterstitialAd;
	private Cocos2dxActivity m_activity;
	private AdRequest.Builder m_adRequestBuilder;
	private Handler m_handler;
	protected CCAdmob(){
	}
	public static CCAdmob Instance(){
		if (s_instance == null){
			s_instance = new CCAdmob();
		}
		return s_instance;
	}
	public void init(Cocos2dxActivity activity, String admob_id, String inter_id, int pos){
		m_activity = activity;
		m_handler = new Handler();
		mInterstitialAd=new InterstitialAd(m_activity);
		mInterstitialAd.setAdUnitId(inter_id);
		m_adRequestBuilder = new AdRequest.Builder();
        m_adRequestBuilder.addTestDevice(AdRequest.DEVICE_ID_EMULATOR);

        mInterstitialAd.setAdListener(new AdListener() {
            @Override
            public void onAdLoaded() {
            }
            @Override
            public void onAdClosed() {
            	mInterstitialAd.loadAd(m_adRequestBuilder.build());
            }
        });
        //mInterstitialAd.loadAd(m_adRequestBuilder.build());     
        
        try{
        	Point p=getDisplaySize(m_activity.getWindowManager().getDefaultDisplay());
        	LinearLayout.LayoutParams adParams;
        	if (pos == TOP){
                adParams = new LinearLayout.LayoutParams(
                	p.x, LinearLayout.LayoutParams.WRAP_CONTENT);       		
        	}else{
        	    adParams = new LinearLayout.LayoutParams(
            		p.x, p.y*2-100); 
        	}
            m_adview = new AdView(m_activity);
            m_adview.setAdSize(AdSize.BANNER);
            m_adview.setAdUnitId( admob_id);
            m_adview.loadAd(m_adRequestBuilder.build());        
            m_activity.addContentView(m_adview, adParams);   
        }catch (Exception e) {
            Log.e("CCAdMob", "ADMOB ERROR: "+e);
        }
	}
	public boolean showInterAd(){

			m_handler.post( new Runnable(){
				public void run(){
					try {					
						if (mInterstitialAd.isLoaded()){
							mInterstitialAd.show();
						}else{
							mInterstitialAd.loadAd(m_adRequestBuilder.build());			
						} 
					}catch (Exception e){
						Log.e("CCAdmob", e.toString());
					}
				}
			});
			return true;
	}
	public static boolean showInter(){
		return Instance().showInterAd();
	}
	public static void showBanner(){
		Instance().m_adview.setVisibility(AdView.VISIBLE);
	}
	public static void hideBanner(){
		Instance().m_adview.setVisibility(AdView.INVISIBLE);
	}
	public static void pause(){
		Instance().m_adview.pause();
	}
	public static void resume(){
		Instance().m_adview.resume();
	}
	public static void destroy(){
		Instance().m_adview.destroy();
	}
	
	private Point getDisplaySize(Display d)
    {
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.HONEYCOMB)
        {
            return getDisplaySizeGE11(d);
        }
        return getDisplaySizeLT11(d);
    }
    @TargetApi(Build.VERSION_CODES.HONEYCOMB_MR2)
    private Point getDisplaySizeGE11(Display d)
    {
        Point p = new Point(0, 0);
        d.getSize(p);
        return p;
    }
    private Point getDisplaySizeLT11(Display d)
    {
        try
        {
            Method getWidth = Display.class.getMethod("getWidth", new Class[] {});
            Method getHeight = Display.class.getMethod("getHeight", new Class[] {});
            return new Point(((Integer) getWidth.invoke(d, (Object[]) null)).intValue(), ((Integer) getHeight.invoke(d, (Object[]) null)).intValue());
        }
        catch (NoSuchMethodException e2) // None of these exceptions should ever occur.
        {
            return new Point(-1, -1);
        }
        catch (IllegalArgumentException e2)
        {
            return new Point(-2, -2);
        }
        catch (IllegalAccessException e2)
        {
            return new Point(-3, -3);
        }
        catch (InvocationTargetException e2)
        {
            return new Point(-4, -4);
        }
    }
}
