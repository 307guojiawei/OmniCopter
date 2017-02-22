package com.OmniCopterGCS.GUI;

import java.util.ArrayList;

import javax.swing.DefaultComboBoxModel;

public class SerialPortsModel
{
	private DefaultComboBoxModel<String> defaultModel;
	public SerialPortsModel()
	{
		defaultModel=new DefaultComboBoxModel<String>(new String[]{"空"});// TODO 自动生成的构造函数存根
	}
	public void refresh(ArrayList<String> commPorts)
	{
		defaultModel.removeAllElements();
		for(String buf:commPorts)
		{
			defaultModel.addElement(buf);
		}		
	}
	public DefaultComboBoxModel<String> getModel()
	{
		return this.defaultModel;
	}
}
