{
  "targets": [
    {
      "target_name": "electron-addressbook",
      "sources": [
        "AddressBook.cc",
        "Person.cc",
	"Group.cc",
        "wrapper.cc"
      ],
      "include_dirs": [
        "<!(node -e \"require('nan')\")"
      ],
      "conditions": [
        ['OS=="mac"', {
          "libraries": [
	    '$(SDKROOT)/System/Library/Frameworks/AddressBook.framework'
          ]
        }]
      ]
    }
  ],
}

