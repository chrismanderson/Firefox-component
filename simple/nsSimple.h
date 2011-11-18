#include "nsISimple.h"


#define NS_SIMPLE_CID \
  {0x3a1f5499, 0x927a, 0x450b, {0xae, 0x59, 0x12, 0xde, 0x80, 0x1a, 0x07, 0x3b}}

// our prog id for this class, here for convenience
#define NS_SIMPLE_PROG_ID "@mozilla.org/simple;1"


//
// class SimpleImpl
//
// Class that saves a list of links/images on a website
//
class SimpleImpl : public nsISimple
{
public:
  // normal ctor and dtor. Factory pattern makes these generally usused
  SimpleImpl();
  virtual ~SimpleImpl();

  // pull in the prototypes for methods of nsISupports
  NS_DECL_ISUPPORTS

  // pull in the prototypes for methods of nsISimple
  NS_DECL_NSISIMPLE

private:

  // whatever you need to impl your class

};

