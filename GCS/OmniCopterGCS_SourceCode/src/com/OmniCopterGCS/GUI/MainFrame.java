package com.OmniCopterGCS.GUI;

import gnu.io.SerialPort;
import gnu.io.SerialPortEvent;
import gnu.io.SerialPortEventListener;

import java.awt.EventQueue;

import javax.swing.DefaultComboBoxModel;
import javax.swing.JFrame;
import javax.swing.JMenuBar;
import javax.swing.JMenu;
import javax.swing.JPanel;

import java.awt.BorderLayout;

import javax.swing.JLabel;
import javax.swing.JComboBox;
import javax.swing.JButton;
import javax.swing.JTextPane;

import serialException.NoSuchPort;
import serialException.NotASerialPort;
import serialException.PortInUse;
import serialException.ReadDataFromSerialPortFailure;
import serialException.SerialPortInputStreamCloseFailure;
import serialException.SerialPortParameterFailure;
import serialException.TooManyListeners;

import com.OmniCopterGCS.SerialPort.SerialTool;

import java.awt.event.FocusAdapter;
import java.awt.event.FocusEvent;
import java.util.ArrayList;
import java.util.Scanner;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.io.BufferedReader;

import javax.swing.JTextField;
import javax.swing.JMenuItem;
import java.awt.Font;

public class MainFrame extends Thread
{

	private JFrame frame;
	private ArrayList<String> ports;
	private SerialPortsModel serialPortsModel;
	private SerialPort serialPort;
	private MainFrame mainFrame;
	private JTextPane uavInfo;
	private readThread read;
	private  int rate=19200;
	private JTextField baudRate;

	/**
	 * Launch the application.
	 */
	public static void main(String[] args)
	{
		EventQueue.invokeLater(new Runnable()
		{
			public void run()
			{
				try
				{
					MainFrame window = new MainFrame();
					window.frame.setVisible(true);
				} catch (Exception e)
				{
					e.printStackTrace();
				}
			}
		});
	}

	/**
	 * Create the application.
	 */
	public MainFrame()
	{
		initialize();
		
	}

	/**
	 * Initialize the contents of the frame.
	 */
	private void initialize()
	{
		ports=new ArrayList<String>();
		read=new readThread(uavInfo,serialPort);
		serialPortsModel=new SerialPortsModel();
		
		frame = new JFrame();
		frame.setBounds(100, 100, 450, 300);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		JMenuBar menuBar = new JMenuBar();
		frame.setJMenuBar(menuBar);
		
		JMenu menu = new JMenu("\u6587\u4EF6");
		menuBar.add(menu);
		
		JMenu menu_1 = new JMenu("\u7F16\u8F91");
		menuBar.add(menu_1);
		
		JMenuItem menuItem = new JMenuItem("\u5237\u65B0");
		menuItem.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				ports=SerialTool.findPort();
				serialPortsModel.refresh(ports);				
			}
		});
		menu_1.add(menuItem);
		
		JPanel panel = new JPanel();
		frame.getContentPane().add(panel, BorderLayout.SOUTH);
		
		JLabel label = new JLabel("\u7AEF\u53E3");
		panel.add(label);
		
		final JComboBox<String> commProts = new JComboBox<String>();
		commProts.setModel(serialPortsModel.getModel());
		commProts.addFocusListener(new FocusAdapter() {
			@Override
			public void focusGained(FocusEvent e) {
				ports=SerialTool.findPort();
				serialPortsModel.refresh(ports);
				commProts.setModel(serialPortsModel.getModel());
			}
		});
		panel.add(commProts);
		
		JButton connect = new JButton("\u8FDE\u63A5");
		connect.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				try
				{
					//System.out.println((String)commProts.getSelectedItem());
					serialPort=SerialTool.openPort((String)commProts.getSelectedItem(), new Integer(baudRate.getText()).intValue());
					//System.out.println("ok");
					//System.out.println(serialPort.getName());
					try
					{
						SerialTool.addListener(serialPort,new SerialPortEventListener()
						{
							
							@Override
							public void serialEvent(SerialPortEvent arg0)
							{
								// TODO 自动生成的方法存根
								try
								{
									
									Scanner input=new Scanner(serialPort.getInputStream());
									String add;
									boolean newLine=false;
									while(input.hasNext())
									{
										add=input.nextLine();
										if(add.contains("#"))
										{
											int index=add.indexOf("#");
											String first=add.substring(0, index);
											String last=add.substring(index+1);
											add=first+"\n"+last;
										}
										uavInfo.setText(uavInfo.getText()+add);
										System.out.print(uavInfo.getText()+add);
										if(add.contains("--$"))
										{
											
											uavInfo.setText(" ");
										}
									}
									
								} catch (Exception e)
								{
									// TODO 自动生成的 catch 块
									e.printStackTrace();
								} 
							}
						});
					} catch (TooManyListeners e1)
					{
						// TODO 自动生成的 catch 块
						e1.printStackTrace();
					}
				} catch (SerialPortParameterFailure e1)
				{
					// TODO 自动生成的 catch 块
					e1.printStackTrace();
				} catch (NotASerialPort e1)
				{
					// TODO 自动生成的 catch 块
					e1.printStackTrace();
				} catch (NoSuchPort e1)
				{
					// TODO 自动生成的 catch 块
					e1.printStackTrace();
				} catch (PortInUse e1)
				{
					// TODO 自动生成的 catch 块
					e1.printStackTrace();
				}
			}
		});
		
		JLabel label_1 = new JLabel("\u6CE2\u7279\u7387");
		panel.add(label_1);
		
		baudRate = new JTextField();
		baudRate.setText("115200");
		panel.add(baudRate);
		baudRate.setColumns(10);
		panel.add(connect);
		uavInfo = new JTextPane();
		uavInfo.setFont(new Font("微软雅黑", Font.PLAIN, 17));
		frame.getContentPane().add(uavInfo, BorderLayout.CENTER);
	}
	

}
class SerialPortsModel
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
class readThread extends Thread
{
	private JTextPane uavInfo;
	private SerialPort serialPort;
	public readThread(JTextPane uavInfo,SerialPort serialPort)
	{
		this.uavInfo=uavInfo;// TODO 自动生成的构造函数存根
		this.serialPort=serialPort;
	}
	@Override
	public void run()
	{
		try
		{
			byte[] buf=SerialTool.readFromPort(serialPort);
			String add=new String(buf);
			uavInfo.setText(uavInfo.getText()+"\n"+add);
			if(add.contains("-"))
			{
				uavInfo.setText(" ");
			}
		} catch (ReadDataFromSerialPortFailure e)
		{
			// TODO 自动生成的 catch 块
			e.printStackTrace();
		} catch (SerialPortInputStreamCloseFailure e)
		{
			// TODO 自动生成的 catch 块
			e.printStackTrace();
		}
	}
}