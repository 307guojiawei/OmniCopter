package Bean;

import java.util.ArrayList;

public class AttributeList
{
	private ArrayList<Attribute> attributeArrayList;
	private static AttributeList attributeList;
	private AttributeList()
	{
		attributeArrayList=new ArrayList<Attribute>();// TODO 自动生成的构造函数存根
	}
	public static AttributeList getInstance()
	{
		if(attributeList==null)
		{
			attributeList=new AttributeList();
		}
		return attributeList;
	}
	public ArrayList<Attribute> getAttributeList()
	{
		return attributeArrayList;
	}
	public void setAttributeList(ArrayList<Attribute> attributeList)
	{
		this.attributeArrayList = attributeList;
	}
	public Attribute findAttributeById(String id)
	{
		for(Attribute attribute:this.attributeArrayList)
		{
			if(attribute.getId().equals(id))
			{
				return attribute;
			}
		}
		return null;
	}
	public Attribute findAttributeByNo(int num)
	{
		if(num<0)return null;
		return this.attributeArrayList.get(num);
	}
	public void addAttribute(Attribute attribute)
	{
		if(this.findAttributeById(attribute.getId())!=null)
		{
			this.deleteAttributeById(attribute.getId());
		}
		this.attributeArrayList.add(attribute);
	}
	public void clearAll()
	{
		this.attributeArrayList.clear();
	}
	public void deleteAttributeById(String id)
	{
		Attribute attributeToDelete=new Attribute();
		for(Attribute attribute:attributeArrayList)
		{
			if(attribute.getId().equals(id))
			{
				attributeToDelete=attribute;
				break;
			}
		}
		if(attributeToDelete.getId()!=null)
		{
			this.attributeArrayList.remove(attributeToDelete);
		}
	}
}
