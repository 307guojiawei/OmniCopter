package com.OmniCopterGCS.GUI;

import gnu.io.SerialPort;
import gnu.io.SerialPortEvent;
import gnu.io.SerialPortEventListener;

import java.awt.EventQueue;

import javax.swing.JFrame;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JMenu;
import javax.swing.JSplitPane;

import java.awt.BorderLayout;

import javax.swing.DefaultComboBoxModel;
import javax.swing.JPanel;
import javax.swing.JLabel;
import javax.swing.JTextField;
import javax.swing.JButton;
import javax.swing.JList;
import javax.swing.AbstractListModel;
import javax.swing.ListSelectionModel;

import Bean.Attribute;
import Bean.AttributeList;
import Bean.ThreadInfo;
import Dao.AttributeSettingDao;

import javax.swing.JSeparator;
import javax.swing.SwingConstants;

import java.awt.FlowLayout;

import javax.swing.JComboBox;

import java.awt.Color;
import java.util.ArrayList;

import javax.swing.border.LineBorder;
import javax.swing.border.CompoundBorder;
import javax.swing.border.SoftBevelBorder;
import javax.swing.border.BevelBorder;
import javax.swing.border.MatteBorder;

import com.OmniCopterGCS.SerialPort.SerialTool;

import java.awt.event.FocusAdapter;
import java.awt.event.FocusEvent;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.awt.event.WindowEvent;
import java.awt.event.WindowListener;

import javax.swing.event.ListSelectionListener;
import javax.swing.event.ListSelectionEvent;
import javax.swing.UIManager;

import java.awt.Window.Type;
import java.awt.Font;

public class AttributeSetting
{

	private JFrame frmAttributeTunning;
	private JTextField attributeName;
	private JTextField attributeValue;
	private SerialPort serialPort;
	private AttributeModel attributeModel;
	private JTextField baudRate;
	private SerialPortsModel serialPortsModel;
	protected ArrayList<String> ports;
	private AttributeSettingDao attributeSettingDao;
	private static boolean isActivate=false;

	/**
	 * Launch the application.
	 */
	public  void excute()
	{
		if(isActivate)return;
		EventQueue.invokeLater(new Runnable()
		{
			public void run()
			{
				try
				{
					AttributeSetting window = new AttributeSetting();
					window.frmAttributeTunning.setVisible(true);
					isActivate=true;
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
	public AttributeSetting()
	{
		initialize();
	}

	/**
	 * Initialize the contents of the frame.
	 */
	private void initialize()
	{
		this.serialPortsModel=new SerialPortsModel();
		frmAttributeTunning = new JFrame();
		frmAttributeTunning.setType(Type.UTILITY);
		frmAttributeTunning.setAlwaysOnTop(true);
		frmAttributeTunning.setTitle("Attribute tunning");
		frmAttributeTunning.setBounds(100, 100, 550, 370);
		frmAttributeTunning.addWindowListener(new WindowListener()
		{
			
			@Override
			public void windowOpened(WindowEvent e)
			{
				ThreadInfo.getInstance().setInfo("AttributeSetting", "t");// TODO 自动生成的方法存根
				
			}
			
			@Override
			public void windowIconified(WindowEvent e)
			{
				// TODO 自动生成的方法存根
				
			}
			
			@Override
			public void windowDeiconified(WindowEvent e)
			{
				// TODO 自动生成的方法存根
				
			}
			
			@Override
			public void windowDeactivated(WindowEvent e)
			{
				// TODO 自动生成的方法存根
				
			}
			
			@Override
			public void windowClosing(WindowEvent e)
			{
				frmAttributeTunning.setVisible(false);
				ThreadInfo.getInstance().setInfo("AttributeSetting", "f");
				if(serialPort!=null)
				{
					serialPort.removeEventListener();
					serialPort.close();
				}
				isActivate=false;
				
			}
			
			@Override
			public void windowClosed(WindowEvent e)
			{
				// TODO 自动生成的方法存根
				
			}
			
			@Override
			public void windowActivated(WindowEvent e)
			{
				// TODO 自动生成的方法存根
				
			}
		});
		
		
		JMenuBar menuBar = new JMenuBar();
		menuBar.setBackground(Color.WHITE);
		frmAttributeTunning.setJMenuBar(menuBar);
		
		JMenu menu = new JMenu("\u6587 \u4EF6");
		menu.setBackground(UIManager.getColor("Button.shadow"));
		menuBar.add(menu);
		
		JMenuItem menuItem = new JMenuItem("\u52A0\u8F7D\u914D\u7F6E\u6587\u4EF6");
		menu.add(menuItem);
		
		JMenuItem menuItem_1 = new JMenuItem("\u4FDD\u5B58\u914D\u7F6E\u6587\u4EF6");
		menu.add(menuItem_1);
		
		JMenu menu_1 = new JMenu("\u7F16 \u8F91");
		menuBar.add(menu_1);
		
		JMenuItem menuItem_2 = new JMenuItem("\u5237\u65B0\u53C2\u6570\u8868");
		menuItem_2.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				attributeModel.refresh();
			}
		});
		menu_1.add(menuItem_2);
		
		JPanel panel = new JPanel();
		panel.setBorder(new CompoundBorder());
		FlowLayout flowLayout = (FlowLayout) panel.getLayout();
		flowLayout.setHgap(0);
		flowLayout.setAlignment(FlowLayout.RIGHT);
		menuBar.add(panel);
		
		JLabel label_2 = new JLabel("\u7AEF\u53E3");
		panel.add(label_2);
		
		final JComboBox serialPortComboBox = new JComboBox();
		serialPortComboBox.addFocusListener(new FocusAdapter() {
			@Override
			public void focusGained(FocusEvent e) {
				ports=SerialTool.findPort();
				serialPortsModel.refresh(ports);
				serialPortComboBox.setModel(serialPortsModel.getModel());
			}
		});
		serialPortComboBox.setModel(this.serialPortsModel.getModel());
		panel.add(serialPortComboBox);
		
		JLabel label_3 = new JLabel("\u6CE2\u7279\u7387");
		panel.add(label_3);
		
		baudRate = new JTextField();
		baudRate.setText("115200");
		panel.add(baudRate);
		baudRate.setColumns(6);
		
		JButton connect = new JButton("\u8FDE\u63A5");
		connect.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				try
				{
					attributeSettingDao=new AttributeSettingDao();
					serialPort=SerialTool.openPort((String)serialPortComboBox.getSelectedItem(), new Integer(baudRate.getText()).intValue());
					//SerialTool.addListener(serialPort,attributeSettingDao.getSerialEventListener());
					
					
				} catch (Exception e1)
				{
					e1.printStackTrace();
				}
			}
		});
			
		
		panel.add(connect);
		
		JButton disconnect = new JButton("\u65AD\u5F00");
		disconnect.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				if(serialPort!=null)
				{
					ThreadInfo.getInstance().setInfo("AttributeSetting", "f");
					serialPort.removeEventListener();
					serialPort.close();
				}
				
			}
		});
		panel.add(disconnect);
		
		JPanel bottomBar = new JPanel();
		frmAttributeTunning.getContentPane().add(bottomBar, BorderLayout.SOUTH);
		
		final JLabel attributeId = new JLabel("id");
		attributeId.setVisible(false);
		bottomBar.add(attributeId);
		
		JLabel label = new JLabel("\u540D\u79F0");
		bottomBar.add(label);
		
		attributeName = new JTextField();
		attributeName.setEnabled(false);
		attributeName.setEditable(false);
		bottomBar.add(attributeName);
		attributeName.setColumns(10);
		
		JLabel label_1 = new JLabel("\u5C5E\u6027\u503C");
		bottomBar.add(label_1);
		
		attributeValue = new JTextField();
		bottomBar.add(attributeValue);
		attributeValue.setColumns(5);
		
		JButton writeAttribute = new JButton("\u5199\u5165");
		writeAttribute.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				Attribute attribute=new Attribute();
				attribute.setId(attributeId.getText());
				attribute.setName(attributeName.getText());
				attribute.setValue(attributeValue.getText());
				attributeSettingDao.setAttributeToUav(attribute);
				/*
				attributeSettingDao.getAttributesFromUav(serialPort);
				attributeModel.refresh();*/
			}
		});
		bottomBar.add(writeAttribute);
		
		JButton refresh = new JButton("\u8BFB\u53D6");
		refresh.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				
				attributeSettingDao.getAttributesFromUav(serialPort);
				
				new SerialReadingThread(serialPort).start();
				
				
				//attributeModel.refresh();
			}
		});
		bottomBar.add(refresh);
		
		JButton button = new JButton("\u5237\u65B0");
		button.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				attributeModel.refresh();
			}
		});
		bottomBar.add(button);
		
		JSeparator separator = new JSeparator();
		separator.setOrientation(SwingConstants.VERTICAL);
		bottomBar.add(separator);
		
		JPanel dataPanel = new JPanel();
		dataPanel.setBorder(null);
		frmAttributeTunning.getContentPane().add(dataPanel, BorderLayout.CENTER);
		dataPanel.setLayout(new BorderLayout(0, 0));
		
		final JList<String> attributeList = new JList<String>();
		attributeList.setLayoutOrientation(JList.VERTICAL_WRAP);
		attributeList.setFont(new Font("微软雅黑 Light", Font.PLAIN, 16));
		attributeList.addListSelectionListener(new ListSelectionListener() {
			public void valueChanged(ListSelectionEvent e) {
				if(attributeList.getSelectedIndex()<0)return;
				Attribute attribute=AttributeList.getInstance().findAttributeByNo(attributeList.getSelectedIndex());
				attributeName.setText(attribute.getName());
				attributeValue.setText(attribute.getValue());
				attributeId.setText(attribute.getId());
			}
		});
		
		this.attributeModel=new AttributeModel(attributeList);
		attributeList.setModel(new AbstractListModel() {
			String[] values = new String[] {};
			public int getSize() {
				return values.length;
			}
			public Object getElementAt(int index) {
				return values[index];
			}
		});
		attributeList.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
		
		dataPanel.add(attributeList);		
	}

}
class AttributeModel
{
	private DefaultComboBoxModel<String> defaultComboBoxModel;
	private JList<String> attributeListView;
	public AttributeModel(JList<String> attributeListView)
	{
		defaultComboBoxModel=new DefaultComboBoxModel<String>(new String[]{"123456"});
		this.attributeListView=attributeListView;;
	}
	public DefaultComboBoxModel<String> getModel()
	{
		return this.defaultComboBoxModel;
	}
	public void refresh()
	{
		DefaultComboBoxModel<String> buf=new DefaultComboBoxModel<String>();
		for(Attribute attribute:AttributeList.getInstance().getAttributeList())
		{
			buf.addElement(attribute.getName()+":\t\t"+attribute.getValue());
		}
		this.defaultComboBoxModel=buf;
		this.attributeListView.setModel(defaultComboBoxModel);
	}
}


