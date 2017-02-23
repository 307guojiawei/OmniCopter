package Dao;

import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.util.ArrayList;
import java.util.Scanner;
import java.util.TooManyListenersException;

import Bean.Attribute;
import Bean.AttributeList;
import gnu.io.SerialPort;
import gnu.io.SerialPortEvent;
import gnu.io.SerialPortEventListener;

public class AttributeSettingDao
{
	private OutputStream os;
	private InputStream is;
	private SerialPort serialPort;

	private ArrayList<Attribute> attributeListBuffer;
	public AttributeSettingDao(SerialPort serialPort)
	{
		this.serialPort=serialPort;
		this.attributeListBuffer=new ArrayList<Attribute>();
	}
	public AttributeSettingDao()
	{
		// TODO 自动生成的构造函数存根
	}
	public void setSerialPort(SerialPort serialPort)
	{
		this.serialPort=serialPort;
	}
	
	
	public void getAttributesFromUav(SerialPort serialPort)
	{
		this.serialPort=serialPort;
//		try
//		{
//			this.serialPort.addEventListener(serialEvent);
//		} catch (TooManyListenersException e)
//		{
//			// TODO 自动生成的 catch 块
//			e.printStackTrace();
//		}
		this.sendRequestToUav();	
		for(int i=0;i<100000000;i++);
	}
	
	public void setAttributeToUav(Attribute attribute)
	{
		try
		{
			OutputStream os=this.serialPort.getOutputStream();
			os.write(new byte[]{0x51,0x15});
			byte atttributeName=new Integer(attribute.getId()).byteValue();
			os.write(new byte[]{atttributeName});
			int data=(int)((new Double(attribute.getValue()).doubleValue())*1000);
			data=data&0xffff;
			byte data1=(byte) (data>>8);
			byte data2=(byte)(data&0xff);
			os.write(new byte[]{data1,data2});
			os.flush();
			os.close();
		} catch (IOException e)
		{
			// TODO 自动生成的 catch 块
			e.printStackTrace();
		}
		
	}
	private void sendRequestToUav()
	{
		try
		{			
			OutputStream os=this.serialPort.getOutputStream();
			os.write(new byte[]{0x51,0x15,0x51,0x01,0x01});
			os.flush();
			os.close();
		} catch (Exception e)
		{
			e.printStackTrace();
		}
		
	}
		
		
		
	
}

