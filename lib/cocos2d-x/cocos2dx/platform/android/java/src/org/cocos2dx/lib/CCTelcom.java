package org.cocos2dx.lib;

import android.app.Activity;
import android.app.PendingIntent;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.os.Bundle;
import android.telephony.SmsManager;
import android.util.Log;


public class CCTelcom {
	public static final String SEND_OK_ACTION="CCtelcom.sendOK";
	private String m_smsaddr;
	private static CCTelcom s_instance=null;
	private Cocos2dxActivity m_activity;
	
	protected CCTelcom(){
		
	}
	public static CCTelcom Instance(){
		if (s_instance == null){
			s_instance = new CCTelcom();
		}
		return s_instance;
	}
	public void init(Cocos2dxActivity activity, String smsaddr){
		m_activity = activity; 
		m_smsaddr = smsaddr;
	}
	public static void paysms(String smstext, String prodid, String orderid){
		Instance().pay(smstext, prodid, orderid);
	}
    public void pay(String smstext, String prodid, String orderid){
    	Intent intent=new Intent(SEND_OK_ACTION);
    	intent.putExtra("prodid", prodid);
    	PendingIntent sentIntent=PendingIntent.getBroadcast(m_activity, 0, intent, 0);
    	SmsManager smsMgr = SmsManager.getDefault();
    	m_activity.registerReceiver(new BroadcastReceiver(){
    		public void onReceive(Context context, Intent intent) {
    			if(intent.getAction().equals(SEND_OK_ACTION)){
    				Bundle extras=intent.getExtras();
    				if (getResultCode()==Activity.RESULT_OK){
    					Log.d("telcom sms pay success---------","支付成功");
    					CCTelcom.onSMSresult(true, extras.getString("prodid"));
    				}else{
    					Log.d("telcom sms pay failed---------","支付失败");
    					CCTelcom.onSMSresult(false, extras.getString("prodid"));
    				}
    			}
    		}}, new IntentFilter(SEND_OK_ACTION));
    	try{
    	smsMgr.sendTextMessage(m_smsaddr, null, smstext, sentIntent, null);
    	//CCTelcom.onSMSresult(true, prodid);
    	}catch(Exception e){
    		
    	}
    }
	public static native void onSMSresult(boolean success, final String goodid);

}

