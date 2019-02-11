#ifndef GROUP_H
#define GROUP_H

#include <string>
#include <vector>
#ifdef __APPLE__
#include <AddressBook/ABAddressBookC.h>
#endif

typedef std::vector<std::string> stringvector;

class Group
{
public:
    Group();
#ifdef __APPLE__
    Group(ABGroupRef p);
#endif

    const std::string& uuid() const { return m_uuid; }
    const std::string& group() const { return m_group; }

private:
#ifdef __APPLE__
    static std::string CFString2String(CFStringRef str);
    static std::string getStringProperty(ABGroupRef group, CFStringRef propertyName);
    static void fillPropertyVector(ABGroupRef group, CFStringRef propertyName, stringvector& vec);
#endif
    std::string m_uuid;
    std::string m_group;
};

#endif // GROUP_H

