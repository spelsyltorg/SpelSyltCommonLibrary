#include "XMLUtilities.h"
#include "tinyxml2.h"

void XMLUtilities::QueryAttribute(const tinyxml2::XMLElement & aElement, const std::string & aAttributeName, std::string & outValue)
{
	if (auto attr = aElement.FindAttribute(aAttributeName.c_str()))
	{
		outValue = attr->Value();
	}
}

void XMLUtilities::QueryAttribute(const tinyxml2::XMLElement & aElement, const std::string & aAttributeName, float & outValue)
{
	if (auto attr = aElement.FindAttribute(aAttributeName.c_str()))
	{
		outValue = attr->FloatValue();
	}
}

void XMLUtilities::QueryAttribute(const tinyxml2::XMLElement & aElement, const std::string & aAttributeName, int & outValue)
{
	if (auto attr = aElement.FindAttribute(aAttributeName.c_str()))
	{
		outValue = attr->IntValue();
	}
}

void XMLUtilities::QueryAttribute(const tinyxml2::XMLElement & aElement, const std::string & aAttributeName, bool & outValue)
{
	if (auto attr = aElement.FindAttribute(aAttributeName.c_str()))
	{
		outValue = attr->BoolValue();
	}
}
