package com.OmniCopterGCS.GUI;

import java.io.IOException;
import java.io.InputStream;
import java.util.Scanner;

import Bean.Attribute;
import Bean.AttributeList;
import Bean.ThreadInfo;
import gnu.io.SerialPort;

public class SerialReadingThread extends Thread
{
	private SerialPort serialPort;
	private String buffer="";
	private static boolean isRunning=false;
	public SerialReadingThread(SerialPort serialPort)
	{
		this.serialPort=serialPort;	
	}
	public static boolean isRunning()
	{
		return isRunning;
	}
	public void start()
	{
		if(isRunning)
		{
			return;
		}else
		{
			super.start();
			isRunning=true;
		}
	}
	public void run()
	{
		try
		{
			for(int i=0;i<10000000;i++);
			InputStream is=serialPort.getInputStream();
			
			while(ThreadInfo.getInstance().getInfo("AttributeSetting").equals("t"))
			{					
				if(serialPort==null)break;
				//is=serialPort.getInputStream();
				Scanner input=new Scanner(is);
				while(input.hasNext())
				{
					String buf=input.nextLine();
					System.out.println(buf);
					if(buf.contains(";"))
					{
						buffer+=buf.substring(0, buf.indexOf(";"));
						decode();
						buffer=buf.substring(buf.indexOf(";")+1);
					}else
					{
						buffer+=buf;
					}
				}
				
			}
			isRunning=false;
		} catch (Exception e)
		{
			e.printStackTrace();
		}
	}
	private void decode()
	{
		Attribute attribute=new Attribute();
		//System.out.println(buffer);
		String buf[]=buffer.split(",");
		attribute.setId(buf[0]);
		attribute.setName(buf[1]);
		attribute.setDataType(buf[2]);
		attribute.setValue(buf[3]);
		AttributeList.getInstance().deleteAttributeById(attribute.getId());
		AttributeList.getInstance().addAttribute(attribute);
	}
}
