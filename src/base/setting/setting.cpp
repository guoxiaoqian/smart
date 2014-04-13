#include "setting.h"
#include "base/3dparty/tinyxml2/include/tinyxml2.h"
using namespace tinyxml2;
#include "base/logger/logger.h"
#include <fstream>
#include <iostream>


namespace base {

SSetting::SSetting()
{
}

SSetting::SSetting(const char *fname, SettingType type)
{
    init(fname,type);
}

SSetting::~SSetting()
{
    if(changed == true)
        save();
}

void SSetting::init(const char *fname, SettingType type)
{
    fileName = string(fname);
    settingType = type;
    changed = false;
    if(settingType == SETTING_INI)
    {
        readIni();
    }
    else if(settingType == SETTING_XML)
    {
        readXml();
    }
}

bool SSetting::isEmpty()
{
    return maps.empty();
}

void SSetting::save()
{
    if(settingType == SETTING_INI)
    {
        writeIni();
    }
    else if(settingType == SETTING_XML)
    {
        writeXml();
    }
}

void SSetting::readIni()
{
    ifstream in(fileName.c_str());
    if(in)
    {
        string line;
        string group;
        string key;
        string value;
        while (!in.eof())
        {
            getline(in,line);
            if(!line.empty() || line[0] != '#')
            {
                if(line[0] == '[')
                {
                    group = line.substr(1,line.size()-2);
                    map<string,string> subMap;
                    maps[group] = subMap;
                }
                else
                {
                    unsigned int pos = line.find('=');
                    if(pos == string::npos)
                        continue;
                    key = line.substr(0,pos);
                    value = line.substr(pos+1,line.size()-1);
                    maps[group][key] = value;
                }
            }
        }
        in.close();
    }
    else
    {
        SError("open file: %s fail!",fileName.c_str());
    }
}

void SSetting::readXml()
{
    tinyxml2::XMLDocument xml;
    if(xml.LoadFile(fileName.c_str()) == XML_SUCCESS)
    {

        string group;
        string key;
        string value;
        XMLElement* rootE = xml.RootElement();
        for(XMLElement* groupE = rootE->FirstChildElement();groupE!=NULL;groupE = groupE->NextSiblingElement())
        {
            group = string(groupE->Name());
            map<string,string> subMap;
            maps[group] = subMap;
            for(XMLElement* keyE = groupE->FirstChildElement();keyE!=NULL;keyE = keyE->NextSiblingElement())
            {
                key = string(keyE->Name());
                value = string(keyE->GetText());
                maps[group][key] = value;
            }
        }
        xml.Clear();
    }
    else
    {
        SError("open file: %s fail!",fileName.c_str());
    }
}

void SSetting::writeIni()
{
    string group;
    string key;
    string value;
    ofstream out(fileName.c_str());
    if(out)
    {
        for(map<string,map<string,string> >::iterator it = maps.begin();it != maps.end(); ++it )
        {
            group = it->first;
            out<<'['+group+']'<<endl;
            map<string,string> subMap = it->second;
            for(map<string,string>::iterator subIt = subMap.begin();subIt != subMap.end(); ++subIt)
            {
                key = subIt->first;
                value = subIt->second;
                out<<key+'='+value<<endl;
            }
        }
        out.close();
    }
    else
    {
        SError("open file: %s fail!",fileName.c_str());
    }
}

void SSetting::writeXml()
{
    string group;
    string key;
    string value;
    ofstream out(fileName.c_str());
    if(out)
    {
        out<<"<?xml version=\"1.0\"?>"<<endl;
        out<<"<root>"<<endl;
        for(map<string,map<string,string> >::iterator it = maps.begin();it != maps.end(); ++it )
        {
            group = it->first;
            out<<"\t<"+group+">"<<endl;
            map<string,string> subMap = it->second;
            for(map<string,string>::iterator subIt = subMap.begin();subIt != subMap.end(); ++subIt)
            {
                key = subIt->first;
                value = subIt->second;
                out<<"\t\t<"+key+">"+value+"</"+key+">"<<endl;
            }
            out<<"\t</"+group+">"<<endl;
        }
        out<<"</root>"<<endl;
        out.close();
    }
    else
    {
        SError("open file: %s fail!",fileName.c_str());
    }
}



string SSetting::getValue(const char *group, const char *key)
{
    if(maps.find(group) == maps.end() || maps[group].find(key) == maps[group].end())
    {
        SError("key: %s not find!",key);
        return string("");
    }
    else
        return maps[string(group)][string(key)];
}

void SSetting::setValue(const char *group, const char *key,const char *value)
{
    changed = true;
    if(maps.find(group) == maps.end())
    {
        map<string,string> subMap;
        maps[group] = subMap;
    }
    maps[string(group)][string(key)] = string(value);
}

void SSetting::print()
{
    string group;
    string key;
    string value;
    cout<<"---------------config------------------"<<endl;
    for(map<string,map<string,string> >::iterator it = maps.begin();it != maps.end(); ++it )
    {
        group = it->first;
        cout<<'['+group+']'<<endl;
        map<string,string> subMap = it->second;
        for(map<string,string>::iterator subIt = subMap.begin();subIt != subMap.end(); ++subIt)
        {
            key = subIt->first;
            value = subIt->second;
            cout<<"\t"+key+" ==> "+value<<endl;
        }
    }
    cout<<"---------------------------------------"<<endl;

}

}
