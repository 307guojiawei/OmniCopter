package com.OmniCopterGCS.GUI;

import gnu.io.SerialPort;
import gnu.io.SerialPortEvent;
import gnu.io.SerialPortEventListener;

import java.awt.EventQueue;

import javax.jws.Oneway;
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
import java.util.Date;
import java.util.Scanner;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.PrintWriter;

import javax.swing.JTextField;
import javax.swing.JMenuItem;
import javax.swing.JFileChooser;
import javax.swing.filechooser.*;

import java.awt.Font;
import java.awt.GridLayout;

import javax.swing.SwingConstants;

import java.awt.GridBagLayout;
import java.awt.GridBagConstraints;
import java.awt.Insets;

public class MainFrame extends Thread
{

	private JFrame frmOmnicopterGcs;
	private ArrayList<String> ports;
	private SerialPortsModel serialPortsModel;
	private SerialPort serialPort;
	private MainFrame mainFrame;
	private JTextPane uavInfo;
	private  int rate=19200;
	private JTextField baudRate;
	private JTextField outerLoopFreq;
	private JTextField innerLoopFreq;
	private JTextField bodyAngle;
	private JTextField quaternion;
	private JTextField desiredBodyRate;
	private JTextField forceTorque;
	private JTextField escOutput;
	private JPanel uavConfig;
	private JTextField rcInput;
	private boolean decodeMode=false;
	private boolean recordInfo=false;
	private File flightInfo;
	private PrintWriter out;
	private flightRecorder recorder;
	private InputStream is;
	private OutputStream os;
	private boolean onFocus=true;

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
					window.frmOmnicopterGcs.setVisible(true);
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
		serialPortsModel=new SerialPortsModel();
		
		frmOmnicopterGcs = new JFrame();
		frmOmnicopterGcs.addFocusListener(new FocusAdapter() {
			@Override
			public void focusGained(FocusEvent e) {
				onFocus=true;
			}
			@Override
			public void focusLost(FocusEvent e) {
				onFocus=false;
			}
		});
		
		frmOmnicopterGcs.setTitle("OmniCopter GCS");
		frmOmnicopterGcs.setBounds(100, 100, 570, 450);
		frmOmnicopterGcs.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		
		JMenuBar menuBar = new JMenuBar();
		frmOmnicopterGcs.setJMenuBar(menuBar);
		
		JMenu menu = new JMenu("\u6587\u4EF6");
		menuBar.add(menu);
		
		JMenuItem menuItem_2 = new JMenuItem("\u98DE\u884C\u6570\u636E\u4FDD\u5B58");
		menuItem_2.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				JFileChooser jf = new JFileChooser(); 
				FileNameExtensionFilter filter=new FileNameExtensionFilter("飞行数据格式csv", "csv");
				jf.setFileFilter(filter); 
				int option=jf.showDialog(null,null);  
				if(option==JFileChooser.APPROVE_OPTION)
				{
					flightInfo = jf.getSelectedFile();					
				}			
			}
		});
		menu.add(menuItem_2);
		
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
		
		final JMenuItem menuItem_1 = new JMenuItem("\u663E\u793A\u89E3\u6790\u5668");
		menuItem_1.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				decodeMode=!decodeMode;
				uavConfig.setVisible(decodeMode);
				if(decodeMode)
				{
					menuItem_1.setText("隐藏解析器");
				}else
				{
					menuItem_1.setText("显示解析器");
				}
			}
		});
		menu_1.add(menuItem_1);
		
		JPanel panel = new JPanel();
		frmOmnicopterGcs.getContentPane().add(panel, BorderLayout.SOUTH);
		
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
					serialPort=SerialTool.openPort((String)commProts.getSelectedItem(), new Integer(baudRate.getText()).intValue());
					SerialTool.addListener(serialPort,new SerialPortEventListener()
					{
						
						private String receiveBuf="";
						private int gcTime=0;
						@Override
						public void serialEvent(SerialPortEvent arg0)
						{								
							try
							{
								is=serialPort.getInputStream();
								os=serialPort.getOutputStream();
								if(!onFocus)
								{
									return;
								}
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
									if(!decodeMode)
										uavInfo.setText(uavInfo.getText()+add);
									receiveBuf+=add;
									if(add.contains("--$"))
									{										
										uavInfo.setText(" ");
										decodeBuf(receiveBuf);
										gcTime++;
										if(gcTime==2)
										{
											System.gc();
											gcTime=0;
										}
										
									}									
								}			
							}catch(Exception e)
							{
								uavInfo.setText("");
								uavInfo.setText(e.getMessage());
							}
											
						}
						private void decodeBuf(String rbuf)
						{
							
							String[] bufferArray=rbuf.split("\n");
							for(String buf:bufferArray)
							{
								String data;
								if(buf.contains("RC:"))
								{
									data=buf.substring(buf.indexOf(":")+1);
									rcInput.setText(data);
									if(recordInfo)
									{
										recorder.setRC(data);
									}
								}else if(buf.contains("OuterLoop:"))
								{
									data=buf.substring(buf.indexOf(":")+1);
									outerLoopFreq.setText(data);
									if(recordInfo)
									{
										recorder.setOuterLoop(data);
									}
								}else if(buf.contains("InnerLoop:"))
								{
									data=buf.substring(buf.indexOf(":")+1);
									innerLoopFreq.setText(data);
									if(recordInfo)
									{
										recorder.setInnerLoop(data);
									}
								}else if(buf.contains("Angle:"))
								{
									data=buf.substring(buf.indexOf(":")+1);
									bodyAngle.setText(data);
									if(recordInfo)
									{
										recorder.setBodyAngle(data);
									}
								}else if(buf.contains("Quaternion:"))
								{
									data=buf.substring(buf.indexOf(":")+1);
									quaternion.setText(data);
									if(recordInfo)
									{
										recorder.setQuaternion(data);
									}
								}else if(buf.contains("DesireBodyRate:"))
								{
									data=buf.substring(buf.indexOf(":")+1);
									desiredBodyRate.setText(data);
									if(recordInfo)
									{
										recorder.setBodyRate(data);
									}
								}else if(buf.contains("Force&Torque:"))
								{
									data=buf.substring(buf.indexOf(":")+1);
									forceTorque.setText(data);
									if(recordInfo)
									{
										recorder.setForceTorque(data);
									}
								}else if(buf.contains("ESC:") )
								{
									data=buf.substring(buf.indexOf(":")+1);
									escOutput.setText(data);
									if(recordInfo)
									{
										recorder.setEscOutput(data);
									}
								}
							}								
							rbuf="";
							if(recordInfo)
							{
								recorder.recordFrame();
							}
						}
					});
					
				} catch (Exception e1)
				{
					uavInfo.setText("");
					uavInfo.setText(e1.getMessage());
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
		
		final JButton flightRecorderButton = new JButton("\u5F00\u59CB\u5F55\u5236");
		flightRecorderButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				if(recordInfo)//已经开始录制了，用户要停止
				{
					flightRecorderButton.setText("开始录制");	
					if(out!=null)
					{
						out.close();
					}
					
				}else//用户要开始录制了
				{
					flightRecorderButton.setText("停止录制");
					try
					{
						FileWriter outf=new FileWriter(flightInfo);
						out=new PrintWriter(outf);
						recorder=new flightRecorder(out);
						recorder.printTitle();
					} catch (Exception e1)
					{
						uavInfo.setText(e1.getMessage());
						
					}
					
				}					
				recordInfo=!recordInfo;
				
			}
		});
		
		JButton closeSerial = new JButton("\u5173\u95ED");
		closeSerial.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				serialPort.removeEventListener();
				serialPort.close();
			}
		});
		panel.add(closeSerial);
		panel.add(flightRecorderButton);
		uavInfo = new JTextPane();
		uavInfo.setEditable(false);
		uavInfo.setFont(new Font("微软雅黑", Font.PLAIN, 17));
		frmOmnicopterGcs.getContentPane().add(uavInfo, BorderLayout.CENTER);
		
		uavConfig = new JPanel();
		uavConfig.setVisible(false);
		frmOmnicopterGcs.getContentPane().add(uavConfig, BorderLayout.NORTH);
		GridBagLayout gbl_uavConfig = new GridBagLayout();
		gbl_uavConfig.columnWidths = new int[] {100, 420, 5};
		gbl_uavConfig.rowHeights = new int[]{30, 30, 30, 30, 30, 30, 30, 30, 0};
		gbl_uavConfig.columnWeights = new double[]{0.0, 0.0, Double.MIN_VALUE};
		gbl_uavConfig.rowWeights = new double[]{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, Double.MIN_VALUE};
		uavConfig.setLayout(gbl_uavConfig);
		
		JLabel label_2 = new JLabel("\u5916\u73AF\u9891\u7387");
		label_2.setFont(new Font("微软雅黑", Font.PLAIN, 17));
		label_2.setHorizontalAlignment(SwingConstants.TRAILING);
		GridBagConstraints gbc_label_2 = new GridBagConstraints();
		gbc_label_2.fill = GridBagConstraints.BOTH;
		gbc_label_2.insets = new Insets(0, 0, 5, 5);
		gbc_label_2.gridx = 0;
		gbc_label_2.gridy = 0;
		uavConfig.add(label_2, gbc_label_2);
		
		outerLoopFreq = new JTextField();
		outerLoopFreq.setEditable(false);
		outerLoopFreq.setFont(new Font("微软雅黑 Light", Font.PLAIN, 17));
		outerLoopFreq.setHorizontalAlignment(SwingConstants.LEFT);
		GridBagConstraints gbc_outerLoopFreq = new GridBagConstraints();
		gbc_outerLoopFreq.fill = GridBagConstraints.BOTH;
		gbc_outerLoopFreq.insets = new Insets(0, 0, 5, 0);
		gbc_outerLoopFreq.gridx = 1;
		gbc_outerLoopFreq.gridy = 0;
		uavConfig.add(outerLoopFreq, gbc_outerLoopFreq);
		outerLoopFreq.setColumns(20);
		
		JLabel label_3 = new JLabel("\u5185\u73AF\u9891\u7387");
		label_3.setFont(new Font("微软雅黑", Font.PLAIN, 17));
		label_3.setHorizontalAlignment(SwingConstants.TRAILING);
		GridBagConstraints gbc_label_3 = new GridBagConstraints();
		gbc_label_3.fill = GridBagConstraints.BOTH;
		gbc_label_3.insets = new Insets(0, 0, 5, 5);
		gbc_label_3.gridx = 0;
		gbc_label_3.gridy = 1;
		uavConfig.add(label_3, gbc_label_3);
		
		innerLoopFreq = new JTextField();
		innerLoopFreq.setEditable(false);
		innerLoopFreq.setFont(new Font("微软雅黑 Light", Font.PLAIN, 17));
		GridBagConstraints gbc_innerLoopFreq = new GridBagConstraints();
		gbc_innerLoopFreq.fill = GridBagConstraints.BOTH;
		gbc_innerLoopFreq.insets = new Insets(0, 0, 5, 0);
		gbc_innerLoopFreq.gridx = 1;
		gbc_innerLoopFreq.gridy = 1;
		uavConfig.add(innerLoopFreq, gbc_innerLoopFreq);
		innerLoopFreq.setColumns(20);
		
		JLabel label_9 = new JLabel("\u9065\u63A7\u8F93\u5165");
		label_9.setFont(new Font("微软雅黑", Font.PLAIN, 17));
		label_9.setHorizontalAlignment(SwingConstants.TRAILING);
		GridBagConstraints gbc_label_9 = new GridBagConstraints();
		gbc_label_9.fill = GridBagConstraints.BOTH;
		gbc_label_9.insets = new Insets(0, 0, 5, 5);
		gbc_label_9.gridx = 0;
		gbc_label_9.gridy = 2;
		uavConfig.add(label_9, gbc_label_9);
		
		rcInput = new JTextField();
		rcInput.setEditable(false);
		rcInput.setFont(new Font("微软雅黑 Light", Font.PLAIN, 17));
		GridBagConstraints gbc_rcInput = new GridBagConstraints();
		gbc_rcInput.fill = GridBagConstraints.BOTH;
		gbc_rcInput.insets = new Insets(0, 0, 5, 0);
		gbc_rcInput.gridx = 1;
		gbc_rcInput.gridy = 2;
		uavConfig.add(rcInput, gbc_rcInput);
		rcInput.setColumns(20);
		
		JLabel label_4 = new JLabel("\u59FF\u6001\u89D2");
		label_4.setFont(new Font("微软雅黑", Font.PLAIN, 17));
		label_4.setHorizontalAlignment(SwingConstants.TRAILING);
		GridBagConstraints gbc_label_4 = new GridBagConstraints();
		gbc_label_4.fill = GridBagConstraints.BOTH;
		gbc_label_4.insets = new Insets(0, 0, 5, 5);
		gbc_label_4.gridx = 0;
		gbc_label_4.gridy = 3;
		uavConfig.add(label_4, gbc_label_4);
		
		bodyAngle = new JTextField();
		bodyAngle.setEditable(false);
		bodyAngle.setFont(new Font("微软雅黑 Light", Font.PLAIN, 17));
		GridBagConstraints gbc_bodyAngle = new GridBagConstraints();
		gbc_bodyAngle.fill = GridBagConstraints.BOTH;
		gbc_bodyAngle.insets = new Insets(0, 0, 5, 0);
		gbc_bodyAngle.gridx = 1;
		gbc_bodyAngle.gridy = 3;
		uavConfig.add(bodyAngle, gbc_bodyAngle);
		bodyAngle.setColumns(20);
		
		JLabel label_5 = new JLabel("\u56DB\u5143\u6570");
		label_5.setFont(new Font("微软雅黑", Font.PLAIN, 17));
		label_5.setHorizontalAlignment(SwingConstants.TRAILING);
		GridBagConstraints gbc_label_5 = new GridBagConstraints();
		gbc_label_5.fill = GridBagConstraints.BOTH;
		gbc_label_5.insets = new Insets(0, 0, 5, 5);
		gbc_label_5.gridx = 0;
		gbc_label_5.gridy = 4;
		uavConfig.add(label_5, gbc_label_5);
		
		quaternion = new JTextField();
		quaternion.setEditable(false);
		quaternion.setFont(new Font("微软雅黑 Light", Font.PLAIN, 17));
		GridBagConstraints gbc_quaternion = new GridBagConstraints();
		gbc_quaternion.fill = GridBagConstraints.BOTH;
		gbc_quaternion.insets = new Insets(0, 0, 5, 0);
		gbc_quaternion.gridx = 1;
		gbc_quaternion.gridy = 4;
		uavConfig.add(quaternion, gbc_quaternion);
		quaternion.setColumns(20);
		
		JLabel label_6 = new JLabel("\u89D2\u901F\u5EA6\u63A7\u5236");
		label_6.setFont(new Font("微软雅黑", Font.PLAIN, 17));
		label_6.setHorizontalAlignment(SwingConstants.TRAILING);
		GridBagConstraints gbc_label_6 = new GridBagConstraints();
		gbc_label_6.fill = GridBagConstraints.BOTH;
		gbc_label_6.insets = new Insets(0, 0, 5, 5);
		gbc_label_6.gridx = 0;
		gbc_label_6.gridy = 5;
		uavConfig.add(label_6, gbc_label_6);
		
		desiredBodyRate = new JTextField();
		desiredBodyRate.setEditable(false);
		desiredBodyRate.setFont(new Font("微软雅黑 Light", Font.PLAIN, 17));
		GridBagConstraints gbc_desiredBodyRate = new GridBagConstraints();
		gbc_desiredBodyRate.fill = GridBagConstraints.BOTH;
		gbc_desiredBodyRate.insets = new Insets(0, 0, 5, 0);
		gbc_desiredBodyRate.gridx = 1;
		gbc_desiredBodyRate.gridy = 5;
		uavConfig.add(desiredBodyRate, gbc_desiredBodyRate);
		desiredBodyRate.setColumns(20);
		
		JLabel label_7 = new JLabel("\u8F93\u51FA\u529B\u548C\u626D\u77E9");
		label_7.setFont(new Font("微软雅黑", Font.PLAIN, 17));
		label_7.setHorizontalAlignment(SwingConstants.TRAILING);
		GridBagConstraints gbc_label_7 = new GridBagConstraints();
		gbc_label_7.fill = GridBagConstraints.BOTH;
		gbc_label_7.insets = new Insets(0, 0, 5, 5);
		gbc_label_7.gridx = 0;
		gbc_label_7.gridy = 6;
		uavConfig.add(label_7, gbc_label_7);
		
		forceTorque = new JTextField();
		forceTorque.setEditable(false);
		forceTorque.setFont(new Font("微软雅黑 Light", Font.PLAIN, 17));
		GridBagConstraints gbc_forceTorque = new GridBagConstraints();
		gbc_forceTorque.fill = GridBagConstraints.BOTH;
		gbc_forceTorque.insets = new Insets(0, 0, 5, 0);
		gbc_forceTorque.gridx = 1;
		gbc_forceTorque.gridy = 6;
		uavConfig.add(forceTorque, gbc_forceTorque);
		forceTorque.setColumns(20);
		
		JLabel label_8 = new JLabel("\u7535\u8C03\u8F93\u51FA");
		label_8.setFont(new Font("微软雅黑", Font.PLAIN, 17));
		label_8.setHorizontalAlignment(SwingConstants.TRAILING);
		GridBagConstraints gbc_label_8 = new GridBagConstraints();
		gbc_label_8.fill = GridBagConstraints.BOTH;
		gbc_label_8.insets = new Insets(0, 0, 0, 5);
		gbc_label_8.gridx = 0;
		gbc_label_8.gridy = 7;
		uavConfig.add(label_8, gbc_label_8);
		
		escOutput = new JTextField();
		escOutput.setEditable(false);
		escOutput.setFont(new Font("微软雅黑 Light", Font.PLAIN, 17));
		GridBagConstraints gbc_escOutput = new GridBagConstraints();
		gbc_escOutput.fill = GridBagConstraints.BOTH;
		gbc_escOutput.gridx = 1;
		gbc_escOutput.gridy = 7;
		uavConfig.add(escOutput, gbc_escOutput);
		escOutput.setColumns(20);
	}
	

}

class flightRecorder
{
	private PrintWriter out;
	private String outerLoop="";
	private String innerLoop="";
	private String bodyAngle[]=new String[3];
	private String quaternion[]=new String[4];
	private String bodyRate[]=new String[3];
	private String ForceTorque[]=new String[6];
	private String escOutput[]=new String[8];
	private String RC[] =new String[6];
	//private String 
	public flightRecorder()
	{
		// TODO 自动生成的构造函数存根
	}
	public flightRecorder(PrintWriter out)
	{
		this.out=out;// TODO 自动生成的构造函数存根
	}
	public void setOutputStream(PrintWriter out)
	{
		this.out=out;
	}
	public void printTitle()
	{
		out.println("时间,外环频率,内环频率,遥控滚转,遥控俯仰,遥控偏航,遥控x,遥控y,遥控z,姿态x,姿态y,姿态z,q0,q1,q2,q3,"
				+ "外环输出x,外环输出y,外环输出z,力x,力y,力z,力矩x,力矩y,力矩z,--,"
				+ "电机1,电机2,电机3,电机4,电机5,电机6,电机7,电机8");
	}
	public void recordFrame()//记录本帧数据
	{
		Date date=new Date();
		out.print(date.getTime()+",");
		out.print(outerLoop+","+innerLoop+",");
		for(String buf:RC)//输出遥控通道
		{
			out.print(buf+",");
		}
		for(String buf:bodyAngle)
		{
			out.print(buf+",");
		}
		for(String buf:quaternion)
		{
			out.print(buf+",");
		}
		for(String buf:bodyRate)
		{
			out.print(buf+",");
		}		
		for(String buf:ForceTorque)
		{
			out.print(buf+",");
		}
		for(String buf:escOutput)
		{
			out.print(buf+",");
		}
		out.print("endOfFrame\n");
	}
	public void setOuterLoop(String outerLoop)
	{
		this.outerLoop = outerLoop;
	}
	public void setInnerLoop(String innerLoop)
	{
		this.innerLoop = innerLoop;
	}
	public void setBodyAngle(String bodyAngle)
	{
		this.bodyAngle = bodyAngle.split(" ");
	}
	public void setQuaternion(String quaternion)
	{
		this.quaternion = quaternion.split(" ");
	}
	public void setBodyRate(String bodyRate)
	{
		this.bodyRate = bodyRate.split(" ");
	}
	public void setForceTorque(String forceTorque)
	{
		ForceTorque = forceTorque.split(" ");
	}
	public void setEscOutput(String escOutput)
	{
		this.escOutput = escOutput.split(" ");
	}
	public void setRC(String rC)
	{
		RC = rC.split(" ");
	}
	
}