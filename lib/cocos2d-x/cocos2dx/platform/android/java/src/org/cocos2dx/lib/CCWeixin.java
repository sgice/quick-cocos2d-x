package org.cocos2dx.lib;

import java.io.IOException;
import java.io.InputStream;

import android.content.res.AssetManager;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.util.Log;

import com.tencent.mm.sdk.openapi.*;
import com.tencent.mm.sdk.constants.ConstantsAPI;
import com.tencent.mm.sdk.modelmsg.*;
import com.tencent.mm.sdk.modelbase.*;

public class CCWeixin {
	public static IWXAPI wxapi;
	private static final int FRIENDS=2;
	private static final int TIMELINE=1;
	
	public static void regApp ( String appId ) {
		wxapi.registerApp(appId);		
	}
	public static boolean wxAvail(){
		boolean avail=wxapi.isWXAppSupportAPI();
		return avail;
	}
	public static void TextMsg(String text, int dest){
		WXMediaMessage msg = new WXMediaMessage();
		msg.description = text ;
		msg.title = text ;
		
		WXTextObject textObj = new WXTextObject();
		textObj.text = text;
		msg.mediaObject = textObj;
		
		SendMessageToWX.Req req = new SendMessageToWX.Req();
		if (dest == FRIENDS){
			req.scene = SendMessageToWX.Req.WXSceneSession;
		}else{
			req.scene = SendMessageToWX.Req.WXSceneTimeline;
		}
		req.transaction = String.valueOf(System.currentTimeMillis());
		req.message = msg ;
		
		wxapi.sendReq(req);		
	}
	public static void UrlMsg(String text, String title, String url, String thumb, int dest){
		WXMediaMessage msg = new WXMediaMessage();
		msg.description = text ;
		msg.title = title ;
		msg.thumbData = getThumb(thumb);
		
		WXWebpageObject urlObj = new WXWebpageObject();
		urlObj.webpageUrl = url;
		msg.mediaObject = urlObj;
		
		SendMessageToWX.Req req = new SendMessageToWX.Req();
		if (dest == FRIENDS){
			req.scene = SendMessageToWX.Req.WXSceneSession;
		}else{
			req.scene = SendMessageToWX.Req.WXSceneTimeline;
		}
		req.transaction = String.valueOf(System.currentTimeMillis());
		req.message = msg ;
		
		wxapi.sendReq(req);			
	}
	public static void MusicMsg(String text, String title, String url, String data_url, String thumb, int dest){
		WXMediaMessage msg = new WXMediaMessage();
		msg.description = text ;
		msg.title = title ;
		msg.thumbData = getThumb(thumb);
		
		WXMusicObject musicObj = new WXMusicObject();
		musicObj.musicDataUrl = data_url;
		musicObj.musicUrl = url;
		msg.mediaObject = musicObj;
		
		SendMessageToWX.Req req = new SendMessageToWX.Req();
		if (dest == FRIENDS){
			req.scene = SendMessageToWX.Req.WXSceneSession;
		}else{
			req.scene = SendMessageToWX.Req.WXSceneTimeline;
		}
		req.transaction = String.valueOf(System.currentTimeMillis());
		req.message = msg ;
		
		wxapi.sendReq(req);					
	}
	public static byte[] getThumb(String thumb){
		Bitmap bmp = BitmapFactory.decodeFile(thumb) ;
		if (bmp == null) {
			AssetManager am=Cocos2dxActivity.getContext().getAssets();
			InputStream is;
			try {
				is = am.open(thumb);
			} catch (Exception e1){
				try {
					thumb=thumb.substring(7);
					is = am.open(thumb);
				}catch(Exception e){
					Log.d("Weixin.java", "could not open assets "+thumb + e.toString());
					return null;
				}
			}
			bmp = BitmapFactory.decodeStream(is);
		}
		if (bmp != null) {
			 return Util.bmpToByteArray( bmp, true);
		}
		return null;
	}
	public static void ImageMsg(String text, String title, String imagefile, String thumb, int dest){
		WXMediaMessage msg = new WXMediaMessage();
		msg.description = text ;
		msg.title = title ;
		msg.thumbData = getThumb(thumb);
		
		WXImageObject imageObj = new WXImageObject();
		imageObj.imagePath = imagefile;
		msg.mediaObject = imageObj;
		
		SendMessageToWX.Req req = new SendMessageToWX.Req();
		if (dest == FRIENDS){
			req.scene = SendMessageToWX.Req.WXSceneSession;
		}else{
			req.scene = SendMessageToWX.Req.WXSceneTimeline;
		}
		req.transaction = String.valueOf(System.currentTimeMillis());
		req.message = msg ;
		
		wxapi.sendReq(req);				
	}
	public static void VideoMsg(String text, String title, String videofile, String thumb, int dest){
		WXMediaMessage msg = new WXMediaMessage();
		msg.description = text ;
		msg.title = title ;
		msg.thumbData = getThumb(thumb);
		
		WXVideoObject vObj = new WXVideoObject();
		vObj.videoUrl = videofile;
		msg.mediaObject = vObj;
		
		SendMessageToWX.Req req = new SendMessageToWX.Req();
		if (dest == FRIENDS){
			req.scene = SendMessageToWX.Req.WXSceneSession;
		}else{
			req.scene = SendMessageToWX.Req.WXSceneTimeline;
		}
		req.transaction = String.valueOf(System.currentTimeMillis());
		req.message = msg ;
		
		wxapi.sendReq(req);				
	}
	public static void AppMsg(String text, String title, String custom_info, String thumb, int dest){
		WXMediaMessage msg = new WXMediaMessage();
		msg.description = text ;
		msg.title = title ;
		msg.thumbData = getThumb(thumb);
		
		WXAppExtendObject appObj = new WXAppExtendObject();
		appObj.extInfo = custom_info;
		msg.mediaObject = appObj;
		
		SendMessageToWX.Req req = new SendMessageToWX.Req();
		if (dest == FRIENDS){
			req.scene = SendMessageToWX.Req.WXSceneSession;
		}else{
			req.scene = SendMessageToWX.Req.WXSceneTimeline;
		}
		req.transaction = String.valueOf(System.currentTimeMillis());
		req.message = msg ;
		
		wxapi.sendReq(req);					
	}
	public static void onReq(BaseReq req){
		if (req.getType()==ConstantsAPI.COMMAND_SHOWMESSAGE_FROM_WX){
			ShowMessageFromWX.Req showreq=(ShowMessageFromWX.Req)req;
			WXMediaMessage wxMsg = showreq.message;		
			WXAppExtendObject obj = (WXAppExtendObject) wxMsg.mediaObject;
			onReqJNI(req.getType(), wxMsg.description, wxMsg.title, obj.extInfo);
		}else if (req.getType()==ConstantsAPI.COMMAND_GETMESSAGE_FROM_WX){
			//GetMessageFromWX.Req getreq=(GetMessageFromWX.Req) req;
		}
	}
	public static void onResp(BaseResp resp){
		onRespJNI(resp.getType(), resp.errCode, resp.errStr);
	}
	public static native void onRespJNI(int type, int code, String str);
	public static native void onReqJNI(int type, String desc, String title, String ext);

}
