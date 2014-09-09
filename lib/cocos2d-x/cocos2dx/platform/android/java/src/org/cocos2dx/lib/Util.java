package org.cocos2dx.lib;

import java.io.ByteArrayOutputStream;

import android.graphics.Bitmap;
import android.graphics.Bitmap.CompressFormat;

public class Util {
		
		private static final String TAG = "cocos2dx.lib.Util";
		
		public static byte[] bmpToByteArray(final Bitmap bmp, final boolean needRecycle) {
			if (bmp == null) return null;
			ByteArrayOutputStream output = new ByteArrayOutputStream();
			bmp.compress(CompressFormat.PNG, 100, output);
			if (needRecycle) {
				bmp.recycle();
			}
			
			byte[] result = output.toByteArray();
			try {
				output.close();
			} catch (Exception e) {
				e.printStackTrace();
			}
			
			return result;
		}
		
}
