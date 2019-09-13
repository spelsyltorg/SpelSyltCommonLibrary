#pragma once
#include <string>

namespace tinyxml2 {
	class XMLElement;
}

namespace XMLUtilities
{
	void QueryAttribute(const tinyxml2::XMLElement& aElement, const std::string& aAttributeName, std::string& outValue);
	void QueryAttribute(const tinyxml2::XMLElement& aElement, const std::string& aAttributeName, float& outValue);
	void QueryAttribute(const tinyxml2::XMLElement& aElement, const std::string& aAttributeName, int& outValue);
	void QueryAttribute(const tinyxml2::XMLElement& aElement, const std::string& aAttributeName, bool& outValue);
}