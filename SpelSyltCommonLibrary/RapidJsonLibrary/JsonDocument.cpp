#include "JsonDocument.h"
#include <fstream>

#include "FileDialog.h"

#include "rapidjson/prettywriter.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"
#include "rapidjson/error/en.h"

#include <iostream>

#pragma warning(push)
#pragma warning(disable:26444)

JsonDocument::JsonDocument()
{
	myDocument.SetObject();
}

JsonDocument::JsonDocument(const char * aFileLocation)
{
	LoadFile(aFileLocation);
}

JsonDocument::~JsonDocument()
{
}

void JsonDocument::LoadFromMemory(char* InStartAdress, unsigned long long InSize)
{
	myDocument.GetAllocator().Clear();
	std::string Data(InStartAdress, InSize);
	myDocument.Parse(Data.c_str());
}

void JsonDocument::LoadFile(const char * aFileLocation, bool aEncode)
{
	myDocument.GetAllocator().Clear();
	myDocument.Parse(CommonUtilities::OpenFile(aFileLocation, aEncode).c_str());
}

void JsonDocument::SaveFile(const char * aFileLocation, bool aPrettify, bool aEncode)
{
	rapidjson::StringBuffer buffer;
	if (aPrettify)
	{
		rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
		myDocument.Accept(writer);
	}
	else
	{
		rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
		myDocument.Accept(writer);
	}

	CommonUtilities::SaveFile(aFileLocation, buffer.GetString(), aEncode);
}

void JsonDocument::AddString(const char * aName, const char * aString)
{
	rapidjson::Value name(aName, myDocument.GetAllocator());
	rapidjson::Value value(aString, myDocument.GetAllocator());
	myDocument.AddMember(name, value.Move(), myDocument.GetAllocator());
}

void JsonDocument::AddObject(const char * aName, JsonObject& aObject)
{
	rapidjson::Value v(aObject.myDocument, myDocument.GetAllocator());
	rapidjson::Value name(aName, myDocument.GetAllocator());
	myDocument.AddMember(name, v, myDocument.GetAllocator());
}

void JsonDocument::AddValue(const char * aName, JsonValue & aJsonValue)
{
	rapidjson::Value v(*aJsonValue.myValue, myDocument.GetAllocator());
	rapidjson::Value name(aName, myDocument.GetAllocator());
	myDocument.AddMember(name, v, myDocument.GetAllocator());
}

void JsonDocument::AddArray(const char * aName, JsonArray& aArray)
{
	rapidjson::Value name(aName, myDocument.GetAllocator());
	myDocument.AddMember(name, aArray.myArray, myDocument.GetAllocator());
}

void JsonDocument::AddArray(const char * aName)
{
	rapidjson::Value name(aName, myDocument.GetAllocator());
	JsonArray arr;
	myDocument.AddMember(name, arr.myArray, myDocument.GetAllocator());
}

bool JsonDocument::Find(const char * aName) const
{
	return myDocument.FindMember(aName) != myDocument.MemberEnd();
}

bool JsonDocument::GetParseFailed() const
{
	bool foundParseError = myDocument.HasParseError();


	return foundParseError;
}

void JsonValue::SetString(const char * aString)
{
	myValue->SetString(aString, myDocument->GetAllocator());
}

void JsonValue::PushBackObject(JsonObject & aObject)
{
	rapidjson::Value v(aObject.myDocument, myDocument->GetAllocator());
	myValue->GetArray().PushBack(v, myDocument->GetAllocator());
}

void JsonValue::PushBackArray(JsonArray & aArray)
{
	rapidjson::Value v(aArray.myDocument, myDocument->GetAllocator());
	myValue->GetArray().PushBack(v, myDocument->GetAllocator());
}

void JsonValue::PushBackValue(JsonValue & aJsonValue)
{
	rapidjson::Value v(*aJsonValue.myValue, myDocument->GetAllocator());
	myValue->GetArray().PushBack(v, myDocument->GetAllocator());
}

void JsonValue::PushBackString(const char * aString)
{
	rapidjson::Value value(aString, myDocument->GetAllocator());
	myValue->GetArray().PushBack(value.Move(), myDocument->GetAllocator());
}

void JsonValue::AddString(const char * aName, const char * aString)
{
	rapidjson::Value name(aName, myDocument->GetAllocator());
	rapidjson::Value value(aString, myDocument->GetAllocator());
	myValue->AddMember(name, value.Move(), myDocument->GetAllocator());
}

void JsonValue::AddObject(const char * aName, JsonObject& aObject)
{
	rapidjson::Value v(aObject.myDocument, myDocument->GetAllocator());
	rapidjson::Value name(aName, myDocument->GetAllocator());
	myDocument->AddMember(name, v, myDocument->GetAllocator());
}

void JsonValue::AddArray(const char * aName, JsonArray & aArray)
{
	assert(myValue->IsArray() || myValue->IsObject());
	rapidjson::Value name(aName, myDocument->GetAllocator());
	myValue->AddMember(name, aArray.myArray, myDocument->GetAllocator());
}

void JsonValue::AddValue(const char* aName, JsonValue & aJsonValue)
{
	rapidjson::Value v(*aJsonValue.myValue, myDocument->GetAllocator());
	rapidjson::Value name(aName, myDocument->GetAllocator());
	myValue->AddMember(name, v, myDocument->GetAllocator());
}

bool JsonValue::Find(const char * aName) const
{
	return myValue->FindMember(aName) != myValue->MemberEnd();
}

JsonValue & JsonValue::operator=(const JsonValue & aRhs)
{
	//*myValue =*aRhs.myValue;
	myValue->CopyFrom(*aRhs.myValue, aRhs.myDocument->GetAllocator());
	return *this;
}

void JsonObject::AddString(const char * aName, const char * aString)
{
	rapidjson::Value name(aName, myDocument.GetAllocator());
	rapidjson::Value value(aString, myDocument.GetAllocator());
	myDocument.AddMember(name, value.Move(), myDocument.GetAllocator());
}

void JsonObject::AddObject(const char * aName, JsonObject& aObject)
{
	rapidjson::Value v(aObject.myDocument, myDocument.GetAllocator());
	rapidjson::Value name(aName, myDocument.GetAllocator());
	myDocument.AddMember(name, v, myDocument.GetAllocator());
}

void JsonObject::AddValue(const char * aName, JsonValue & aJsonValue)
{
	rapidjson::Value v(*aJsonValue.myValue, myDocument.GetAllocator());
	rapidjson::Value name(aName, myDocument.GetAllocator());
	myDocument.AddMember(name, v, myDocument.GetAllocator());
}

void JsonObject::AddArray(const char * aName, JsonArray & aArray)
{
	rapidjson::Value name(aName, myDocument.GetAllocator());
	myDocument.AddMember(name, aArray.myArray, myDocument.GetAllocator());
}

void JsonObject::AddArray(const char * aName)
{
	rapidjson::Value name(aName, myDocument.GetAllocator());
	JsonArray arr;
	myDocument.AddMember(name, arr.myArray, myDocument.GetAllocator());
}

bool JsonObject::Find(const char * aName) const
{
	return myDocument.FindMember(aName) != myDocument.MemberEnd();
}

void JsonArray::PushBackObject(JsonObject& aObject)
{
	rapidjson::Value v(aObject.myDocument, myDocument.GetAllocator());
	myArray.PushBack(v, myDocument.GetAllocator());
}

void JsonArray::PushBackArray(JsonArray & aArray)
{
	rapidjson::Value v;
	v.CopyFrom(aArray.myArray, myDocument.GetAllocator());
	myArray.PushBack(v, myDocument.GetAllocator());
}

void JsonArray::PushBackValue(JsonValue & aJsonValue)
{
	rapidjson::Value v(*aJsonValue.myValue, myDocument.GetAllocator());
	myArray.PushBack(v, myDocument.GetAllocator());
}

void JsonArray::PushBackString(const char * aString)
{
	rapidjson::Value value(aString, myDocument.GetAllocator());
	myArray.PushBack(value.Move(), myDocument.GetAllocator());
}

#pragma warning(pop)