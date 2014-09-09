package org.cocos2dx.lib;
import android.os.Bundle;
import android.os.Handler;
import android.util.Log;

import com.linktech.linkallpayment.LinkSMSFaildActivity;
import com.linktech.linkallpayment.Payment;
import com.linktech.linkallpayment.PaymentListener;

public class CCUnicom {
	private String m_softcode;
	private String m_company ;
	private String m_gamename ;
	private String m_softkey ;
	private String m_servicephone ;
	private static CCUnicom s_instance=null;
	private Cocos2dxActivity m_activity;
	private Handler m_handler;
	
	protected CCUnicom(){
		
	}
	public static CCUnicom Instance(){
		if (s_instance == null){
			s_instance = new CCUnicom();
		}
		return s_instance;
	}
	public void init(Cocos2dxActivity activity, String scode, String skey, String cpny, String game, String sphone){
		m_activity = activity; 
		m_softcode = scode;
		m_softkey = skey; m_company=cpny; m_gamename=game;m_servicephone=sphone;
		m_handler = new Handler();
	}
	public static void paysms(String goodname, String goodsubid, String costmoney){
		Instance().pay(goodname, goodsubid, costmoney);
	
	}
	public static native void onSMSresult(boolean success, final String goodsubid, final String errstr);
	public void pay(String goodname, final String goodsubid, String costmoney){
		final Bundle goodBundle = new Bundle();
		goodBundle.putCharSequence("softcode", m_softcode);
		goodBundle.putCharSequence("goodname", goodname);
		goodBundle.putCharSequence("goodsubid", goodsubid);// 商品ID
		goodBundle.putCharSequence("company", m_company);
		goodBundle.putCharSequence("costmoney", costmoney);
		//goodBundle.putCharSequence("channelid", channelid);
		goodBundle.putCharSequence("gamename", m_gamename);
		goodBundle.putCharSequence("softkey", m_softkey);
		goodBundle.putCharSequence("orderno", "00000000");
		goodBundle.putCharSequence("servicephone", m_servicephone);
		m_handler.post(new Runnable() { 
			public void run(){
		Payment.pay(m_activity, goodBundle,
			new PaymentListener() {

				@Override
				public void paymentResult(int resultCode,
						String resultStr) {
					if (resultCode == 0) {
						Log.d("unicom sms pay success---------",
								"支付成功");
						onSMSresult(true, goodsubid, resultStr);
					} else {
						Log.d("unicom sms pay fail---------", "支付失败");
						onSMSresult(false, goodsubid, resultStr);
					}

				}
			});
			}
		});
	}
}
