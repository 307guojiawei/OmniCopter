package Bean;

import java.util.HashMap;

public class ThreadInfo
{
	private HashMap<String, String> infoList; 
	private static ThreadInfo threadInfo;
	private ThreadInfo()
	{
		// TODO 自动生成的构造函数存根
		infoList=new HashMap<String,String>();
	}
	public static ThreadInfo getInstance()
	{
		if(threadInfo==null)
		{
			threadInfo=new ThreadInfo();
		}
		return threadInfo;
	}
	public String getInfo(String name)
	{		
		return infoList.get(name);
	}
	public void setInfo(String name,String info)
	{
		infoList.put(name, info);
	}
	public void removeInfo(String name)
	{
		infoList.remove(name);
	}
}
