#include <iostream>
#include "libraries/rapidjson/include/rapidjson/document.h"
#include "libraries/rapidjson/include/rapidjson/writer.h"
#include "libraries/rapidjson/include/rapidjson/stringbuffer.h"
#include "libraries/rapidjson/include/rapidjson/pointer.h"

using namespace std;
using namespace rapidjson;

bool checkFull(int arr[8][8]){
	for(int i = 0; i < 8; i++)
	{
		for(int j = 0; j < 8; j++){
			if(arr[i][j] == 0) return true;
		}
	}
	return false;
}

bool CheckSquare(Document& d){
	return true;
}

void recursion(Document& d, char* lastMove, int index){
	int polje[8][8] = {{0,0,0,0,0,0,0,0}, {0,0,0,0,0,0,0,0}, {0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0}};
	Document::AllocatorType& allocator = d.GetAllocator();
	
	Value obj(kObjectType);
	Value val(kObjectType);
	obj.AddMember("id", 1, allocator);

	val.SetBool(true);
	obj.AddMember("checked", val, allocator);

	Value temp (kArrayType);
	temp.PushBack(obj, allocator);
	Pointer("moves").Set(d, temp);
	Value& s = d["moves"];
	s.SetInt(s.GetInt() + 1);
	
	/* else{
		Value temp (kArrayType);
		temp.PushBack(obj, allocator);
		d.AddMember("moves", temp, allocator);
	} */
		
	StringBuffer buffer;
	Writer<StringBuffer> writer(buffer);
	d.Accept(writer);
	cout << buffer.GetString() << endl;
	index++;
	if(checkFull(polje) && index < 10){
		recursion(d, ,index);
	}
}

int main() {
	int index = 0;
	const char* json = "{\"moves\":[\"{1.2\":[]},{\"2.1\":[]}], \"checked\": true}"; 
	Document doc;
	doc.Parse(json);
	recursion(doc, index);
	
	
	return 0;
}

	/* const char* json = "{\"project\":\"rapidjson\",\"stars\":10}"; 
	Document d;
	d.Parse(json);
																				// 2. Modify it by DOM.
	Value& s = d["stars"];
	s.SetInt(s.GetInt() + 1);
																				// 3. Stringify the DOM
	StringBuffer buffer;
	Writer<StringBuffer> writer(buffer);
	d.Accept(writer);
																				// Output {"project":"rapidjson","stars":11}
	cout << buffer.GetString() << endl; */