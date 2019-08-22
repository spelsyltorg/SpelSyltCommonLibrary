#pragma once

#ifdef _DEBUG
#define SHOULDPRETTYPRINT = true
#endif // _DEBUG

#include "rapidjson/document.h"
#include <assert.h>

class JsonArray;
class JsonObject;
class JsonValue;
class JsonDocument;

class JsonValue
{
	friend JsonArray;
	friend JsonObject;
	friend JsonDocument;
public:
	JsonValue(rapidjson::Value* aValue, rapidjson::Document* aDocument) :myValue(aValue), myDocument(aDocument) { }
	double GetDouble() { return myValue->GetDouble(); }
	float GetFloat() { return myValue->GetFloat(); }
	int GetInt() { return myValue->GetInt(); }
	long long GetInt64() { return myValue->GetInt64(); }
	bool GetBool() { return myValue->GetBool(); }
	const char* GetString() { return myValue->GetString(); }

	void SetString(const char* aString);
	void SetBool(bool aBool) { myValue->SetBool(aBool); }
	void SetInt(int aInt) { myValue->SetInt(aInt); }
	void SetFloat(float aFloat) { myValue->SetFloat(aFloat); }
	void SetDouble(double aDouble) { myValue->SetDouble(aDouble); }

	// Only for arrays

	// DET SOM ÄR UTKOMMENTERAT ÄR FÖR ATT ASSERT BREAKAR MIN MÖJLIGHET ATT BYGGA I DEBUG. DUNNO WHAY

	int GetSize() { /*assert(myValue->IsArray());*/ return myValue->GetArray().Size(); }
	template<typename T>
	void PushBack(T aValue);
	void PushBackObject(JsonObject& aObject);
	void PushBackArray(JsonArray& aArray);
	void PushBackValue(JsonValue& aJsonValue);
	void PushBackString(const char* aString);
	//Only for objects
	template<typename T>
	void AddMember(const char* aName, T aValue);
	void AddString(const char * aName, const char * aString);

	//Only for objects and arrays
	void AddObject(const char* aName, JsonObject& aObject);
	void AddArray(const char* aName, JsonArray& aArray);
	void AddValue(const char* aName, JsonValue& aJsonValue);
	bool Find(const char* aName) const;

	JsonValue operator[] (const char* aName) { return JsonValue(&(*myValue)[aName], myDocument); };
	JsonValue operator[] (int aIndex) { return JsonValue(&(*myValue)[aIndex], myDocument); }
	JsonValue& operator=(const JsonValue& aRhs);

private:
	rapidjson::Value* myValue;
	rapidjson::Document* myDocument;
};

class JsonArray
{
public:
	friend JsonDocument;
	friend JsonValue;
	friend JsonObject;
	JsonArray() { myArray = rapidjson::Value(rapidjson::kArrayType); }
	JsonValue operator[] (int aIndex) { return JsonValue(&myArray[aIndex], &myDocument); }
	int GetSize() { return myArray.GetArray().Size(); }
	template<typename T>
	void PushBack(T aValue);
	void PushBackObject(JsonObject& aObject);
	void PushBackArray(JsonArray& aArray);
	void PushBackValue(JsonValue& aJsonValue);
	void PushBackString(const char* aString);
private:
	rapidjson::Value myArray;
	rapidjson::Document myDocument;
};

class JsonObject
{
public:
	friend JsonDocument;
	friend JsonValue;
	friend JsonArray;
	JsonObject() { myDocument.SetObject(); }
	JsonValue operator[] (const char* aName) { return JsonValue(&myDocument[aName], &myDocument); }

	template<typename T>
	void AddMember(const char* aName, T aValue);
	void AddString(const char* aName, const char* aString);
	void AddObject(const char* aName, JsonObject& aObject);
	void AddValue(const char* aName, JsonValue& aJsonValue);
	void AddArray(const char* aName, JsonArray& aArray);
	void AddArray(const char* aName);
	bool Find(const char* aName) const;
private:
	rapidjson::Document myDocument;
};

class JsonDocument
{
public:
	friend JsonObject;
	friend JsonArray;
	friend JsonValue;
	JsonDocument();
	JsonDocument(const char* aFileLocation);
	~JsonDocument();

	void LoadFromMemory(char* InStartAdress, unsigned long long InSize);
	void LoadFile(const char* aFileLocation, bool aEncode = false);
	void SaveFile(const char* aFileLocation, bool aPrettify = true, bool aEncode = false);
	JsonValue operator[] (const char* aName) { return JsonValue(&(myDocument[aName]), &myDocument); }
	template<typename T>
	void AddMember(const char* aName, T aValue);
	void AddString(const char* aName, const char* aString);
	void AddObject(const char* aName, JsonObject& aObject);
	void AddValue(const char* aName, JsonValue& aJsonValue);
	void AddArray(const char* aName, JsonArray& aArray);
	void AddArray(const char* aName);
	bool Find(const char* aName) const;

	bool GetParseFailed() const;
private:
	rapidjson::Document myDocument;
};

template<typename T>
inline void JsonDocument::AddMember(const char* aName, T aValue)
{
	rapidjson::Value name(aName, myDocument.GetAllocator());
	myDocument.AddMember(name, aValue, myDocument.GetAllocator());
}


template<typename T>
inline void JsonArray::PushBack(T aValue)
{
	myArray.GetArray().PushBack<T>(aValue, myDocument.GetAllocator());
}


template<typename T>
inline void JsonObject::AddMember(const char * aName, T aValue)
{
	rapidjson::Value name(aName, myDocument.GetAllocator());
	myDocument.AddMember(name, aValue, myDocument.GetAllocator());
}

template<typename T>
inline void JsonValue::PushBack(T aValue)
{
	myValue->GetArray().PushBack<T>(aValue, myDocument->GetAllocator());
}

template<typename T>
inline void JsonValue::AddMember(const char * aName, T aValue)
{
	rapidjson::Value name(aName, myDocument->GetAllocator());
	myValue->AddMember(name, aValue, myDocument->GetAllocator());
}

#pragma warning(pop)
