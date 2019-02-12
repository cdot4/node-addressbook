#include "Group.h"
#include "AddressBook.h"

#ifdef __APPLE__
std::string Group::CFString2String(CFStringRef str)
{
        std::string rv;
        CFIndex length = CFStringGetLength(str);
        CFIndex maxSize = CFStringGetMaximumSizeForEncoding(length, kCFStringEncodingUTF8) + 1;
        char *buffer = (char *)malloc(maxSize);
        if (CFStringGetCString(str, buffer, maxSize, kCFStringEncodingUTF8)) {
            rv = buffer;
		    free(buffer);
        }   

        return rv; 
}

std::string Group::getStringProperty(ABGroupRef group, CFStringRef propertyName)
{
	CFStringRef propertyVal = (CFStringRef)ABRecordCopyValue(group, propertyName);
	std::string rv;

	if (propertyVal && CFGetTypeID(propertyVal) == CFStringGetTypeID()) {
		rv = CFString2String(propertyVal);
		CFRelease(propertyVal);
	}   

	return rv;
}

void Group::fillPropertyVector(ABGroupRef group, CFStringRef propertyName, stringvector& vec)
{
    ABMultiValueRef propertyArray = (ABMultiValueRef)ABRecordCopyValue(group, propertyName);

    if (propertyArray) {
        CFIndex count = ABMultiValueCount(propertyArray);
        for(CFIndex p = 0; p < count; p++) {
            CFStringRef propertyVal = (CFStringRef)ABMultiValueCopyValueAtIndex(propertyArray, p);
            vec.push_back(CFString2String(propertyVal));
            CFRelease(propertyVal);
        }   
    }
}

void Group::fillMembersVector(ABGroupRef group, personvector& pv)
{
    CFArrayRef groupMembers =(CFArrayRef)ABGroupCopyArrayOfAllMembers(group);
    CFIndex count = CFArrayGetCount(groupMembers);

	// Person p = NULL;
    for (int i = 0; i < count; i++) {
        ABPersonRef pRef = (ABPersonRef)CFArrayGetValueAtIndex(groupMembers, i);
        Person* p = new Person(pRef);
        pv.push_back(*p);
        CFRelease(pRef);
        delete p;
    }
}
#endif

Group::Group()
{
}

#ifdef __APPLE__
Group::Group(ABGroupRef g)
{
    m_group = getStringProperty(g, kABGroupNameProperty);
    m_uuid = getStringProperty(g, kABUIDProperty);
    fillMembersVector(g, m_members);
}
#endif

const personvector& Group::members() const
{
	return m_members;
}
