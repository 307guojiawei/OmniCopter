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
import javax.swing.event.ListSelectionListener;
import javax.swing.event.ListSelectionEvent;

public class AttributeSetting
{

	private JFrame frame;
	private JTextField attributeName;
	private JTextField attributeValue;
	private SerialPort serialPort;
	private AttributeModel attributeModel;
	private JTextField baudRate;
	private SerialPortsModel serialPortsModel;
	protected ArrayList<String> ports;
	private AttributeSettingDao attributeSettingDao;

	/**
	 * Launch the application.
	 */
	public static void main(String args[])
	{
		EventQueue.invokeLater(new Runnable()
		{
			public void run()
			{
				try
				{
					AttributeSetting window = new AttributeSetting();
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
		frame = new JFrame();
		frame.setBounds(100, 100, 450, 300);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		JMenuBar menuBar = new JMenuBar();
		menuBar.setBackground(Color.WHITE);
		frame.setJMenuBar(menuBar);
		
		JMenu menu = new JMenu("\u6587\u4EF6");
		menu.setBackground(Color.LIGHT_GRAY);
		menuBar.add(menu);
		
		JMenuItem menuItem = new JMenuItem("\u52A0\u8F7D\u914D\u7F6E\u6587\u4EF6");
		menu.add(menuItem);
		
		JMenuItem menuItem_1 = new JMenuItem("\u4FDD\u5B58\u914D\u7F6E\u6587\u4EF6");
		menu.add(menuItem_1);
		
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
					SerialTool.addListener(serialPort,attributeSettingDao.getSerialEventListener());
					
				} catch (Exception e1)
				{
				}
			}
		});
			
		
		panel.add(connect);
		
		JButton disconnect = new JButton("\u65AD\u5F00");
		disconnect.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				serialPort.removeEventListener();
				serialPort.close();
			}
		});
		panel.add(disconnect);
		
		JPanel bottomBar = new JPanel();
		frame.getContentPane().add(bottomBar, BorderLayout.SOUTH);
		
		final JLabel attributeId = new JLabel("id");
		attributeId.setVisible(false);
		bottomBar.add(attributeId);
		
		JLabel label = new JLabel("\u540D\u79F0");
		bottomBar.add(label);
		
		attributeName = new JTextField();
		attributeName.setEnabled(false);
		attributeName.setEditable(false);
		bottomBar.add(attributeName);
		attributeName.setColumns(6);
		
		JLabel label_1 = new JLabel("\u5C5E\u6027\u503C");
		bottomBar.add(label_1);
		
		attributeValue = new JTextField();
		bottomBar.add(attributeValue);
		attributeValue.setColumns(10);
		
		JButton writeAttribute = new JButton("\u5199\u5165");
		writeAttribute.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				Attribute attribute=new Attribute();
				attribute.setId(attributeId.getText());
				attribute.setName(attributeName.getText());
				attribute.setValue(attributeValue.getText());
				attributeSettingDao.setAttributeToUav(attribute);
				
				attributeSettingDao.getAttributesFromUav();
				attributeModel.refresh();
			}
		});
		bottomBar.add(writeAttribute);
		
		JButton refresh = new JButton("\u5237\u65B0");
		refresh.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				attributeSettingDao.getAttributesFromUav();
				attributeModel.refresh();
			}
		});
		bottomBar.add(refresh);
		
		JSeparator separator = new JSeparator();
		separator.setOrientation(SwingConstants.VERTICAL);
		bottomBar.add(separator);
		
		JPanel dataPanel = new JPanel();
		dataPanel.setBorder(null);
		frame.getContentPane().add(dataPanel, BorderLayout.CENTER);
		dataPanel.setLayout(new BorderLayout(0, 0));
		
		final JList<String> attributeList = new JList<String>();
		attributeList.addListSelectionListener(new ListSelectionListener() {
			public void valueChanged(ListSelectionEvent e) {
				Attribute attribute=AttributeList.getInstance().findAttributeByNo(attributeList.getSelectedIndex());
				attributeName.setText(attribute.getName());
				attributeValue.setText(attribute.getValue());
				attributeId.setText(attribute.getId());
			}
		});
		
		this.attributeModel=new AttributeModel(attributeList);
		attributeList.setModel(attributeModel.getModel());
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


