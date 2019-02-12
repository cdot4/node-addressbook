#ifndef GROUP_H
#define GROUP_H

#include <string>
#include <vector>
#include "Person.h"
#ifdef __APPLE__
#include <AddressBook/ABAddressBookC.h>
#endif

typedef std::vector<std::string> stringvector;
typedef std::vector<Person> personvector;

class Group
{
public:
    Group();
#ifdef __APPLE__
    Group(ABGroupRef p);
#endif

    const std::string& uuid() const { return m_uuid; }
    const std::string& group() const { return m_group; }
    const personvector& members() const;

private:
#ifdef __APPLE__
    static std::string CFString2String(CFStringRef str);
    static std::string getStringProperty(ABGroupRef group, CFStringRef propertyName);
    static void fillPropertyVector(ABGroupRef group, CFStringRef propertyName, stringvector& vec);
    static void fillMembersVector(ABGroupRef gr, personvector& pv);
#endif
    std::string m_uuid;
    std::string m_group;
    personvector m_members;
};

#endif // GROUP_H

