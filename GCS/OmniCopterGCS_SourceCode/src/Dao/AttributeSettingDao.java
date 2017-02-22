package Dao;

import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.util.ArrayList;
import java.util.Scanner;

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
	private SerialEvent serialEvent;
	private ArrayList<Attribute> attributeListBuffer;
	public AttributeSettingDao(SerialPort serialPort)
	{
		this.serialPort=serialPort;
		this.attributeListBuffer=new ArrayList<Attribute>();
		this.serialEvent=new SerialEvent(attributeListBuffer);
	}
	public AttributeSettingDao()
	{
		// TODO 自动生成的构造函数存根
	}
	public void setSerialPort(SerialPort serialPort)
	{
		this.serialPort=serialPort;
	}
	public SerialEvent getSerialEventListener()
	{
		return this.serialEvent;
	}	
	
	public void getAttributesFromUav()
	{
		this.sendRequestToUav();	
		for(int i=0;i<10000000;i++);
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
	class SerialEvent implements SerialPortEventListener
	{
		private String buffer;
		private ArrayList<Attribute> attributeListBuffer;
		public SerialEvent(ArrayList<Attribute> list)
		{
			this.buffer=new String();
			attributeListBuffer=list;
		}
		@Override
		public void serialEvent(SerialPortEvent arg0)
		{
			try
			{
				InputStream is=serialPort.getInputStream();
				Scanner input=new Scanner(is);
				while(input.hasNext())
				{
					String buf=input.next();
					if(buf.contains(";"))
					{
						buffer+=buf.substring(0, buf.indexOf(";"));
						decode();
						buffer=buf.substring(buf.indexOf(";")+1);
					}
				}
			} catch (IOException e)
			{
				e.printStackTrace();
			}
			
		}
		
		private void decode()
		{
			Attribute attribute=new Attribute();
			String buf[]=buffer.split(",");
			attribute.setId(buf[0]);
			attribute.setName(buf[1]);
			attribute.setDataType(buf[2]);
			attribute.setValue(buf[3]);
			AttributeList.getInstance().addAttribute(attribute);
		}
		
	}
}

